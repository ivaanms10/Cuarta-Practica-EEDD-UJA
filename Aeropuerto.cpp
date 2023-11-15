//
// Created by Imora on 02/10/2023.
//
#include "Aeropuerto.h"

//Constructor por defecto.
Aeropuerto::Aeropuerto() : _id(""), _iata(""), _tipo(""), _nombre(""),
                           _continente(""), _iso_pais(""), _posicion(UTM()){

}

//Constructor parametrizado.
Aeropuerto::Aeropuerto(std::string id, std::string iata, std::string tipo, std::string nombre,
                       std::string continente, std::string isoPais, UTM posicion) : _id(id),
                                                                                    _iata(iata),
                                                                                    _tipo(tipo),
                                                                                    _nombre(nombre),
                                                                                    _continente(continente),
                                                                                    _iso_pais(isoPais),
                                                                                    _posicion(posicion) {

}

//Constructor de copia.
Aeropuerto::Aeropuerto(const Aeropuerto &orig) : _id(orig._id),
                                                 _iata(orig._iata),
                                                 _tipo(orig._tipo),
                                                 _nombre(orig._nombre),
                                                 _continente(orig._continente),
                                                 _iso_pais(orig._iso_pais),
                                                 _posicion(orig._posicion){

}

//Operador de asignación.
Aeropuerto &Aeropuerto::operator=(const Aeropuerto &orig) {
    if (this != &orig) {
        this->_id = orig._id;
        this->_iata = orig._iata;
        this->_tipo = orig._tipo;
        this->_nombre = orig._nombre;
        this->_continente = orig._continente;
        this->_iso_pais = orig._iso_pais;
        this->_posicion = orig._posicion;
    }
    return *this;
}

//Destructor.
Aeropuerto::~Aeropuerto() {

}


//Getter del atributo 'ID'.
std::string Aeropuerto::getId(){
    return _id;
}

//Setter del atributo 'ID'.
void Aeropuerto::setId(std::string id) {
    _id = id;
}


//Getter del atributo 'IATA'.
std::string Aeropuerto::getIata(){
    return _iata;
}

//Setter del atributo 'IATA'.
void Aeropuerto::setIata(std::string iata) {
    _iata = iata;
}


//Getter del atributo 'Tipo'.
std::string Aeropuerto::getTipo(){
    return _tipo;
}

//Setter del atributo 'Tipo'.
void Aeropuerto::setTipo(std::string tipo) {
    _tipo = tipo;
}


//Getter del atributo 'Nombre'.
std::string Aeropuerto::getNombre(){
    return _nombre;
}

//Setter del atributo 'Nombre'.
void Aeropuerto::setNombre(std::string nombre) {
    _nombre = nombre;
}


//Getter del atributo 'Continente'.
std::string Aeropuerto::getContinente(){
    return _continente;
}

//Setter del atributo 'Continente'.
void Aeropuerto::setContinente(std::string continente) {
    _continente = continente;
}


//Getter del atributo 'IsoPais'.
std::string Aeropuerto::getIsoPais(){
    return _iso_pais;
}

//Setter del atributo 'IsoPais'.
void Aeropuerto::setIsoPais(std::string isoPais) {
    _iso_pais = isoPais;
}


//Getter del atributo 'Posicion'.
UTM Aeropuerto::getPosicion(){
    return _posicion;
}

//Setter del atributo 'Posicion'.
void Aeropuerto::setPosicion(UTM posicion) {
    _posicion = posicion;
}


//Operator menor que.
bool Aeropuerto::operator<(const Aeropuerto &orig) {
    bool es_menor = false;
    if( _iata < orig._iata){
        es_menor = true;
    }
    return es_menor;
}

//Operator mayor que.
bool Aeropuerto::operator>(const Aeropuerto &orig) {
    bool es_mayor = false;
    if( _iata > orig._iata){
        es_mayor = true;
    }
    return es_mayor;
}

//Operator de comparación.
bool Aeropuerto::operator==(const Aeropuerto &orig) {
    bool son_iguales = false;
    if (_iata == orig._iata) {
        son_iguales = true;
    }
    return son_iguales;
}