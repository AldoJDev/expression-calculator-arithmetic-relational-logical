#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "structures.h"
#include "Fila.h"
#include "Pilha.h"

class ShuntingYard {
private:
    // Retorna a precedência de um operador
    int getPrecedencia(const Token& t);
    
    // Verifica se o operador é associativo à direita
    bool ehAssociativoDireita(const Token& t);

public:
    // Converte fila de tokens infixos para fila de tokens pós-fixos
    Fila<Token> converter(Fila<Token>& tokens);
};

#endif // SHUNTING_YARD_H