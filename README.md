# TDA Defensa de Torres

## Descripcion

APE de Estructura de Datos (UTA, Nivel III): simulador simplificado de un
juego de **defensa de torres**. El objetivo pedagogico de la guia (Ape2 -
Listas Secuenciales) es comparar **Pilas y Colas** usando las
clases/interfaces nativas de Java (`Stack`, `Queue` / `LinkedList`), no
construirlas desde cero. El mismo diseno se porto a **C++**
(`std::stack`, `std::queue`).

### Enunciado

CASO DE ESTUDIO: JUEGO DE DEFENSA DE TORRES CON BUSQUEDA DE RUTAS E HISTORIAL DE COMANDOS

Disenar y desarrollar un simulador simplificado de juego de defensa de
torres, donde los jugadores colocan torres para defenderse de oleadas de
enemigos. El juego utilizara colas para gestionar el movimiento del
enemigo a lo largo de una ruta predefinida y pilas para implementar un
sistema de deshacer/rehacer para la colocacion y las mejoras de torres.
Es **obligatorio** que en la implementacion la clase/entidad "Enemigo"
se llame `Cozy`.

Caracteristicas clave:

1. **Logica del juego**
   - Los enemigos tienen puntos de vida (PV) y las torres infligen dano (DD)
     a los enemigos dentro de su alcance.
   - Los enemigos entran en el escenario en un sistema de oleadas.
   - Si un enemigo llega al final de la ruta, el jugador pierde vida.
2. **Movimiento del enemigo**
   - Los enemigos aparecen en oleadas, con dificultad creciente (mas
     enemigos, mayor vida, etc.).
   - Los enemigos siguen una ruta predefinida en el mapa (definida por la
     estrategia de colocacion de las torres).
3. **Colocacion de las torres**
   - El jugador dispone de diversas torres y las coloca de forma
     estrategica para crear una configuracion defensiva.
4. **Interfaz**
   - El enunciado pide mapa, opciones de torres, deshacer/rehacer, vida,
     oleada actual y puntuacion. El equipo lo resolvio con una **demo de
     consola** que muestra esos datos en cada paso.

Estructuras de datos a utilizar:

- **Colas:** movimiento del enemigo a lo largo de la ruta y orden de las oleadas.
- **Pilas:** historial de colocacion de torres para deshacer/rehacer.
- **Listas secuenciales:** variedad de torres colocadas (y, si se quisiera, mapas u oleadas).

A tener en cuenta:

1. Usar una **cola circular** para actualizar el estado de cada enemigo
   (PV) despues de cada quantum de tiempo.
2. Cada enemigo se retira de la cola de rutas si sus PV llegan a cero.
3. Usar una **pila** para el historial de colocaciones:
   - `deshacer` elimina la ultima torre colocada (extrae de la pila).
   - `rehacer` vuelve a aplicar una colocacion previamente deshecha.

> **Nota del enunciado:** para lo que no queda cerrado, cada equipo toma
> sus propias decisiones de diseno. Guia asociada: Ape2, 8 horas
> presenciales. Solo un integrante sube el informe.

### Solucion propuesta

Se crea el TDA `JuegoDefensaTorres`, que administra:

| Estructura | Tipo | Para que sirve |
|---|---|---|
| Lista de torres | `List` / `vector` | torres ya colocadas en el mapa |
| Pila deshacer | `Stack` / `std::stack` | historial de colocaciones |
| Pila rehacer | `Stack` / `std::stack` | colocaciones deshechas, para rehacerlas |
| Cola de oleadas | `Queue` / `std::queue` | orden FIFO de las oleadas |
| Cola de ruta | `Queue` / `std::queue` | `Cozy` que avanzan por la ruta, un quantum a la vez |

El programa tiene estas clases:

| Clase | Responsabilidad |
|---|---|
| `Cozy` | Enemigo (nombre obligatorio del enunciado). PV y posicion en la ruta. |
| `Torre` | Clase abstracta: nombre, alcance, posicion y dano polimorfico. |
| `TorreArquera` | Alcance 4, dano 8. |
| `TorreCanon` | Alcance 1, dano 25. |
| `Oleada` | Numero, cantidad de enemigos y PV de cada uno. |
| `AccionColocarTorre` | Recuerda que torre se colo y en que indice, para deshacer/rehacer. |
| `JuegoDefensaTorres` | TDA: pilas, colas y la simulacion por quanta. |
| `Main` | Escenario de prueba en consola. |

