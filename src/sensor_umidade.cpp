#include "sensor_umidade.h"
#include <iostream>

SensorUmidade::SensorUmidade(const std::string& id,
                             const std::string& localizacao,
                             double umidade)
    : Sensor(id, localizacao), umidade(umidade) {}

double SensorUmidade::ler_valor() const {
    return umidade;
}

std::string SensorUmidade::unidade() const {
    return "%";
}

void SensorUmidade::status() const {
    Sensor::status();
    std::cout << " | Tipo: Umidade"
              << " | Leitura: " << umidade << " " << unidade()
              << std::endl;
}
