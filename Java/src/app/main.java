package app;

import modelo.Oleada;
import modelo.Torre;
import modelo.TorreArquera;
import modelo.TorreCanon;
import negocio.JuegoDefensaTorres;

public class Main {
    public static void main(String[] args) {
        JuegoDefensaTorres juego = new JuegoDefensaTorres(10, 20);

        System.out.println("=== 1. Colocacion de torres (Pila de historial) ===");
        Torre arquera = new TorreArquera("Arquera-1", 2);
        Torre canon = new TorreCanon("Canon-1", 5);
        juego.colocarTorre(arquera);
        juego.colocarTorre(canon);
        System.out.println("Torres colocadas: " + juego.getTorresColocadas());
        System.out.println("Pila deshacer: " + juego.getPilaDeshacerTamano() + " | Pila rehacer: " + juego.getPilaRehacerTamano());

        System.out.println("\n=== 2. Deshacer la ultima colocacion (Canon-1) ===");
        juego.deshacerUltimaColocacion();
        System.out.println("Torres colocadas: " + juego.getTorresColocadas());
        System.out.println("Pila deshacer: " + juego.getPilaDeshacerTamano() + " | Pila rehacer: " + juego.getPilaRehacerTamano());

        System.out.println("\n=== 3. Rehacer (recupera Canon-1) ===");
        juego.rehacerColocacion();
        System.out.println("Torres colocadas: " + juego.getTorresColocadas());
        System.out.println("Pila deshacer: " + juego.getPilaDeshacerTamano() + " | Pila rehacer: " + juego.getPilaRehacerTamano());

        System.out.println("\n=== 4. Oleadas (Cola de oleadas) ===");
        juego.agregarOleada(new Oleada(1, 3, 15));
        juego.agregarOleada(new Oleada(2, 4, 30));
        juego.iniciarSiguienteOleada();
        System.out.println("Oleada actual: " + juego.getOleadaActual() + " | Cozy en ruta: " + juego.getCantidadEnColaRuta());

        System.out.println("\n=== 5. Simulacion por quanta (Cola circular de ruta) ===");
        int quantum = 0;
        while (juego.oleadaEnCurso()) {
            quantum++;
            juego.avanzarQuantum();
            System.out.printf("Quantum %d -> vida jugador: %d | puntuacion: %d | Cozy vivos en ruta: %d%n",
                    quantum, juego.getVidaJugador(), juego.getPuntuacion(), juego.getCantidadEnColaRuta());
        }

        System.out.println("\n=== 6. Segunda oleada, mas dificil ===");
        juego.iniciarSiguienteOleada();
        System.out.println("Oleada actual: " + juego.getOleadaActual() + " | Cozy en ruta: " + juego.getCantidadEnColaRuta());
        while (juego.oleadaEnCurso()) {
            quantum++;
            juego.avanzarQuantum();
            System.out.printf("Quantum %d -> vida jugador: %d | puntuacion: %d | Cozy vivos en ruta: %d%n",
                    quantum, juego.getVidaJugador(), juego.getPuntuacion(), juego.getCantidadEnColaRuta());
        }

        System.out.println("\n=== 7. Tercera oleada: un Cozy resistente que SI llega al final ===");
        juego.agregarOleada(new Oleada(3, 1, 200));
        juego.iniciarSiguienteOleada();
        System.out.println("Oleada actual: " + juego.getOleadaActual() + " | Cozy en ruta: " + juego.getCantidadEnColaRuta());
        while (juego.oleadaEnCurso()) {
            quantum++;
            juego.avanzarQuantum();
            System.out.printf("Quantum %d -> vida jugador: %d | puntuacion: %d | Cozy vivos en ruta: %d%n",
                    quantum, juego.getVidaJugador(), juego.getPuntuacion(), juego.getCantidadEnColaRuta());
        }

        System.out.println("\n=== Resultado final ===");
        System.out.println("Vida jugador: " + juego.getVidaJugador());
        System.out.println("Puntuacion: " + juego.getPuntuacion());
    }
}