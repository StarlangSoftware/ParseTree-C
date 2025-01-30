//
// Created by Olcay Taner YILDIZ on 31.05.2023.
//

#include "IsLeaf.h"

/**
 * Implemented node condition for the leaf node. If a node has no children it is a leaf node.
 * @param parse_node Checked node.
 * @return True if the input node is a leaf node, false otherwise.
 */
bool leaf_satisfies(const Parse_node *parse_node) {
    return number_of_children(parse_node) == 0;
}
