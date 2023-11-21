//
// Created by Olcay Taner YILDIZ on 30.05.2023.
//

#include <string.h>
#include "Symbol.h"

/**
 * Checks if this symbol is a verb type.
 * @return True if the symbol is a verb, false otherwise.
 */
bool is_verb(const char *word) {
    return contains(verb_labels, 62, word);
}

bool contains(const char **list, int size, const char *searchedItem) {
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i], searchedItem) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if the symbol is VP or not.
 * @return True if the symbol is VB, false otherwise.
 */
bool is_VP(const char *word) {
    return strcmp(word, VPLabel) == 0;
}

/**
 * Checks if this symbol is a terminal symbol or not. A symbol is terminal if it is a punctuation symbol, or
 * if it starts with a lowercase symbol.
 * @return True if this symbol is a terminal symbol, false otherwise.
 */
bool is_terminal(const char *word) {
    int i;
    if (string_in_list(word, (char*[]) {",", ".", "!", "?", ":", ";", "\"", "''", "'", "`", "``", "...", "-", "--"}, 14))
        return true;
    if (contains(non_terminal_list, 62, word)) {
        return false;
    }
    if (strcmp(word, "I") == 0 || strcmp(word, "A") == 0)
        return true;
    for (i = 0; i < strlen(word); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            return true;
        }
    }
    return false;
}

/**
 * Checks if this symbol can be a chunk label or not.
 * @return True if this symbol can be a chunk label, false otherwise.
 */
bool is_chunk_label(const char *word) {
    if (is_punctuation(word) || contains(sentence_labels, 5, word) || contains(phrase_labels, 6, word))
        return true;
    return false;
}

/**
 * If the symbol's data contains '-' or '=', this method trims all characters after those characters and returns
 * the resulting string.
 * @return Trimmed symbol.
 */
char* trim_symbol(char* word) {
    char* result;
    int minusIndex, equalIndex;
    if (starts_with(word, "-") || (str_find_c(word, "-") == -1 && str_find_c(word, "=") == -1)){
        return word;
    }
    minusIndex = str_find_c(word, "-");
    equalIndex = str_find_c(word,"=");
    if (minusIndex != -1 || equalIndex != -1){
        String_ptr tmp;
        if (minusIndex != -1 && equalIndex != -1){
            if (minusIndex < equalIndex){
                tmp = substring(word, 0, minusIndex);
            } else {
                tmp = substring(word, 0, equalIndex);
            }
        } else {
            if (minusIndex != -1){
                tmp = substring(word, 0, minusIndex);
            } else {
                tmp = substring(word, 0, equalIndex);
            }
        }
        result = str_copy(result, tmp->s);
        free_string_ptr(tmp);
    } else {
        result = word;
    }
    return result;
}
