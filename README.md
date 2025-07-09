# Pipex


**Pipex** is a project from 42 that simulates the behavior of Unix pipes by connecting multiple processes through command-line arguments. It involves creating a pipeline where the output of one command is passed as input to the next, mimicking shell pipe behavior.

---

## Features

- Execute multiple commands in a pipeline
- Handle file input and output redirection
- Properly manage child processes and pipes
- Error handling for invalid commands or files

---

## Bonus Features

- Support for **here_doc** functionality (here-document)
- Enhanced error messages and edge case handling
- Support for multiple pipes chaining more than two commands

---

## Technologies

- C programming language  
- Unix system calls: `fork`, `pipe`, `execve`, `dup2`, etc.  
- Makefile for compilation 
