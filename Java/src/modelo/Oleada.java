package modelo;

public class Oleada {
    private final int numero;
    private final int cantidadEnemigos;
    private final int pvPorEnemigo;

    public Oleada(int numero, int cantidadEnemigos, int pvPorEnemigo) {
        if (cantidadEnemigos <= 0 || pvPorEnemigo <= 0) {
            throw new IllegalArgumentException("Cantidad de enemigos y PV deben ser positivos");
        }
        this.numero = numero;
        this.cantidadEnemigos = cantidadEnemigos;
        this.pvPorEnemigo = pvPorEnemigo;
    }

    public int getNumero() { return numero; }
    public int getCantidadEnemigos() { return cantidadEnemigos; }
    public int getPvPorEnemigo() { return pvPorEnemigo; }
}
