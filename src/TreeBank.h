//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#ifndef PARSETREE_TREEBANK_H
#define PARSETREE_TREEBANK_H

#include <ArrayList.h>
#include "ParseTree.h"

struct tree_bank {
    Array_list_ptr parse_trees;
};

typedef struct tree_bank Tree_bank;

typedef Tree_bank *Tree_bank_ptr;

Tree_bank_ptr create_tree_bank(const char *folder);

void free_tree_bank(Tree_bank_ptr tree_bank);

void strip_punctuation_tree_bank(const Tree_bank* tree_bank);

int word_count_tree_bank(const Tree_bank* tree_bank, bool exclude_stop_words);

Parse_tree_ptr get_parse_tree(const Tree_bank* tree_bank, int index);

void remove_tree(Tree_bank_ptr tree_bank, int index);

int tree_bank_size(const Tree_bank* tree_bank);

#endif //PARSETREE_TREEBANK_H
