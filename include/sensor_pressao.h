#ifndef SENSOR_PRESSAO_H
#define SENSOR_PRESSAO_H

#include "sensor.h"

/**
 * @brief Sensor de pressão atmosférica.
 *
 * Herda publicamente de Sensor. A leitura é fornecida em hectopascais (hPa).
 */
class SensorPressao : public Sensor {
private:
    double pressao; ///< Valor de pressão em hPa

public:
    SensorPressao(const std::string& id,
                  const std::string& localizacao,
                  double pressao);

    double      ler_valor() const override;
    std::string unidade()   const override;

    /// Chama Sensor::status() e adiciona a leitura de pressão.
    void status() const override;
};

#endif // SENSOR_PRESSAO_H