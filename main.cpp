#include <iostream>
#include "VuelaFlight.h"

/**
 * @author Iván Morales Sánchez ims00051@red.ujaen.es
 */
int main(int argc, const char * argv[]) {
    std::string archivo_aeropuertos = "../aeropuertos_v2.csv";
    std::string archivo_rutas = "../rutas_v1.csv";
    std::string archivo_aerolineas = "../aerolineas_v1.csv";
    std::string archivo_vuelos = "../infovuelos_v1.csv";

//1.- Instanciar la clase VuelaFlight según el diseño UML cargando correctamente los aeropuertos,
// aerolineas, rutas y vuelos como se ha descrito anteriormente.
    clock_t t_ini1 = clock();

    VuelaFlight vuelaFlight(archivo_aeropuertos, archivo_aerolineas, archivo_rutas, archivo_vuelos);
    Aerolinea *baw = vuelaFlight.buscaAerolinea("BAW");
    std::cout << "El tiempo que tarda en cargar todos los aeropuertos, aerolineas, rutas  y vuelos es: "
              << ((clock() - t_ini1) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

//2.- Para los vuelos con identificador de vuelo AEA5201 y VLG2021, si existen, mostrar:
//       *Datos de la aerolínea que los opera ( nombre completo y país al que pertenece) e iata de los
//       aeropuertos de origen, destino.
//       * Listado con todas las fechas y estado del tiempo en las que se ha efectuado en condiciones
//       de lluvia o chubascos
    clock_t t_ini2 = clock();

    std::deque<Vuelo *> vuelos_lluvia_AEA;
    std::deque<Vuelo *> vuelos_chubascos_AEA;

    try {
        std::deque<Vuelo *> vuelos_AEA5201 = vuelaFlight.buscaVuelos("AEA5201");
        std::cout << std::endl << "Informacion de la aerolinea que realiza los vuelos con el Flightnumber: "
                  << vuelos_AEA5201[0]->getFlightNumb() << std::endl;
        std::cout << "  ** ICAO de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getIcao() << std::endl;
        std::cout << "  ** Nombre de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getNombre() << std::endl;
        std::cout << "  ** Pais de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getPais() << std::endl;
        std::cout << "  ** IATA aeropuerto origen: " << vuelos_AEA5201[0]->getAeropuertoOrig()->getIata()
                  << std::endl;
        std::cout << "  ** IATA aeropuerto destino: " << vuelos_AEA5201[0]->getAeropuertoDest()->getIata()
                  << std::endl;

        for (int i = 0; i < vuelos_AEA5201.size(); i++) {
            std::string dato_vuelo = "";
            for (int j = 0; j < (vuelos_AEA5201[i]->getDatoMeteo()).length() && vuelos_AEA5201[i]->getDatoMeteo()[j] != ' '; j++) {
                dato_vuelo = dato_vuelo + vuelos_AEA5201[i]->getDatoMeteo()[j];
            }
            if (dato_vuelo == "Lluvia") {
                vuelos_lluvia_AEA.push_back(vuelos_AEA5201[i]);
            }
            if (dato_vuelo == "Chubascos") {
                vuelos_chubascos_AEA.push_back(vuelos_AEA5201[i]);
            }
        }

        std::cout << std::endl << "El vuelo con el Flightnumber '" << vuelos_AEA5201[0]->getFlightNumb()
                  << "' ha realizado " << vuelos_lluvia_AEA.size() << " vuelos en condiciones de lluvia."
                  << std::endl;
        if (!vuelos_lluvia_AEA.empty()) {
            for (int i = 0; i < vuelos_lluvia_AEA.size(); i++) {
                std::cout << i + 1 << " vuelo: " << vuelos_lluvia_AEA[i]->getFecha().verDia() << "/"
                          << vuelos_lluvia_AEA[i]->getFecha().verMes() << "/"
                          << vuelos_lluvia_AEA[i]->getFecha().verAnio()
                          << " y las condiciones eran: " << vuelos_lluvia_AEA[i]->getDatoMeteo() << std::endl;
            }
        }

        std::cout << std::endl << "El vuelo con el Flightnumber '" << vuelos_AEA5201[0]->getFlightNumb()
                  << "' ha realizado " << vuelos_chubascos_AEA.size() << " vuelos en condiciones de chubascos."
                  << std::endl;
        if (!vuelos_chubascos_AEA.empty()) {
            for (int i = 0; i < vuelos_chubascos_AEA.size(); i++) {
                std::cout << i + 1 << " vuelo: " << vuelos_chubascos_AEA[i]->getFecha().verDia() << "/"
                          << vuelos_chubascos_AEA[i]->getFecha().verMes() << "/"
                          << vuelos_chubascos_AEA[i]->getFecha().verAnio() << " y las condiciones eran: "
                          << vuelos_chubascos_AEA[i]->getDatoMeteo() << std::endl;
            }
        }
    } catch (std::out_of_range &e) {
        std::cout << std::endl << "ERROR: " << e.what() << std::endl;
    }

    std::cout
            << "Tiempo que tarda en mostrar la informacion de la aerolinea y el tiempo que hacia en los vuelos 'AEA5201' es: "
            << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs" << std::endl;

    clock_t t_ini3 = clock();

    std::deque<Vuelo *> vuelos_lluvia_VLG;
    std::deque<Vuelo *> vuelos_chubascos_VLG;

    try {
        std::deque<Vuelo *> vuelos_VLG2021 = vuelaFlight.buscaVuelos("VLG2021");
        std::cout << std::endl << "Informacion de la aerolinea que realiza los vuelos con el Flightnumber: "
                  << vuelos_VLG2021[0]->getFlightNumb() << std::endl;
        std::cout << "  ** ICAO de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getIcao() << std::endl;
        std::cout << "  ** Nombre de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getNombre() << std::endl;
        std::cout << "  ** Pais de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getPais() << std::endl;
        std::cout << "  ** IATA aeropuerto origen: " << vuelos_VLG2021[0]->getAeropuertoOrig()->getIata()
                  << std::endl;
        std::cout << "  ** IATA aeropuerto destino: " << vuelos_VLG2021[0]->getAeropuertoDest()->getIata()
                  << std::endl;

        for (int i = 0; i < vuelos_VLG2021.size(); i++) {
            std::string dato_vuelo = "";
            for (int j = 0; j < (vuelos_VLG2021[i]->getDatoMeteo()).length() && vuelos_VLG2021[i]->getDatoMeteo()[j] != ' '; j++) {
                dato_vuelo = dato_vuelo + vuelos_VLG2021[i]->getDatoMeteo()[j];
            }
            if (dato_vuelo == "Lluvia") {
                vuelos_lluvia_VLG.push_back(vuelos_VLG2021[i]);
            }
            if (dato_vuelo == "Chubascos") {
                vuelos_chubascos_VLG.push_back(vuelos_VLG2021[i]);
            }
        }

        std::cout << std::endl << "El vuelo con el Flightnumber '" << vuelos_VLG2021[0]->getFlightNumb()
                  << "' ha realizado " << vuelos_lluvia_VLG.size() << " vuelos en condiciones de lluvia."
                  << std::endl;
        if (!vuelos_lluvia_VLG.empty()) {
            for (int i = 0; i < vuelos_lluvia_VLG.size(); i++) {
                std::cout << i + 1 << " vuelo: " << vuelos_lluvia_VLG[i]->getFecha().verDia() << "/"
                          << vuelos_lluvia_VLG[i]->getFecha().verMes() << "/"
                          << vuelos_lluvia_VLG[i]->getFecha().verAnio()
                          << " y las condiciones eran: " << vuelos_lluvia_VLG[i]->getDatoMeteo() << std::endl;
            }
        }

        std::cout << std::endl << "El vuelo con el Flightnumber '" << vuelos_VLG2021[0]->getFlightNumb()
                  << "' ha realizado " << vuelos_chubascos_VLG.size() << " vuelos en condiciones de chubascos."
                  << std::endl;
        if (!vuelos_chubascos_VLG.empty()) {
            for (int i = 0; i < vuelos_chubascos_VLG.size(); i++) {
                std::cout << i + 1 << " vuelo: " << vuelos_chubascos_VLG[i]->getFecha().verDia() << "/"
                          << vuelos_chubascos_VLG[i]->getFecha().verMes() << "/"
                          << vuelos_chubascos_VLG[i]->getFecha().verAnio() << " y las condiciones eran: "
                          << vuelos_chubascos_VLG[i]->getDatoMeteo() << std::endl;
            }
        }
    } catch (std::out_of_range &e) {
        std::cout << std::endl << "ERROR: " << e.what() << std::endl;
    }

    std::cout<< "Tiempo que tarda en mostrar la informacion de la aerolinea y el tiempo que hacia en los vuelos 'VLG2021' es: "
             << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs" << std::endl;

//3.-Mostrar los modelos de aviones (únicos) utilizados en vuelos operados por Vueling, VLG, el 13/4/2018
    clock_t t_ini4 = clock();

    try {
        Fecha f; f.asignarDia(13, 4, 18);
        std::list<Vuelo *> vuelos_VLG = vuelaFlight.vuelosOperadosPor("VLG", f);
        std::map<std::string, Vuelo *> modelos_avion;

        std::list<Vuelo *>::iterator Ite; Ite = vuelos_VLG.begin();

        for (int i = 0; i < vuelos_VLG.size(); i++) {
            std::pair<std::string, Vuelo *> aviones_modelo;
            aviones_modelo.first = (*Ite)->getPlane();
            aviones_modelo.second = *Ite;
            modelos_avion.insert(aviones_modelo);
            Ite++;
        }

        std::multimap<std::string, Vuelo *>::iterator Ite2; Ite2 = modelos_avion.begin();

        std::cout << std::endl
                  << "El numero de modelos de avion que ha usado la aerolinea Vueling(VLG) el 13/4/18 ha sido: "
                  << modelos_avion.size() << std::endl;
        for (int i = 0; i < modelos_avion.size(); i++) {
            std::cout << "El dia " << Ite2->second->getFecha().verDia() << "/" << Ite2->second->getFecha().verMes()
                      << "/" << Ite2->second->getFecha().verAnio() << " la aerolinea Vueling(VLG) uso el avion: "
                      << Ite2->second->getPlane() << std::endl;
            Ite2++;
        }
    } catch (std::out_of_range &e) {
        std::cout << std::endl << "ERROR: " << e.what() << std::endl;
    }

    std::cout<< "Tiempo que tarda en mostrar los modelos de avion de la aerolinea Vueling(VLG) en una fecha concreta es: "
             << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

//4.- Mostrar identificadores de vuelo (únicos) con destino a Londres (LHR, STN, LTN,LGW) desde
// cualquier aeropuerto español.
    clock_t t_ini5 = clock();

    std::vector<std::string> aeropuertos_Londres = {"LHR","STN","LTN","LGW"};
    for(int i=0;i<aeropuertos_Londres.size();i++){
        std::set<std::string> vuelos_ESP_LON;
        vuelos_ESP_LON = vuelaFlight.buscaVuelosDestAerop("ES",aeropuertos_Londres[i]);

        if(vuelos_ESP_LON.empty()){
            std::cout<<std::endl<<"No hay ningun vuelo entre todos los aeropuertos de Espania y el aeropuerto con el codigo '"<<aeropuertos_Londres[i]<<std::endl;
        }else {
            std::set<std::string>::iterator Ite; Ite = vuelos_ESP_LON.begin();

            std::cout << std::endl << "El numero de vuelos que hay desde un aeropuerto de Espania a el aeropuerto '"
                      << aeropuertos_Londres[i] << "' es: " << vuelos_ESP_LON.size() << std::endl;
            for (int j = 0; j < vuelos_ESP_LON.size(); j++) {
                std::cout << j + 1 << " numero de vuelo: " << (*Ite)<< std::endl;
                Ite++;
            }
        }
    }

    std::cout<< "Tiempo que tarda en mostrar los modelos de avion de la aerolinea Vueling(VLG) en una fecha concreta es: "
             << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}