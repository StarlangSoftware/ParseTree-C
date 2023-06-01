//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//
#include <stdio.h>
#include "../src/ParseTree.h"

Parse_tree_ptr parseTree1, parseTree2, parseTree3, parseTree4, parseTree5;

void testNodeCount(){
    if (34 != node_count(parseTree1)){
        printf("Error in node count 1");
    }
    if (39 != node_count(parseTree2)){
        printf("Error in node count 2");
    }
    if (32 != node_count(parseTree3)){
        printf("Error in node count 3");
    }
    if (28 != node_count(parseTree4)){
        printf("Error in node count 4");
    }
    if (9 != node_count(parseTree5)){
        printf("Error in node count 5");
    }
}

void testFullSentence(){
    if (!is_full_sentence(parseTree1)){
        printf("Error in full sentence 1");
    }
    if (!is_full_sentence(parseTree2)){
        printf("Error in full sentence 2");
    }
    if (!is_full_sentence(parseTree3)){
        printf("Error in full sentence 3");
    }
    if (!is_full_sentence(parseTree4)){
        printf("Error in full sentence 4");
    }
    if (is_full_sentence(parseTree5)){
        printf("Error in full sentence 5");
    }
}

void testLeafCount(){
    if (13 != leaf_count(parseTree1)){
        printf("Error in leaf count 1");
    }
    if (15 != leaf_count(parseTree2)){
        printf("Error in leaf count 2");
    }
    if (10 != leaf_count(parseTree3)){
        printf("Error in leaf count 3");
    }
    if (10 != leaf_count(parseTree4)){
        printf("Error in leaf count 4");
    }
    if (4 != leaf_count(parseTree5)){
        printf("Error in leaf count 5");
    }
}

void testNodeCountWithMultipleChildren(){
    if (8 != node_count_with_multiple_children(parseTree1)){
        printf("Error in node count with multiple children 1");
    }
    if (9 != node_count_with_multiple_children(parseTree2)){
        printf("Error in node count with multiple children 2");
    }
    if (8 != node_count_with_multiple_children(parseTree3)){
        printf("Error in node count with multiple children 3");
    }
    if (6 != node_count_with_multiple_children(parseTree4)){
        printf("Error in node count with multiple children 4");
    }
    if (1 != node_count_with_multiple_children(parseTree5)){
        printf("Error in node count with multiple children 5");
    }
}

void testWordCount(){
    if (7 != word_count_tree(parseTree1, true)){
        printf("Error in word count 1");
    }
    if (8 != word_count_tree(parseTree2, true)){
        printf("Error in word count 2");
    }
    if (6 != word_count_tree(parseTree3, true)){
        printf("Error in word count 3");
    }
    if (7 != word_count_tree(parseTree4, true)){
        printf("Error in word count 4");
    }
    if (2 != word_count_tree(parseTree5, true)){
        printf("Error in word count 5");
    }
}

int main(){
    parseTree1 = create_parse_tree("../trees/0000.dev");
    parseTree2 = create_parse_tree("../trees/0001.dev");
    parseTree3 = create_parse_tree("../trees/0002.dev");
    parseTree4 = create_parse_tree("../trees/0003.dev");
    parseTree5 = create_parse_tree("../trees/0014.dev");
    testNodeCount();
    testFullSentence();
    testLeafCount();
    testNodeCountWithMultipleChildren();
    testWordCount();
    free_parse_tree(parseTree1);
    free_parse_tree(parseTree2);
    free_parse_tree(parseTree3);
    free_parse_tree(parseTree4);
    free_parse_tree(parseTree5);
}