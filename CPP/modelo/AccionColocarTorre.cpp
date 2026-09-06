#ifndef ACCION_COLOCAR_TORRE_CPP
#define ACCION_COLOCAR_TORRE_CPP

#include "Torre.cpp"

class AccionColocarTorre {
private:
    Torre* torre;
    int indiceEnLista;

public:
    AccionColocarTorre(Torre* torre, int indiceEnLista) {
        this->torre = torre;
        this->indiceEnLista = indiceEnLista;
    }

    Torre* getTorre() const { return torre; }
    int getIndiceEnLista() const { return indiceEnLista; }
};

#endif