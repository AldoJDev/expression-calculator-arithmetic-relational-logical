# Calculadora de Expressões

## Descrição

Este projeto implementa uma calculadora capaz de avaliar expressões aritméticas, relacionais e lógicas usando pilhas e filas. A implementação é feita "na mão", sem uso de classes da STL.

## Estrutura do Projeto

```
.
├── String.h           # Implementação manual de String
├── Lista.h            # Classe base para estruturas dinâmicas
├── Pilha.h            # Implementação de Pilha
├── Fila.h             # Implementação de Fila
├── structures.h       # Definição de Token e tipos
├── lexer.h/cpp        # Tokenizador (análise léxica)
├── shunting_yard.h/cpp # Conversor infixa -> pós-fixa
├── evaluator.h/cpp    # Avaliador RPN
├── main.cpp           # Programa principal
├── tests.txt          # Casos de teste
├── expected.txt       # Resultados esperados
└── README.md          # Este arquivo
```

## Operadores Suportados

### Aritméticos
- `+` (adição)
- `-` (subtração)
- `*` (multiplicação)
- `/` (divisão)
- `^` (exponenciação)
- `-` unário (negação: ex: `-5`, `-(2+3)`)

### Relacionais
- `>` (maior que)
- `<` (menor que)
- `>=` (maior ou igual)
- `<=` (menor ou igual)
- `==` (igual)
- `!=` (diferente)

### Lógicos
- `&&` (E lógico)
- `||` (OU lógico)
- `!` (negação lógica)

### Literais
- Números: inteiros e reais (ex: `12`, `3.14`, `-5.5`)
- Booleanos: `true` e `false`

### Outros
- Parênteses: `(` e `)`

## Precedência e Associatividade

Do mais forte para o mais fraco:

1. `( )` - parênteses
2. `!` - negação lógica (unário, direita)
3. `#` - negação aritmética/menos unário (direita)
4. `^` - exponenciação (direita)
5. `*`, `/` - multiplicação e divisão (esquerda)
6. `+`, `-` - adição e subtração (esquerda)
7. `>`, `<`, `>=`, `<=` - relacionais (esquerda)
8. `==`, `!=` - igualdade (esquerda)
9. `&&` - E lógico (esquerda)
10. `||` - OU lógico (esquerda)

## Compilação

### Linux/Mac
```bash
g++ -o calc main.cpp lexer.cpp shunting_yard.cpp evaluator.cpp -lm
```

### Windows (MinGW)
```bash
g++ -o calc.exe main.cpp lexer.cpp shunting_yard.cpp evaluator.cpp
```

## Execução

```bash
./calc
```

O programa entrará em modo interativo:

```
=====================================
   Calculadora de Expressoes
=====================================
Suporta:
  - Aritmetica: +, -, *, /, ^
  - Relacional: >, <, >=, <=, ==, !=
  - Logico: &&, ||, !
  - Literais: numeros, true, false
  - Parenteses: ( )

Digite 'exit' para sair.
=====================================

calc >
```

## Exemplos de Uso

```
calc > 10 + (2 * 3 - 4) ^ 2 / 4 + 6 * 2
>> Resultado: 23

calc > (8 / 2) > (3 + 1)
>> Resultado: false

calc > (10 > 5) && (2 + 2 == 4)
>> Resultado: true

calc > (3 * 2 <= 7) || (4 ^ 2 == 16 && !(5 < 2))
>> Resultado: true

calc > -5 + 3
>> Resultado: -2

calc > -(2 + 3) * 4
>> Resultado: -20
```

## Arquitetura

### 1. Tokenização (lexer.cpp)
Converte a string de entrada em uma fila de tokens, reconhecendo:
- Números (com ponto decimal)
- Literais booleanos (`true`, `false`)
- Operadores (incluindo operadores de dois caracteres como `>=`, `&&`)
- Parênteses
- Menos unário (convertido para `#`)

### 2. Conversão Infixa → Pós-fixa (shunting_yard.cpp)
Implementa o algoritmo Shunting Yard para converter expressões infixas em notação pós-fixa (RPN), respeitando:
- Precedência de operadores
- Associatividade (direita/esquerda)
- Parênteses

### 3. Avaliação RPN (evaluator.cpp)
Avalia a expressão pós-fixa usando uma pilha:
- Números e booleanos são empilhados
- Operadores consomem operandos da pilha
- Verifica compatibilidade de tipos
- Detecta erros (divisão por zero, tipos incompatíveis, etc.)

## Tratamento de Erros

O programa detecta e reporta os seguintes erros:

- **Token inválido**: Caracteres não reconhecidos
- **Parênteses desbalanceados**: Falta de `(` ou `)`
- **Operador com operandos insuficientes**: Faltam valores na pilha
- **Tipo incompatível**: Operação entre tipos incompatíveis (ex: `5 && true`)
- **Divisão por zero**: Tentativa de dividir por zero
- **Comparação entre tipos diferentes**: `==` ou `!=` entre number e boolean
- **Expressão mal formada**: Pilha final contém mais de um valor

## Decisões de Projeto

1. **Representação do Token**: Usamos uma `union` para armazenar valores numéricos ou booleanos no mesmo struct, economizando memória.

2. **Menos unário**: Convertemos `-` unário para `#` durante a tokenização para facilitar o tratamento no Shunting Yard e no avaliador.

3. **C-strings**: Toda manipulação de strings é feita com `char*` e funções C (`strlen`, `strcmp`, `strtod`).

4. **Estruturas manuais**: Implementamos Pilha e Fila usando listas encadeadas, sem uso da STL.

5. **Validação de tipos**: O avaliador verifica rigorosamente a compatibilidade de tipos antes de cada operação.

## Limitações

- Não suporta variáveis
- Não suporta funções matemáticas (sin, cos, etc.)
- Strings não são suportadas
- Tamanho máximo de entrada: 2048 caracteres

## Testes

Execute os testes com:

```bash
./calc < tests.txt > output.txt
diff output.txt expected.txt
```

## Referências

- Algoritmo Shunting Yard: Edsger Dijkstra
- Notação Polonesa Reversa (RPN)
- Especificação do projeto: Prof. André Luís