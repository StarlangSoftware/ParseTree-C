//
// Created by Olcay Taner YILDIZ on 30.05.2023.
//

#include <stdlib.h>
#include <string.h>
#include <Memory/Memory.h>
#include "ParseNode.h"
#include "Symbol.h"
#include "ConstituentSpan.h"

/**
 * Another simple constructor for ParseNode. It only take input the data, and sets it.
 * @param data Data for this node.
 */
Parse_node_ptr create_parse_node(char* data) {
    Parse_node_ptr result = create_parse_node5();
    result->data = data;
    return result;
}

/**
 * Constructs a ParseNode from a single line. If the node is a leaf node, it only sets the data. Otherwise, splits
 * the line w.r.t. spaces and paranthesis and calls itself resursively to generate its child parseNodes.
 * @param parent The parent node of this node.
 * @param line The input line to create this parseNode.
 * @param is_leaf True, if this node is a leaf node; false otherwise.
 */
Parse_node_ptr create_parse_node2(Parse_node_ptr parent,
                                  const char *line,
                                  bool is_leaf) {
    Parse_node_ptr result = create_parse_node5();
    String_ptr tmp;
    int parenthesisCount = 0;
    result->parent = parent;
    if (is_leaf) {
        result->data = str_copy(result->data, line);
    } else {
        tmp = substring(line, 1, str_find_c(line, " ") - 1);
        result->data = str_copy(result->data, tmp->s);
        free_string_ptr(tmp);
        if (str_find_c(line, ")") == str_find_last_c(line, ")")) {
            tmp = substring(line, str_find_c(line, " ") + 1, str_find_c(line, ")") - str_find_c(line, " ") - 1);
            array_list_add(result->children, create_parse_node2(result, tmp->s, true));
            free_string_ptr(tmp);
        } else {
            String_ptr childLine = create_string();
            for (int i = str_find_c(line, " ") + 1; i < word_size(line); i++) {
                String_ptr ch = char_at(line, i);
                if (!string_equals2(ch, " ") || parenthesisCount > 0) {
                    string_append_s(childLine, ch);
                }
                if (line[i] == '(') {
                    parenthesisCount++;
                } else {
                    if (line[i] == ')') {
                        parenthesisCount--;
                    }
                }
                free_string_ptr(ch);
                if (parenthesisCount == 0 && !string_empty(childLine)) {
                    tmp = trim(childLine->s);
                    array_list_add(result->children, create_parse_node2(result, tmp->s, false));
                    free_string_ptr(tmp);
                    clean_string(childLine);
                }
            }
            free_string_ptr(childLine);
        }
    }
    return result;
}

/**
 * Another simple constructor for ParseNode. It takes inputs left and right children of this node, and the data.
 * Sets the corresponding attributes with these inputs.
 * @param left Left child of this node.
 * @param right Right child of this node.
 * @param data Data for this node.
 */
Parse_node_ptr create_parse_node3(Parse_node_ptr left,
                                  Parse_node_ptr right,
                                  char* data) {
    Parse_node_ptr result = create_parse_node4(left, data);
    array_list_add(result->children, right);
    right->parent = result;
    return result;
}

/**
 * Another simple constructor for ParseNode. It takes inputs left child of this node and the data.
 * Sets the corresponding attributes with these inputs.
 * @param left Left child of this node.
 * @param data Data for this node.
 */
Parse_node_ptr create_parse_node4(Parse_node_ptr left, char* data) {
    Parse_node_ptr result = create_parse_node(data);
    array_list_add(result->children, left);
    left->parent = result;
    return result;
}

Parse_node_ptr create_parse_node5() {
    Parse_node_ptr result = malloc_(sizeof(Parse_node), "create_parse_node5");
    result->data = NULL;
    result->parent = NULL;
    result->children = create_array_list();
    return result;
}

void free_parse_node(Parse_node_ptr parse_node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        free_parse_node(array_list_get(parse_node->children, i));
    }
    free_array_list(parse_node->children, NULL);
    free_(parse_node->data);
    free_(parse_node);
}

/**
 * Extracts the head of the children of this current node.
 * @param priorityList Depending on the pos of current node, the priorities among the children are given with this parameter
 * @param direction Depending on the pos of the current node, search direction is either from left to right, or from
 *                  right to left.
 * @param defaultCase If true, and no child appears in the priority list, returns first child on the left, or first
 *                    child on the right depending on the search direction.
 * @return Head node of the children of the current node
 */
