//
// Created by Imora on 18/10/2023.
//
#include "Ruta.h"

//Constructor por defecto de la clase Ruta.
Ruta::Ruta() : company(nullptr),
               origin(nullptr),
               destination(nullptr),
               flightRoute(){

}

//Constructor parametrizado de la clase Ruta.
Ruta::Ruta(Aerolinea *company, Aeropuerto *origin, Aeropuerto *destination) : company(company),
                                                                              origin(origin),
                                                                              destination(destination) {

}

//Constructor copia de la clase Ruta.
Ruta::Ruta(const Ruta &orig) : company(orig.company),
                               origin(orig.origin),
                               destination(orig.destination),
                               flightRoute(orig.flightRoute){

}

//Operador de asignación.
Ruta &Ruta::operator=(const Ruta &orig) {
    if(this != &orig){
        this->company = orig.company;
        this->origin = orig.origin;
        this->destination = orig.destination;
        this->flightRoute = orig.flightRoute;
    }
    return *this;
}

//Destructor de la clase Ruta.
Ruta::~Ruta() {

}


//Getter del atributo 'Company'.
Aerolinea *Ruta::getCompany(){
    return company;
}

//Setter del atributo 'Company'.
void Ruta::setCompany(Aerolinea *company) {
    Ruta::company = company;
}


//Getter del atributo 'Origen'.
Aeropuerto *Ruta::getOrigin(){
    return origin;
}

//Setter del atributo 'Origen'.
void Ruta::setOrigin(Aeropuerto *origin) {
    Ruta::origin = origin;
}


//Getter del atributo 'Destino'.
Aeropuerto *Ruta::getDestination(){
    return destination;
}

//Setter del atributo 'Destino'.
void Ruta::setDestination(Aeropuerto *destination) {
    Ruta::destination = destination;
}


/**
 * @brief Método que establece una conexión entre la ruta y un vuelo.
 * @param v Puntero a el vuelo que va a ser vinculada con la ruta.
 * @return Si el vuelo se ha añadido correctamente devuelve True, en caso contrario False.
 */
bool Ruta::addVuelo(Vuelo &v) {
    if (origin == v.getAeropuertoOrig()) {
        if (destination == v.getAeropuertoDest()) {
            if (company == v.getAerolinea()) {
                flightRoute.push_back(&v);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Método para conocer el número total de vuelos que tiene una ruta.
 * @return El número de vuelos que tiene la ruta.
 */
int Ruta::getNumVuelos() {
    return flightRoute.size();
}

/**
 * @brief Método que devuelve todos los vuelos que hace esa ruta.
 * @return Una referencia a la lista de vuelos de la ruta.
 */
std::list<Vuelo*> Ruta::getVuelos() {
    std::list<Vuelo*> vuelos_ruta;
    std::list<Vuelo*>::iterator Ite; Ite = flightRoute.begin();

    for (int i = 0; i < flightRoute.size(); i++) {
        vuelos_ruta.push_back(*Ite);
        Ite++;
    }
    return vuelos_ruta;
}