//
// Created by Olcay Taner YILDIZ on 31.05.2023.
//

#include <string.h>
#include "IsEnglishLeaf.h"
#include "IsLeaf.h"

/**
 * Implemented node condition for English leaf node.
 * @param parseNode Checked node.
 * @return If the node is a leaf node and is not a dummy node, returns true; false otherwise.
 */
bool english_leaf_satisfies(const Parse_node *parse_node) {
    if (leaf_satisfies(parse_node)){
        char* data = parse_node->data->name;
        char* parent_data = parse_node->parent->data->name;
        if (str_find_c(data, "*") != -1 || (strcmp(data, "0") == 0 && strcmp(parent_data, "-NONE-") == 0)){
            return false;
        }
        return true;
    }
    return false;
}
