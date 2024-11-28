#ifndef DUNGEON_EDITOR_H
#define DUNGEON_EDITOR_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>


class NPC {
protected:
    std::string name;
    int x, y;
public:
    NPC(std::string name, int x, int y) : name(name), x(x), y(y) {}
    void accept(class BattleVisitor& v, NPC& fighter, NPC& target);
    virtual ~NPC() = default;
    virtual std::string getType() const = 0;
    std::string getName() const {return name;}
    int getX() const {return x;}
    int getY() const {return y;}
};

class Squirrel : public NPC {
public:
    Squirrel(std::string name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override {return "Squirrel"; }
};

class SlaveTrader : public NPC {
public:
    SlaveTrader(std::string name, int x, int y) : NPC(name, x, y) {}
    std::string getType() const override {return "SlaveTrader"; }
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

        if( (type1 == "SlaveTrader" && type2 == "Squirrel") || (type1 == "Squirrel" && type2 == "Squirrel") || (type1 == "Knight" && type2 == "SlaveTrader") ) {
            return true;
        }
        return false;
    }
};

void NPC::accept(class BattleVisitor& v, NPC& fighter, NPC& target) {
    if (v.fight(fighter, target)) {
        std::cout << fighter.getName() << " wins " << target.getName() << std::endl;
    }
    else {
        std::cout << fighter.getName() << " can't win " << target.getName() << std::endl;
    }
    return;
}

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileObserver : public Observer {
private:
    std::ofstream log;
public:
    FileObserver(const std::string filename) {
        log.open(filename, std::ios::app);
    }
     ~FileObserver() override {
        if (log.is_open()) log.close();
    }
    void update(const std::string& message) override {
        if (log.is_open()) {
            log << message << std::endl;
        }
    }
};

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
    std::vector<Observer*> observers;
    void notifyObservers(const std::string message) {
        for(auto obs : observers) {
            obs->update(message);
        }
    }
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void addNPC(const std::string& type, const std::string& name, int x, int y) {
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            std::cout << "Wrong coordinates!" << std::endl;
            return;
        }
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
        std::string message = type + " " + name + " was added to (" + std::to_string(x) + ", " + std::to_string(y) + ")";
        notifyObservers(message);
    }

    void printNPCs() {
        for (const auto npc : npcs) {
            std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    void battle(int range) {
        BattleVisitor v;
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = 0; j < npcs.size(); ++j) {
                if (j == i) continue;
                int dx = npcs[i]->getX() - npcs[j]->getX();
                int dy = npcs[i]->getY() - npcs[j]->getY();
                if (sqrt(dx * dx + dy * dy) <= range) {
                    npcs[i]->accept(v,*npcs[i], *npcs[j]);
                }
            }
        }
    }
};

#endif // DUNGEON_EDITOR_H