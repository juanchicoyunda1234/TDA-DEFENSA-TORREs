package modelo;

public class TorreCanon extends Torre {
    private static final int DANO_BASE = 25;

    public TorreCanon(String nombre, int posicion) {
        super(nombre, 1, posicion);
    }

    @Override
    public int calcularDano() {
        return DANO_BASE;
    }
}