# BasicOS

## Overview
Provide a brief description of what the program does here.

## Prerequisites

Before running this program, make sure you have the following installed on your system:

- A C++ compiler (e.g., GCC, MinGW, MSVC)
- (Optional) A build tool like `make`
- Basic knowledge of command-line interface (CLI) usage

## Files

- `main.cpp`: The main C++ source file (replace with actual file names if there are more)
- Other necessary source files if your project contains multiple files.

## Instructions to Compile and Run

### 1. Using GCC (on Linux/macOS) or MinGW (on Windows)

#### Linux/macOS

1. **Open a terminal**.
2. Navigate to the folder containing your C++ source files:

    ```bash
    
    cd /path/to/your/project
    
    ```

3. **Compile the program** using the following command:

    ```bash
    
    g++ -o program_name main.cpp
    
    ```

   Replace `program_name` with your desired name for the executable.

4. **Run the program**:

    ```bash
    
    ./program_name
    
    ```

#### Windows (Using MinGW)

1. **Open Command Prompt** or **PowerShell**.
2. Navigate to the folder containing your C++ source files:

    ```cmd
    
    cd C:\path\to\your\project
    
    ```

3. **Compile the program** using the MinGW compiler:

    ```cmd
    
    g++ -o program_name.exe main.cpp
    
    ```

   Replace `program_name.exe` with your desired name for the executable.

4. **Run the program**:

    ```cmd
    
    program_name.exe
    
    ```

### 2. Using Microsoft Visual Studio (MSVC)

1. Open **Visual Studio**.
2. Create a new **Console Application** or open your existing project.
3. Add your `main.cpp` file to the project.
4. Click on **Build** -> **Build Solution**.
5. The `.exe` file will be generated in the `Debug` or `Release` folder.
6. Run the program by clicking **Debug** -> **Start Without Debugging**, or navigate to the `.exe` file in the `Debug/Release` folder and double-click to run it.

### 3. (Optional) Using `make`

If you have a `Makefile` available for the project, follow these steps:

1. Open the terminal or Command Prompt.
2. Navigate to the folder containing the project files and the `Makefile`.
3. Run the `make` command:

    ```bash
    make
    ```

This will automatically compile the program and generate an executable based on the rules defined in the `Makefile`.

### 4. Additional Compiler Flags

You can use additional flags when compiling, depending on your needs:

- `-Wall`: Show all warnings.
- `-std=c++17`: Use a specific C++ standard (C++17 in this case).
- `-O2`: Optimize the code during compilation.

Example with flags:

```bash
g++ -std=c++17 -Wall -O2 -o program_name main.cpp
```

## Author

Alfred Victoria
Izabella Imperial
Marc Marasigan
Nikolai Santiago
