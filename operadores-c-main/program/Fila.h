#ifndef FILA_H
#define FILA_H

#include "Lista.h"

template <typename T>
class Fila : public Lista<T> {
    using typename Lista<T>::pNo;
    using Lista<T>::Inicio;
public:
    void Enfileirar(const T& valor) {
        pNo novo = new typename Lista<T>::sNo;
        novo->Info = valor;
        novo->Prox = nullptr;
        if (this->Vazia()) {
            Inicio = novo;
        } else {
            pNo atual = Inicio;
            while (atual->Prox != nullptr) atual = atual->Prox;
            atual->Prox = novo;
        }
    }

    T Desenfileirar() {
        if (this->Vazia()) throw "Fila vazia";
        pNo temp = Inicio;
        T valor = temp->Info;
        Inicio = Inicio->Prox;
        delete temp;
        return valor;
    }
};

#endif // FILA_H