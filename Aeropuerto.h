//
// Created by Imora on 02/10/2023.
//
#ifndef CUARTA_PRACTICA_AEROPUERTO_H
#define CUARTA_PRACTICA_AEROPUERTO_H
#include "UTM.h"

class Aeropuerto {
private:
    std::string _id = "";
    std::string _iata = "";
    std::string _tipo = "";
    std::string _nombre = "";
    std::string _continente = "";
    std::string _iso_pais = "";

    UTM _posicion;

public:
    Aeropuerto();
    Aeropuerto(std::string id, std::string iata, std::string tipo, std::string nombre,
               std::string continente, std::string isoPais, UTM posicion);
    Aeropuerto(const Aeropuerto &orig);
    Aeropuerto &operator=(const Aeropuerto &orig);
    ~Aeropuerto();

    std::string getId();
    void setId(std::string id);

    std::string getIata();
    void setIata(std::string iata);

    std::string getTipo();
    void setTipo(std::string tipo);

    std::string getNombre();
    void setNombre(std::string nombre);

    std::string getContinente();
    void setContinente(std::string continente);

    std::string getIsoPais();
    void setIsoPais(std::string isoPais);

    UTM getPosicion();
    void setPosicion(UTM posicion);

    bool operator<(const Aeropuerto &orig);
    bool operator>(const Aeropuerto &orig);
    bool operator==(const Aeropuerto &orig);
};

#endif //CUARTA_PRACTICA_AEROPUERTO_H