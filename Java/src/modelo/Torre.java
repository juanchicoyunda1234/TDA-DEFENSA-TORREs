package modelo;

public abstract class Torre {
    private final String nombre;
    private final int alcance;
    private final int posicion;

    public Torre(String nombre, int alcance, int posicion) {
        if (nombre == null || nombre.isEmpty()) {
            throw new IllegalArgumentException("El nombre de la torre es obligatorio");
        }
        if (alcance <= 0) {
            throw new IllegalArgumentException("El alcance debe ser positivo");
        }
        if (posicion < 0) {
            throw new IllegalArgumentException("La posicion no puede ser negativa");
        }
        this.nombre = nombre;
        this.alcance = alcance;
        this.posicion = posicion;
    }

    public boolean enRango(int posicionCozy) {
        return Math.abs(posicionCozy - this.posicion) <= this.alcance;
    }

    public abstract int calcularDano();

    public String getNombre() { return nombre; }
    public int getAlcance() { return alcance; }
    public int getPosicion() { return posicion; }

    @Override
    public String toString() {
        return String.format("%s(%s)[pos=%d, alcance=%d, dano=%d]",
                nombre, getClass().getSimpleName(), posicion, alcance, calcularDano());
    }
}
