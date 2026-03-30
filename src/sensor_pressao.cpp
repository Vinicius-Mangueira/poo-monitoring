#include "sensor_pressao.h"
#include <iostream>

SensorPressao::SensorPressao(const std::string& id,
                             const std::string& localizacao,
                             double pressao)
    : Sensor(id, localizacao), pressao(pressao) {}

double SensorPressao::ler_valor() const {
    return pressao;
}

std::string SensorPressao::unidade() const {
    return "hPa";
}

void SensorPressao::status() const {
    Sensor::status();
    std::cout << " | Tipo: Pressão"
              << " | Leitura: " << pressao << " " << unidade()
              << std::endl;
}
