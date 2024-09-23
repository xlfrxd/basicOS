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

using namespace std;

// colors
const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;


// number of valid commands
int recogCmdSize = 7;
// string array of valid commands
string recognizedCmds[] = {"initialize", "screen", "scheduler-test", "scheduler-stop", "report-util", "clear", "exit"};

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

void printInstruc(){
    SetConsoleColor(RESET);
    cout << "Enter a command: ";
}

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

void execute(string cmd){
    // Clear
    if(cmd=="clear"){
        system("cls"); // clear screen
        printHeader(); // display header on clear
    }
}

int main(int argc, const char * argv[]) {
    // Display OS header
    printHeader();
    // Initialize temp var for input
    string input = "";
    while(input!="exit"){
        // Display instructions
        printInstruc();
        // Get command
        getline(cin, input);
        // Check if exit
        if(input=="exit") break;

        // Validate command
        // Recognized command
        if(validateCmd(input)){
            SetConsoleColor(BLUE);
            cout << "\"" << input << "\"";
            SetConsoleColor(GREEN);
            cout << " command recognized. Doing something.\n";
            // Execute recognized command
            execute(input);
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
