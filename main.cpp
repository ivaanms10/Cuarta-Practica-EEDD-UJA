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

    VuelaFlight vuelaFlight(archivo_aeropuertos, archivo_aerolineas, archivo_rutas, archivo_vuelos);

    int valor_menu = 0;

    while (valor_menu != 3) {
        valor_menu = 0;
        std::cout << "                              MENU                      " << std::endl;
        std::cout << "1.- PROGRAMA DE PRUEBA I: probar la funcionalidad de la practica 3 en STL." << std::endl;
        std::cout << "2.- PROGRAMA DE PRUEBA II: probar la funcionalidad de la practica 4 en STL." << std::endl;
        std::cout << "3.- EXIT" << std::endl;
        while (valor_menu == 0 || valor_menu > 3 || valor_menu < 0) {
            std::cout << "Inserte un numero: ";
            std::cin >> valor_menu;
        }

        if (valor_menu == 1) {
            // 1.- Visualiza toda la información de la aerolínea Ryanair, RYR.
            clock_t t_ini2 = clock();

            Aerolinea *Ryanair = vuelaFlight.buscaAerolinea("RYR");
            if (Ryanair != nullptr) {
                std::cout << std::endl << "Informacion de la aerolinea Ryanair(RYR): " << std::endl;
                std::cout << "  ** ID de la aerolinea: " << Ryanair->getId() << std::endl;
                std::cout << "  ** ICAO de la aerolinea: " << Ryanair->getIcao() << std::endl;
                std::cout << "  ** Nombre de la aerolinea: " << Ryanair->getNombre() << std::endl;
                std::cout << "  ** Pais de la aerolinea: " << Ryanair->getPais() << std::endl;
                if (Ryanair->isActivo()) {
                    std::cout << "  ** La aerolinea Ryanair esta activa actualmente." << std::endl;
                } else {
                    std::cout << "  ** La aerolinea Ryanair no esta activa actualmente." << std::endl;
                }
            } else {
                std::cout << "La aerolinea con el ICAO (RYR) no existe entre todas las aerolineas." << std::endl;
            }

            std::cout << "El tiempo que tarda en buscar la aerolinea Ryanair(RYR) y mostrar su informacion es: "
                      << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

            // 2.- Muestra todas las aerolíneas activas.
            clock_t t_ini3 = clock();

            std::list<Aerolinea*> aerolineas_activas = vuelaFlight.buscaAerolineaActiva();

            if(aerolineas_activas.empty()){
                std::cout<<std::endl<<"No hay actualmente ninguna aerolinea activa."<<std::endl;
            }else{
                std::cout << std::endl << "El numero de aerolineas que hay activas actualmente es: "
                          << aerolineas_activas.size()
                          << std::endl;

                std::list<Aerolinea*>::iterator Ite; Ite = aerolineas_activas.begin();
                for (int i = 0; i < aerolineas_activas.size(); ++i) {
                    std::cout << i + 1 << ".-  ICAO: " << (*Ite)->getIcao()
                              << ", Nombre: " << (*Ite)->getNombre() << ", Pais: "
                              << (*Ite)->getPais()
                              << std::endl;
                    ++Ite;
                }
            }

            std::cout << "El tiempo que tarda en buscar todas las aerolineas activas y mostrarlas es: "
                      << ((clock() - t_ini3) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

            // 3.- Busca todos los aeropuertos (origen) en los que opera Iberia Airlines, con icao IBE.
            clock_t t_ini4 = clock();

            Aerolinea *Iberia = vuelaFlight.buscaAerolinea("IBE");
            if(Iberia == nullptr){
                std::cout<<std::endl<<"La aerolinea que intenta buscar no ha sido encontrada correctamente."<<std::endl;
            }else{
                std::deque<Aeropuerto*> aeropuertos_iberia = Iberia->getAeropuertosOrig();

                std::cout << std::endl << "El numero de aeropuertos donde opera Iberia(IBE) es: " << aeropuertos_iberia.size() << std::endl;
                for (int i = 0; i < aeropuertos_iberia.size(); ++i) {
                        std::cout << i + 1 << ".- IATA: " << aeropuertos_iberia[i]->getIata() << ", Nombre: "
                                  << aeropuertos_iberia[i]->getNombre() << std::endl;
                    }
                }

            std::cout << "El tiempo que tarda en buscar todos los aeropuertos de origen sin repetirse de la aerolinea Iberia es: "
                      << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

            // 4.- Busca todas las rutas operadas por Iberia Airlines con origen en el aeropuerto de Málaga(AGP).
            clock_t t_ini5 = clock();

            Iberia = vuelaFlight.buscaAerolinea("IBE");
            if(Iberia == nullptr) {
                std::cout<<std::endl<<"La aerolinea que intenta buscar no ha sido encontrada correctamente."<<std::endl;
            }else{
                std::list <Ruta*> todas_rutas_iberia_malaga = Iberia->getRutasAeropuerto("AGP");
                std::vector <Ruta*> iberia_malaga;

                if(todas_rutas_iberia_malaga.empty()){
                    std::cout<<std::endl<<"No hay ninguna ruta cuyo aeropuerto de origen sea 'AGP' operado por la aerolinea Iberia."<<std::endl;
                }else{
                    std::list<Ruta*>::iterator Ite; Ite = todas_rutas_iberia_malaga.begin();
                    for (int i = 0; i < todas_rutas_iberia_malaga.size(); ++i) {
                        if ((*Ite)->getOrigin()->getIata() == "AGP") {
                            iberia_malaga.push_back(*Ite);
                        }
                        ++Ite;
                    }
                }

                std::cout << std::endl
                          << "El numero de rutas cuya aerolinea es Iberia y el aeropuerto de origen es Malaga es: "
                          << iberia_malaga.size() << std::endl;
                for (int i = 0; i < iberia_malaga.size(); i++) {
                    std::cout << i + 1 << ".- Arolinea: " << iberia_malaga[i]->getCompany()->getNombre() << ", Origen: "
                              << iberia_malaga[i]->getOrigin()->getNombre() << ", Destino: "
                              << iberia_malaga[i]->getDestination()->getNombre() << std::endl;
                }
            }

            std::cout << "El tiempo que tarda en buscar las rutas cuya aerolinea es Iberia y el aeropuerto de origen Malaga es: "
                      << ((clock() - t_ini5) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

            // 5.- Implementar el método VuelaFlight::getAerolineasPais(String idPais): Aerolinea[] que muestra todas
            // las aerolíneas de un país dado como parámetro (utilizar el recorrido inorden). Para probarlo, muestra
            // por pantalla la información de las aerolíneas que operan en España
            clock_t t_ini6 = clock();

            try {
                std::list<Aerolinea*> aerolineas_spain = vuelaFlight.getAerolineasPais("Spain");
                if (aerolineas_spain.size() != 0) {
                    std::list<Aerolinea*>::iterator Ite; Ite = aerolineas_spain.begin();
                    std::cout << std::endl << "El numero de aerolineas que hay Spain es: " << aerolineas_spain.size()
                              << std::endl;
                    for (int i = 0; i < aerolineas_spain.size(); ++i) {
                        std::cout << i + 1 << ".- ICAO: " << (*Ite)->getIcao() << ", Nombre: "
                                  << (*Ite)->getNombre() << ", Pais: " << (*Ite)->getPais()
                                  << std::endl;
                    }
                } else {
                    std::cout << "El pais que ha buscado no contiene ninguna aerolinea." << std::endl;
                }
            } catch (std::out_of_range &e) {
                std::cout << std::endl << "ERROR: " << e.what() << std::endl;
            }

            std::cout << "El tiempo que tarda en buscar y mostrar todas las aerolineas que hay en Spain es: "
                      << ((clock() - t_ini6) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

        }

        if (valor_menu == 2) {
            //1.- Para los vuelos con identificador de vuelo AEA5201 y VLG2021, si existen, mostrar:
            //       *Datos de la aerolínea que los opera ( nombre completo y país al que pertenece) e iata de los
            //       aeropuertos de origen, destino.
            //       * Listado con todas las fechas y estado del tiempo en las que se ha efectuado en condiciones
            //       de lluvia o chubascos
            clock_t t_ini2 = clock();

            std::deque<Vuelo*> vuelos_lluvia_AEA;
            std::deque<Vuelo*> vuelos_chubascos_AEA;

            try {
                std::deque<Vuelo*> vuelos_AEA5201 = vuelaFlight.buscaVuelos("AEA5201");
                std::cout << std::endl << "Informacion de la aerolinea que realiza los vuelos con el Flightnumber: "
                          << vuelos_AEA5201[0]->getFlightNumb() << std::endl;
                std::cout << "  ** ICAO de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getIcao() << std::endl;
                std::cout << "  ** Nombre de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getNombre()
                          << std::endl;
                std::cout << "  ** Pais de la aerolinea: " << vuelos_AEA5201[0]->getAerolinea()->getPais() << std::endl;
                std::cout << "  ** IATA aeropuerto origen: " << vuelos_AEA5201[0]->getAeropuertoOrig()->getIata()
                          << std::endl;
                std::cout << "  ** IATA aeropuerto destino: " << vuelos_AEA5201[0]->getAeropuertoDest()->getIata()
                          << std::endl;

                for (int i = 0; i < vuelos_AEA5201.size(); i++) {
                    std::string dato_vuelo = "";

                    for (int j = 0; j < (vuelos_AEA5201[i]->getDatoMeteo()).length() && vuelos_AEA5201[i]->getDatoMeteo()[j] != ' '; ++j) {
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
                    for (int i = 0; i < vuelos_lluvia_AEA.size(); ++i) {
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
                    for (int i = 0; i < vuelos_chubascos_AEA.size(); ++i) {
                        std::cout << i + 1 << " vuelo: " << vuelos_chubascos_AEA[i]->getFecha().verDia() << "/"
                                  << vuelos_chubascos_AEA[i]->getFecha().verMes() << "/"
                                  << vuelos_chubascos_AEA[i]->getFecha().verAnio() << " y las condiciones eran: "
                                  << vuelos_chubascos_AEA[i]->getDatoMeteo() << std::endl;
                    }
                }
            } catch (std::out_of_range &e) {
                std::cout << std::endl << "ERROR: " << e.what() << std::endl;
            }

            std::cout << "Tiempo que tarda en mostrar la informacion de la aerolinea y el tiempo que hacia en los vuelos 'AEA5201' es: "
                      << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs" << std::endl;

            clock_t t_ini3 = clock();

            std::deque<Vuelo*> vuelos_lluvia_VLG;
            std::deque<Vuelo*> vuelos_chubascos_VLG;

            try {
                std::deque<Vuelo*> vuelos_VLG2021 = vuelaFlight.buscaVuelos("VLG2021");
                std::cout << std::endl << "Informacion de la aerolinea que realiza los vuelos con el Flightnumber: "
                          << vuelos_VLG2021[0]->getFlightNumb() << std::endl;
                std::cout << "  ** ICAO de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getIcao() << std::endl;
                std::cout << "  ** Nombre de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getNombre()
                          << std::endl;
                std::cout << "  ** Pais de la aerolinea: " << vuelos_VLG2021[0]->getAerolinea()->getPais() << std::endl;
                std::cout << "  ** IATA aeropuerto origen: " << vuelos_VLG2021[0]->getAeropuertoOrig()->getIata()
                          << std::endl;
                std::cout << "  ** IATA aeropuerto destino: " << vuelos_VLG2021[0]->getAeropuertoDest()->getIata()
                          << std::endl;

                for (int i = 0; i < vuelos_VLG2021.size(); ++i) {
                    std::string dato_vuelo = "";

                    for (int j = 0; j < (vuelos_VLG2021[i]->getDatoMeteo()).length() && vuelos_VLG2021[i]->getDatoMeteo()[j] != ' '; ++j) {
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
                    for (int i = 0; i < vuelos_lluvia_VLG.size(); ++i) {
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
                    for (int i = 0; i < vuelos_chubascos_VLG.size(); ++i) {
                        std::cout << i + 1 << " vuelo: " << vuelos_chubascos_VLG[i]->getFecha().verDia() << "/"
                                  << vuelos_chubascos_VLG[i]->getFecha().verMes() << "/"
                                  << vuelos_chubascos_VLG[i]->getFecha().verAnio() << " y las condiciones eran: "
                                  << vuelos_chubascos_VLG[i]->getDatoMeteo() << std::endl;
                    }
                }
            } catch (std::out_of_range &e) {
                std::cout << std::endl << "ERROR: " << e.what() << std::endl;
            }

            std::cout << "Tiempo que tarda en mostrar la informacion de la aerolinea y el tiempo que hacia en los vuelos 'VLG2021' es: "
                      << ((clock() - t_ini2) / (float) CLOCKS_PER_SEC) << " segs" << std::endl;

            //2.-Mostrar los modelos de aviones (únicos) utilizados en vuelos operados por Vueling, VLG, el 13/4/2018
            clock_t t_ini4 = clock();

            try {
                Fecha f; f.asignarDia(13, 4, 18);
                std::list<Vuelo*> vuelos_VLG = vuelaFlight.vuelosOperadosPor("VLG", f);
                std::map<std::string, Vuelo*> modelos_avion;

                std::list<Vuelo*>::iterator Ite; Ite = vuelos_VLG.begin();

                for (int i = 0; i < vuelos_VLG.size(); ++i) {
                    std::pair<std::string, Vuelo *> aviones_modelo;
                    aviones_modelo.first = (*Ite)->getPlane();
                    aviones_modelo.second = *Ite;
                    modelos_avion.insert(aviones_modelo);
                    ++Ite;
                }

                std::multimap<std::string, Vuelo*>::iterator Ite2; Ite2 = modelos_avion.begin();

                std::cout << std::endl
                          << "El numero de modelos de avion que ha usado la aerolinea Vueling(VLG) el 13/4/18 ha sido: "
                          << modelos_avion.size() << std::endl;
                for (int i = 0; i < modelos_avion.size(); ++i) {
                    std::cout << "El dia " << Ite2->second->getFecha().verDia() << "/"
                              << Ite2->second->getFecha().verMes()
                              << "/" << Ite2->second->getFecha().verAnio()
                              << " la aerolinea Vueling(VLG) uso el avion: "
                              << Ite2->second->getPlane() << std::endl;
                    ++Ite2;
                }
            } catch (std::out_of_range &e) {
                std::cout << std::endl << "ERROR: " << e.what() << std::endl;
            }

            std::cout << "Tiempo que tarda en mostrar los modelos de avion de la aerolinea Vueling(VLG) en una fecha concreta es: "
                      << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

            //3.- Mostrar identificadores de vuelo (únicos) con destino a Londres (LHR, STN, LTN,LGW) desde
            // cualquier aeropuerto español.
            clock_t t_ini5 = clock();

            std::vector<std::string> aeropuertos_Londres = {"LHR", "STN", "LTN", "LGW"};
            for (int i = 0; i < aeropuertos_Londres.size(); ++i) {
                std::set<std::string> vuelos_ESP_LON;
                vuelos_ESP_LON = vuelaFlight.buscaVuelosDestAerop("ES", aeropuertos_Londres[i]);

                if (vuelos_ESP_LON.empty()) {
                    std::cout << std::endl
                              << "No hay ningun vuelo entre todos los aeropuertos de Espania y el aeropuerto con el codigo '"
                              << aeropuertos_Londres[i] << std::endl;
                } else {
                    std::set<std::string>::iterator Ite; Ite = vuelos_ESP_LON.begin();

                    std::cout << std::endl
                              << "El numero de vuelos que hay desde un aeropuerto de Espania a el aeropuerto '"
                              << aeropuertos_Londres[i] << "' es: " << vuelos_ESP_LON.size() << std::endl;
                    for (int j = 0; j < vuelos_ESP_LON.size(); ++j) {
                        std::cout << j + 1 << " numero de vuelo: " << (*Ite) << std::endl;
                        ++Ite;
                    }
                }
            }

            std::cout << "Tiempo que tarda en mostrar los numeros de vuelos que hay desde Espania a los 4 aeropuertos de Londres es: "
                      << ((clock() - t_ini4) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
        }
    }
}