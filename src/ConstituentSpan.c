//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include "ConstituentSpan.h"

Constituent_span_ptr create_constituent_span(const Word *constituent, int start, int end) {
    Constituent_span_ptr result = malloc(sizeof(Constituent_span));
    result->constituent = create_word(constituent->name);
    result->start = start;
    result->end = end;
    return result;
}

void free_constituent_span(Constituent_span_ptr constituent_span) {
    free_word(constituent_span->constituent);
    free(constituent_span);
}
