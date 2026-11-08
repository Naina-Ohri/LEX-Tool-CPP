# LEX Tool Using C++

## Project Overview
An educational LEX-inspired lexical analyzer mini-project developed using C++17. A custom rule generator reads lexical rules and generates C++ scanner source. A Python standard-library server connects the scanner to a browser-based interface.

## Features
- Keyword and identifier recognition
- Integer and decimal floating-point literals
- String and character literals
- Single-line and multi-line comments
- Arithmetic, relational, logical and assignment operators
- Compound assignment and increment/decrement operators
- Punctuation recognition
- Longest-match token recognition
- Lexical error reporting with line and column information
- Browser-based interface

## Technologies
- C++17
- Python 3 standard library
- HTML, CSS and JavaScript
- PowerShell for Windows automation

## Project Structure
- `src/` - C++ rule generator and scanner
- `tests/` - lexical rules and test scripts
- `web/` - browser interface
- `server.py` - Python backend
- `start.bat` - Windows launcher
- `CMakeLists.txt` - CMake build configuration

## Requirements
- Windows 10 or later for the supplied launcher
- Python 3
- A C++17-compatible compiler
- A modern web browser

## Run the Project
Open PowerShell in the project directory and run:

```powershell
.\start.bat
```

## Run Tests

```powershell
.\tests\run_tests.ps1
```

## Limitations
This is a simplified educational LEX-inspired implementation, not a complete Lex/Flex replacement or a full C/C++ compiler. It recognizes only the patterns defined in its lexical rules. Advanced numeric formats and complete escape-sequence validation are not supported.

## Academic Purpose
Developed as a Compiler Design mini-project to demonstrate lexical analysis, rule-based scanning, token recognition and lexical error handling.
