//-
//  ConsoleManager.h
//  basicOS
//
//  CSOPESY S16
//  Group 2
//  
//  Izabella Imperial
//  Marc Daniel Marasigan
//  Nikolai Santiago
//  Alfred Victoria
//

#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <windows.h>

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
bool validateCmd(const std::string& cmd, const std::vector<std::string>& arr);
void clearScreen();
void displayScreen(const ScreenInfo& screen);
void createScreen(const std::string& screenName);
void displayError(const std::string& cmd);
void displayRecognized(const std::string& cmd);
void resumeScreen(const std::string& screenName);
void execute(const std::vector<std::string>& cmd);
void writeToFile(const std::string& fileName, const std::string& content);
void logPrintCommand(const std::string& fileName, int coreId);

#endif // CONSOLEMANAGER_H