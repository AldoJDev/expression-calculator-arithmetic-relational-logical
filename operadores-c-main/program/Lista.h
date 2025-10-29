#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
protected:
    struct sNo {
        T Info;
        sNo* Prox;
    };
    using pNo = sNo*;
    pNo Inicio;

public:
    Lista() : Inicio(nullptr) {}
    virtual ~Lista() {
        while (Inicio != nullptr) {
            pNo temp = Inicio;
            Inicio = Inicio->Prox;
            delete temp;
        }
    }
    bool Vazia() const { return Inicio == nullptr; }
};

#endif // LISTA_H