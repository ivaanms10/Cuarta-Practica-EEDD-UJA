//
// Created by Imora on 24/10/2023.
//
#ifndef CUARTA_PRACTICA_AEROLINEA_H
#define CUARTA_PRACTICA_AEROLINEA_H
#include <deque>
#include <map>
#include "Ruta.h"
class Aerolinea {
private:
    unsigned int _id;
    std::string _icao = "";
    std::string _nombre = "";
    std::string _pais = "";
    bool _activo = false;

    std::deque<Ruta*> aeroroutes;
    std::multimap<std::string , Vuelo> flights;

public:
    Aerolinea();
    Aerolinea(unsigned int id, std::string icao, std::string nombre,
              std::string pais, bool activo);
    Aerolinea(const Aerolinea &orig);
    Aerolinea &operator=(const Aerolinea &orig);
    ~Aerolinea();

    unsigned int getId();
    void setId(unsigned int id);

    std::string getIcao();
    void setIcao(std::string icao);

    std::string getNombre();
    void setNombre(std::string nombre);

    std::string getPais();
    void setPais(std::string pais);

    bool isActivo();
    void setActivo(bool activo);

    bool operator<(const Aerolinea &orig);
    bool operator>(const Aerolinea &orig);
    bool operator==(const Aerolinea &orig);

    //Práctica 3.
    std::deque<Aeropuerto*> getAeropuertosOrig();
    std::list<Ruta*> getRutasAeropuerto(std::string iataAirport);
    void linkAerolRuta(Ruta *r);

    //Práctica 4.
    Vuelo* addVuelo(Vuelo &v);
    std::deque<Vuelo*> getVuelos(std::string fNmbr);
    std::list<Vuelo*> getVuelos(Fecha fIni, Fecha fFin);
};

#endif //CUARTA_PRACTICA_AEROLINEA_H