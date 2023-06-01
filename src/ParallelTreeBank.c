//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include <HashMap/HashMap.h>
#include "ParallelTreeBank.h"

Parallel_tree_bank_ptr create_parallel_tree_bank(const char *folder1, const char *folder2) {
    Parallel_tree_bank_ptr result = malloc(sizeof(Parallel_tree_bank));
    result->from_tree_bank = create_tree_bank(folder1);
    result->to_tree_bank = create_tree_bank(folder2);
    remove_different_trees(result);
    return result;
}

void free_parallel_tree_bank(Parallel_tree_bank_ptr parallel_tree_bank) {
    free_tree_bank(parallel_tree_bank->from_tree_bank);
    free_tree_bank(parallel_tree_bank->to_tree_bank);
    free(parallel_tree_bank);
}

void remove_different_trees(Parallel_tree_bank_ptr parallel_tree_bank) {
    int i, j;
    i = 0;
    j = 0;
    while (i < tree_bank_size(parallel_tree_bank->from_tree_bank) && j <tree_bank_size(parallel_tree_bank->to_tree_bank)){
        int cmp = compare_string(get_parse_tree(parallel_tree_bank->from_tree_bank, i)->name, get_parse_tree(parallel_tree_bank->to_tree_bank, i)->name);
        if (cmp < 0){
            remove_tree(parallel_tree_bank->from_tree_bank, i);
        } else {
            if (cmp > 0){
                remove_tree(parallel_tree_bank->to_tree_bank, j);
            } else {
                i++;
                j++;
            }
        }
    }
    while (i < tree_bank_size(parallel_tree_bank->from_tree_bank)){
        remove_tree(parallel_tree_bank->from_tree_bank, i);
    }
    while (j < tree_bank_size(parallel_tree_bank->from_tree_bank)){
        remove_tree(parallel_tree_bank->from_tree_bank, j);
    }
}

Parse_tree_ptr from_tree(const Parallel_tree_bank *parallelTreeBank, int index) {
    return get_parse_tree(parallelTreeBank->from_tree_bank, index);
}

Parse_tree_ptr to_tree(const Parallel_tree_bank *parallelTreeBank, int index) {
    return get_parse_tree(parallelTreeBank->to_tree_bank, index);
}

int parallel_tree_bank_size(const Parallel_tree_bank *parallel_tree_bank) {
    return parallel_tree_bank->from_tree_bank->parse_trees->size;
}

int size(const Parallel_tree_bank *parallelTreeBank) {
    return tree_bank_size(parallelTreeBank->from_tree_bank);
}
