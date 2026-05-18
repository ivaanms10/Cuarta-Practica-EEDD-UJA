# Práctica 4: Integración de Estructuras de la STL y Gestión de Relaciones Complejas en C++

Este repositorio contiene la entrega de la **Práctica 4** de la asignatura **Estructuras de Datos** del **Grado en Ingeniería en Informática** (Curso 2023/24) en la **Universidad de Jaén**.

## 🎯 Objetivos de la Práctica

* Reemplazar las estructuras de datos de diseño propio desarrolladas en las prácticas anteriores por contenedores optimizados de la biblioteca estándar de C++ (**STL**).
* Aprender a gestionar la **inclusión circular** de clases de objetos mediante el uso correcto de declaraciones adelantadas (*forward declarations*).
* Incorporar la gestión de registros temporales históricos (Vuelos) interconectando múltiples entidades del sistema de manera eficiente y sin redundancia en memoria.

---

## 🛠️ Migración a Contenedores de la STL

En esta fase del proyecto, las estructuras de datos dinámicas personalizadas se sustituyen por los contenedores de la STL que mejor se adaptan a los requisitos de complejidad algorítmica de cada relación:

* **En la clase gestora `VuelaFlight`:**
  * `airports`: Modificado a `std::vector<Aeropuerto>`, manteniendo los elementos ordenados por su código IATA para permitir búsquedas eficientes.
  * `routes`: Modificado a `std::list<Ruta>` para permitir inserciones y borrados eficientes.
  * `airlines`: Implementado como un `std::map<std::string, Aerolinea>` utilizando el código ICAO de 3 letras como clave (*Key*) única.

* **En la clase `Aerolinea`:**
  * `flights`: Implementado como un `std::multimap<std::string, Vuelo>` indexando los históricos de vuelo por su identificador para admitir códigos repetidos en distintas fechas.
  * `aeroroutes`: Almacenado eficientemente mediante un `std::deque<Ruta*>`.

* **En la clase `Ruta`:**
  * `flightRoute`: Colección de referencias a los vuelos comerciales que operan el trayecto mediante un `std::list<Vuelo*>`.

---

## ✈️ Ampliación del Ecosistema: Registro de Vuelos (`Vuelo`)

Se introduce la clase `Vuelo` para almacenar las operaciones reales llevadas a cabo por las aerolíneas. Cada vuelo registra su identificador, el modelo de avión, la fecha del trayecto y las condiciones meteorológicas asociadas.

### 🔄 Gestión de Inclusión Circular

Debido a la interdependencia mutua entre las clases `Aerolinea` y `Vuelo` (una aerolínea gestiona múltiples vuelos y un vuelo conoce a la aerolínea que lo opera), se aplican directivas de compilación limpia utilizando **declaraciones adelantadas** (`class Vuelo;`) en las cabeceras para evitar problemas en la inclusión condicional.

### Carga y Vinculación Lógica del Sistema

El sistema realiza una lectura integral desde el archivo `vuelos_vl.csv` invocando al método `VuelaFlight::cargarVuelos()`. Por cada registro:

1. Se extrae la aerolínea a través de los tres primeros caracteres del número de vuelo (ej. *AEA5201* pertenece a *AirEuropa, AEA*).
2. Se construyen los objetos inicializando sus punteros correspondientes a `Aeropuerto` (origen/destino) y `Aerolinea`.
3. Al insertarse en la aerolínea mediante `Aerolinea::addVuelo()`, si este coincide con una ruta comercial existente de la compañía, se indexa automáticamente y de forma recíproca dentro de `Ruta::flightRoute`.

---

## ⚙️ Nuevas Funcionalidades del Negocio

Siguiendo la política del proyecto, **ningún método realiza copias innecesarias de objetos en memoria**, retornando siempre punteros o referencias directas:

* **Clase `Aerolinea`:**
  * `addVuelo(Vuelo v)`: Añade una copia del vuelo inicializado. Valida la integridad de los datos y retorna su dirección de memoria en el contenedor.
  * `getVuelos(String fNumber)`: Emplea `multimap::find` e iteradores para recuperar eficientemente todos los vuelos con el mismo identificador.
  * `getVuelos(Fecha fIni, Fecha fFin)`: Filtra y extrae vuelos dentro de un rango cronológico determinado.

* **Clase `Ruta`:**
  * `addVuelo(Vuelo v)`: Verifica que la aerolínea y aeropuertos coincidan plenamente con el trayecto de la ruta antes de insertarlo.

* **Clase Gestora `VuelaFlight`:**
  * `registrarVuelo(...)`: Construye, valida lógicamente y procesa el alta de un vuelo.
  * `vuelosOperadosPor(String icaoAerol, Fecha f)`: Obtiene los vuelos de una aerolínea específica para una fecha concreta.
  * `buscaVuelosDestAerop(String paisOrig, String iataAeroDest)`: Localiza vuelos únicos con destino a un aeropuerto específico partiendo desde cualquier terminal de un país de origen. Hace uso interno de un `std::set` para purgar duplicados de forma nativa.

---

## 🧪 Casos de Prueba del Programa Principal

El nuevo programa de prueba valida el rendimiento de la STL y la lógica de interconexión resolviendo los siguientes supuestos por pantalla:

1. **Adaptación de la Práctica 3:** Inicializar todos los componentes del sistema (`VuelaFlight`) migrados a contenedores STL cargando los archivos CSV correspondientes.

2. **Auditoría de Vuelos Específicos:** Localizar los vuelos `AEA5201` y `VLG2021` e imprimir:
   * Información extendida de la aerolínea operadora (nombre y país).
   * Códigos IATA de los aeropuertos origen y destino.
   * Fechas e informes meteorológicos de aquellos días en los que el trayecto se efectuó bajo condiciones de **lluvia o chubascos**.

3. **Flota Operativa por Fecha:** Mostrar de forma unívoca (sin repeticiones) los modelos de aviones utilizados por la compañía Vueling (`VLG`) exactamente el día `13/4/2018`.

4. **Búsqueda Internacional de Rutas:** Mostrar los identificadores únicos de vuelo que tienen como destino la ciudad de Londres (`LHR`, `STN`, `LTN`, `LGW`) despegando desde cualquier aeropuerto de España (`ES`).

5. **(Modalidad por Parejas):** Implementar y verificar el método `VuelaFlight::buscaAeropuertosAerolinea(icaoAerolinea)` imprimiendo ordenadamente y sin duplicados las ciudades donde opera activamente la aerolínea Iberojet (`EVE`).

---

## ⚙️ Requisitos de Estilo y Calidad

* **Formateo Estricto:** Código limpio con niveles de indentación profesional según los estándares establecidos para C++.
* **Gestión de Excepciones:** Robustez total frente a desbordamientos, lecturas de ficheros corruptos o parámetros nulos mediante capturas estructuradas.
* **Eficiencia STL:** Uso correcto de funciones miembro nativas de los contenedores (`find`, `lower_bound`, etc.) evitando búsquedas lineales costosas de complejidad $O(n)$ donde sea posible.
