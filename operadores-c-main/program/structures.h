#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "String.h"

enum TokenType {
    NUMBER,
    BOOLEAN,
    OPERATOR,
    L_PAREN,
    R_PAREN
};

struct Token {
    TokenType type;
    union {
        double num_val;
        bool bool_val;
    };
    String op_str;
};

#endif // STRUCTURES_H