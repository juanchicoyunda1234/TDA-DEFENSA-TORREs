#ifndef TORRE_ARQUERA_CPP
#define TORRE_ARQUERA_CPP

#include "Torre.cpp"

class TorreArquera : public Torre {
private:
    static const int DANO_BASE = 8;

public:
    TorreArquera(std::string nombre, int posicion) : Torre(nombre, 4, posicion) {}

    int calcularDano() const override { return DANO_BASE; }
    std::string tipo() const override { return "TorreArquera"; }
};

#endif