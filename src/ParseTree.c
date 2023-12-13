//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include <Memory/Memory.h>
#include "ParseTree.h"
#include "NodeCollector.h"
#include "NodeCondition/IsEnglishLeaf.h"
#include "Symbol.h"

/**
 * Constructor of the ParseTree. The method takes the file containing a single line as input and constructs
 * the whole tree by calling the ParseNode constructor recursively.
 * @param file_name File containing a single line for a ParseTree
 */
Parse_tree_ptr create_parse_tree(const char *file_name) {
    char line[MAX_LINE_LENGTH];
    Parse_tree_ptr result = malloc_(sizeof(Parse_tree), "create_parse_tree");
    result->name = str_copy(result->name, file_name);
    FILE* input_file = fopen(file_name, "r");
    char* read = fgets(line, MAX_LINE_LENGTH, input_file);
    int opening_parenthesis = str_find_c(line, "(");
    int closing_parenthesis = str_find_last_c(line, ")");
    if (read != NULL && opening_parenthesis != -1 && closing_parenthesis != -1){
        String_ptr tmp = substring(line, opening_parenthesis + 1,  closing_parenthesis - opening_parenthesis - 1);
        String_ptr root_line = trim(tmp->s);
        free_string_ptr(tmp);
        result->root = create_parse_node2(NULL, root_line->s, false);
        free_string_ptr(root_line);
    } else {
        result->root = NULL;
    }
    fclose(input_file);
    return result;
}

void free_parse_tree(Parse_tree_ptr parse_tree) {
    free_(parse_tree->name);
    if (parse_tree->root != NULL){
        free_parse_node(parse_tree->root);
    }
    free_(parse_tree);
}

/**
 * Gets the next leaf node after the given leaf node in the ParseTree.
 * @param parseNode ParseNode for which next node is calculated.
 * @return Next leaf node after the given leaf node.
 */
Parse_node_ptr next_leaf_node(const Parse_tree* parse_tree, const Parse_node* parse_node) {
    Node_collector_ptr node_collector = create_node_collector(parse_tree->root, english_leaf_satisfies);
    Array_list_ptr leafList = collect(node_collector);
    for (int i = 0; i < leafList->size - 1; i++){
        Parse_node_ptr leaf = array_list_get(leafList, i);
        if (leaf == parse_node){
            free_node_collector(node_collector);
            return array_list_get(leafList, i + 1);
        }
    }
    free_node_collector(node_collector);
    return NULL;
}

/**
 * Gets the previous leaf node before the given leaf node in the ParseTree.
 * @param parseNode ParseNode for which previous node is calculated.
 * @return Previous leaf node before the given leaf node.
 */
Parse_node_ptr previous_leaf_node(const Parse_tree* parse_tree, const Parse_node* parse_node) {
    Node_collector_ptr node_collector = create_node_collector(parse_tree->root, english_leaf_satisfies);
    Array_list_ptr leafList = collect(node_collector);
    for (int i = 1; i < leafList->size; i++){
        Parse_node_ptr leaf = array_list_get(leafList, i);
        if (leaf == parse_node){
            free_node_collector(node_collector);
            return array_list_get(leafList, i - 1);
        }
    }
    free_node_collector(node_collector);
    return NULL;
}

/**
 * Calls recursive method to calculate the number of all nodes, which have more than one children.
 * @return Number of all nodes, which have more than one children.
 */
int node_count_with_multiple_children(const Parse_tree *parse_tree) {
    return node_count_with_multiple_children_r(parse_tree->root);
}

/**
 * Calls recursive method to calculate the number of all nodes tree.
 * @return Number of all nodes in the tree.
 */
int node_count(const Parse_tree *parse_tree){
    return node_count_r(parse_tree->root);
}

/**
 * Calls recursive method to calculate the number of all leaf nodes in the tree.
 * @return Number of all leaf nodes in the tree.
 */
int leaf_count(const Parse_tree *parse_tree) {
    return leaf_count_r(parse_tree->root);
}

bool is_full_sentence(const Parse_tree *parse_tree) {
    if (parse_tree->root != NULL && contains(sentence_labels, 5, parse_tree->root->data)){
        return true;
    }
    return false;
}

/**
 * Calls recursive function to convert the tree to a string.
 * @return A string which contains all words in the tree.
 */
String_ptr parse_tree_to_string(const Parse_tree *parse_tree) {
    return parse_node_to_string(parse_tree->root);
}

/**
 * Calls recursive method to restore the parents of all nodes in the tree.
 */
void correct_parents(const Parse_tree *parse_tree) {
    correct_parents_r(parse_tree->root);
}

/**
 * Calls recursive method to remove all punctuation nodes from the tree.
 */
void strip_punctuation_tree(const Parse_tree *parse_tree) {
    strip_punctuation_r(parse_tree->root);
}

/**
 * Calls recursive function to count the number of words in the tree.
 * @param excludeStopWords If true, stop words are not counted.
 * @return Number of words in the tree.
 */
int word_count_tree(const Parse_tree *parse_tree, bool exclude_stop_words) {
    return word_count_node(parse_tree->root, exclude_stop_words);
}

/**
 * Generates a list of constituents in the parse tree and their spans.
 * @return A list of constituents in the parse tree and their spans.
 */
Array_list_ptr constituent_span_list(const Parse_tree *parse_tree) {
    Array_list_ptr result = create_array_list();
    if (parse_tree->root != NULL){
        constituent_span_list_r(parse_tree->root, 1, result);
    }
    return result;
}

int compare_parse_tree(const Parse_tree *parse_tree1, const Parse_tree *parse_tree2) {
    return strcmp(parse_tree1->name, parse_tree2->name);
}
