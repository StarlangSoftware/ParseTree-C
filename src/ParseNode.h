//
// Created by Olcay Taner YILDIZ on 30.05.2023.
//

#ifndef PARSETREE_PARSENODE_H
#define PARSETREE_PARSENODE_H

#include <ArrayList.h>
#include "Dictionary/Word.h"
#include "SearchDirectionType.h"

struct parse_node {
    Array_list_ptr children;
    struct parse_node *parent;
    Word_ptr data;
};

static const char *ADJP[] = {"NNS", "QP", "NN", "$", "ADVP", "JJ", "VBN", "VBG", "ADJP", "JJR", "NP", "JJS", "DT", "FW",
                             "RBR", "RBS", "SBAR", "RB"};

static const char *ADVP[] = {"RB", "RBR", "RBS", "FW", "ADVP", "TO", "CD", "JJR", "JJ", "IN", "NP", "JJS", "NN"};
static const char *CONJP[] = {"CC", "RB", "IN"};
static const char *FRAG[] = {};
static const char *INTJ[] = {};
static const char *LST[] = {"LS", ":"};
static const char *NAC[] = {"NN", "NNS", "NNP", "NNPS", "NP", "NAC", "EX", "$", "CD", "QP", "PRP", "VBG", "JJ", "JJS",
                            "JJR", "ADJP", "FW"};
static const char *PP[] = {"IN", "TO", "VBG", "VBN", "RP", "FW"};
static const char *PRN[] = {};
static const char *PRT[] = {"RP"};
static const char *QP[] = {"$", "IN", "NNS", "NN", "JJ", "RB", "DT", "CD", "NCD", "QP", "JJR", "JJS"};
static const char *RRC[] = {"VP", "NP", "ADVP", "ADJP", "PP"};
static const char *S[] = {"TO", "IN", "VP", "S", "SBAR", "ADJP", "UCP", "NP"};
static const char *SBAR[] = {"WHNP", "WHPP", "WHADVP", "WHADJP", "IN", "DT", "S", "SQ", "SINV", "SBAR", "FRAG"};
static const char *SBARQ[] = {"SQ", "S", "SINV", "SBARQ", "FRAG"};
static const char *SINV[] = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "S", "SINV", "ADJP", "NP"};
static const char *SQ[] = {"VBZ", "VBD", "VBP", "VB", "MD", "VP", "SQ"};
static const char *UCP[] = {};
static const char *VP[] = {"TO", "VBD", "VBN", "MD", "VBZ", "VB", "VBG", "VBP", "VP", "ADJP", "NN", "NNS", "NP"};
static const char *WHADJP[] = {"CC", "WRB", "JJ", "ADJP"};
static const char *WHADVP[] = {"CC", "WRB"};
static const char *WHNP[] = {"WDT", "WP", "WP$", "WHADJP", "WHPP", "WHNP"};
static const char *WHPP[] = {"IN", "TO", "FW"};
static const char *NP1[] = {"NN", "NNP", "NNPS", "NNS", "NX", "POS", "JJR"};
static const char *NP2[] = {"NP"};
static const char *NP3[] = {"$", "ADJP", "PRN"};
static const char *NP4[] = {"CD"};
static const char *NP5[] = {"JJ", "JJS", "RB", "QP"};

typedef struct parse_node Parse_node;

typedef Parse_node *Parse_node_ptr;

Parse_node_ptr create_parse_node(Word_ptr data);

Parse_node_ptr create_parse_node2(Parse_node_ptr parent,
                                  const char *line,
                                  bool is_leaf);

Parse_node_ptr create_parse_node3(Parse_node_ptr left, Parse_node_ptr right, Word_ptr data);

Parse_node_ptr create_parse_node4(Parse_node_ptr left, Word_ptr data);

Parse_node_ptr create_parse_node5();

void free_parse_node(Parse_node_ptr parse_node);

Parse_node_ptr search_head_child(const Parse_node *parse_node, const char *priority_list[], int list_size,
                                 Search_direction_type direction, bool default_case);

Parse_node_ptr head_leaf(Parse_node_ptr parse_node);

Parse_node_ptr head_child(const Parse_node *parse_node);

void add_child(Parse_node_ptr parse_node, Parse_node_ptr child);

void correct_parents_r(Parse_node_ptr parse_node);

void add_child2(Parse_node_ptr parse_node, int index, Parse_node_ptr child);

void set_child(Parse_node_ptr parse_node, int index, Parse_node_ptr child);

void remove_child(Parse_node_ptr parse_node, Parse_node_ptr child);

int leaf_count_r(const Parse_node *parse_node);

int node_count_r(const Parse_node *parse_node);

int node_count_with_multiple_children_r(const Parse_node *parse_node);

void strip_punctuation_r(Parse_node_ptr parse_node);

int number_of_children(const Parse_node *parse_node);

Parse_node_ptr get_child(const Parse_node *parse_node, int i);

Parse_node_ptr first_child(const Parse_node *parse_node);

Parse_node_ptr last_child(const Parse_node *parse_node);

bool is_last_child(const Parse_node *parse_node, const Parse_node *child);

Parse_node_ptr previous_sibling(const Parse_node *parse_node);

Parse_node_ptr next_sibling(const Parse_node *parse_node);

int word_count_node(const Parse_node *parse_node, bool exclude_stop_words);

bool is_leaf(const Parse_node *parse_node);

bool is_dummy_node(const Parse_node *parse_node);

String_ptr parse_node_to_string(const Parse_node *parse_node);

void move_left(Parse_node_ptr parse_node, const Parse_node *node);

String_ptr ancestor_string(const Parse_node *parse_node);

void move_right(Parse_node_ptr parse_node, const Parse_node *node);

int get_child_index(const Parse_node *parse_node, const Parse_node *node);

bool is_descendant(const Parse_node *parse_node, const Parse_node *node);

void constituent_span_list_r(const Parse_node *parse_node, int start_index, Array_list_ptr list);

#endif //PARSETREE_PARSENODE_H
