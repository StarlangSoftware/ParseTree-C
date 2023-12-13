//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "NodeCollector.h"

/**
 * Constructor for the NodeCollector class. NodeCollector's main aim is to collect a set of ParseNode's from a
 * subtree rooted at rootNode, where the ParseNode's satisfy a given NodeCondition, which is implemented by other
 * interface class.
 * @param root_node Root node of the subtree
 * @param satisfies The condition interface for which all nodes in the subtree rooted at rootNode will be checked
 */
Node_collector_ptr create_node_collector(Parse_node_ptr root_node, bool (*satisfies)(const Parse_node *)) {
    Node_collector_ptr result = malloc_(sizeof(Node_collector), "create_node_collector");
    result->root_node = root_node;
    result->satisfies = satisfies;
    return result;
}

void free_node_collector(Node_collector_ptr node_collector) {
    free_(node_collector);
}

/**
 * Private recursive method to check all descendants of the parseNode, if they ever satisfy the given node condition
 * @param parseNode Root node of the subtree
 * @param collected The ArrayList where the collected ParseNode's will be stored.
 */
void collect_nodes(Node_collector_ptr node_collector, Parse_node_ptr parse_node, Array_list_ptr collected) {
    if (node_collector->satisfies == NULL || node_collector->satisfies(parse_node)){
        array_list_add(collected,parse_node);
    }
    for (int i = 0; i < parse_node->children->size; i++){
        Parse_node_ptr child = array_list_get(parse_node->children, i);
        collect_nodes(node_collector, child, collected);
    }
}

/**
 * Collects and returns all ParseNode's satisfying the node condition.
 * @return All ParseNode's satisfying the node condition.
 */
Array_list_ptr collect(Node_collector_ptr node_collector) {
    Array_list_ptr result = create_array_list();
    collect_nodes(node_collector, node_collector->root_node, result);
    return result;
}
