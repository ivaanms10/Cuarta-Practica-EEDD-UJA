cmake_minimum_required(VERSION 3.26)
project(Cuarta_Practica)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cuarta_Practica main.cpp Aerolinea.cpp Aerolinea.h Aeropuerto.cpp Aeropuerto.h fecha.cpp fecha.h
        Ruta.cpp Ruta.h UTM.cpp UTM.h VuelaFlight.cpp VuelaFlight.h Vuelo.cpp Vuelo.h)
