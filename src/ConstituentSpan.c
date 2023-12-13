//
// Created by Olcay Taner YILDIZ on 1.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "ConstituentSpan.h"

Constituent_span_ptr create_constituent_span(const char *constituent, int start, int end) {
    Constituent_span_ptr result = malloc_(sizeof(Constituent_span), "create_constituent_span");
    result->constituent = str_copy(result->constituent, constituent);
    result->start = start;
    result->end = end;
    return result;
}

void free_constituent_span(Constituent_span_ptr constituent_span) {
    free_(constituent_span->constituent);
    free_(constituent_span);
}
