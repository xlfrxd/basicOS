//-
//  main.cpp
//  basicOS
//
//  Created by Alfred Victoria on 9/6/24.
//

#include <iostream> // basic input output   
#include <string> // getline func
#include <stdlib.h> // clear screen
#include <windows.h> // colors 
#include <map> // screen manager
#include <ctime> // time stamp
#include <iomanip> // time format
#include <sstream> // tokenize
#include <vector> // token vector

#include "ConsoleManager.h"

using namespace std;

// colors
const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

// MAIN_MENU Commands
// TODO: Add more if necessary; DO NOT ADD SUBCOMMANDS LIKE screen -r HERE)
vector<string> MAIN_MENU_CMD; // Main Menu command list
// Initialize main menu commands
void initializeMainMenuCmds() {
    MAIN_MENU_CMD.push_back("initialize");
    MAIN_MENU_CMD.push_back("screen");
    MAIN_MENU_CMD.push_back("scheduler-test");
    MAIN_MENU_CMD.push_back("scheduler-stop");
    MAIN_MENU_CMD.push_back("report-util");
    MAIN_MENU_CMD.push_back("clear");
    MAIN_MENU_CMD.push_back("exit");
}
// Helper function for setting text color
void SetConsoleColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}
// Struct to hold information about each screen/process

// Global map to store all screens created by the user
map<string, ScreenInfo> screens;
string currentScreen = "Main Menu";  // Track the current screen (default to "Main Menu")
// Helper function for getting system current timestamp
string getCurrentTimestamp(){
    time_t now;
    struct tm * datetime;
    
    time(&now);
    datetime = localtime(&now);

    char output[50];
    // MM/DD/YYYY, HH:MM:SS AM/PM
    strftime(output, sizeof(output), "%m/%d/%Y, %I:%M:%S %p", datetime);
    cout << output;
    return output;
}
// Main menu header
void printHeader(){
    // ascii header
    SetConsoleColor(RESET);
    cout << "                              #######  #####  \n";
    cout << "#####    ##    ####  #  ####  #     # #     # \n";
    cout << "#    #  #  #  #      # #    # #     # #       \n";
    cout << "#####  #    #  ####  # #      #     #  #####  \n";
    cout << "#    # ######      # # #      #     #       # \n";
    cout << "#    # #    # #    # # #    # #     # #     # \n";
    cout << "#####  #    #  ####  #  ####  #######  #####  \n\n";
    SetConsoleColor(GREEN);
    cout << "Hello, welcome to the basicOS command line! \n";
    SetConsoleColor(YELLOW);
    cout << "Type 'exit' to quit, 'clear' to clear the screen. \n";
    SetConsoleColor(RESET);
}
// Display cmd frontline
void printInstruc(){
    SetConsoleColor(RESET);
    cout << "Enter a command: ";
}
// Checks if a command exists in given command list
bool validateCmd(string& cmd, vector<string>& arr){
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == cmd) {
            return true; // Command exists
        }
    }
    return false; // Command not recognized
}
// Clear a screen (currently used for exit cmd) TODO: update for new implementations/screens
void clearScreen(){
    system("cls");
}
// Display console for screen
void displayScreen(const ScreenInfo& screen) {
    clearScreen();
    cout << "\n========== Screen: ";
    SetConsoleColor(GREEN);
    cout << screen.processName;
    SetConsoleColor(RESET);
    cout << " ==========\n";
    cout << "Process Name: "; 
    SetConsoleColor(GREEN);
    cout << screen.processName; 
    SetConsoleColor(RESET);
    cout << "\n";
    cout << "Current Instruction: "; 
    SetConsoleColor(BLUE);
    cout << screen.currentLine;
    SetConsoleColor(RESET);
    cout << " / ";
    SetConsoleColor(BLUE);
    cout << screen.totalLines;
    SetConsoleColor(RESET);
    cout << "\n";
    cout << "Screen Created: "; 
    SetConsoleColor(BLUE);
    cout << screen.creationTimestamp << "\n";
    SetConsoleColor(YELLOW);
    cout << "Type 'exit' to return to the Main Menu.\n";
    SetConsoleColor(RESET);
    cout << "=========================================\n";
}
// Handle creation of new screen
void createScreen(const string& screenName) {
    if (screens.find(screenName) == screens.end()) {
        ScreenInfo newScreen;
        newScreen.processName = screenName;
        newScreen.currentLine = 1;  // Start at instruction 1
        newScreen.totalLines = 100; // Simulated total number of instructions
        newScreen.creationTimestamp = getCurrentTimestamp(); // Store creation time stamp
        newScreen.commandArr.push_back("exit"); // Default new screen command //TODO: append if necessary
        screens[screenName] = newScreen;  // Store the new screen
        currentScreen = screenName;  // Switch to the newly created screen
        displayScreen(screens[screenName]);  // Display the new screen layout
    } else {
        cout << "Screen '" << screenName << "' already exists.\n";
    }
}
// Display unknown command
void displayError(const string& cmd){
    SetConsoleColor(RED);
    cout << "ERROR: \"" << cmd << "\" command not recognized.\n";
    SetConsoleColor(RESET);
}
// Display recognized command
void displayRecognized(const string& cmd){
    SetConsoleColor(BLUE);
    cout << "\"" << cmd << "\"";
    // Recognized command
    SetConsoleColor(GREEN);
    cout << " command recognized. Doing something.\n";  
    SetConsoleColor(RESET);
}
// Display created screen
void resumeScreen(const string& screenName) {
    if (screens.find(screenName) != screens.end()) {
        currentScreen = screenName;
        displayScreen(screens[screenName]);  // Display the screen layout
    } else {
        cout << "Screen '" << screenName << "' not found.\n"; // Screen not existing
    }
}
// Execute commandArgs
void execute(const vector<string>& cmd){
    // Clear
    if(cmd[0]=="clear"){
        clearScreen(); // clear screen
        printHeader(); // display header on clear
    }
    // Screen
    else if(cmd[0]=="screen"){
        // TODO: Find a way to save the states of these screens
        // screen -s
        if(cmd[1]=="-s"){
            // Create and display new screen
            createScreen(cmd[2]); // Pass screen name
        }
        else if(cmd[1]=="-r"){
            // Resume existing screen
            resumeScreen(cmd[2]); // Pass screen name
        }
        else {
            // Throw error unknown screen subcommand
            displayError(cmd[1]);
        }
    }
}

