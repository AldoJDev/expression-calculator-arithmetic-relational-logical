# Makefile para Calculadora de Expressões

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lm

TARGET = calc
SOURCES = main.cpp lexer.cpp shunting_yard.cpp evaluator.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = String.h Lista.h Pilha.h Fila.h structures.h lexer.h shunting_yard.h evaluator.h

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET) output.txt

test: $(TARGET)
	@echo "Executando testes..."
	@./$(TARGET) < tests.txt > output.txt 2>&1
	@echo "Comparando resultados..."
	@diff -u expected.txt output.txt && echo "✓ Todos os testes passaram!" || echo "✗ Alguns testes falharam"

run: $(TARGET)
	./$(TARGET)t