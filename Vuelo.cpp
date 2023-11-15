//
// Created by Imora on 06/11/2023.
//
#include "Vuelo.h"

//Constructor por defecto de la clase Vuelo.
Vuelo::Vuelo() : _flightNumb(""), _plane(""),
                 _datoMeteo(""), _fecha(Fecha()),
                 airpOrigin(nullptr), airpDestin(nullptr),
                 linkaero(nullptr){

}

//Constructor parametrizado de la clase Vuelo.
Vuelo::Vuelo(std::string flightNumb, std::string plane, std::string datoMeteo, Fecha fecha,
             Aeropuerto *airpOrigin, Aeropuerto *airpDestin, Aerolinea *linkaero) : _flightNumb(flightNumb),
                                                                                    _plane(plane),
                                                                                    _datoMeteo(datoMeteo),
                                                                                    _fecha(fecha),
                                                                                    airpOrigin(airpOrigin),
                                                                                    airpDestin(airpDestin),
                                                                                    linkaero(linkaero){

}

//Constructor de copia de la clase Vuelo.
Vuelo::Vuelo(const Vuelo &orig) : _flightNumb(orig._flightNumb),
                                  _plane(orig._plane),
                                  _datoMeteo(orig._datoMeteo),
                                  _fecha(orig._fecha),
                                  airpOrigin(orig.airpOrigin),
                                  airpDestin(orig.airpDestin),
                                  linkaero(orig.linkaero){

}

//Operador de asignación
Vuelo &Vuelo::operator=(const Vuelo &orig) {
    if(this != &orig){
        this->_flightNumb = orig._flightNumb;
        this->_plane = orig._plane;
        this->_datoMeteo = orig._datoMeteo;
        this->_fecha = orig._fecha;
        this->airpOrigin = orig.airpOrigin;
        this->airpDestin = orig.airpDestin;
        this->linkaero = orig.linkaero;
    }
    return *this;
}

//Destructor de la clase Vuelo.
Vuelo::~Vuelo() {

}


//Getter del atributo 'Flightnumb'.
std::string Vuelo::getFlightNumb(){
    return _flightNumb;
}

//Setter del atributo 'Flightnumb'.
void Vuelo::setFlightNumb(std::string flightNumb){
    _flightNumb = flightNumb;
}


//Getter del atributo 'Plane'.
std::string Vuelo::getPlane(){
    return _plane;
}

//Setter del atributo 'Plane'.
void Vuelo::setPlane(std::string plane){
    _plane = plane;
}


//Getter del atributo 'Datometeo'.
std::string Vuelo::getDatoMeteo(){
    return _datoMeteo;
}

//Setter del atributo 'Datometeo'.
void Vuelo::setDatoMeteo(std::string datoMeteo){
    _datoMeteo = datoMeteo;
}


//Getter del atributo 'Fecha'.
Fecha Vuelo::getFecha(){
    return _fecha;
}

//Setter del atributo 'Fecha'.
void Vuelo::setFecha(Fecha fecha){
    _fecha = fecha;
}


//Getter del atributo 'airpOrigin'.
Aeropuerto* Vuelo::getAeropuertoOrig() {
    return airpOrigin;
}

//Setter del atributo 'airpOrigin'.
void Vuelo::setAirpOrigin(Aeropuerto *airpOrigin){
    Vuelo::airpOrigin = airpOrigin;
}


//Getter del atributo 'airpDestin'.
Aeropuerto* Vuelo::getAeropuertoDest() {
    return airpDestin;
}

//Setter del atributo 'airpDestin'.
void Vuelo::setAirpDestin(Aeropuerto *airpDestin) {
    Vuelo::airpDestin = airpDestin;
}


//Getter del atributo 'linkaero'.
Aerolinea* Vuelo::getAerolinea(){
    return linkaero;
}

//Setter del atributo 'linkaero'.
void Vuelo::setLinkaero(Aerolinea *linkaero){
    Vuelo::linkaero = linkaero;
}


//Operator menor que.
bool Vuelo::operator<(const Vuelo &orig) {
    bool es_menor = false;
    if(_flightNumb < orig._flightNumb){
        es_menor = true;
    }
    return es_menor;
}

//Operator mayor que.
bool Vuelo::operator>(const Vuelo &orig) {
    bool es_mayor = false;
    if (_flightNumb > orig._flightNumb) {
        es_mayor = true;
    }
    return es_mayor;
}

//Operator de comparación.
bool Vuelo::operator==(const Vuelo &orig) {
    bool es_igual = false;
    if (_flightNumb == orig._flightNumb) {
        es_igual = true;
    }
    return es_igual;
}
