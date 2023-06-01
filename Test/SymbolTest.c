//
// Created by Olcay Taner YILDIZ on 31.05.2023.
//

#include <string.h>
#include <stdio.h>
#include "../src/Symbol.h"

int main(){
    Word_ptr word = create_word("NP-SBJ");
    Word_ptr result = trim_symbol(word);
    if (strcmp(result->name, "NP") != 0){
        printf("Error in trim 1");
    }
    free_word(word);
    free_word(result);
    word = create_word("VP-SBJ-2");
    result = trim_symbol(word);
    if (strcmp(result->name, "VP") != 0){
        printf("Error in trim 2");
    }
    free_word(word);
    free_word(result);
    word = create_word("NNP-SBJ-OBJ-TN");
    result = trim_symbol(word);
    if (strcmp(result->name, "NNP") != 0){
        printf("Error in trim 3");
    }
    free_word(word);
    free_word(result);
    word = create_word("S-SBJ=OBJ");
    result = trim_symbol(word);
    if (strcmp(result->name, "S") != 0){
        printf("Error in trim 4");
    }
    free_word(word);
    free_word(result);
}