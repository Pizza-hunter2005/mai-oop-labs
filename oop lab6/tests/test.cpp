#include <gtest/gtest.h>
#include "dungeon_editor.h"

TEST(DungeonEditorTest, AddNPC) {
    DungeonEditor editor;
    ConsoleObserver consoleObserver;
    editor.addObserver(&consoleObserver);

    editor.addNPC("Squirrel", "Bulba", 100, 100);
    testing::internal::CaptureStdout();
    editor.printNPCs();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Squirrel Bulba (100, 100)") != std::string::npos);
}

TEST(DungeonEditorTest, AddNPCWrongCoordinates) {
    DungeonEditor editor;
    ConsoleObserver consoleObserver;
    editor.addObserver(&consoleObserver);

    editor.addNPC("Squirrel", "Bulba", 600, 100);
    testing::internal::CaptureStdout();
    editor.printNPCs();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Squirrel Bulba (600, 100)") == std::string::npos);
}

TEST(DungeonEditorTest, PrintNPCs) {
    DungeonEditor editor;
    editor.addNPC("Squirrel", "Squirrel_1", 100, 100);
    editor.addNPC("SlaveTrader", "Trader_1", 105, 105);
    editor.addNPC("Knight", "Knight_1", 1, 1);
    editor.addNPC("Knight", "Knight_2", 99, 99);
    
    testing::internal::CaptureStdout();
    editor.printNPCs();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Squirrel Squirrel_1 (100, 100)") != std::string::npos);
    EXPECT_TRUE(output.find("SlaveTrader Trader_1 (105, 105)") != std::string::npos);
    EXPECT_TRUE(output.find("Knight Knight_1 (1, 1)") != std::string::npos);
    EXPECT_TRUE(output.find("Knight Knight_2 (99, 99)") != std::string::npos);
}

TEST(DungeonEditorTest, Battle) {
    DungeonEditor editor;
    editor.addNPC("Squirrel", "Squirrel_1", 100, 100);
    editor.addNPC("SlaveTrader", "Trader_1", 105, 105);

    testing::internal::CaptureStdout();
    editor.battle(10);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Trader_1 wins Squirrel_1") != std::string::npos);
}

TEST(DungeonEditorTest, BattleMultipleNPCs) {
     DungeonEditor editor;
    editor.addNPC("Squirrel", "Squirrel_1", 100, 100);
    editor.addNPC("SlaveTrader", "Trader_1", 105, 105);
    editor.addNPC("Knight", "Knight_1", 110, 110);
    editor.addNPC("Squirrel", "Squirrel_2", 200, 200);
    editor.addNPC("SlaveTrader", "Trader_2", 150, 150);

    testing::internal::CaptureStdout();
    editor.battle(15);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Trader_1 wins Squirrel_1") != std::string::npos);
    EXPECT_TRUE(output.find("Knight_1 wins Trader_1") != std::string::npos);

    // Проверяем, что NPC вне радиуса не участвуют в битвах
    EXPECT_TRUE(output.find("Squirrel_1 wins Trader_2") == std::string::npos);
    EXPECT_TRUE(output.find("Squirrel_2 wins Knight_1") == std::string::npos);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}