//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#ifndef PARSETREE_PARSETREE_H
#define PARSETREE_PARSETREE_H

#include "ParseNode.h"

struct parse_tree {
    Parse_node_ptr root;
    char *name;
};

typedef struct parse_tree Parse_tree;

typedef Parse_tree *Parse_tree_ptr;

Parse_tree_ptr create_parse_tree(const char *file_name);

Parse_tree_ptr create_parse_tree2(Parse_node_ptr root);

void free_parse_tree(Parse_tree_ptr parse_tree);

Parse_node_ptr next_leaf_node(const Parse_tree *parse_tree, const Parse_node *parse_node);

Parse_node_ptr previous_leaf_node(const Parse_tree *parse_tree, const Parse_node *parse_node);

int node_count_with_multiple_children(const Parse_tree *parse_tree);

int node_count(const Parse_tree *parse_tree);

int leaf_count(const Parse_tree *parse_tree);

bool is_full_sentence(const Parse_tree *parse_tree);

String_ptr parse_tree_to_string(const Parse_tree *parse_tree);

void correct_parents(const Parse_tree *parse_tree);

void strip_punctuation_tree(const Parse_tree *parse_tree);

int word_count_tree(const Parse_tree *parse_tree, bool exclude_stop_words);

Array_list_ptr constituent_span_list(const Parse_tree *parse_tree);

int compare_parse_tree(const Parse_tree *parse_tree1, const Parse_tree *parse_tree2);

#endif //PARSETREE_PARSETREE_H
