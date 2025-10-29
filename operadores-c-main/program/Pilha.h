#ifndef PILHA_H
#define PILHA_H

#include "Lista.h"

template <typename T>
class Pilha : public Lista<T> {
    using typename Lista<T>::pNo;
    using Lista<T>::Inicio;
public:
    void Empilhar(const T& valor) {
        pNo novo = new typename Lista<T>::sNo;
        novo->Info = valor;
        novo->Prox = Inicio;
        Inicio = novo;
    }

    T Desempilhar() {
        if (this->Vazia()) throw "Pilha vazia";
        pNo temp = Inicio;
        T valor = temp->Info;
        Inicio = Inicio->Prox;
        delete temp;
        return valor;
    }

    T Topo() const {
        if (this->Vazia()) throw "Pilha vazia";
        return Inicio->Info;
    }
};

#endif // PILHA_H