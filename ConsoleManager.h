#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

const string MAIN_CONSOLE = "MAIN_CONSOLE";
const vector<Console> CONSOLES;
const vector<string> MAIN_CONSOLE_CMDS;

class Console {
    public:
        string consoleName;
        vector<string> commandList;
        string creationTimestamp;
        int currentLine;
        int totalLines;

    Console(string conName, vector<string> cmdArray, string time, int curLine, int totLine){
        consoleName = conName;
        commandList = cmdArray;
        creationTimestamp = time;
        currentLine = curLine;
        totalLines = totLine;
    };
};

class ConsoleManager {
    public:

    ConsoleManager() {
        MAIN_CONSOLE_CMDS.push_back("initialize");
        MAIN_CONSOLE_CMDS.push_back("screen");
        MAIN_CONSOLE_CMDS.push_back("scheduler-test");
        MAIN_CONSOLE_CMDS.push_back("scheduler-stop");
        MAIN_CONSOLE_CMDS.push_back("report-util");
        MAIN_CONSOLE_CMDS.push_back("clear");
        MAIN_CONSOLE_CMDS.push_back("exit");
        
        Console(MAIN_CONSOLE, MAIN_CONSOLE_CMDS, getCurrentTimestamp, 1, 100);
    }
    // Helper function to get current time
    string getCurrentTimestamp(){
        string output;
        time_t now;
        struct tm * datetime;

        time(&now);
        datetime = localtime(&now);

        char output[50];
        // Time format: MM/DD/YYYY, HH:MM:SS AM/PM
        strftime(output, sizeof(output), "%m/%d/%Y, %I:%M:%S %p", datetime);

        return output;
    }
    // Helper function to check if a screen exists
    bool screenExists(const string& screenName) { 
        if(CONSOLES.find(screenName) == CONSOLES.end()) { 
            // Screen does not exist
            return false;
        }
        // Screen exists
        return true;
    }
    // Create a new screen
    void createScreen(const string& screenName) {
        if(!screenExists(screenName)){
            // New screen

            // Default values
            vector<string> defCmd;

            // Default screen commands
            defCmd.push_back("exit");

            int defCur = 1;
            int defTot = 100;

            // Create console
            Console(screenName, defCmd, getCurrentTimestamp, defCur, defTot);
        }
        print("Screen already exists");
    }
    // Draw an existing screen
    void resumeScreen(const string& screenName) {
        
    }
    // Helper function to draw a screen
    void drawScreen(const string& screenName) {

    }
    // Helper function to clear screen
    void clearScreen(){
        system("cls");
    }
    // Helper function to print a string
    void print(const string& text){
        cout << text << endl;
    }
};


