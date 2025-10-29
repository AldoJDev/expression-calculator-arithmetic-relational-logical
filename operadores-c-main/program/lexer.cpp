#include "lexer.h"
#include <cctype>
#include <cstdlib>
#include <cstring>

Fila<Token> Lexer::tokenizar(const String& expressao) {
    Fila<Token> filaTokens;
    TokenType ultimoTipo = L_PAREN; // Inicializa como L_PAREN para detectar - unário no início

    for (int i = 0; i < expressao.length(); ++i) {
        char c = expressao[i];
        
        // Ignora espaços em branco
        if (isspace(c)) continue;

        // Reconhece números (inteiros e reais)
        if (isdigit(c) || (c == '.' && i + 1 < expressao.length() && isdigit(expressao[i+1]))) {
            const char* start = expressao.c_str() + i;
            char* end;
            double val = strtod(start, &end);
            int length = end - start;
            
            Token t;
            t.type = NUMBER;
            t.num_val = val;
            filaTokens.Enfileirar(t);
            
            i += length - 1;
            ultimoTipo = NUMBER;
        }
        // Reconhece literal booleano "true"
        else if (strncmp(expressao.c_str() + i, "true", 4) == 0 && 
                 (i + 4 >= expressao.length() || !isalnum(expressao[i+4]))) {
            Token t;
            t.type = BOOLEAN;
            t.bool_val = true;
            filaTokens.Enfileirar(t);
            i += 3;
            ultimoTipo = BOOLEAN;
        }
        // Reconhece literal booleano "false"
        else if (strncmp(expressao.c_str() + i, "false", 5) == 0 && 
                 (i + 5 >= expressao.length() || !isalnum(expressao[i+5]))) {
            Token t;
            t.type = BOOLEAN;
            t.bool_val = false;
            filaTokens.Enfileirar(t);
            i += 4;
            ultimoTipo = BOOLEAN;
        }
        // Reconhece parêntese esquerdo
        else if (c == '(') {
            Token t;
            t.type = L_PAREN;
            t.op_str = "(";
            filaTokens.Enfileirar(t);
            ultimoTipo = L_PAREN;
        }
        // Reconhece parêntese direito
        else if (c == ')') {
            Token t;
            t.type = R_PAREN;
            t.op_str = ")";
            filaTokens.Enfileirar(t);
            ultimoTipo = R_PAREN;
        }
        // Reconhece operadores
        else {
            Token t;
            t.type = OPERATOR;
            char c2 = (i + 1 < expressao.length()) ? expressao[i + 1] : '\0';
            
            // Operadores de dois caracteres: >=, <=, ==, !=, &&, ||
            if ((c == '>' || c == '<' || c == '=' || c == '!') && c2 == '=') {
                char s[3] = {c, c2, '\0'};
                t.op_str = String(s);
                i++;
            }
            else if ((c == '&' && c2 == '&') || (c == '|' && c2 == '|')) {
                char s[3] = {c, c2, '\0'};
                t.op_str = String(s);
                i++;
            }
            // Trata - unário: se o último token foi ( ou outro operador, é unário
            else if (c == '-' && (ultimoTipo == L_PAREN || ultimoTipo == OPERATOR)) {
                t.op_str = String("#"); // Usa '#' para representar - unário
            }
            // Operadores de um caractere
            else {
                char s[2] = {c, '\0'};
                t.op_str = String(s);
            }

            // Valida se é um operador reconhecido
            if (strchr("+-*/^><!&|#=", t.op_str[0]) == nullptr) {
                throw "Token invalido";
            }
            
            filaTokens.Enfileirar(t);
            ultimoTipo = OPERATOR;
        }
    }
    
    return filaTokens;
}