package negocio;

import modelo.AccionColocarTorre;
import modelo.Cozy;
import modelo.Oleada;
import modelo.Torre;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class JuegoDefensaTorres {

    private final List<Torre> torresColocadas = new ArrayList<>();
    private final Stack<AccionColocarTorre> historialDeshacer = new Stack<>();
    private final Stack<AccionColocarTorre> historialRehacer = new Stack<>();

    private final Queue<Oleada> oleadasPendientes = new LinkedList<>();
    private final Queue<Cozy> colaRuta = new LinkedList<>();

    private final int longitudRuta;
    private int vidaJugador;
    private int puntuacion;
    private int oleadaActual;

    public JuegoDefensaTorres(int longitudRuta, int vidaInicialJugador) {
        this.longitudRuta = longitudRuta;
        this.vidaJugador = vidaInicialJugador;
        this.puntuacion = 0;
        this.oleadaActual = 0;
    }

    public void colocarTorre(Torre torre) {
        torresColocadas.add(torre);
        int indice = torresColocadas.size() - 1;
        historialDeshacer.push(new AccionColocarTorre(torre, indice));
        historialRehacer.clear();
    }

    public boolean deshacerUltimaColocacion() {
        if (historialDeshacer.isEmpty()) {
            return false;
        }
        AccionColocarTorre accion = historialDeshacer.pop();
        torresColocadas.remove(accion.getTorre());
        historialRehacer.push(accion);
        return true;
    }

    public boolean rehacerColocacion() {
        if (historialRehacer.isEmpty()) {
            return false;
        }
        AccionColocarTorre accion = historialRehacer.pop();
        int indice = Math.min(accion.getIndiceEnLista(), torresColocadas.size());
        torresColocadas.add(indice, accion.getTorre());
        historialDeshacer.push(accion);
        return true;
    }

    public void agregarOleada(Oleada oleada) {
        oleadasPendientes.add(oleada);
    }

    public boolean iniciarSiguienteOleada() {
        Oleada oleada = oleadasPendientes.poll();
        if (oleada == null) {
            return false;
        }
        this.oleadaActual = oleada.getNumero();
        for (int i = 1; i <= oleada.getCantidadEnemigos(); i++) {
            colaRuta.add(new Cozy("Cozy-O" + oleada.getNumero() + "-" + i, oleada.getPvPorEnemigo()));
        }
        return true;
    }

    public void avanzarQuantum() {
        int enemigosEnEsteQuantum = colaRuta.size();
        for (int i = 0; i < enemigosEnEsteQuantum; i++) {
            Cozy cozy = colaRuta.poll();
            if (cozy == null) {
                break;
            }
            for (Torre torre : torresColocadas) {
                if (torre.enRango(cozy.getPosicionEnRuta())) {
                    cozy.recibirDano(torre.calcularDano());
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
            colaRuta.add(cozy);
        }
    }

    public boolean oleadaEnCurso() {
        return !colaRuta.isEmpty();
    }

    public List<Torre> getTorresColocadas() { return torresColocadas; }
    public int getVidaJugador() { return vidaJugador; }
    public int getPuntuacion() { return puntuacion; }
    public int getOleadaActual() { return oleadaActual; }
    public int getCantidadEnColaRuta() { return colaRuta.size(); }
    public int getPilaDeshacerTamano() { return historialDeshacer.size(); }
    public int getPilaRehacerTamano() { return historialRehacer.size(); }
}
