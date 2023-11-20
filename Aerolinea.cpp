//
// Created by Imora on 24/10/2023.
//
#include "Aerolinea.h"

//Constructor por defecto de la clase Aerolinea.
Aerolinea::Aerolinea() : _id(0),
                         _icao(""),
                         _nombre(""),
                         _pais(""),
                         _activo(false),
                         aeroroutes(),
                         flights(){

}

//Constructor parametrizado de la clase Aerolinea.
Aerolinea::Aerolinea(unsigned int id, std::string icao, std::string nombre,
                     std::string pais, bool activo) : _id(id),
                                                       _icao(icao),
                                                       _nombre(nombre),
                                                       _pais(pais),
                                                       _activo(activo) {

}

//Constructor de copia de la clase Aerolinea.
Aerolinea::Aerolinea(const Aerolinea &orig) : _id(orig._id),
                                              _icao(orig._icao),
                                              _nombre(orig._nombre),
                                              _pais(orig._pais),
                                              _activo(orig._activo),
                                              aeroroutes(orig.aeroroutes),
                                              flights(orig.flights){

}

//Operador de asignación.
Aerolinea &Aerolinea::operator=(const Aerolinea &orig) {
    if(this != &orig){
        this->_id = orig._id;
        this->_icao = orig._icao;
        this->_nombre = orig._nombre;
        this->_pais = orig._pais;
        this->_activo = orig._activo;
        this->aeroroutes = orig.aeroroutes;
        this->flights = orig.flights;
    }
    return *this;
}

//Destructor de la clase Aerolinea.
Aerolinea::~Aerolinea(){

}


//Getter del atributo 'ID'.
unsigned int Aerolinea::getId() {
    return _id;
}

//Setter del atributo 'ID'.
void Aerolinea::setId(unsigned int id) {
    _id = id;
}


//Getter del atributo 'ICAO'.
std::string Aerolinea::getIcao(){
    return _icao;
}

//Setter del atributo 'ICAO'.
void Aerolinea::setIcao(std::string icao) {
    _icao = icao;
}


//Getter del atributo 'Nombre'.
std::string Aerolinea::getNombre(){
    return _nombre;
}

//Setter del atributo 'Nombre'.
void Aerolinea::setNombre(std::string nombre) {
    _nombre = nombre;
}


//Getter del atributo 'Pais'.
std::string Aerolinea::getPais(){
    return _pais;
}

//Setter del atributo 'Pais'.
void Aerolinea::setPais(std::string pais) {
    _pais = pais;
}


//Getter del atributo 'Activo'.
bool Aerolinea::isActivo(){
    return _activo;
}

//Setter del atributo 'Activo'.
void Aerolinea::setActivo(bool activo) {
    _activo = activo;
}


//Operator menor que.
bool Aerolinea::operator<(const Aerolinea &orig) {
    bool es_menor = false;
    if(_icao < orig._icao){
        es_menor = true;
    }
    return es_menor;
}

//Operator mayor que.
bool Aerolinea::operator>(const Aerolinea &orig) {
    bool es_mayor = false;
    if (_icao > orig._icao) {
        es_mayor = true;
    }
    return es_mayor;
}

//Operator de comparación.
bool Aerolinea::operator==(const Aerolinea &orig) {
    bool es_igual = false;
    if (_icao == orig._icao) {
        es_igual = true;
    }
    return es_igual;
}


//Práctica 3.

/**
 * @brief Método que obtiene todos los aeropuertos de origen de una aerolinea.
 * @return Un vector std::deque de punteros a los aeropuertos de origen de la aerolinea.
 */
std::deque<Aeropuerto*> Aerolinea::getAeropuertosOrig() {
    std::deque<Aeropuerto*> todos_aeropuertos;
    std::map<std::string, Aeropuerto*> aeropuertos_sin_repetir;

    if (this->isActivo()) {
        for (int i = 0; i < this->aeroroutes.size(); i++) {
            std::map<std::string, Aeropuerto *>::iterator Ite;
            Ite = aeropuertos_sin_repetir.find(aeroroutes[i]->getOrigin()->getIata());

            if (Ite == aeropuertos_sin_repetir.end()) {
                std::pair<std::string, Aeropuerto *> nuevo_aeropuerto;
                nuevo_aeropuerto.first = aeroroutes[i]->getOrigin()->getIata();
                nuevo_aeropuerto.second = aeroroutes[i]->getOrigin();
                aeropuertos_sin_repetir.insert(nuevo_aeropuerto);
                todos_aeropuertos.push_back(aeroroutes[i]->getOrigin());
            }
        }
    }
    return todos_aeropuertos;
}

