#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"


char* readInput(){
    //create initial buffer
    size_t bufferLength = 0;
    char* buffer = malloc(sizeof(char) * bufferLength);

    ssize_t lastChar = getline(&buffer, &bufferLength, stdin);

    //delete last char which is always the '\n' 
    buffer[lastChar-1] = '\0';
    
    return buffer;
}

char** tokenize(char* buffer){

    char** tokens = malloc(sizeof(buffer)*sizeof(char));
    int tokensIndex = 0;
    char* token;

    while((token = strtok_r(buffer, " ", &buffer))){
        tokens[tokensIndex] = token;
        tokensIndex++;
    }
    
    free(token);

    return tokens;

    free(tokens);
}

int executeInstruction(char** tokens){
    
    pid_t retVal;
    int status;

    retVal = fork();
    if (retVal < 0) {
        // Error forking
        printf("fork() failed\n");
        return 1;
    } else if (retVal == 0) {
        //execute instruction
        execvp(tokens[0], tokens);
    } else {
        // Parent process
        // while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
        // waitpid(retVal, &status, WUNTRACED);
        wait(NULL);
         
    }

    return 0;
}

int main()
{
    char** tokens;
    char* buffer;
    //test
    do
    {
        
    printf("$ ");
    buffer = readInput();
    buffer = unescape(buffer, NULL);
    tokens = tokenize(buffer);
    executeInstruction(tokens);    

    } while (strcmp(tokens[0],"exit") != 0);

    free(tokens);
    free(buffer);

    return 0;
}


