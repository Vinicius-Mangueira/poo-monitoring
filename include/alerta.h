#ifndef ALERTA_H
#define ALERTA_H

#include "sensor.h"
#include <string>

/**
 * @brief Monitora um sensor e dispara alertas quando a leitura ultrapassa um limite.
 *
 * Usa um ponteiro polimórfico para Sensor*, portanto funciona com qualquer
 * tipo concreto de sensor sem precisar conhecer a classe derivada.
 */
class Alerta {
private:
    Sensor*     sensor;    ///< Ponteiro polimórfico para o sensor monitorado
    double      limite;    ///< Valor máximo permitido
    std::string mensagem;  ///< Texto exibido quando o alerta é disparado

public:
    /**
     * @param sensor   Ponteiro para o sensor a monitorar (não gerencia a memória)
     * @param limite   Valor a partir do qual o alerta é acionado
     * @param mensagem Mensagem registrada no Logger quando o limite é excedido
     */
    Alerta(Sensor* sensor, double limite, const std::string& mensagem);

    /// Retorna true se a leitura atual do sensor excede o limite configurado.
    bool verificar() const;

    /**
     * @brief Verifica e, se necessário, registra o alerta no Logger via erro().
     *
     * Usa Logger::get_instancia() para manter o Singleton como ponto único de log.
     */
    void disparar() const;
};
#endif // ALERTA_H