#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "sensor.h"

/**
 * @brief Sensor de temperatura ambiental.
 *
 * Herda publicamente de Sensor e implementa todas as virtuais puras.
 * A leitura é armazenada em graus Celsius.
 */
class SensorTemperatura : public Sensor {
private:
    double temperatura; ///< Valor de temperatura em °C

public:
    SensorTemperatura(const std::string& id,
                      const std::string& localizacao,
                      double temperatura);

    double      ler_valor() const override;
    std::string unidade()   const override;

    /**
     * @brief Exibe status completo: herda saída da base e adiciona a leitura.
     *
     * Chama Sensor::status() primeiro (reutiliza a implementação da base)
     * e acrescenta temperatura + unidade.
     */
    void status() const override;
};

#endif // SENSOR_TEMPERATURA_H