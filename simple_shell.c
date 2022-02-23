#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char* readInput(){
    
    //create initial buffer
    size_t bufferLength = 0;
    char* buffer = malloc(sizeof(char) * bufferLength);

    getline(&buffer, &bufferLength, stdin);
    
    return buffer;

}

int main()
{
    
    //test
    printf("$");
    char* buffer = readInput();

    buffer = unescape(buffer, NULL);

    char** tokens = malloc(64*sizeof(char));
    int tokensIndex = 0;
    char* token;

    while((token = strtok_r(buffer, " ", &buffer))){
        tokens[tokensIndex] = token;
        tokensIndex++;
    }
    
    for (int i = 0; i < tokensIndex; i++)
    {
        printf("%s\n", tokens[i]);
    }
    

    // printf(buffer);

    return 0;

}


