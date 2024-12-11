#ifndef DUNGEON_EDITOR_H
#define DUNGEON_EDITOR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <random>
#include <chrono>

class NPC {
protected:
    std::string name;
    int x, y;
    bool alive = true;

public:
    NPC(std::string name, int x, int y) : name(name), x(x), y(y) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    void move(int dx, int dy, int maxX, int maxY) {
        if (!alive) return;
        x = std::clamp(x + dx, 0, maxX);
        y = std::clamp(y + dy, 0, maxY);
    }
};

class Squirrel : public NPC {
public:
    Squirrel(std::string name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "Squirrel"; }
};

class SlaveTrader : public NPC {
public:
    SlaveTrader(std::string name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "SlaveTrader"; }
};

class Knight : public NPC {
public:
    Knight(std::string name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override { return "Knight"; }
};

class BattleVisitor {
public:
    bool fight(NPC& npc1, NPC& npc2) {
        std::string type1 = npc1.getType();
        std::string type2 = npc2.getType();

        if ((type1 == "SlaveTrader" && type2 == "Squirrel") ||
            (type1 == "Squirrel" && type2 == "Squirrel") ||
            (type1 == "Knight" && type2 == "SlaveTrader")) {
            return true;
        }
        return false;
    }

    bool rollDice() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(1, 6);
        return dist(gen) > dist(gen);
    }
};

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << message << std::endl;
    }
    static std::mutex& getOutputMutex() {
        return outputMutex;
    }

private:
    static std::mutex outputMutex;
};

std::mutex ConsoleObserver::outputMutex;

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string name, int x, int y) {
        if (type == "Squirrel") return std::make_shared<Squirrel>(name, x, y);
        if (type == "SlaveTrader") return std::make_shared<SlaveTrader>(name, x, y);
        if (type == "Knight") return std::make_shared<Knight>(name, x, y);
        throw std::invalid_argument("Unknown type of NPC");
    }
};

class DungeonEditor {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::shared_mutex npcMutex;
    std::vector<Observer*> observers;

    void notifyObservers(const std::string& message) {
        for (auto obs : observers) {
            obs->update(message);
        }
    }

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void addNPC(const std::string& type, const std::string& name, int x, int y) {
        if (x < 0 || x > 100 || y < 0 || y > 100) {
            std::cout << "Wrong coordinates!" << std::endl;
            return;
        }
        std::unique_lock lock(npcMutex);
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
        notifyObservers(type + " " + name + " was added to (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }

    void moveNPCs(int maxX, int maxY) {
        std::unique_lock lock(npcMutex);
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->move(rand() % 21 - 10, rand() % 21 - 10, maxX, maxY);
            }
        }
    }

    void processFights(int range) {
        BattleVisitor visitor;
        std::unique_lock lock(npcMutex);
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[i]->isAlive() || !npcs[j]->isAlive()) continue;
                int dx = npcs[i]->getX() - npcs[j]->getX();
                int dy = npcs[i]->getY() - npcs[j]->getY();
                if (sqrt(dx * dx + dy * dy) <= range && visitor.fight(*npcs[i], *npcs[j])) {
                    if (visitor.rollDice()) {
                        notifyObservers(npcs[i]->getName() + " killed " + npcs[j]->getName());
                        npcs[j]->kill();
                    } else {
                        notifyObservers(npcs[j]->getName() + " killed " + npcs[i]->getName());
                        npcs[i]->kill();
                    }
                }
            }
        }
    }

    void printMap() {
        const int gridSize = 10;
        char grid[gridSize][gridSize] = {};
        {
            std::shared_lock lock(npcMutex);
            for (const auto& npc : npcs) {
                if (!npc->isAlive()) continue;
                int x = npc->getX() / 10;
                int y = npc->getY() / 10;
                char symbol = npc->getType()[0];
                grid[y][x] = symbol;
            }
        }

        std::lock_guard<std::mutex> lock(ConsoleObserver::getOutputMutex());
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                std::cout << (grid[i][j] ? grid[i][j] : '.') << ' ';
            }
            std::cout << std::endl;
        }
    }

    void runSimulation(int durationSeconds, int moveIntervalMs, int fightRange) {
        std::thread moveThread([this, moveIntervalMs]() {
            while (true) {
                moveNPCs(100, 100);
                std::this_thread::sleep_for(std::chrono::milliseconds(moveIntervalMs));
            }
        });

        std::thread fightThread([this, fightRange]() {
            while (true) {
                processFights(fightRange);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });

        auto start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() < durationSeconds) {
            printMap();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        moveThread.detach();
        fightThread.detach();
    }

    const std::vector<std::shared_ptr<NPC>>& getNPCs() const {
        return npcs;
    }

    std::shared_mutex& getNPCMutex() {
        return npcMutex;
    }
};

#endif
