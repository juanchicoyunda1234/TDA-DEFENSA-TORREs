#ifndef COZY_CPP
#define COZY_CPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class Cozy {
private:
    std::string nombre;
    int pv;
    int posicionEnRuta;

public:
    Cozy(std::string nombre, int pvInicial) {
        if (nombre.empty()) {
            throw std::invalid_argument("El nombre del Cozy es obligatorio");
        }
        if (pvInicial <= 0) {
            throw std::invalid_argument("Los PV iniciales deben ser positivos");
        }
        this->nombre = nombre;
        this->pv = pvInicial;
        this->posicionEnRuta = 0;
    }

    void recibirDano(int dano) {
        this->pv = std::max(0, this->pv - dano);
    }

    void avanzar() {
        this->posicionEnRuta++;
    }

    bool estaVivo() const {
        return this->pv > 0;
    }

    bool alcanzoElFinal(int longitudRuta) const {
        return this->posicionEnRuta >= longitudRuta;
    }

    std::string getNombre() const { return nombre; }
    int getPv() const { return pv; }
    int getPosicionEnRuta() const { return posicionEnRuta; }

    std::string describir() const {
        std::ostringstream oss;
        oss << nombre << "[pv=" << pv << ", pos=" << posicionEnRuta << "]";
        return oss.str();
    }
};

#endif