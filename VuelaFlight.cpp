//
// Created by Imora on 18/10/2023.
//
#include "VuelaFlight.h"

//Constructor por defecto de la clase VuelaFlight.
VuelaFlight::VuelaFlight() : airports(),
                             routes(),
                             airlines(){

}

//Constructor parametrizado de la clase VuelaFlight.
VuelaFlight::VuelaFlight(std::string archivo_aeropuerto, std::string archivo_aerolinea, std::string archivo_ruta, std::string archivo_vuelo){
    cargarAeropuertos(archivo_aeropuerto);
    ordenarAeropuertos();
    cargarAerolineas(archivo_aerolinea);
    cargarRutas(archivo_ruta);
    cargarVuelos(archivo_vuelo);
}

//Constructor de copia de la clase VuelaFlight.
VuelaFlight::VuelaFlight(const VuelaFlight &orig) : airports(orig.airports),
                                                    routes(orig.routes),
                                                    airlines(orig.airlines){

}

//Operador de asignación.
VuelaFlight &VuelaFlight::operator=(const VuelaFlight &orig) {
    if(this != &orig){
        this->airports = orig.airports;
        this->routes = orig.routes;
        this->airlines = orig.airlines;
    }
    return *this;
}

//Destructor de la clase VuelaFlight.
VuelaFlight::~VuelaFlight() {

}


//Práctica 2.

/**
 * @brief Metodo para buscar una ruta con un aeropuerto de origen y destino específicos.
 * @param idAerOrig Identificador del aeropuerto de origen que se desea buscar.
 * @param idAerDest Identificador del aeropuerto de destino que se desea buscar.
 * @throw std::out_of_range Si no se ha encontrado ninguna ruta con el aeropuerto de origen y destino.
 * @return Una referencia a la ruta que coincide con los aeropuertos de origen y destino.
 */
Ruta* VuelaFlight::buscarRutasOriDes(std::string idAerOrig, std::string idAerDest) {
    std::list<Ruta>::iterator Ite; Ite = routes.begin();

    for (int i = 0; i < routes.size(); i++) {
        if (idAerOrig == Ite->getOrigin()->getIata()) {
            if (idAerDest == Ite->getDestination()->getIata()) {
                return &(*Ite);
            }
        }
        Ite++;
    }
    return nullptr;
}

/**
 *@brief Metodo para buscar todas las rutas con un origen especifico.
 * @param idAerOrig Identificador del aeropuerto de origen que se desea buscar.
 * @return Una lista de punteros a objetos de tipo Ruta que coincide con el aeropuerto de origen.
 */
std::deque<Ruta*> VuelaFlight::buscarRutasOrigen(std::string idAerOrig) {
    std::list<Ruta>::iterator Ite; Ite = routes.begin();
    std::deque<Ruta*> Rutas_Origen;

    for (int i = 0; i < routes.size(); ++i) {
        if (idAerOrig == Ite->getOrigin()->getIata()) {
            Rutas_Origen.push_back(&(*Ite));
        }
        Ite++;
    }
    return Rutas_Origen;
}

/**
 * @brief Metodo para conocer todos los aeropuertos de un pais.
 * @param pais Nombre del pais del que se quiere conocer los aeropuertos.
 * @return Referencia al vector de paises cuyo nombre de pais coincide con el buscado.
 */
std::deque<Aeropuerto*> VuelaFlight::buscarAeropuertoPais(std::string pais) {
    std::deque<Aeropuerto*> Aeropuertos_pais;

    for (int i = 0; i < this->airports.size(); ++i) {
        if (airports[i].getIsoPais() == pais) {
            Aeropuertos_pais.push_back(&airports[i]);
        }
    }
    return Aeropuertos_pais;
}


//Práctica 3.