/**
 * @brief Método que obtiene una lista de rutas asociadas a un aeropuerto específico.
 * @param iataAirport El código IATA del aeropuerto para el que se desean obtener rutas.
 * @return Una lista std::list de punteros a Rutas asociadas al aeropuerto especificado.
 */
std::list<Ruta*> Aerolinea::getRutasAeropuerto(std::string iataAirport) {
    std::list<Ruta*> rutas_aeropuerto;

    for (int i = 0; i < this->aeroroutes.size(); i++) {
        if (this->aeroroutes[i]->getOrigin()->getIata() == iataAirport) {
            rutas_aeropuerto.push_back(aeroroutes[i]);
        }
        if (this->aeroroutes[i]->getDestination()->getIata() == iataAirport) {
            rutas_aeropuerto.push_back(aeroroutes[i]);
        }
    }
    return rutas_aeropuerto;
}

/**
 * @brief Método que establece una conexión entre la aerolínea y una ruta.
 * @param r Puntero a la ruta que va a ser vinculada con la aerolinea.
 */
void Aerolinea::linkAerolRuta(Ruta *r) {
    if(r != nullptr){
        this->aeroroutes.push_back(r);
    }
}


//Práctica 4.

/**
 * @brief Método que añade un nuevo vuelo a la aerolinea.
 * @param v El vuelo que se desea añadir a la aerolinea.
 * @return Puntero al nuevo vuelo añadido o en caso de que este mal inicializado nullptr.
 */
Vuelo* Aerolinea::addVuelo(Vuelo &v) {
    if (v.getAeropuertoOrig() != nullptr && v.getAeropuertoDest() != nullptr && v.getAerolinea() != nullptr) {
        std::pair<std::string, Vuelo> p;
        p.first = v.getFlightNumb();
        p.second = v;
        flights.insert(p);

        std::multimap<std::string, Vuelo>::iterator Ite; Ite = flights.find(v.getFlightNumb());
        for (int i = 0; i < flights.count(v.getFlightNumb()) - 1; i++) {
            Ite++;
        }

        for (int i = 0; i < this->aeroroutes.size(); i++) {
            if (Ite->second.getAeropuertoOrig() == aeroroutes[i]->getOrigin()) {
                if (Ite->second.getAeropuertoDest() == aeroroutes[i]->getDestination()) {
                    aeroroutes[i]->addVuelo(Ite->second);
                    break;
                }
            }
        }
        return &(Ite->second);
    } else {
        return nullptr;
    }
}

/**
 * @brief Método que obtiene todos los vuelos con un numero de vuelo especifico.
 * @param fNmbr El número de el vuelo que se desea buscar.
 * @return Un vector std::deque de punteros a los vuelos que tienen el flightNumber especificado.
 */
std::deque<Vuelo*> Aerolinea::getVuelos(std::string fNmbr) {
    std::deque<Vuelo *> vuelos_fNmbr;
    std::multimap<std::string, Vuelo>::iterator Ite; Ite = flights.find(fNmbr);

    if(Ite == flights.end()){
        throw std::out_of_range("[Aerolinea::getVuelos] : La aerolinea no realizo ningun vuelo cuyo flightnumber fuera ese.");
    }

    for (int i = 0; i < flights.count(fNmbr); i++) {
        vuelos_fNmbr.push_back(&Ite->second);
        Ite++;
    }
    return vuelos_fNmbr;
}

/**
 * @brief Método que obtiene todos los vuelos programados dentro de un rango de fechas.
 * @param fIni Fecha de inicio de el rango horario.
 * @param fFin Fecha de fin de el rango horario.
 * @return Una lista std::list de punteros a los vuelos programados dentro de el rango horario.
 */
std::list<Vuelo*> Aerolinea::getVuelos(Fecha fIni, Fecha fFin) {
    std::list<Vuelo*> vuelos_horario;
    std::multimap<std::string, Vuelo>::iterator Ite; Ite = flights.begin();

    for (int i = 0; i < flights.size(); i++) {
        if (fIni <= Ite->second.getFecha() && Ite->second.getFecha() <= fFin) {
            vuelos_horario.push_back(&(Ite->second));
        }
        Ite++;
    }
    return vuelos_horario;
}