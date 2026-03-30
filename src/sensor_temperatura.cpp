#include "sensor_temperatura.h"
#include <iostream>

SensorTemperatura::SensorTemperatura(const std::string& id,
                                     const std::string& localizacao,
                                     double temperatura)
    : Sensor(id, localizacao), temperatura(temperatura) {}

double SensorTemperatura::ler_valor() const {
    return temperatura;
}

std::string SensorTemperatura::unidade() const {
    return "C";
}

void SensorTemperatura::status() const {
    // Reutiliza a implementação da base (id + localização) e acrescenta detalhes.
    Sensor::status();
    std::cout << " | Tipo: Temperatura"
              << " | Leitura: " << temperatura << " " << unidade()
              << std::endl;
}
