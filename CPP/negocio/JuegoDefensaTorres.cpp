#ifndef JUEGO_DEFENSA_TORRES_CPP
#define JUEGO_DEFENSA_TORRES_CPP

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "../modelo/Torre.cpp"
#include "../modelo/Cozy.cpp"
#include "../modelo/Oleada.cpp"
#include "../modelo/AccionColocarTorre.cpp"

class JuegoDefensaTorres {
private:
    std::vector<Torre*> torresColocadas;
    std::stack<AccionColocarTorre> historialDeshacer;
    std::stack<AccionColocarTorre> historialRehacer;

    std::queue<Oleada> oleadasPendientes;
    std::queue<Cozy> colaRuta;

    int longitudRuta;
    int vidaJugador;
    int puntuacion;
    int oleadaActual;

public:
    JuegoDefensaTorres(int longitudRuta, int vidaInicialJugador) {
        this->longitudRuta = longitudRuta;
        this->vidaJugador = vidaInicialJugador;
        this->puntuacion = 0;
        this->oleadaActual = 0;
    }

    void colocarTorre(Torre* torre) {
        torresColocadas.push_back(torre);
        int indice = (int)torresColocadas.size() - 1;
        historialDeshacer.push(AccionColocarTorre(torre, indice));
        while (!historialRehacer.empty()) {
            historialRehacer.pop();
        }
    }

    bool deshacerUltimaColocacion() {
        if (historialDeshacer.empty()) {
            return false;
        }
        AccionColocarTorre accion = historialDeshacer.top();
        historialDeshacer.pop();
        auto it = std::find(torresColocadas.begin(), torresColocadas.end(), accion.getTorre());
        if (it != torresColocadas.end()) {
            torresColocadas.erase(it);
        }
        historialRehacer.push(accion);
        return true;
    }

    bool rehacerColocacion() {
        if (historialRehacer.empty()) {
            return false;
        }
        AccionColocarTorre accion = historialRehacer.top();
        historialRehacer.pop();
        int indice = std::min(accion.getIndiceEnLista(), (int)torresColocadas.size());
        torresColocadas.insert(torresColocadas.begin() + indice, accion.getTorre());
        historialDeshacer.push(accion);
        return true;
    }

    void agregarOleada(Oleada oleada) {
        oleadasPendientes.push(oleada);
    }

    bool iniciarSiguienteOleada() {
        if (oleadasPendientes.empty()) {
            return false;
        }
        Oleada oleada = oleadasPendientes.front();
        oleadasPendientes.pop();
        this->oleadaActual = oleada.getNumero();
        for (int i = 1; i <= oleada.getCantidadEnemigos(); i++) {
            colaRuta.push(Cozy("Cozy-O" + std::to_string(oleada.getNumero()) + "-" + std::to_string(i),
                                oleada.getPvPorEnemigo()));
        }
        return true;
    }

    void avanzarQuantum() {
        int enemigosEnEsteQuantum = (int)colaRuta.size();
        for (int i = 0; i < enemigosEnEsteQuantum; i++) {
            if (colaRuta.empty()) {
                break;
            }
            Cozy cozy = colaRuta.front();
            colaRuta.pop();
            for (Torre* torre : torresColocadas) {
                if (torre->enRango(cozy.getPosicionEnRuta())) {
                    cozy.recibirDano(torre->calcularDano());
                }
            }
            if (!cozy.estaVivo()) {
                puntuacion += 10;
                continue;
            }
            cozy.avanzar();
            if (cozy.alcanzoElFinal(longitudRuta)) {
                vidaJugador--;
                continue;
            }
            colaRuta.push(cozy);
        }
    }

    bool oleadaEnCurso() const {
        return !colaRuta.empty();
    }

    const std::vector<Torre*>& getTorresColocadas() const { return torresColocadas; }
    int getVidaJugador() const { return vidaJugador; }
    int getPuntuacion() const { return puntuacion; }
    int getOleadaActual() const { return oleadaActual; }
    int getCantidadEnColaRuta() const { return (int)colaRuta.size(); }
    int getPilaDeshacerTamano() const { return (int)historialDeshacer.size(); }
    int getPilaRehacerTamano() const { return (int)historialRehacer.size(); }
};

#endif