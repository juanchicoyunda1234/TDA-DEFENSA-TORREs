#ifndef TORRE_CPP
#define TORRE_CPP

#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

class Torre {
protected:
    std::string nombre;
    int alcance;
    int posicion;

public:
    Torre(std::string nombre, int alcance, int posicion) {
        if (nombre.empty()) {
            throw std::invalid_argument("El nombre de la torre es obligatorio");
        }
        if (alcance <= 0) {
            throw std::invalid_argument("El alcance debe ser positivo");
        }
        if (posicion < 0) {
            throw std::invalid_argument("La posicion no puede ser negativa");
        }
        this->nombre = nombre;
        this->alcance = alcance;
        this->posicion = posicion;
    }

    virtual ~Torre() {}

    bool enRango(int posicionCozy) const {
        return std::abs(posicionCozy - this->posicion) <= this->alcance;
    }

    virtual int calcularDano() const = 0;
    virtual std::string tipo() const = 0;

    std::string getNombre() const { return nombre; }
    int getAlcance() const { return alcance; }
    int getPosicion() const { return posicion; }

    std::string describir() const {
        std::ostringstream oss;
        oss << nombre << "(" << tipo() << ")[pos=" << posicion << ", alcance=" << alcance
            << ", dano=" << calcularDano() << "]";
        return oss.str();
    }
};

#endif