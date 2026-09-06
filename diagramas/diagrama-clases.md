# Diagrama de clases - TDA Defensa de Torres

El TDA `JuegoDefensaTorres` administra las torres colocadas, dos pilas de
historial (deshacer/rehacer), una cola de oleadas y una cola circular de
`Cozy` en la ruta. `Torre` es abstracta: las hijas (`TorreArquera` y
`TorreCanon`) definen el dano. `Main` instancia el escenario de prueba.

Vista grafica: `diagramas/diagrama-clases.png`.

```mermaid
classDiagram
    direction TB

    class Cozy {
        -String nombre
        -int pv
        -int posicionEnRuta
        +Cozy(nombre, pvInicial)
        +recibirDano(int) void
        +avanzar() void
        +estaVivo() boolean
        +alcanzoElFinal(int) boolean
    }

    class Torre {
        <<abstract>>
        -String nombre
        -int alcance
        -int posicion
        +Torre(nombre, alcance, posicion)
        +enRango(int) boolean
        +calcularDano()* int
    }

    class TorreArquera {
        -int DANO_BASE 8
        +TorreArquera(nombre, posicion)
        +calcularDano() int
    }

    class TorreCanon {
        -int DANO_BASE 25
        +TorreCanon(nombre, posicion)
        +calcularDano() int
    }

    class Oleada {
        -int numero
        -int cantidadEnemigos
        -int pvPorEnemigo
        +Oleada(numero, cantidadEnemigos, pvPorEnemigo)
    }

    class AccionColocarTorre {
        -Torre torre
        -int indiceEnLista
        +AccionColocarTorre(torre, indiceEnLista)
        +getTorre() Torre
        +getIndiceEnLista() int
    }

    class JuegoDefensaTorres {
        -List~Torre~ torresColocadas
        -Stack~AccionColocarTorre~ historialDeshacer
        -Stack~AccionColocarTorre~ historialRehacer
        -Queue~Oleada~ oleadasPendientes
        -Queue~Cozy~ colaRuta
        -int longitudRuta
        -int vidaJugador
        -int puntuacion
        -int oleadaActual
        +JuegoDefensaTorres(longitudRuta, vidaInicial)
        +colocarTorre(Torre) void
        +deshacerUltimaColocacion() boolean
        +rehacerColocacion() boolean
        +agregarOleada(Oleada) void
        +iniciarSiguienteOleada() boolean
        +avanzarQuantum() void
        +oleadaEnCurso() boolean
    }

    class Main {
        +main(String[]) void
    }

    Torre <|-- TorreArquera : hereda
    Torre <|-- TorreCanon : hereda
    AccionColocarTorre --> Torre : 1
    JuegoDefensaTorres "1" o-- "0..*" Torre : torres colocadas
    JuegoDefensaTorres "1" o-- "0..*" Cozy : cola de ruta
    JuegoDefensaTorres "1" o-- "0..*" Oleada : cola de oleadas
    JuegoDefensaTorres "1" o-- "0..*" AccionColocarTorre : pilas de historial
    Main ..> JuegoDefensaTorres : usa
    Main ..> TorreArquera : instancia
    Main ..> TorreCanon : instancia
    Main ..> Oleada : instancia
```

## Lectura del diagrama

| Relacion | Que representa |
|---|---|
| `Torre <|-- TorreArquera` y `Torre <|-- TorreCanon` | **Herencia.** Las hijas reutilizan nombre, alcance y posicion. |
| `calcularDano()` abstracto en `Torre` | **Polimorfismo.** Cada hija lo sobrescribe (`@Override` / `override`). |
| `JuegoDefensaTorres o-- Torre` | Lista secuencial de torres colocadas. |
| `JuegoDefensaTorres o-- Cozy` | **Cola** circular de enemigos en la ruta. |
| `JuegoDefensaTorres o-- Oleada` | **Cola** FIFO de oleadas pendientes. |
| `JuegoDefensaTorres o-- AccionColocarTorre` | **Pilas** de deshacer y rehacer. |
| `AccionColocarTorre --> Torre` | Cada accion recuerda la torre colocada y su indice. |
| `Main ..> TorreArquera` y `Main ..> TorreCanon` | **Instanciacion.** El escenario de prueba hace `new` de cada tipo. |

## Responsabilidades

| Clase | Paquete / carpeta | Responsabilidad |
|---|---|---|
| `Cozy` | `modelo` | Enemigo: PV, avance por la ruta y retiro al morir o al llegar al final. |
| `Torre` | `modelo` | Clase abstracta con alcance, posicion y dano. |
| `TorreArquera` | `modelo` | Torre de largo alcance (4) y dano 8. |
| `TorreCanon` | `modelo` | Torre de corto alcance (1) y dano 25. |
| `Oleada` | `modelo` | Datos de una oleada (cantidad y PV). |
| `AccionColocarTorre` | `modelo` | Registro de una colocacion para deshacer/rehacer. |
| `JuegoDefensaTorres` | `negocio` | TDA: pilas, colas y simulacion por quanta. |
| `Main` | `app` | Demo de consola: coloca, deshace, rehace y corre oleadas. |
