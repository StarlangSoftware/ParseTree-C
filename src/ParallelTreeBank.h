//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#ifndef PARSETREE_PARALLELTREEBANK_H
#define PARSETREE_PARALLELTREEBANK_H

#include "TreeBank.h"

struct parallel_tree_bank{
    Tree_bank_ptr from_tree_bank;
    Tree_bank_ptr to_tree_bank;
};

typedef struct parallel_tree_bank Parallel_tree_bank;

typedef Parallel_tree_bank *Parallel_tree_bank_ptr;

Parallel_tree_bank_ptr create_parallel_tree_bank(const char* folder1, const char* folder2);

void free_parallel_tree_bank(Parallel_tree_bank_ptr parallel_tree_bank);

void remove_different_trees(Parallel_tree_bank_ptr parallel_tree_bank);

Parse_tree_ptr from_tree(const Parallel_tree_bank* parallel_tree_bank, int index);

Parse_tree_ptr to_tree(const Parallel_tree_bank* parallel_tree_bank, int index);

int parallel_tree_bank_size(const Parallel_tree_bank* parallel_tree_bank);

int size(const Parallel_tree_bank* parallel_tree_bank);

#endif //PARSETREE_PARALLELTREEBANK_H
