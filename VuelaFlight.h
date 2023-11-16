//
// Created by Imora on 18/10/2023.
//
#ifndef CUARTA_PRACTICA_VUELAFLIGHT_H
#define CUARTA_PRACTICA_VUELAFLIGHT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include "Aerolinea.h"

class VuelaFlight {
private:
    std::vector<Aeropuerto> airports;
    std::list<Ruta> routes;
    std::map<std::string , Aerolinea> airlines;

    void cargarAeropuertos(std::string fichAeropuertos);
    void cargarAerolineas(std::string fichAerolineas);
    void cargarRutas(std::string fichRutas);
    void cargarVuelos(std::string fichVuelos);

    Aeropuerto* busquedaBinAeropuerto(const Aeropuerto &dato);
    void ordenarAeropuertos(){ std::sort(airports.begin(),airports.end()); }

public:
    VuelaFlight();
    VuelaFlight(std::string archivo_aeropuerto, std::string archivo_aerolinea, std::string archivo_ruta, std::string archivo_vuelo);
    VuelaFlight(const VuelaFlight &orig);
    VuelaFlight &operator=(const VuelaFlight &orig);
    ~VuelaFlight();

    //Práctica 2.
    Ruta* buscarRutasOriDes(std::string idAerOrig, std::string idAerDest);
    std::deque<Ruta*> buscarRutasOrigen(std::string idAerOrig);
    std::deque<Aeropuerto*> buscarAeropuertoPais(std::string pais);

    //Práctica 3.
    Aerolinea* buscaAerolinea(std::string icaoAerolinea);
    std::list<Aerolinea*> buscaAerolineaActiva();
    std::list<Aerolinea*> getAerolineasPais(std::string idPais);

    //Práctica 4.
    std::deque<Vuelo*> buscaVuelos(std::string fNumber);
    std::list<Vuelo*> vuelosOperadosPor(std::string icaoAerolinea, Fecha f);
    std::set<std::string> buscaVuelosDestAerop(std::string paisOrig, std::string iataAeroDest);

    //Cargar datos.
    void addNuevoAeropuerto(std::string id, std::string iata, std::string tipo, std::string nombre,
                            std::string continente, std::string isoPais, UTM posicion);
    void addNuevaAerolinea(int id, std::string icao, std::string nombre, std::string pais, bool activo);
    void addNuevaRuta(std::string idAerOrig, std::string idAerDest, std::string compani);
    bool registrarVuelo(std::string fNumber, std::string iataAeroOrig, std::string iataAeroDest,
                        std::string plane, std::string datosMeteo, Fecha f);
};

#endif //CUARTA_PRACTICA_VUELAFLIGHT_H