# Pipex

## Overview
The goal of this project is to create a program that takes in four arguments:

* file1: an input file
* cmd1: a shell command with parameters
* cmd2: another shell command with parameters
* file2: an output file

The program should behave exactly the same as the following shell command:
$> < file1 cmd1 | cmd2 > file2

The pipex project provides extra points for handling multiple pipes, as in < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2. The project also rewards supporting « and » when the first parameter is "here_doc", which should behave like cmd << LIMITER | cmd1 >> file.

## Evaluation
#### First submission
11/01/2023  
0%  

#### Second submission
16/01/2023  
125%
