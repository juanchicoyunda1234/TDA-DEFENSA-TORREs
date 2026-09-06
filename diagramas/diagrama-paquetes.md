# Diagrama de paquetes - TDA Defensa de Torres

Arquitectura en tres capas, igual en Java (`Java/src/`) y en C++ (`CPP/`).
En Java los paquetes se llaman `modelo`, `negocio` y `app`.

```mermaid
flowchart TB
    subgraph app [app]
        Main["Main<br/>escenario de prueba:<br/>colocar, deshacer, rehacer<br/>y simular oleadas"]
    end

    subgraph negocio [negocio]
        Juego["JuegoDefensaTorres<br/>TDA - pilas, colas y quanta"]
    end

    subgraph modelo [modelo]
        Base["Torre<br/>clase abstracta"]
        Arquera["TorreArquera"]
        Canon["TorreCanon"]
        Cozy["Cozy"]
        Oleada["Oleada"]
        Accion["AccionColocarTorre"]
        Arquera --> Base
        Canon --> Base
        Accion --> Base
    end

    Main --> Juego
    Main --> Arquera
    Main --> Canon
    Main --> Oleada
    Juego --> Base
    Juego --> Cozy
    Juego --> Oleada
    Juego --> Accion
```

```mermaid
classDiagram
    direction LR

    namespace modelo {
        class Torre {
            <<abstract>>
        }
        class TorreArquera
        class TorreCanon
        class Cozy
        class Oleada
        class AccionColocarTorre
    }

    namespace negocio {
        class JuegoDefensaTorres
    }

    namespace app {
        class Main
    }

    Torre <|-- TorreArquera
    Torre <|-- TorreCanon
    AccionColocarTorre --> Torre
    JuegoDefensaTorres o-- Torre
    JuegoDefensaTorres o-- Cozy
    JuegoDefensaTorres o-- Oleada
    JuegoDefensaTorres o-- AccionColocarTorre
    Main ..> JuegoDefensaTorres
    Main ..> TorreArquera
    Main ..> TorreCanon
    Main ..> Oleada
```

## Dependencias entre carpetas

| Capa | Contiene | Depende de |
|---|---|---|
| `modelo/` | `Cozy`, `Torre`, `TorreArquera`, `TorreCanon`, `Oleada`, `AccionColocarTorre` | nada |
| `negocio/` | `JuegoDefensaTorres` | `modelo` |
| `app/` | `Main` | `modelo` y `negocio` |

`negocio` trabaja con el tipo `Torre`. El tipo concreto (`TorreArquera` o
`TorreCanon`) lo decide `Main` al instanciar, y el TDA lo trata de forma
polimorfica. La cola de ruta trabaja con `Cozy`; las pilas, con
`AccionColocarTorre`.
