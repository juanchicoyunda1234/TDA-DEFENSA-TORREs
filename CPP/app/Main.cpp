#include <iostream>
#include <vector>
#include <string>
#include "../modelo/TorreArquera.cpp"
#include "../modelo/TorreCanon.cpp"
#include "../modelo/Oleada.cpp"
#include "../negocio/JuegoDefensaTorres.cpp"

std::string listarTorres(const std::vector<Torre*>& torres) {
    std::string resultado = "[";
    for (size_t i = 0; i < torres.size(); i++) {
        resultado += torres[i]->describir();
        if (i + 1 < torres.size()) {
            resultado += ", ";
        }
    }
    resultado += "]";
    return resultado;
}

int main() {
    JuegoDefensaTorres juego(10, 20);

    std::cout << "=== 1. Colocacion de torres (Pila de historial) ===" << std::endl;
    TorreArquera arquera("Arquera-1", 2);
    TorreCanon canon("Canon-1", 5);
    juego.colocarTorre(&arquera);
    juego.colocarTorre(&canon);
    std::cout << "Torres colocadas: " << listarTorres(juego.getTorresColocadas()) << std::endl;
    std::cout << "Pila deshacer: " << juego.getPilaDeshacerTamano()
              << " | Pila rehacer: " << juego.getPilaRehacerTamano() << std::endl;

    std::cout << "\n=== 2. Deshacer la ultima colocacion (Canon-1) ===" << std::endl;
    juego.deshacerUltimaColocacion();
    std::cout << "Torres colocadas: " << listarTorres(juego.getTorresColocadas()) << std::endl;
    std::cout << "Pila deshacer: " << juego.getPilaDeshacerTamano()
              << " | Pila rehacer: " << juego.getPilaRehacerTamano() << std::endl;

    std::cout << "\n=== 3. Rehacer (recupera Canon-1) ===" << std::endl;
    juego.rehacerColocacion();
    std::cout << "Torres colocadas: " << listarTorres(juego.getTorresColocadas()) << std::endl;
    std::cout << "Pila deshacer: " << juego.getPilaDeshacerTamano()
              << " | Pila rehacer: " << juego.getPilaRehacerTamano() << std::endl;

    std::cout << "\n=== 4. Oleadas (Cola de oleadas) ===" << std::endl;
    juego.agregarOleada(Oleada(1, 3, 15));
    juego.agregarOleada(Oleada(2, 4, 30));
    juego.iniciarSiguienteOleada();
    std::cout << "Oleada actual: " << juego.getOleadaActual()
              << " | Cozy en ruta: " << juego.getCantidadEnColaRuta() << std::endl;

    std::cout << "\n=== 5. Simulacion por quanta (Cola circular de ruta) ===" << std::endl;
    int quantum = 0;
    while (juego.oleadaEnCurso()) {
        quantum++;
        juego.avanzarQuantum();
        std::cout << "Quantum " << quantum << " -> vida jugador: " << juego.getVidaJugador()
                  << " | puntuacion: " << juego.getPuntuacion()
                  << " | Cozy vivos en ruta: " << juego.getCantidadEnColaRuta() << std::endl;
    }

    std::cout << "\n=== 6. Segunda oleada, mas dificil ===" << std::endl;
    juego.iniciarSiguienteOleada();
    std::cout << "Oleada actual: " << juego.getOleadaActual()
              << " | Cozy en ruta: " << juego.getCantidadEnColaRuta() << std::endl;
    while (juego.oleadaEnCurso()) {
        quantum++;
        juego.avanzarQuantum();
        std::cout << "Quantum " << quantum << " -> vida jugador: " << juego.getVidaJugador()
                  << " | puntuacion: " << juego.getPuntuacion()
                  << " | Cozy vivos en ruta: " << juego.getCantidadEnColaRuta() << std::endl;
    }

    std::cout << "\n=== 7. Tercera oleada: un Cozy resistente que SI llega al final ===" << std::endl;
    juego.agregarOleada(Oleada(3, 1, 200));
    juego.iniciarSiguienteOleada();
    std::cout << "Oleada actual: " << juego.getOleadaActual()
              << " | Cozy en ruta: " << juego.getCantidadEnColaRuta() << std::endl;
    while (juego.oleadaEnCurso()) {
        quantum++;
        juego.avanzarQuantum();
        std::cout << "Quantum " << quantum << " -> vida jugador: " << juego.getVidaJugador()
                  << " | puntuacion: " << juego.getPuntuacion()
                  << " | Cozy vivos en ruta: " << juego.getCantidadEnColaRuta() << std::endl;
    }

    std::cout << "\n=== Resultado final ===" << std::endl;
    std::cout << "Vida jugador: " << juego.getVidaJugador() << std::endl;
    std::cout << "Puntuacion: " << juego.getPuntuacion() << std::endl;

    return 0;
}