//
// Created by Imora on 18/10/2023.
//
#ifndef CUARTA_PRACTICA_RUTA_H
#define CUARTA_PRACTICA_RUTA_H
#include <list>
#include "Vuelo.h"

class Aerolinea;

class Ruta {
private:
    Aeropuerto *origin = nullptr;
    Aeropuerto *destination = nullptr;
    Aerolinea *company = nullptr;

    std::list<Vuelo*> flightRoute;

public:
    Ruta();
    Ruta(Aerolinea *company, Aeropuerto *origin, Aeropuerto *destination);
    Ruta(const Ruta &orig);
    Ruta &operator=(const Ruta &orig);
    ~Ruta();

    Aerolinea *getCompany();
    void setCompany(Aerolinea *company);

    Aeropuerto *getOrigin();
    void setOrigin(Aeropuerto *origin);

    Aeropuerto *getDestination();
    void setDestination(Aeropuerto *destination);

    bool addVuelo(Vuelo &v);
    int getNumVuelos();
    std::list<Vuelo*> getVuelos();
};

#endif //CUARTA_PRACTICA_RUTA_H