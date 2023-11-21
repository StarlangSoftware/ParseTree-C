//
// Created by Olcay Taner YILDIZ on 30.05.2023.
//

#include <stdbool.h>
#include <Dictionary/Word.h>

#ifndef PARSETREE_SYMBOL_H
#define PARSETREE_SYMBOL_H

static const char *non_terminal_list[] = {"ADJP", "ADVP", "CC", "CD", "CONJP", "DT", "EX", "FRAG", "FW", "IN", "INTJ", "JJ",
                                          "JJR", "JJS", "LS",
                                          "LST", "MD", "NAC", "NN", "NNP", "NNPS", "NNS", "NP", "NX", "PDT", "POS", "PP", "PRN",
                                          "PRP", "PRP$", "PRT",
                                          "PRT|ADVP", "QP", "RB", "RBR", "RP", "RRC", "S", "SBAR", "SBARQ", "SINV", "SQ", "SYM",
                                          "TO", "UCP", "UH", "VB", "VBD", "VBG", "VBN",
                                          "VBP", "VBZ", "VP", "WDT", "WHADJP", "WHADVP", "WHNP", "WP", "WP$", "WRB", "X",
                                          "-NONE-"};
static const char *phrase_labels[] = {"NP", "PP", "ADVP", "ADJP", "CC", "VG"};
static const char *sentence_labels[] = {"SINV", "SBARQ", "SBAR", "SQ", "S"};
static const char *verb_labels[] = {"VB", "VBD", "VBG", "VBN", "VBP", "VBZ", "VERB"};
static const char *VPLabel = "VP";

bool contains(const char* list[], int size, const char* searchedItem);

bool is_verb(const char* word);

bool is_VP(const char* word);

bool is_terminal(const char* word);

bool is_chunk_label(const char* word);

char* trim_symbol(char* word);

#endif //PARSETREE_SYMBOL_H
