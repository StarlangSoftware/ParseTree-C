//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>

#include "../src/ParallelTreeBank.h"

int main(){
    start_memory_check();
    Parallel_tree_bank_ptr parallel_tree_bank = create_parallel_tree_bank("trees", "trees2");
    if (tree_bank_size(parallel_tree_bank->from_tree_bank) != 3){
        printf("Error in Parallel_tree_bank_ptr");
    }
    free_parallel_tree_bank(parallel_tree_bank);
    end_memory_check();
}