#ifndef OLEADA_CPP
#define OLEADA_CPP

#include <stdexcept>

class Oleada {
private:
    int numero;
    int cantidadEnemigos;
    int pvPorEnemigo;

public:
    Oleada(int numero, int cantidadEnemigos, int pvPorEnemigo) {
        if (cantidadEnemigos <= 0 || pvPorEnemigo <= 0) {
            throw std::invalid_argument("Cantidad de enemigos y PV deben ser positivos");
        }
        this->numero = numero;
        this->cantidadEnemigos = cantidadEnemigos;
        this->pvPorEnemigo = pvPorEnemigo;
    }

    int getNumero() const { return numero; }
    int getCantidadEnemigos() const { return cantidadEnemigos; }
    int getPvPorEnemigo() const { return pvPorEnemigo; }
};

#endif