/**
 * @brief Método para buscar una aerolinea por su codigo ICAO.
 * @param icaoAerolinea Código ICAO de la aerolinea que se desea buscar.
 * @return Una referencia a la aerolínea encontrada, si no se ha encontrado se devuelve una referencia nula.
 */
 Aerolinea* VuelaFlight::buscaAerolinea(std::string icaoAerolinea) {
    std::map<std::string, Aerolinea>::iterator Ite;
    Ite = airlines.find(icaoAerolinea);

    if (Ite != airlines.end()) {
        return &(Ite->second);
    } else {
        return nullptr;
    }
}

/**
 * @brief Método que encuentra todas las aerolineas que estan activas actualmente.
 * @return Vector dinámico de punteros a las aerolineas activas.
 */
std::deque<Aerolinea*> VuelaFlight::buscaAerolineaActiva() {
    std::deque<Aerolinea*> aerolineas_activas;
    std::map<std::string, Aerolinea>::iterator Ite; Ite = airlines.begin();

    for (int i = 0; i < airlines.size(); i++) {
        if (Ite->second.isActivo()) {
            aerolineas_activas.push_back(&(Ite->second));
        }
        Ite++;
    }
    return aerolineas_activas;
}

/**
 * @brief Método que obtiene todas las aerolineas que operan en un país especifico.
 * @param idPais Nombre del país del que se desea obtener las aerolineas.
 * @return Vector dinamico de punteros a las aerolineas que operan en ese país.
 */
std::list<Aerolinea*> VuelaFlight::getAerolineasPais(std::string idPais) {
    std::list<Aerolinea*> aerolineas_pais;
    std::map<std::string, Aerolinea>::iterator Ite; Ite = airlines.begin();

    for (int i = 0; i < airlines.size(); ++i) {
        if (Ite->second.getPais() == idPais) {
            aerolineas_pais.push_back(&Ite->second);
        }
        Ite++;
    }
    if (aerolineas_pais.empty()) {
        throw std::out_of_range("[VuelaFlight::getAerolineasPais]: El pais que ha pasado por parametro no existe.");
    } else {
        return aerolineas_pais;
    }
}


//Práctica 4.

/**
 * @brief Método que busca los vuelos que tienen el flightNumber proporcionado.
 * @param fNumber Número de el vuelo que se desea buscar.
 * @return Un vector deque de punteros a vuelos que coinciden con el número de vuelo proporcionado.
 */
std::deque<Vuelo*> VuelaFlight::buscaVuelos(std::string fNumber) {
    std::string ICAO = ""; ICAO = ICAO + fNumber[0] + fNumber[1] + fNumber[2];

    Aerolinea *aerolinea = buscaAerolinea(ICAO);
    if (aerolinea == nullptr) {
        throw std::out_of_range("[VuelaFlight::buscaVuelos] : La aerolinea no se ha encontrado, por tanto no hay ningun vuelo.");
    }

    std::deque<Vuelo*> vuelos_identificador;
    vuelos_identificador = aerolinea->getVuelos(fNumber);
    return vuelos_identificador;
}

/**
 * @brief Método que obtiene los vuelos operados por una aerolínea en una fecha específica.
 * @param icaoAerolinea Código ICAO de la aerolinea que se desea buscar.
 * @param f Fecha para la cual se buscan los vuelos operados.
 * @return Un mapa donde tiene una clave y un puntero al objeto vuelo correspondiente.
 */
std::list<Vuelo*> VuelaFlight::vuelosOperadosPor(std::string icaoAerolinea, Fecha f) {
    Aerolinea *aerolinea = buscaAerolinea(icaoAerolinea);
    if (aerolinea == nullptr) {
        throw std::out_of_range(
                "[VuelaFlight::vuelosoperadosPor] : La aerolinea que intenta buscar no existe.");
    }

    std::list<Vuelo*> vuelos_fecha = aerolinea->getVuelos(f,f);
    return vuelos_fecha;
}


