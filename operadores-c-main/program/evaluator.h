#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "structures.h"
#include "Fila.h"
#include "Pilha.h"

class Evaluator {
public:
    // Avalia uma expressão em notação pós-fixa
    Token avaliar(Fila<Token>& expressaoPosFixa);
};

#endif // EVALUATOR_H