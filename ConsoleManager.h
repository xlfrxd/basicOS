#include <iostream>
#include <vector>
#include <map>

using namespace std;

const string MAIN_CONSOLE = "MAIN_CONSOLE";
const vector<Console> CONSOLES;

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
            vector<string> defCmd = {"exit"};
            int defCur = 1;
            int defTot = 100;
            string creationTimeStamp = 
            Console(screenName, )
        }
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
};