### Modelo de dominio

- **`Cozy`:** aparece en la posicion 0 de una ruta de longitud 10. Recibe
  dano, avanza una casilla por quantum y se retira si muere o si llega al
  final (resta 1 de vida al jugador). Cada baja suma 10 puntos.
- **`Torre` (abstracta):** `enRango(posicionCozy)` y `calcularDano()`.
- **`TorreArquera` / `TorreCanon`:** dos tipos con distinto alcance y dano.
- **`JuegoDefensaTorres`:** vida inicial 20. Cada quantum saca a todos los
  `Cozy` de la cola de ruta, aplica el dano de las torres en rango, y
  reencola a los que siguen vivos y no han llegado al final (cola circular).

### Decisiones de diseno

- El enemigo se llama `Cozy`, no `Enemigo`.
- Dos pilas (deshacer y rehacer). El enunciado habla de "la pila" en
  singular; para rehacer de verdad hacen falta las dos.
- Pilas y colas nativas (`java.util.Stack` y `Queue`/`LinkedList`;
  `std::stack` y `std::queue`). No se reimplementan con arreglo + tope.
- Variedad de torres con herencia y polimorfismo. Un solo tipo de `Cozy`.
- Demo de consola en lugar de interfaz grafica: coloca torres, deshace,
  rehace y corre tres oleadas (la tercera tiene un `Cozy` de 200 PV que
  si llega al final).
- Resultado de referencia de esa demo: vida **19**, puntuacion **70**.

### Conceptos aplicados

| Requisito | Java | C++ |
|---|---|---|
| Pila | `Stack<AccionColocarTorre>` | `std::stack<AccionColocarTorre>` |
| Cola | `Queue` con `LinkedList` | `std::queue` |
| Lista secuencial | `ArrayList<Torre>` | `std::vector<Torre*>` |
| Herencia | `TorreArquera extends Torre` | `class TorreArquera : public Torre` |
| Polimorfismo | `calcularDano()` abstracto con `@Override` | `virtual int calcularDano() const = 0` y `override` |
| Encapsulamiento | atributos `private` / `final` | atributos `private` / `protected` |

## Estructura del proyecto

Arquitectura modular en 3 paquetes/carpetas (Java y C++):

- `modelo/`  -> dominio: `Cozy`, `Torre`, `TorreArquera`, `TorreCanon`, `Oleada`, `AccionColocarTorre`
- `negocio/` -> TDA `JuegoDefensaTorres` (pilas, colas y simulacion)
- `app/`     -> punto de entrada (`Main.java` / `Main.cpp`)

En Java los paquetes son `modelo`, `negocio` y `app`.

## Diagramas

- Diagrama de clases: `diagramas/diagrama-clases.md`
- Diagrama de paquetes: `diagramas/diagrama-paquetes.md`

## Como ejecutar

### Java

Desde la carpeta `Java`:

```bash
# Compilar todas las clases
javac -d bin src/modelo/*.java src/negocio/*.java src/app/*.java

# Ejecutar
java -cp bin app.Main
```

### C++

> **Nota:** Este proyecto no utiliza archivos de cabecera `.h`. Cada clase
> contiene su declaracion e implementacion en su archivo `.cpp` con guardas
> `#ifndef`, incluyendose automaticamente en cadena. Por lo tanto, solo
> debe compilarse `app/Main.cpp`.

Desde la carpeta `CPP`:

```bash
# Compilar
g++ -std=c++17 app/Main.cpp -o programa

# Ejecutar (Linux / macOS)
./programa

# Ejecutar (Windows)
programa.exe
```

Si el compilador es antiguo (por ejemplo Dev-C++ con g++ 4.9.2) y no
acepta `-std=c++17`, usar `-std=c++11`.

## Equipo

| Rol | Integrante |
|---|---|
| Lider | Chico Yunda Juan Carlos |
| Documentacion - Diagramas | Torosina Armendariz Jeremy |
| Documentacion - Informe | Altamirano Segovia Jullisa |
| Backend - Modelo | Romo Núñez Joseph |
| Backend - Negocio | Llamuca Abrajan Andres |
| Frontend - Integracion | Tuza Quinatoa Noemi |
