#ifndef SENSOR_UMIDADE_H
#define SENSOR_UMIDADE_H

#include "sensor.h"

/**
 * @brief Sensor de umidade relativa do ar.
 *
 * Herda publicamente de Sensor. A leitura representa umidade em percentual (%).
 */
class SensorUmidade : public Sensor {
private:
    double umidade; ///< Valor de umidade em %

public:
    SensorUmidade(const std::string& id,
                  const std::string& localizacao,
                  double umidade);

    double      ler_valor() const override;
    std::string unidade()   const override;

    /// Chama Sensor::status() e adiciona a leitura de umidade.
    void status() const override;
};

#endif // SENSOR_UMIDADE_H