#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "shunting_yard.h"
#include "evaluator.h"
#include "String.h"

int main() {
    char buffer[2048];
    Lexer lexer;
    ShuntingYard conversor;
    Evaluator avaliador;

    printf("\n=====================================\n");
    printf("   Calculadora de Expressoes         \n");
    printf("=====================================\n");
    printf("Suporta:\n");
    printf("  - Aritmetica: +, -, *, /, ^\n");
    printf("  - Relacional: >, <, >=, <=, ==, !=\n");
    printf("  - Logico: &&, ||, !\n");
    printf("  - Literais: numeros, true, false\n");
    printf("  - Parenteses: ( )\n");
    printf("\nDigite 'exit' para sair.\n");
    printf("=====================================\n");

    while (true) {
        printf("\ncalc > ");
        
        // Lê entrada do usuário
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        
        // Remove o newline
        buffer[strcspn(buffer, "\n")] = 0;
        String expressao(buffer);

        // Verifica se o usuário quer sair
        if (expressao == "exit") {
            break;
        }
        
        // Ignora entradas vazias
        if (expressao.length() == 0) {
            continue;
        }

        try {
            // Fase 1: Tokenização
            Fila<Token> filaTokens = lexer.tokenizar(expressao);
            
            // Fase 2: Conversão infixa -> pós-fixa
            Fila<Token> filaPosfixa = conversor.converter(filaTokens);
            
            // Fase 3: Avaliação
            Token resultado = avaliador.avaliar(filaPosfixa);

            // Exibe resultado
            printf(">> Resultado: ");
            if (resultado.type == NUMBER) {
                printf("%g", resultado.num_val);
            } 
            else if (resultado.type == BOOLEAN) {
                printf("%s", (resultado.bool_val ? "true" : "false"));
            }
            printf("\n");

        } catch (const char* msg) {
            fprintf(stderr, "Erro: %s\n", msg);
        }
    }

    printf("\nEncerrando calculadora...\n");
    printf("=====================================\n");
    return 0;
}