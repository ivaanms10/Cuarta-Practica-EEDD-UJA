//
// Created by Imora on 06/11/2023.
//
#ifndef CUARTA_PRACTICA_VUELO_H
#define CUARTA_PRACTICA_VUELO_H
#include "fecha.h"
#include "Aeropuerto.h"

class Aerolinea;

class Vuelo {
private:
    std::string _flightNumb = "";
    std::string _plane = "";
    std::string _datoMeteo = "";
    Fecha _fecha;

    Aeropuerto *airpOrigin = nullptr;
    Aeropuerto *airpDestin = nullptr;
    Aerolinea *linkaero = nullptr;

public:
    Vuelo();
    Vuelo(std::string flightNumb, std::string plane, std::string datoMeteo, Fecha fecha,
          Aeropuerto *airpOrigin, Aeropuerto *airpDestin, Aerolinea *linkaero);
    Vuelo(const Vuelo &orig);
    Vuelo &operator=(const Vuelo &orig);
    ~Vuelo();

    std::string getFlightNumb();
    void setFlightNumb(std::string flightNumb);

    std::string getPlane();
    void setPlane(std::string plane);

    std::string getDatoMeteo();
    void setDatoMeteo(std::string datoMeteo);

    Fecha getFecha();
    void setFecha(Fecha fecha);

    Aeropuerto* getAeropuertoOrig();
    void setAirpOrigin(Aeropuerto *airpOrigin);

    Aeropuerto* getAeropuertoDest();
    void setAirpDestin(Aeropuerto *airpDestin);

    Aerolinea* getAerolinea();
    void setLinkaero(Aerolinea *linkaero);

    bool operator<(const Vuelo &orig);
    bool operator>(const Vuelo &orig);
    bool operator==(const Vuelo &orig);
};

#endif //CUARTA_PRACTICA_VUELO_H