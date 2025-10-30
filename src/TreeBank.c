//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include <dirent.h>
#include <HashMap/HashMap.h>
#include <Memory/Memory.h>
#include "TreeBank.h"
#include "ParseTree.h"

/**
 * A constructor of TreeBank class which reads all {@link ParseTree] files inside the given folder. For each
 * file inside that folder, the constructor creates a ParseTree and puts in inside the list parseTrees.
 * @param folder Folder that stores the tree bank files.
*/
Tree_bank_ptr create_tree_bank(const char *folder) {
    Tree_bank_ptr result = malloc_(sizeof(Tree_bank));
    result->parse_trees = create_array_list();
    DIR *d;
    struct dirent *dir;
    d = opendir(folder);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG){
                String_ptr tmp = create_string4(folder, "/", dir->d_name);
                Parse_tree_ptr parse_tree = create_parse_tree(tmp->s);
                free_string_ptr(tmp);
                free_(parse_tree->name);
                parse_tree->name = str_copy(parse_tree->name, dir->d_name);
                array_list_add(result->parse_trees, parse_tree);
            }
        }
        closedir(d);
    }
    array_list_sort(result->parse_trees, (int (*)(const void *, const void *)) compare_parse_tree);
    return result;
}

/**
 * Frees memory allocated for treebank.
 * @param tree_bank Current treebank.
 */
void free_tree_bank(Tree_bank_ptr tree_bank) {
    free_array_list(tree_bank->parse_trees, (void (*)(void *)) free_parse_tree);
    free_(tree_bank);
}

/**
 * Strips punctuation symbols from all parseTrees in this TreeBank.
 * @param tree_bank Current treebank.
 */
void strip_punctuation_tree_bank(const Tree_bank *tree_bank) {
    for (int i = 0; i < tree_bank->parse_trees->size; i++){
        Parse_tree_ptr parse_tree = array_list_get(tree_bank->parse_trees, i);
        strip_punctuation_tree(parse_tree);
    }
}

/**
 * Returns number of trees in the TreeBank.
 * @param tree_bank Current treebank.
 * @return Number of trees in the TreeBank.
 */
int tree_bank_size(const Tree_bank *tree_bank) {
    return tree_bank->parse_trees->size;
}

/**
 * Returns number of words in the parseTrees in the TreeBank. If excludeStopWords is true, stop words are not
 * counted.
 * @param tree_bank Current treebank.
 * @param exclude_stop_words If true, stop words are not included in the count process.
 * @return Number of all words in all parseTrees in the TreeBank.
 */
int word_count_tree_bank(const Tree_bank *tree_bank, bool exclude_stop_words) {
    int count = 0;
    for (int i = 0; i < tree_bank->parse_trees->size; i++){
        Parse_tree_ptr parse_tree = array_list_get(tree_bank->parse_trees, i);
        count += word_count_tree(parse_tree, exclude_stop_words);
    }
    return count;
}

/**
 * Accessor for a single ParseTree.
 * @param tree_bank Current treebank.
 * @param index Index of the parseTree.
 * @return The ParseTree at the given index.
 */
Parse_tree_ptr get_parse_tree(const Tree_bank* tree_bank, int index) {
    return array_list_get(tree_bank->parse_trees, index);
}

/**
 * Removes the parse tree at position index from the treebank.
 * @param tree_bank Current treebank.
 * @param index Position of the tree in the treebank.
 */
void remove_tree(Tree_bank_ptr tree_bank, int index) {
    array_list_remove(tree_bank->parse_trees, index, (void (*)(void *)) free_parse_tree);
}

