package modelo;

public class Cozy {
    private final String nombre;
    private int pv;
    private int posicionEnRuta;

    public Cozy(String nombre, int pvInicial) {
        if (nombre == null || nombre.isEmpty()) {
            throw new IllegalArgumentException("El nombre del Cozy es obligatorio");
        }
        if (pvInicial <= 0) {
            throw new IllegalArgumentException("Los PV iniciales deben ser positivos");
        }
        this.nombre = nombre;
        this.pv = pvInicial;
        this.posicionEnRuta = 0;
    }

    public void recibirDano(int dano) {
        this.pv = Math.max(0, this.pv - dano);
    }

    public void avanzar() {
        this.posicionEnRuta++;
    }

    public boolean estaVivo() {
        return this.pv > 0;
    }

    public boolean alcanzoElFinal(int longitudRuta) {
        return this.posicionEnRuta >= longitudRuta;
    }

    public String getNombre() { return nombre; }
    public int getPv() { return pv; }
    public int getPosicionEnRuta() { return posicionEnRuta; }

    @Override
    public String toString() {
        return String.format("%s[pv=%d, pos=%d]", nombre, pv, posicionEnRuta);
    }
}