Parse_node_ptr search_head_child(const Parse_node* parse_node,
                                 const char **priority_list,
                                 int list_size,
                                 Search_direction_type direction,
                                 bool default_case) {
    switch (direction) {
        case LEFT:
            for (int i = 0; i < list_size; i++) {
                const char *item = priority_list[i];
                for (int j = 0; j < parse_node->children->size; j++) {
                    Parse_node_ptr child = array_list_get(parse_node->children, j);
                    char* trimmed = trim_symbol(child->data);
                    if (strcmp(trimmed, item) == 0) {
                        free_(trimmed);
                        return child;
                    }
                    free_(trimmed);
                }
            }
            if (default_case) {
                return first_child(parse_node);
            }
            break;
        case RIGHT:
            for (int i = 0; i < list_size; i++) {
                const char *item = priority_list[i];
                for (int j = parse_node->children->size - 1; j >= 0; j--) {
                    Parse_node_ptr child = array_list_get(parse_node->children, j);
                    char* trimmed = trim_symbol(child->data);
                    if (strcmp(trimmed, item) == 0) {
                        free_(trimmed);
                        return child;
                    }
                    free_(trimmed);
                }
            }
            if (default_case) {
                return last_child(parse_node);
            }
    }
    return NULL;
}

/**
 * If current node is not a leaf, it has one or more children, this method determines recursively the head of
 * that (those) child(ren). Otherwise, it returns itself. In this way, this method returns the head of all leaf
 * successors.
 * @return Head node of the descendant leaves of this current node.
 */
Parse_node_ptr head_leaf(Parse_node_ptr parse_node) {
    if (parse_node->children->size != 0){
        Parse_node_ptr head = head_child(parse_node);
        if (head != NULL){
            return head_leaf(head);
        } else {
            return NULL;
        }
    } else {
        return parse_node;
    }
}

/**
 * Calls searchHeadChild to determine the head node of all children of this current node. The search direction and
 * the search priority list is determined according to the symbol in this current parent node.
 * @return Head node among its children of this current node.
 */
