#include "shunting_yard.h"

int ShuntingYard::getPrecedencia(const Token& t) {
    if (t.type != OPERATOR) return -1;
    
    const String& op = t.op_str;

    //operadores unários (! e #) têm a maior precedência
    if (op == "!" || op == "#") return 5;
    
    // Exponenciação
    if (op == "^") return 4;
    
    // Multiplicação e Divisão
    if (op == "*" || op == "/") return 3;
    
    // Adição e Subtração
    if (op == "+" || op == "-") return 2;
    
    // Operadores relacionais
    if (op == ">" || op == "<" || op == ">=" || op == "<=") return 1;
    
    // Igualdade e desigualdade
    if (op == "==" || op == "!=") return 1;
    
    // Operadores lógicos
    if (op == "&&" || op == "||") return 0;
    
    return -1;
}

bool ShuntingYard::ehAssociativoDireita(const Token& t) {
    if (t.type != OPERATOR) return false;
    
    // Apenas operadores unários e exponenciação são associativos à direita
    return t.op_str == "^" || t.op_str == "!" || t.op_str == "#";
}

Fila<Token> ShuntingYard::converter(Fila<Token>& tokens) {
    Fila<Token> filaSaida;
    Pilha<Token> pilhaOps;

    while (!tokens.Vazia()) {
        Token t = tokens.Desenfileirar();

        // Números e booleanos vão direto para a saída
        if (t.type == NUMBER || t.type == BOOLEAN) {
            filaSaida.Enfileirar(t);
        }
        // Parêntese esquerdo vai para a pilha
        else if (t.type == L_PAREN) {
            pilhaOps.Empilhar(t);
        }
        // Parêntese direito: desempilha até encontrar o (
        else if (t.type == R_PAREN) {
            while (!pilhaOps.Vazia() && pilhaOps.Topo().type != L_PAREN) {
                filaSaida.Enfileirar(pilhaOps.Desempilhar());
            }
            
            if (pilhaOps.Vazia()) {
                throw "Parenteses desbalanceados";
            }
            
            pilhaOps.Desempilhar(); //remove o (
        }
        //operador: aplica regras de precedência e associatividade
        else if (t.type == OPERATOR) {
            while (!pilhaOps.Vazia() && pilhaOps.Topo().type == OPERATOR) {
                int precAtual = getPrecedencia(t);
                int precTopo = getPrecedencia(pilhaOps.Topo());
                
                // Desempilha se topo tem precedência maior
                // OU se tem precedência igual e o operador atual é associativo à esquerda
                if (precTopo > precAtual || 
                    (precTopo == precAtual && !ehAssociativoDireita(t))) {
                    filaSaida.Enfileirar(pilhaOps.Desempilhar());
                } else {
                    break;
                }
            }
            pilhaOps.Empilhar(t);
        }
    }

    // Desempilha todos os operadores restantes
    while (!pilhaOps.Vazia()) {
        if (pilhaOps.Topo().type == L_PAREN) {
            throw "Parenteses desbalanceados";
        }
        filaSaida.Enfileirar(pilhaOps.Desempilhar());
    }
    
    return filaSaida;
}