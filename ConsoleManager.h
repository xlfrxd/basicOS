//-
//  ConsoleManager.h
//  basicOS
//
//  Created by Alfred Victoria on 9/6/24.
//

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

// Constants for colors
extern const int RED;
extern const int GREEN;
extern const int YELLOW;
extern const int BLUE;
extern const int RESET;

// Struct to hold information about each screen/process
struct ScreenInfo {
    std::string processName;
    int currentLine;
    int totalLines;
    std::string creationTimestamp;
    std::vector<std::string> commandArr;
    std::string logFileName;
};

// Process structure
struct Process {
    std::string name;
    int totalInstructions;
    int executedInstructions;
    std::string creationTimestamp;
    std::string logFileName;
    int coreId;
    bool finished;
};

// Global variables
extern std::map<std::string, ScreenInfo> screens;
extern std::string currentScreen;
extern std::vector<std::string> MAIN_MENU_CMD;

// Function declarations
void initializeMainMenuCmds();
void SetConsoleColor(int textColor);
std::string getCurrentTimestamp();
void printHeader();
void printInstruc();
bool validateCmd(std::string& cmd, std::vector<std::string>& arr);
void clearScreen();
void displayScreen(const ScreenInfo& screen);
void createScreen(const std::string& screenName);
void displayError(const std::string& cmd);
void displayRecognized(const std::string& cmd);
void resumeScreen(const std::string& screenName);
void execute(const std::vector<std::string>& cmd);

#endif // MAIN_H