Parse_node_ptr head_child(const Parse_node* parse_node) {
    Parse_node_ptr result = NULL;
    char* head_symbol = trim_symbol(parse_node->data);
    if (strcmp(head_symbol, "ADJP") == 0) {
        result = search_head_child(parse_node, ADJP, 18, LEFT, true);
    } else {
        if (strcmp(head_symbol, "ADVP") == 0) {
            result = search_head_child(parse_node, ADVP, 13, RIGHT, true);
        } else {
            if (strcmp(head_symbol, "CONJP") == 0) {
                result = search_head_child(parse_node, CONJP, 3, RIGHT, true);
            } else {
                if (strcmp(head_symbol, "FRAG") == 0) {
                    result = search_head_child(parse_node, FRAG, 0, RIGHT, true);
                } else {
                    if (strcmp(head_symbol, "INTJ") == 0){
                        result = search_head_child(parse_node, INTJ, 0, LEFT, true);
                    } else {
                        if (strcmp(head_symbol, "LST") == 0){
                            result = search_head_child(parse_node, LST, 2, RIGHT, true);
                        } else {
                            if (strcmp(head_symbol, "NAC") == 0){
                                result = search_head_child(parse_node, NAC, 17, LEFT, true);
                            } else {
                                if (strcmp(head_symbol, "PP") == 0){
                                    result = search_head_child(parse_node, PP, 6, RIGHT, true);
                                } else {
                                    if (strcmp(head_symbol, "PRN") == 0){
                                        result = search_head_child(parse_node, PRN, 0, LEFT, true);
                                    } else {
                                        if (strcmp(head_symbol, "PRT") == 0){
                                            result = search_head_child(parse_node, PRT, 1, RIGHT, true);
                                        } else {
                                            if (strcmp(head_symbol, "QP") == 0){
                                                result = search_head_child(parse_node, QP, 12, LEFT, true);
                                            } else {
                                                if (strcmp(head_symbol, "RRC") == 0){
                                                    result = search_head_child(parse_node, RRC, 5, RIGHT, true);
                                                } else {
                                                    if (strcmp(head_symbol, "S") == 0){
                                                        result = search_head_child(parse_node, S, 8, LEFT, true);
                                                    } else {
                                                        if (strcmp(head_symbol, "SBAR") == 0){
                                                            result = search_head_child(parse_node, SBAR, 11, LEFT, true);
                                                        } else {
                                                            if (strcmp(head_symbol, "SBARQ") == 0){
                                                                result = search_head_child(parse_node, SBARQ, 5, LEFT, true);
                                                            } else {
                                                                if (strcmp(head_symbol, "SINV") == 0){
                                                                    result = search_head_child(parse_node, SINV, 10, LEFT, true);
                                                                } else {
                                                                    if (strcmp(head_symbol, "SQ") == 0){
                                                                        result = search_head_child(parse_node, SQ, 7, LEFT, true);
                                                                    } else {
                                                                        if (strcmp(head_symbol, "UCP") == 0){
                                                                            result = search_head_child(parse_node, UCP, 0, RIGHT, true);
                                                                        } else {
                                                                            if (strcmp(head_symbol, "VP") == 0){
                                                                                result = search_head_child(parse_node, VP, 13, LEFT, true);
                                                                            } else {
                                                                                if (strcmp(head_symbol, "WHADJP") == 0){
                                                                                    result = search_head_child(parse_node, WHADJP, 4, LEFT, true);
                                                                                } else {
                                                                                    if (strcmp(head_symbol, "WHADVP") == 0){
                                                                                        result = search_head_child(parse_node, WHADVP, 2, RIGHT, true);
                                                                                    } else {
                                                                                        if (strcmp(head_symbol, "WHNP") == 0){
                                                                                            result = search_head_child(parse_node, WHNP, 6, LEFT, true);
                                                                                        } else {
                                                                                            if (strcmp(head_symbol, "WHPP") == 0){
                                                                                                result = search_head_child(parse_node, WHPP, 3, RIGHT, true);
                                                                                            } else {
                                                                                                if (strcmp(head_symbol, "NP") == 0){
                                                                                                    if (strcmp(last_child(parse_node)->data, "POS") == 0){
                                                                                                        return last_child(parse_node);
                                                                                                    } else {
                                                                                                        result = search_head_child(parse_node, NP1, 7, RIGHT, false);
                                                                                                        if (result != NULL){
                                                                                                            return result;
                                                                                                        } else {
                                                                                                            result = search_head_child(parse_node, NP2, 1, LEFT, false);
                                                                                                            if (result != NULL){
                                                                                                                return result;
                                                                                                            } else {
                                                                                                                result = search_head_child(parse_node, NP3, 3, RIGHT, false);
                                                                                                                if (result != NULL){
                                                                                                                    return result;
                                                                                                                } else {
                                                                                                                    result = search_head_child(parse_node, NP4, 1, RIGHT, false);
                                                                                                                    if (result != NULL){
                                                                                                                        return result;
                                                                                                                    } else {
                                                                                                                        result = search_head_child(parse_node, NP5, 4, RIGHT, false);
                                                                                                                        if (result != NULL){
                                                                                                                            return  result;
                                                                                                                        } else {
                                                                                                                            return last_child(parse_node);
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free_(head_symbol);
    return result;
}

/**
 * Adds a child node at the end of the children node list.
 * @param child Child node to be added.
 */
void add_child(Parse_node_ptr parse_node, Parse_node_ptr child) {
    array_list_add(parse_node->children, child);
    child->parent = parse_node;
}

/**
 * Recursive method to restore the parents of all nodes below this node in the hierarchy.
 */
void correct_parents_r(Parse_node_ptr parse_node) {
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        child->parent = parse_node;
        correct_parents_r(child);
    }
}

/**
 * Adds a child node at the given specific index in the children node list.
 * @param index Index where the new child node will be added.
 * @param child Child node to be added.
 */
void add_child2(Parse_node_ptr parse_node, int index, Parse_node_ptr child) {
    array_list_insert(parse_node->children, index, child);
    child->parent = parse_node;
}

/**
 * Replaces a child node at the given specific with a new child node.
 * @param index Index where the new child node replaces the old one.
 * @param child Child node to be replaced.
 */
void set_child(Parse_node_ptr parse_node, int index, Parse_node_ptr child) {
    array_list_replace(parse_node->children, index, child, NULL);
}

/**
 * Removes a given child from children node list.
 * @param child Child node to be deleted.
 */
void remove_child(Parse_node_ptr parse_node, Parse_node_ptr child) {
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_ptr current = array_list_get(parse_node->children, i);
        if (current == child){
            array_list_remove(parse_node->children, i, (void (*)(void *)) free_parse_node);
            break;
        }
    }
}

/**
 * Recursive method to calculate the number of all leaf nodes in the subtree rooted with this current node.
 * @return Number of all leaf nodes in the current subtree.
 */
int leaf_count_r(const Parse_node* parse_node) {
    if (parse_node->children->size == 0){
        return 1;
    } else {
        int sum = 0;
        for (int i = 0; i < parse_node->children->size; i++) {
            Parse_node_ptr child = array_list_get(parse_node->children, i);
            sum += leaf_count_r(child);
        }
        return sum;
    }
}

/**
 * Recursive method to calculate the number of all nodes in the subtree rooted with this current node.
 * @return Number of all nodes in the current subtree.
 */
int node_count_r(const Parse_node* parse_node) {
    if (parse_node->children->size != 0){
        int sum = 1;
        for (int i = 0; i < parse_node->children->size; i++) {
            Parse_node_ptr child = array_list_get(parse_node->children, i);
            sum += node_count_r(child);
        }
        return sum;
    } else {
        return 1;
    }
}

/**
 * Recursive method to calculate the number of all nodes, which have more than one children, in the subtree rooted
 * with this current node.
 * @return Number of all nodes, which have more than one children, in the current subtree.
 */
int node_count_with_multiple_children_r(const Parse_node* parse_node) {
    if (parse_node->children->size > 1){
        int sum = 1;
        for (int i = 0; i < parse_node->children->size; i++) {
            Parse_node_ptr child = array_list_get(parse_node->children, i);
            sum += node_count_with_multiple_children_r(child);
        }
        return sum;
    } else {
        return 0;
    }
}

/**
 * Recursive method to remove all punctuation nodes from the current subtree.
 */
void strip_punctuation_r(Parse_node_ptr parse_node) {
    int i = 0;
    while (i < parse_node->children->size) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        if (is_punctuation(child->data)){
            array_list_remove(parse_node->children, i, (void (*)(void *)) free_parse_node);
        } else {
            i++;
        }
    }
    for (i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        strip_punctuation_r(child);
    }
}

/**
 * Returns number of children of this node.
 * @return Number of children of this node.
 */
int number_of_children(const Parse_node* parse_node) {
    return parse_node->children->size;
}

/**
 * Returns the i'th child of this node.
 * @param i Index of the retrieved node.
 * @return i'th child of this node.
 */
Parse_node_ptr get_child(const Parse_node *parse_node, int i) {
    return array_list_get(parse_node->children, i);
}

/**
 * Returns the first child of this node.
 * @return First child of this node.
 */
Parse_node_ptr first_child(const Parse_node *parse_node) {
    return array_list_get(parse_node->children, 0);
}

/**
 * Returns the last child of this node.
 * @return Last child of this node.
 */
Parse_node_ptr last_child(const Parse_node *parse_node) {
    return array_list_get(parse_node->children, parse_node->children->size - 1);
}

/**
 * Checks if the given node is the last child of this node.
 * @param child To be checked node.
 * @return True, if child is the last child of this node, false otherwise.
 */
bool is_last_child(const Parse_node *parse_node, const Parse_node *child) {
    Parse_node_ptr current = array_list_get(parse_node->children, parse_node->children->size - 1);
    return current == child;
}

/**
 * Returns the previous sibling (sister) of this node.
 * @return If this is the first child of its parent, returns null. Otherwise, returns the previous sibling of this
 * node.
 */
Parse_node_ptr previous_sibling(const Parse_node *parse_node) {
    for (int i = 1; i < parse_node->parent->children->size; i++){
        Parse_node_ptr current = array_list_get(parse_node->parent->children, i);
        if (current == parse_node){
            return array_list_get(parse_node->parent->children, i - 1);
        }
    }
    return NULL;
}

/**
 * Returns the next sibling (sister) of this node.
 * @return If this is the last child of its parent, returns null. Otherwise, returns the next sibling of this
 * node.
 */
Parse_node_ptr next_sibling(const Parse_node *parse_node) {
    for (int i = 0; i < parse_node->parent->children->size - 1; i++){
        Parse_node_ptr current = array_list_get(parse_node->parent->children, i);
        if (current == parse_node){
            return array_list_get(parse_node->parent->children, i + 1);
        }
    }
    return NULL;
}

/**
 * Recursive function to count the number of words in the subtree rooted at this node.
 * @param excludeStopWords If true, stop words are not counted.
 * @return Number of words in the subtree rooted at this node.
 */
int word_count_node(const Parse_node *parse_node, bool exclude_stop_words) {
    int sum;
    if (parse_node->children->size == 0){
        if (!exclude_stop_words){
            sum = 1;
        } else {
            char* lowerCase = to_lowercase(parse_node->data);
            if (str_find_c(lowerCase, "*") != -1 ||
            string_in_list(lowerCase, (char*[]) {",", ".", ";", "...", "at", "the", "to", "a", "an", "not", "is", "was",
                                                 "were", "have", "had", "has", "!", "?", "by", "at", "on", "off", "'s",
                                                 "n't", "can", "could", "may", "might", "will", "would", "''", "'",
                                                 "\"", "\"\"", "as", "with", "for", "will", "would", "than", "``", "$",
                                                 "and", "or", "of", "are", "be", "been", "do", "few", "there", "up",
                                                 "down", "in", "'re"}, 55)) {
                sum = 0;
            } else {
                sum = 1;
            }
            free_(lowerCase);
        }
    }
    else{
        sum = 0;
    }
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        sum += word_count_node(child, exclude_stop_words);
    }
    return sum;
}

/**
 * Returns true if this node is leaf, false otherwise.
 * @return true if this node is leaf, false otherwise.
 */
bool is_leaf(const Parse_node *parse_node) {
    return parse_node->children->size == 0;
}

/**
 * Returns true if this node does not contain a meaningful data, false otherwise.
 * @return true if this node does not contain a meaningful data, false otherwise.
 */
bool is_dummy_node(const Parse_node *parse_node) {
    return str_find_c(parse_node->data, "*") != -1 || (strcmp(parse_node->data, "0") == 0 && strcmp(parse_node->parent->data, "-NONE-") == 0);
}

/**
 * Recursive function to convert the subtree rooted at this node to a string.
 * @return A string which contains all words in the subtree rooted at this node.
 */
String_ptr parse_node_to_string(const Parse_node *parse_node) {
    if (parse_node->children->size < 2){
        if (parse_node->children->size == 0){
            return create_string2(parse_node->data);
        } else {
            String_ptr s = create_string2("");
            string_append(s, parse_node->data);
            string_append(s, " ");
            String_ptr child_string = parse_node_to_string(first_child(parse_node));
            string_append(s, child_string->s);
            free_string_ptr(child_string);
            string_append(s, ")");
            return s;
        }
    } else {
        String_ptr s = create_string2("(");
        string_append(s, parse_node->data);
        for (int i = 0; i < parse_node->children->size; i++) {
            Parse_node_ptr child = array_list_get(parse_node->children, i);
            String_ptr child_string = parse_node_to_string(child);
            string_append(s, child_string->s);
            free_string_ptr(child_string);
        }
        string_append(s, ") ");
        return s;
    }
}

/**
 * Swaps the given child node of this node with the previous sibling of that given node. If the given node is the
 * leftmost child, it swaps with the last node.
 * @param node Node to be swapped.
 */
void move_left(Parse_node_ptr parse_node, const Parse_node* node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        if (child == node){
            if (i == 0){
                array_list_swap(parse_node->children, 0, parse_node->children->size - 1);
            } else {
                array_list_swap(parse_node->children, i, (i - 1) % parse_node->children->size);
            }
            return;
        }
    }
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        move_left(child, node);
    }
}

/**
 * Recursive function to concatenate the data of the all ascendant nodes of this node to a string.
 * @return A string which contains all data of all the ascendant nodes of this node.
 */
String_ptr ancestor_string(const Parse_node *parse_node) {
    if (parse_node->parent == NULL){
        return create_string2(parse_node->data);
    } else {
        String_ptr s = ancestor_string(parse_node->parent);
        string_append(s, parse_node->data);
        return s;
    }
}

/**
 * Swaps the given child node of this node with the next sibling of that given node. If the given node is the
 * rightmost child, it swaps with the first node.
 * @param node Node to be swapped.
 */
void move_right(Parse_node_ptr parse_node, const Parse_node* node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        if (child == node){
            if (i == 0){
                array_list_swap(parse_node->children, 0, parse_node->children->size - 1);
            } else {
                array_list_swap(parse_node->children, i, (i + 1) % parse_node->children->size);
            }
            return;
        }
    }
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        move_right(child, node);
    }
}

/**
 * Returns the index of the given child of this node.
 * @return Index of the child of this node.
 */
int get_child_index(const Parse_node* parse_node, const Parse_node* node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        if (child == node) {
            return i;
        }
    }
    return -1;
}

/**
 * Returns true if the given node is a descendant of this node.
 * @return True if the given node is descendant of this node.
 */
bool is_descendant(const Parse_node *parse_node, const Parse_node *node) {
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        if (child == node){
            return true;
        } else {
            if (is_descendant(child, node)){
                return true;
            }
        }
    }
    return false;
}

/**
 * Construct recursively the constituent span list of a subtree rooted at this node.
 * @param startIndex Start index of the leftmost leaf node of this subtree.
 * @param list Returned span list.
 */
void constituent_span_list_r(const Parse_node *parse_node, int start_index, Array_list_ptr list) {
    if (parse_node->children->size != 0) {
        array_list_add(list,
                       create_constituent_span(parse_node->data, start_index, start_index + leaf_count_r(parse_node)));
    }
    int total = 0;
    for (int i = 0; i < parse_node->children->size; i++) {
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        constituent_span_list_r(child, start_index + total, list);
        total += leaf_count_r(child);
    }
}
