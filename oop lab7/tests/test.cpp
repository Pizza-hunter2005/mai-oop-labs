#include <gtest/gtest.h>
#include "dungeon_editor.h"

TEST(DungeonEditorTest, AddNPC) {
    DungeonEditor editor;
    ConsoleObserver observer;
    editor.addObserver(&observer);

    testing::internal::CaptureStdout();
    editor.addNPC("Knight", "Arthur", 10, 20);
    std::string output = testing::internal::GetCapturedStdout();

    const auto& npcs = editor.getNPCs();
    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Arthur");
    EXPECT_EQ(npcs[0]->getType(), "Knight");
    EXPECT_EQ(npcs[0]->getX(), 10);
    EXPECT_EQ(npcs[0]->getY(), 20);
    EXPECT_TRUE(npcs[0]->isAlive());


    EXPECT_TRUE(output.find("Arthur was added") != std::string::npos);
}


TEST(DungeonEditorTest, MoveNPCs) {
    DungeonEditor editor;
    editor.addNPC("Squirrel", "Chippy", 50, 50);

    const auto& npcs = editor.getNPCs();
    auto initialX = npcs[0]->getX();
    auto initialY = npcs[0]->getY();

    editor.moveNPCs(100, 100);

    EXPECT_NE(npcs[0]->getX(), initialX);
    EXPECT_NE(npcs[0]->getY(), initialY);
    EXPECT_GE(npcs[0]->getX(), 0);
    EXPECT_LE(npcs[0]->getX(), 100);
    EXPECT_GE(npcs[0]->getY(), 0);
    EXPECT_LE(npcs[0]->getY(), 100);
}


TEST(DungeonEditorTest, PrintMap) {
    DungeonEditor editor;
    editor.addNPC("Knight", "Lancelot", 10, 20);
    editor.addNPC("Squirrel", "Nutty", 50, 50);

    editor.printMap();
    testing::internal::CaptureStdout();
    editor.printMap();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find('K') != std::string::npos);
    EXPECT_TRUE(output.find('S') != std::string::npos);
}

TEST(DungeonEditorTest, DeadNPCDoesNotFight) {
    DungeonEditor editor;
    ConsoleObserver observer;
    editor.addObserver(&observer);

    editor.addNPC("Knight", "DeadKnight", 10, 10);
    editor.addNPC("Squirrel", "AliveSquirrel", 15, 15);

    auto& npcs = editor.getNPCs();
    {
        std::lock_guard<std::shared_mutex> lock(editor.getNPCMutex());
        npcs[0]->kill(); 
    }

    testing::internal::CaptureStdout();
    editor.processFights(10);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("DeadKnight") == std::string::npos); 
}


TEST(DungeonEditorTest, RunSimulation) {
    DungeonEditor editor;
    ConsoleObserver observer;
    editor.addObserver(&observer);

    editor.addNPC("Squirrel", "FastSquirrel", 20, 20);
    editor.addNPC("Knight", "SlowKnight", 80, 80);

    testing::internal::CaptureStdout();
    editor.runSimulation(3, 500, 10);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find('S') != std::string::npos); 
    EXPECT_TRUE(output.find('K') != std::string::npos); 
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
