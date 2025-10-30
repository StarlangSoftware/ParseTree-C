//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>

#include "../src/TreeBank.h"

int main(){
    start_memory_check();
    Tree_bank_ptr tree_bank = create_tree_bank("trees");
    if (tree_bank_size(tree_bank) != 5){
        printf("Error in tree bank test 1");
    }
    if (word_count_tree_bank(tree_bank, true) != 30){
        printf("Error in tree bank test 2");
    }
    free_tree_bank(tree_bank);
    end_memory_check();
}