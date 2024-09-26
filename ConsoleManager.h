#include <iostream>
#include <vector>
#include <map>

using namespace std;

const string MAIN_CONSOLE = "MAIN_CONSOLE";

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
    private:
        vector<Console> consoles;
};
