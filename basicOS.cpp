//-
//  main.cpp
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

#define _CRT_SECURE_NO_WARNINGS

#include <iostream> // basic input output   
#include <string> // getline func
#include <stdlib.h> // clear screen
#include <windows.h> // colors 
#include <map> // screen manager
#include <ctime> // time stamp
#include <iomanip> // time format
#include <sstream> // tokenize
#include <vector> // token vector
#include <fstream> // text file r/w
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

#include "ConsoleManager.h"

using namespace std;

// colors
const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

// MAIN_MENU Commands
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

// Global map to store all screens created by the user
map<string, ScreenInfo> screens;
string currentScreen = "Main Menu";  // Track the current screen (default to "Main Menu")
// Helper function for getting system current timestamp
string getCurrentTimestamp() {
    time_t now;
    struct tm* datetime;

    time(&now);
    datetime = localtime(&now);

    char output[50];
    // MM/DD/YYYY, HH:MM:SS AM/PM
    strftime(output, sizeof(output), "%m/%d/%Y, %I:%M:%S %p", datetime);
    return output;
}
// Main menu header
void printHeader() {
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
void printInstruc() {
    SetConsoleColor(RESET);
    cout << "Enter a command: ";
}
// Checks if a command exists in given command list
bool validateCmd(string& cmd, vector<string>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == cmd) {
            return true; // Command exists
        }
    }
    return false; // Command not recognized
}
// Clear a screen (currently used for exit cmd) TODO: update for new implementations/screens
void clearScreen() {
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
// Write to text file
void writeToFile(const string& fileName, const string& content) {
    ofstream logFile;
    // Open file in append mode
    logFile.open(fileName.c_str(), ios::app);

    if (logFile.is_open()) {
        // Get the current timestamp
        string timestamp = getCurrentTimestamp();
        // Write content
        logFile << content;
        // Close the file
        logFile.close();
    }

}
// Print logs
void logPrintCommand(const string& fileName, int coreId) {
    // Convert int to str
    stringstream str_coreId;
    str_coreId << coreId;

    // Log value
    string log = "(" + getCurrentTimestamp() + ") Core:" + str_coreId.str() + ": \"Hello world from " + fileName + "!\"\n";

    // Write to log file
    writeToFile(fileName, log);
}
// Handle creation of new screen
void createScreen(const string& screenName) {
    if (screens.find(screenName) == screens.end()) {
        ScreenInfo newScreen;
        newScreen.processName = screenName;
        newScreen.currentLine = 1;  // Start at instruction 1
        newScreen.totalLines = 100; // Simulated total number of instructions
        newScreen.creationTimestamp = getCurrentTimestamp(); // Store creation time stamp
        newScreen.logFileName = screenName + "_log.txt"; // Default logs text file
        newScreen.commandArr.push_back("exit"); // Default new screen command
        newScreen.commandArr.push_back("print"); // Print logs
        screens[screenName] = newScreen;  // Store the new screen
        currentScreen = screenName;  // Switch to the newly created screen
        displayScreen(screens[screenName]);  // Display the new screen layout

        // Add default log file header
        string content = "Process name: " + screenName + "\n" + "Logs:\n\n";
        writeToFile(newScreen.logFileName, content);
    }
    else {
        cout << "Screen '" << screenName << "' already exists.\n";
    }
}
// Display unknown command
void displayError(const string& cmd) {
    SetConsoleColor(RED);
    cout << "ERROR: \"" << cmd << "\" command not recognized.\n";
    SetConsoleColor(RESET);
}
// Display recognized command
void displayRecognized(const string& cmd) {
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
    }
    else {
        SetConsoleColor(RED);
        cout << "Screen '" << screenName << "' not found.\n"; // Screen not existing
        SetConsoleColor(RESET);
    }
}

// Class to represent a process
class Process {
public:
    string id;
    int burst_time;
    int progress;
    int core_id;
    chrono::system_clock::time_point arrival_time;
    string logFileName;

    Process(const string& pid, int burst)
        : id(pid), burst_time(burst), progress(0), core_id(-1), arrival_time(chrono::system_clock::now()), logFileName(pid + "_log.txt") {
    }

    string getTimeStamp() const {
        time_t now = chrono::system_clock::to_time_t(arrival_time);
        tm time_info;
        localtime_s(&time_info, &now);
        ostringstream oss;
        oss << put_time(&time_info, "%m/%d/%Y %I:%M:%S%p");
        return oss.str();
    }
};

// Class to handle the scheduling
class Scheduler {
    queue<Process> ready_queue;
    vector<Process> running_processes;
    vector<Process> finished_processes;
    mutex queue_mutex;
    condition_variable cv;
    bool scheduler_done;

public:
    Scheduler() : scheduler_done(false) {
    }

    void addProcess(const Process& process) {
        lock_guard<mutex> lock(queue_mutex);
        ready_queue.push(process);
        cv.notify_all();
    }

    Process getNextProcess(int core_id) {
        unique_lock<mutex> lock(queue_mutex);
        cv.wait(lock, [&] { return !ready_queue.empty() || scheduler_done; });

        if (ready_queue.empty()) {
            return Process("", 0); // Return an empty process if no more processes
        }

        Process p = ready_queue.front();
        ready_queue.pop();
        p.core_id = core_id;
        running_processes.push_back(p);
        return p;
    }

