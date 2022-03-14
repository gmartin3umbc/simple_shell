# CMSC421 - PROJECT 2 
## _Student: Gabriel Martins Figueiredo_

This is a brief explanation of my take and implementation on the simple shell project.
## Implementation and Requirements
## Part 1
- For the first requirement, I decided to use the $ symbol to prompt users to input information.

- For the second requirement, I decided to check for any args passed into my main, and if it showed there were command line argumments, my code prints an error and exits.

- For the third requirement, I tackled the issue creating a buffer using getline so that it resizes my buffer according to the users input.

- For the fourth requirement, I parsed the users input with the utility function unescape and then tokenized it. That way I could simply execute the command using the parsed array of strings, which allowed for me to open direct or relative path files. 

- For the exit command, I created a loop that ends once exit is inputted and frees all memory from the process.

- For the memory leak requirement, I debugged my code and fixed any leaks and errors making the program memory leak free.

## Part 2

- For part 2, I tackled the proc requirements by parsing the input the same way as in part 1. However this time, I concatenated the input and formatted it into a file name so that I could simply open, read and print from it.

- As for making sure there are no errors, the code checks for issues opening the file and prints it to the user.

