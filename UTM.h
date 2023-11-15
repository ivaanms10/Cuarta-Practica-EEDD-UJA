//
// Created by Imora on 02/10/2023.
//
#ifndef CUARTA_PRACTICA_UTM_H
#define CUARTA_PRACTICA_UTM_H
#include <stdexcept>
#include <string>

class UTM {
private:
    float _latitud = 0.0;
    float _longitud = 0.0;

public:
    UTM();
    UTM(float latitud, float longitud);
    UTM &operator=(const UTM &orig);
    UTM(const UTM &orig);
    ~UTM();

    float getLatitud();
    void setLatitud(float latitud);

    float getLongitud();
    void setLongitud(float longitud);
};

#endif //CUARTA_PRACTICA_UTM_H