/**
 * @brief Método que busca vuelos hacia un aeropuerto específico desde un país de origen.
 * @param paisOrig El país de origen de los vuelos a buscar.
 * @param iataAeroDest El código IATA del aeropuerto de destino.
 * @return Un std::set con los flightNumbers de los vuelos que cumplen los requisitos.
 * @note Primero obtenemos todos los aeropuertos que hay en España. Segundo obtengo todas las rutas donde
 *       el aeropuerto de origen es uno de los anteriores. Tercero obtengo de las rutas anteriores aquellas
 *       cuyo aeropuerto de destino es el parametro iataAeroDest. Cuarto obtengo todos los vuelos de la
 *       ruta cuyo aeropuerto de origen es uno de España y el de destino es el parametro. Quinto se inserta
 *       en el set el flightNumber de los vuelos.
 */
std::set<std::string> VuelaFlight::buscaVuelosDestAerop(std::string paisOrig, std::string iataAeroDest) {
    std::set<std::string> flightNumbers;
    std::deque<Aeropuerto *> aeropuertos_pais = buscarAeropuertoPais(paisOrig);

    for (int i = 0; i < aeropuertos_pais.size(); i++) {
        std::deque<Ruta *> rutas_aeropuerto_orig = buscarRutasOrigen(aeropuertos_pais[i]->getIata());
        if (!rutas_aeropuerto_orig.empty()) {
            std::deque<Ruta *> rutas_espania_londres;
            for (int z = 0; z < rutas_aeropuerto_orig.size(); z++) {
                if (rutas_aeropuerto_orig[z]->getDestination()->getIata() == iataAeroDest) {
                    rutas_espania_londres.push_back(rutas_aeropuerto_orig[z]);
                }
            }

            if (!rutas_espania_londres.empty()) {
                for (int j = 0; j < rutas_espania_londres.size(); j++) {
                    std::list<Vuelo *> vuelos_ruta = rutas_espania_londres[j]->getVuelos();
                    if (!vuelos_ruta.empty()) {
                        std::list<Vuelo *>::iterator Ite; Ite = vuelos_ruta.begin();
                        for (int m = 0; m < vuelos_ruta.size(); m++) {
                            flightNumbers.insert((*Ite)->getFlightNumb());
                            Ite++;
                        }
                    }
                }
            }
        }
    }
    return flightNumbers;
}


//Cargar datos.

/**
 * @brief Metodo para añadir un nuevo aeropuerto al vector de aeropuertos.
 * @param id Identificación del aeropuerto.
 * @param iata Codigo IATA del aeropuerto.
 * @param tipo Tipo del aeropuerto.
 * @param nombre Nombre del aeropuerto.
 * @param continente Continente en el que se encuentra el aeropuerto.
 * @param isoPais Codigo ISO del pais al que pertenece el aeropuerto.
 * @param posicion Posicion del aeropuerto en el sistema de coordenadas UTM.
 */
void VuelaFlight::addNuevoAeropuerto(std::string id, std::string iata, std::string tipo, std::string nombre,
                                     std::string continente, std::string isoPais, UTM posicion) {
    Aeropuerto aeropuerto1(id, iata, tipo, nombre, continente, isoPais, posicion);
    airports.push_back(aeropuerto1);
}

/**
 * @brief Metodo para añadir una nueva aerolínea al árbol de aerolineas.
 * @param id Identificación de la aerolínea.
 * @param icao Codigo ICAO de la aerolínea.
 * @param nombre Nombre de la aerolínea.
 * @param pais País de origen de la aerolínea.
 * @param activo Indica si la aerolínea está activa o inactiva
 */
void VuelaFlight::addNuevaAerolinea(int id, std::string icao, std::string nombre, std::string pais, bool activo) {
    Aerolinea aerolinea1(id,icao,nombre,pais,activo);

    std::pair<std::string , Aerolinea> nueva_aerolinea;
    nueva_aerolinea.first = icao;
    nueva_aerolinea.second = aerolinea1;

    airlines.insert(nueva_aerolinea);
}

