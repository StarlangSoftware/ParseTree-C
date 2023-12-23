//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#ifndef PARSETREE_NODECOLLECTOR_H
#define PARSETREE_NODECOLLECTOR_H

#include "ParseNode.h"

struct node_collector{
    bool (*satisfies)(const Parse_node* parse_node);
    Parse_node_ptr root_node;
};

typedef struct node_collector Node_collector;

typedef Node_collector* Node_collector_ptr;

Node_collector_ptr create_node_collector(Parse_node_ptr root_node, bool (*satisfies)(const Parse_node* parse_node));

void free_node_collector(Node_collector_ptr node_collector);

void parse_node_collect_nodes(Node_collector_ptr node_collector, Parse_node_ptr parse_node, Array_list_ptr collected);

Array_list_ptr parse_node_collect(Node_collector_ptr node_collector);

#endif //PARSETREE_NODECOLLECTOR_H
