//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#ifndef PARSETREE_CONSTITUENTSPAN_H
#define PARSETREE_CONSTITUENTSPAN_H

#include <Dictionary/Word.h>

struct constituent_span {
    char* constituent;
    int start;
    int end;
};

typedef struct constituent_span Constituent_span;

typedef Constituent_span *Constituent_span_ptr;

Constituent_span_ptr create_constituent_span(const char* constituent, int start, int end);

void free_constituent_span(Constituent_span_ptr constituent_span);

#endif //PARSETREE_CONSTITUENTSPAN_H