/**
 *@brief Metodo para aniadir una nueva Ruta a la lista de rutas.
 * @param idAerOrig IATA del aeropuerto donde tiene origen el vuelo.
 * @param idAerDest IATA del aeropuerto donde tiene destino el vuelo.
 * @param compani ICAO de la aerolinea.
 */
void VuelaFlight::addNuevaRuta(std::string idAerOrig, std::string idAerDest, std::string compani) {
    std::vector<Aeropuerto> buscar_aeropuerto(2);
    buscar_aeropuerto[0].setIata(idAerOrig);
    buscar_aeropuerto[1].setIata(idAerDest);

    Aeropuerto *aeropuerto_origen = busquedaBinAeropuerto(buscar_aeropuerto[0]);
    Aeropuerto *aeropuerto_destino = busquedaBinAeropuerto(buscar_aeropuerto[1]);
    Aerolinea *aerolinea_company = buscaAerolinea(compani);

    if (aerolinea_company == nullptr || aeropuerto_origen == nullptr || aeropuerto_destino == nullptr) {
        throw std::out_of_range(
                "[VuelaFlight::addNuevaRuta]: No se ha podido insertar la ruta ya que los aeropuertos o la aerolinea no es correcta.");
    }

    Ruta ruta1(aerolinea_company, aeropuerto_origen, aeropuerto_destino);
    routes.push_back(ruta1);

    std::list<Ruta>::iterator Ite2; Ite2 = routes.end(); Ite2--;
    aerolinea_company->linkAerolRuta(&(*Ite2));
}

/**
 * @brief Metodo para añadir una nuevo Vuelo.
 * @param fNumber Número del vuelo que se va a añadir.
 * @param iataAeroOrig IATA del aeropuerto donde tiene origen el vuelo.
 * @param iataAeroDest IATA del aeropuerto donde tiene origen el vuelo.
 * @param plane Modelo del avión que se usa para el vuelo.
 * @param datosMeteo Información metereologica relacionada con el vuelo.
 * @param f Fecha en la que se produjo el vuelo.
 * @return True si el vuelo se ha añadido correctamente, False en caso contrario.
 */
bool VuelaFlight::registrarVuelo(std::string fNumber, std::string iataAeroOrig, std::string iataAeroDest,
                                 std::string plane, std::string datosMeteo, Fecha f) {
    std::vector<Aeropuerto> buscar_aeropuerto(2);
    buscar_aeropuerto[0].setIata(iataAeroOrig);
    buscar_aeropuerto[1].setIata(iataAeroDest);
    std::string ICAO = ""; ICAO = ICAO + fNumber[0] + fNumber[1] + fNumber[2];

    Aeropuerto *aeropuerto_origen = busquedaBinAeropuerto(buscar_aeropuerto[0]);
    Aeropuerto *aeropuerto_destino = busquedaBinAeropuerto(buscar_aeropuerto[1]);
    Aerolinea *aerolinea = buscaAerolinea(ICAO);

    if (aeropuerto_origen == nullptr || aeropuerto_destino == nullptr || aerolinea == nullptr) {
        return false;
    }

    Vuelo vuelo1(fNumber, plane, datosMeteo, f, aeropuerto_origen, aeropuerto_destino, aerolinea);
    if (aerolinea->addVuelo(vuelo1) != nullptr) {
        return true;
    } else {
        return false;
    };
}


//Métodos privados.

void VuelaFlight::cargarAeropuertos(std::string fichAeropuertos) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "", iata = "", tipo = "", nombre = "", latitud_str = "", longitud_str = "", continente = "", iso_pais = "";
    float latitud = 0, longitud = 0;

    is.open(fichAeropuertos);
    if (is.good()) {

        while (getline(is, fila)) {

            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id, ';');
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');

                latitud = std::stof(latitud_str);
                longitud = std::stof(longitud_str);

                fila = "";
                columnas.clear();
                try {
                    UTM utm1;
                    utm1.setLatitud(latitud);
                    utm1.setLongitud(longitud);
                    addNuevoAeropuerto(id, iata, tipo, nombre, continente, iso_pais, utm1);
                } catch (std::out_of_range &e) {
                    throw e;
                }
            }
        }
        is.close();
    }
}

