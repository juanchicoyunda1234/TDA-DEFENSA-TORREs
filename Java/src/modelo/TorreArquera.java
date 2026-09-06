package modelo;

public class TorreArquera extends Torre {
    private static final int DANO_BASE = 8;

    public TorreArquera(String nombre, int posicion) {
        super(nombre, 4, posicion);
    }

    @Override
    public int calcularDano() {
        return DANO_BASE;
    }
}
