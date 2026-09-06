#ifndef TORRE_CANON_CPP
#define TORRE_CANON_CPP

#include "Torre.cpp"

class TorreCanon : public Torre {
private:
    static const int DANO_BASE = 25;

public:
    TorreCanon(std::string nombre, int posicion) : Torre(nombre, 1, posicion) {}

    int calcularDano() const override { return DANO_BASE; }
    std::string tipo() const override { return "TorreCanon"; }
};

#endif