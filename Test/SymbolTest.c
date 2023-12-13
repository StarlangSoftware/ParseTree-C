//
// Created by Olcay Taner YILDIZ on 31.05.2023.
//

#include <string.h>
#include <stdio.h>
#include <Memory/Memory.h>
#include "../src/Symbol.h"

int main(){
    char* word = "NP-SBJ";
    char* result = trim_symbol(word);
    if (strcmp(result, "NP") != 0){
        printf("Error in trim 1");
    }
    free_(result);
    word = "VP-SBJ-2";
    result = trim_symbol(word);
    if (strcmp(result, "VP") != 0){
        printf("Error in trim 2");
    }
    free_(result);
    word = "NNP-SBJ-OBJ-TN";
    result = trim_symbol(word);
    if (strcmp(result, "NNP") != 0){
        printf("Error in trim 3");
    }
    free_(result);
    word = "S-SBJ=OBJ";
    result = trim_symbol(word);
    if (strcmp(result, "S") != 0){
        printf("Error in trim 4");
    }
    free_(result);
}