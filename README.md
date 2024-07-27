# BASIC Subset to C Transpiler
## Overview
The BASIC Subset to C transpiler is a tool designed to convert programs written in a dialect of BASIC into equivalent C code.

Based on https://austinhenley.com/blog/teenytinycompiler1.html

## Prerequisites
- C++ Compiler: A modern C++ compiler (e.g., GCC, Clang)
- CMake: Version 3.24 or higher
- Python: For running the scripts

## Installation
### 1. Clone the Repository

```bash
git clone https://github.com/inzrv/BASIC2C.git
```

### 2. Navigate to the Project Directory

```bash
cd BASIC2C
```

### 3. Run the Build Script

The build.py script will set up the CMake project and compile the translator:

```bash
python3 build.py
```
This will generate the build files and compile the transpiler. By default, the compiled binary will be placed in the `build` directory.

## BASIC Subset Grammar Overview
The transpiler supports a fictional programming language with the following grammar:
```
program ::= {statement}
statement ::= "PRINT" (expression | string) nl
    | "IF" comparison "THEN" nl {statement} "ENDIF" nl
    | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
    | "LABEL" ident nl
    | "GOTO" ident nl
    | "LET" ident "=" expression nl
    | "INPUT" ident nl
comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression)+
expression ::= term {( "-" | "+" ) term}
term ::= unary {( "/" | "*" ) unary}
unary ::= ["+" | "-"] primary
primary ::= number | ident
nl ::= '\n'+
```

## Usage
### 1. Prepare Your Input File

Write your program in the BASIC subset language and save it with a `.bas` extension.

### 2. Run the Translator

```bash
bst prog.bas
```
Here, `prog.bas` is your source file, and `prog.c` will be the resulting C code file.

### 3. Compile the C Code

Use any standard C compiler to compile the generated C code:

```bash
gcc prog.c
```

### 4*. Format C code

Run the script `format_code.py` if you want to format the generated code in C.
```bash
python3 format_code.py prog.c
```

## Example

### BASIC Subset Code (prog.bas):

```
# Compute average of given values.

PRINT "Input n"
INPUT n

IF n < 0 THEN
    PRINT "n should be greater than or equal to 0"
ENDIF

LET f1 = 0
LET f2 = 1
WHILE n > 0 REPEAT
    LET tmp = f1 + f2
    LET f1 = f2
    LET f2 = tmp
    LET n = n - 1
ENDWHILE
PRINT f1
```

### Generated C Code (prog.c):

```c
#include <stdio.h>
int main(void) {
  float n;
  float f1;
  float f2;
  float tmp;
  printf("Input n\n");
  scanf("%f", &n);
  if (n < 0) {
    printf("n should be greater than or equal to 0\n");
  }
  f1 = 0;
  f2 = 1;
  while (n > 0) {
    tmp = f1 + f2;
    f1 = f2;
    f2 = tmp;
    n = n - 1;
  }
  printf("%.2f\n", (float)(f1));
  return 0;
}
```