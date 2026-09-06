package modelo;

public class AccionColocarTorre {
    private final Torre torre;
    private final int indiceEnLista;

    public AccionColocarTorre(Torre torre, int indiceEnLista) {
        this.torre = torre;
        this.indiceEnLista = indiceEnLista;
    }

    public Torre getTorre() { return torre; }
    public int getIndiceEnLista() { return indiceEnLista; }
}
