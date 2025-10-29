#ifndef LEXER_H
#define LEXER_H

#include "structures.h"
#include "Fila.h"

class Lexer {
public:
    Fila<Token> tokenizar(const String& expressao);
};

#endif 