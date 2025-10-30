//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <HashMap/HashMap.h>
#include "ParallelTreeBank.h"
#include "Memory/Memory.h"

/**
 * Constructor for the ParallelTreeBank class. A ParallelTreeBank consists of two treebanks, where each sentence
 * appears in both treebanks with possibly different tree structures. Each treebank is stored in a separate folder.
 * Both treebanks are read and distinct sentences are removed from the treebanks.
 * @param folder1 Folder containing the files for trees in the first treebank.
 * @param folder2 Folder containing the files for trees in the second treebank.
 */
Parallel_tree_bank_ptr create_parallel_tree_bank(const char *folder1, const char *folder2) {
    Parallel_tree_bank_ptr result = malloc_(sizeof(Parallel_tree_bank));
    result->from_tree_bank = create_tree_bank(folder1);
    result->to_tree_bank = create_tree_bank(folder2);
    remove_different_trees(result);
    return result;
}

/**
 * Frees memory allocated for parallel treebank.
 * @param parallel_tree_bank Parallel treebank.
 */
void free_parallel_tree_bank(Parallel_tree_bank_ptr parallel_tree_bank) {
    free_tree_bank(parallel_tree_bank->from_tree_bank);
    free_tree_bank(parallel_tree_bank->to_tree_bank);
    free_(parallel_tree_bank);
}

/**
 * Given two treebanks read, the method removes the trees which do not exist in one of the treebanks. At the end,
 * we will only have the tree files that exist in both treebanks.
 * @param parallel_tree_bank Parallel treebank.
 */
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

/**
 * Returns the tree at position index in the first treebank.
 * @param parallel_tree_bank Parallel treebank.
 * @param index Position of the tree in the first treebank.
 * @return The tree at position index in the first treebank.
 */
Parse_tree_ptr from_tree(const Parallel_tree_bank *parallel_tree_bank, int index) {
    return get_parse_tree(parallel_tree_bank->from_tree_bank, index);
}

/**
 * Returns the tree at position index in the second treebank.
 * @param parallel_tree_bank Parallel treebank.
 * @param index Position of the tree in the second treebank.
 * @return The tree at position index in the second treebank.
 */
Parse_tree_ptr to_tree(const Parallel_tree_bank *parallel_tree_bank, int index) {
    return get_parse_tree(parallel_tree_bank->to_tree_bank, index);
}

/**
 * Returns number of sentences in ParallelTreeBank.
 * @param parallel_tree_bank Parallel treebank.
 * @return Number of sentences.
 */
int parallel_tree_bank_size(const Parallel_tree_bank *parallel_tree_bank) {
    return parallel_tree_bank->from_tree_bank->parse_trees->size;
}

/**
 * Returns number of sentences in ParallelTreeBank.
 * @param parallel_tree_bank Parallel treebank.
 * @return Number of sentences.
 */
int size(const Parallel_tree_bank *parallel_tree_bank) {
    return tree_bank_size(parallel_tree_bank->from_tree_bank);
}
