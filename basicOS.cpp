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
#include <sstream>
#include <vector>

using namespace std;

// colors
const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;


// number of valid commands
int CMD_ARR_SIZE = 7;
// string array of valid commands
string CMD_ARR[] = {"initialize", "screen", "scheduler-test", "scheduler-stop", "report-util", "clear", "exit"};

// set color
void SetConsoleColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}


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
// Checks valid commands in recognizedcmds array
bool validateCmd(string input){
    // iterate thru valid commands (7)
    for (int i = 0; i<7; i++) {
        if (recognizedCmds[i]==input) {
            // return true when command recognized
            return true;
        }
    }
    // invalid command
    return false;
}

void clearScreen(){
    system("cls");
}

void execute(string cmd){
    // Clear
    if(cmd=="clear"){
        clearScreen(); // clear screen
        printHeader(); // display header on clear
    }
}

int main(int argc, const char * argv[]) {
    // Display OS header
    printHeader();
    // Initialize temp var for input
    string input = ""; 
    vector<string> commandArgs; // Vector for commands
    while(input!="exit"){
        // Clear previous tokens
        commandArgs.clear();

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
        if(command == "exit") break;

        // Validate command
        if(validateCmd(command)){
            SetConsoleColor(BLUE);
            cout << "\"" << command << "\"";
            // Recognized command
            SetConsoleColor(GREEN);
            cout << " command recognized. Doing something.\n";
            // Execute recognized command
            execute(command);
        }
        // Unrecognized command
        else{
            SetConsoleColor(RED);
            cout << "ERROR: \"" << input << "\" command not recognized.\n";
        }
    }
    SetConsoleColor(RESET);
    // exit app
    return 0;
}
