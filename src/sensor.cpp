#include "sensor.h"
#include <iostream>
#include <stdexcept>

Sensor::Sensor(const std::string& id, const std::string& localizacao)
    : id(id), localizacao(localizacao) {}

void Sensor::status() const {
    std::cout << "[Sensor] ID: " << id
              << " | Localização: " << localizacao;
}

std::string Sensor::get_id() const {
    return id;
}

std::string Sensor::get_localizacao() const {
    return localizacao;
}

// ----------------------------------------------------------------------------
// Função livre — percorre o vetor via polimorfismo e retorna o sensor com a
// maior leitura. Não conhece os tipos concretos: opera apenas por Sensor*.
// ----------------------------------------------------------------------------
Sensor* maior_leitura(std::vector<Sensor*>& sensores) {
    if (sensores.empty()) {
        return nullptr;
    }

    Sensor* maior = sensores[0];
    for (std::size_t i = 1; i < sensores.size(); ++i) {
        if (sensores[i]->ler_valor() > maior->ler_valor()) {
            maior = sensores[i];
        }
    }
    return maior;
}