int main(int argc, const char * argv[]) {
    // TODO: Find a way to save the states of the main menu screen
    // Initialize main menu commands
    initializeMainMenuCmds();
    // Initialize temp var for input
    string input = ""; 
    vector<string> commandArgs; // Vector for commands
    while(true){
        // Clear previous tokens
        commandArgs.clear();

        // Display OS header
        if(currentScreen=="Main Menu") printHeader();

        // Display instructions
        printInstruc();

        // Get command
        getline(cin, input); // Reads entire line

        stringstream ss(input); // Get input stream
        string token;
        while (ss >> token) {
            commandArgs.push_back(token); // Store each token in vector
        }

        // Store commandArgs
        string command = commandArgs[0];
        
        // Check if exit
        if(command == "exit"){
            // Check if current screen is Main Menu
            if(currentScreen=="Main Menu") break; // Exit program
            // Exit from current screen
            currentScreen="Main Menu"; // Set current screen to Main Menu
            clearScreen();
            continue;
        };

        // Validate Commands
        if(currentScreen=="Main Menu"){
            // Validate Main Menu screen's command
            if(validateCmd(command, MAIN_MENU_CMD)){
                displayRecognized(command);
                // Execute recognized command
                // Send command arguments
                execute(commandArgs);
            }
            // Unrecognized command
            else{
                displayError(command);
            }
        }
        else {
            // Validate current screen's command to its command list
            if(validateCmd(command,screens.at(currentScreen).commandArr)){
                //TODO: Make a better solution than brute forcing the screen's command list
            }
            // Unrecognized command
            else {
                displayError(command);
            }
        }
    }
    // Set text color back to default
    SetConsoleColor(RESET);
    // exit app
    return 0;
}