void VuelaFlight::cargarAerolineas(std::string fichAerolineas) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string id = "", icao = "", nombre = "", pais = "", activo = "";
    int _id = 0;

    is.open(fichAerolineas);
    if (is.good()) {

        while (getline(is, fila)) {
            bool _activo = false;
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id, ';');
                getline(columnas, icao, ';');
                getline(columnas, nombre, ';');
                getline(columnas, pais, ';');
                getline(columnas, activo, ';');

                _id = std::stoi(id);
                if (activo == "Y") {
                    _activo = true;
                }

                fila = "";
                columnas.clear();
                try {
                    addNuevaAerolinea(_id, icao, nombre, pais, _activo);
                } catch (std::out_of_range &e) {
                    throw e;
                }
            }
        }
        is.close();
    }
}

void VuelaFlight::cargarRutas(std::string fichRutas) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string company = "", AerOrigen = "", AerDestino = "";

    is.open(fichRutas);
    if (is.good()) {

        while (getline(is, fila)) {

            if (fila != "") {

                columnas.str(fila);

                getline(columnas, company, ';');
                getline(columnas, AerOrigen, ';');
                getline(columnas, AerDestino, ';');

                fila = "";
                columnas.clear();
                try {
                    addNuevaRuta(AerOrigen, AerDestino, company);
                } catch (std::out_of_range &e) {
                    throw e;
                }
            }
        }
        is.close();
    }
}

void VuelaFlight::cargarVuelos(std::string fichVuelos) {
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;

    std::string flightNumber = "", dep_airport_code = "", arr_airport_code = "", _plane = "", dep_weather_desc = "", dep_date = "";
    is.open(fichVuelos);
    if (is.good()) {

        while (getline(is, fila)) {

            if (fila != "") {

                columnas.str(fila);

                getline(columnas, flightNumber, ';');
                getline(columnas, dep_airport_code, ';');
                getline(columnas, arr_airport_code, ';');
                getline(columnas, _plane, ';');
                getline(columnas, dep_weather_desc, ';');
                getline(columnas, dep_date, ';');

                fila = "";
                columnas.clear();
                try {
                    std::string _dia = ""; _dia = _dia + dep_date[0] + dep_date[1];
                    std::string _mes = ""; _mes = _mes + dep_date[3] + dep_date[4];
                    std::string _anio = ""; _anio = _anio + dep_date[6] + dep_date[7];

                    int dia = stoi(_dia);
                    int mes = stoi(_mes);
                    int anio = stoi(_anio);

                    Fecha fecha; fecha.asignarDia(dia, mes, anio);
                    registrarVuelo(flightNumber, dep_airport_code, arr_airport_code, _plane, dep_weather_desc, fecha);
                } catch (std::out_of_range &e) {
                    throw e;
                }
            }
        }
        is.close();
    }
}

/**
 * @brief Metodo para buscar un aeropuerto dentro de el vector de forma logaritmica.
 * @param dato Aeropuerto que deseamos buscar entre todos los aeropuertos del vector.
 * @return Posicion en la que se encuentra el aeropuerto dentro del vector.
 */
Aeropuerto* VuelaFlight::busquedaBinAeropuerto(const Aeropuerto &dato) {
    int inferior = 0;
    int superior = airports.size() - 1;
    int aux = 0;
    while (inferior <= superior) {
        aux = (inferior + superior) / 2;
        if (airports[aux] == dato) {
            return &(airports[aux]);
        } else if (airports[aux] < dato) {
            inferior = aux + 1;
        } else {
            superior = aux - 1;
        }
    }
    return nullptr;
}