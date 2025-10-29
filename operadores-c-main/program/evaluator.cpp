#include "evaluator.h"
#include <cmath>

Token Evaluator::avaliar(Fila<Token>& expressaoPosFixa) {
    Pilha<Token> pilhaResultados;
    
    while (!expressaoPosFixa.Vazia()) {
        Token t = expressaoPosFixa.Desenfileirar();
        
        // Números e booleanos são empilhados
        if (t.type == NUMBER || t.type == BOOLEAN) {
            pilhaResultados.Empilhar(t);
        }
        // Operadores são avaliados
        else if (t.type == OPERATOR) {
            Token res;
            
            // Operadores unários: ! e #
            if (t.op_str == "!" || t.op_str == "#") {
                if (pilhaResultados.Vazia()) {
                    throw "Operador com operandos insuficientes";
                }
                
                Token op = pilhaResultados.Desempilhar();
                
                // Negação lógica (!)
                if (t.op_str == "!") {
                    if (op.type != BOOLEAN) {
                        throw "Tipo incompativel para '!'";
                    }
                    res.type = BOOLEAN;
                    res.bool_val = !op.bool_val;
                }
                // Negação aritmética (#)
                else {
                    if (op.type != NUMBER) {
                        throw "Tipo incompativel para '-' unario";
                    }
                    res.type = NUMBER;
                    res.num_val = -op.num_val;
                }
            }
            // Operadores binários
            else {
                if (pilhaResultados.Vazia()) {
                    throw "Operador com operandos insuficientes";
                }
                Token op2 = pilhaResultados.Desempilhar();
                
                if (pilhaResultados.Vazia()) {
                    throw "Operador com operandos insuficientes";
                }
                Token op1 = pilhaResultados.Desempilhar();
                
                // Operadores aritméticos
                if (t.op_str == "+" || t.op_str == "-" || t.op_str == "*" || 
                    t.op_str == "/" || t.op_str == "^") {
                    
                    if (op1.type != NUMBER || op2.type != NUMBER) {
                        throw "Tipo incompativel para operador aritmetico";
                    }
                    
                    res.type = NUMBER;
                    
                    if (t.op_str == "+") {
                        res.num_val = op1.num_val + op2.num_val;
                    }
                    else if (t.op_str == "-") {
                        res.num_val = op1.num_val - op2.num_val;
                    }
                    else if (t.op_str == "*") {
                        res.num_val = op1.num_val * op2.num_val;
                    }
                    else if (t.op_str == "/") {
                        if (op2.num_val == 0) {
                            throw "Divisao por zero";
                        }
                        res.num_val = op1.num_val / op2.num_val;
                    }
                    else if (t.op_str == "^") {
                        res.num_val = pow(op1.num_val, op2.num_val);
                    }
                }
                // Operadores relacionais
                else if (t.op_str == ">" || t.op_str == "<" || 
                         t.op_str == ">=" || t.op_str == "<=") {
                    
                    if (op1.type != NUMBER || op2.type != NUMBER) {
                        throw "Tipo incompativel para operador relacional";
                    }
                    
                    res.type = BOOLEAN;
                    
                    if (t.op_str == ">") {
                        res.bool_val = op1.num_val > op2.num_val;
                    }
                    else if (t.op_str == "<") {
                        res.bool_val = op1.num_val < op2.num_val;
                    }
                    else if (t.op_str == ">=") {
                        res.bool_val = op1.num_val >= op2.num_val;
                    }
                    else if (t.op_str == "<=") {
                        res.bool_val = op1.num_val <= op2.num_val;
                    }
                }
                // Operadores de igualdade
                else if (t.op_str == "==" || t.op_str == "!=") {
                    if (op1.type != op2.type) {
                        throw "Comparacao entre tipos diferentes";
                    }
                    
                    res.type = BOOLEAN;
                    bool same;
                    
                    if (op1.type == NUMBER) {
                        same = (op1.num_val == op2.num_val);
                    } else {
                        same = (op1.bool_val == op2.bool_val);
                    }
                    
                    res.bool_val = (t.op_str == "==") ? same : !same;
                }
                // Operadores lógicos
                else if (t.op_str == "&&" || t.op_str == "||") {
                    if (op1.type != BOOLEAN || op2.type != BOOLEAN) {
                        throw "Tipo incompativel para operador logico";
                    }
                    
                    res.type = BOOLEAN;
                    
                    if (t.op_str == "&&") {
                        res.bool_val = op1.bool_val && op2.bool_val;
                    }
                    else {
                        res.bool_val = op1.bool_val || op2.bool_val;
                    }
                }
            }
            
            pilhaResultados.Empilhar(res);
        }
    }
    
    // Valida resultado final
    if (pilhaResultados.Vazia()) {
        throw "Expressao invalida";
    }
    
    Token resultado = pilhaResultados.Desempilhar();
    
    if (!pilhaResultados.Vazia()) {
        throw "Expressao mal formada";
    }
    
    return resultado;
}