    void updateProcessProgress(const Process& process) {
        lock_guard<mutex> lock(queue_mutex);
        auto it = find_if(running_processes.begin(), running_processes.end(),
            [&process](const Process& p) { return p.id == process.id; });
        if (it != running_processes.end()) {
            it->progress = process.progress;
        }
    }

    void markAsFinished(const Process& process) {
        lock_guard<mutex> lock(queue_mutex);
        auto it = find_if(running_processes.begin(), running_processes.end(),
            [&process](const Process& p) { return p.id == process.id; });
        if (it != running_processes.end()) {
            finished_processes.push_back(*it);
            running_processes.erase(it);
        }
        cv.notify_all();
    }

    bool allProcessesFinished() {
        lock_guard<mutex> lock(queue_mutex);
        return ready_queue.empty() && running_processes.empty();
    }

    void displayStatus() {
        lock_guard<mutex> lock(queue_mutex);

        cout << "--------------------------------------" << endl;
        cout << "Running processes:" << endl;
        for (const auto& p : running_processes) {
            cout << p.id << "\t(" << p.getTimeStamp() << ")\tCore: \t" << p.core_id << "\t"
                << p.progress << "/" << p.burst_time << endl;
        }

        cout << "\nFinished processes:" << endl;
        for (const auto& p : finished_processes) {
            cout << p.id << "\t(" << p.getTimeStamp() << ")\tFinished\t" << p.burst_time << "/" << p.burst_time
                << endl;
        }

        cout << "--------------------------------------" << endl;
    }

    bool isSchedulerDone() const {
        return scheduler_done;
    }

    void setSchedulerDone(bool value) {
        scheduler_done = value;
    }
};

// Worker function for each core
void coreWorker(Scheduler& scheduler, int core_id) {
    while (true) {
        Process p = scheduler.getNextProcess(core_id);
        if (p.id.empty()) {
            break; // Exit if no more processes
        }

        while (p.progress < p.burst_time) {
            this_thread::sleep_for(chrono::seconds(1)); // Simulate work
            p.progress++;
            scheduler.updateProcessProgress(p); // Update progress in the scheduler
            logPrintCommand(p.logFileName, core_id);
        }

        scheduler.markAsFinished(p);
    }
}

// Execute Main Menu commandArgs
void execute(Scheduler& scheduler, const vector<string>& cmd) {
    static atomic<bool> exit_flag(false);
    static vector<thread> worker_threads;
    static thread input_thread;

    // Clear
    if (cmd[0] == "clear") {
        clearScreen(); // clear screen
        printHeader(); // display header on clear
    }
    // Screen
    else if (cmd[0] == "screen") {
        if (cmd[1] == "-s") {
            createScreen(cmd[2]); // Pass screen name
        }
        else if (cmd[1] == "-r") {
            resumeScreen(cmd[2]); // Pass screen name
        }
        else if (cmd[1] == "-ls") {
            scheduler.displayStatus();
        }
        else {
            displayError(cmd[1]);
        }
    }
}

int main(int argc, const char* argv[]) {
    initializeMainMenuCmds(); // Initialize main menu commands
    string input = "";
    vector<string> commandArgs; // Vector for commands

    // Initialize scheduler and worker threads
    static Scheduler scheduler;
    static vector<thread> worker_threads;
    for (int i = 0; i < 4; ++i) {
        worker_threads.emplace_back(coreWorker, ref(scheduler), i);
    }

    // Add 10 processes to the scheduler, each with 100 print commands
    for (int i = 1; i <= 10; ++i) {
        scheduler.addProcess({ "Process_" + to_string(i), 100 });
    }

    while (true) {
        commandArgs.clear(); // Clear previous tokens

        if (currentScreen == "Main Menu") printHeader(); // Display OS header

        printInstruc(); // Display instructions

        getline(cin, input); // Get command

        stringstream ss(input); // Get input stream
        string token;
        while (ss >> token) {
            commandArgs.push_back(token); // Store each token in vector
        }

        string command = commandArgs[0]; // Store commandArgs

        if (command == "exit") {
            if (currentScreen == "Main Menu") break; // Exit program if in Main Menu
            currentScreen = "Main Menu"; // Exit from current screen to Main Menu
            clearScreen();
            continue;
        }
        else if (command == "print") {
            displayRecognized(command);
            int CORES = 4;
            for (int i = 0; i < 100; ++i) { // Simulate 100 print commands
                int coreId = i % CORES;
                logPrintCommand(screens.at(currentScreen).logFileName, coreId);
            }
        }

        if (currentScreen == "Main Menu") {
            if (validateCmd(command, MAIN_MENU_CMD)) {
                displayRecognized(command);
                execute(scheduler, commandArgs); // Execute recognized command
            }
            else {
                displayError(command); // Unrecognized command
            }
        }
        else {
            if (validateCmd(command, screens.at(currentScreen).commandArr)) {
                // TODO: Implement screen-specific command execution
            }
            else {
                displayError(command); // Unrecognized command
            }
        }
    }

    // Mark scheduler as done
    scheduler.setSchedulerDone(true);

    // Join worker threads
    for (auto& t : worker_threads) {
        t.join();
    }

    SetConsoleColor(RESET); // Set text color back to default
    return 0; // Exit app
}