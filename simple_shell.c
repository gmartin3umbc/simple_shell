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
    char* buffer = NULL;

    ssize_t lastChar = getline(&buffer, &bufferLength, stdin);

    //delete last char which is always the '\n'
    buffer[lastChar-1] = '\0';

    return buffer;

}

char** tokenize(char* buffer){

    //allocate memory for one pointer
    char** tokens = malloc(sizeof(char*));
    int tokensIndex = 0;
    char* token;

    while((token = strtok_r(buffer, " ", &buffer))){
        //allocate more memory for another pointer
        tokens = realloc(tokens, (tokensIndex+1)*sizeof(char*));
        tokens[tokensIndex] = token;
        tokensIndex++;
    }

    //include final NULL pointer to be used in execvp
    tokens = realloc(tokens, (tokensIndex+1)*sizeof(char*));
    tokens[tokensIndex] = NULL;
    
    free(token);
    return tokens;
}

int executeInstruction(char** tokens){
    
    pid_t retVal;
    int status = 0;

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

        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
        waitpid(retVal, &status, WUNTRACED);
        // wait(NULL);
        }
         
    }

    return 0;
}

int main()
{
    char** tokens;
    char* buffer;
    char* unescaped;
    char* instruction;

    printf("$ ");
    buffer = readInput();
    unescaped = unescape(buffer, NULL);
    tokens = tokenize(unescaped);
    instruction = tokens[0];
    executeInstruction(tokens);   

    while (strcmp(instruction, "exit") != 0)
    {
        free(buffer);
        free(unescaped);
        free(tokens);

        printf("$ ");

        buffer = readInput();
        unescaped = unescape(buffer, NULL);
        tokens = tokenize(unescaped);
        instruction = tokens[0];
        executeInstruction(tokens); 
    }
    

    free(buffer);
    free(unescaped);
    free(tokens);    

    return 0;
}


