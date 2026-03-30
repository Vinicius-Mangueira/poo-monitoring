#include "alerta.h"
#include "logger.h"
#include <iostream>

Alerta::Alerta(Sensor* sensor, double limite, const std::string& mensagem)
    : sensor(sensor), limite(limite), mensagem(mensagem) {}

bool Alerta::verificar() const {
    // Usa o ponteiro polimórfico — ler_valor() despacha para a classe concreta.
    return sensor->ler_valor() > limite;
}

void Alerta::disparar() const {
    if (verificar()) {
        // Monta a mensagem completa com contexto do sensor.
        std::string msg = mensagem
                        + " | Sensor: " + sensor->get_id()
                        + " | Leitura: " + std::to_string(sensor->ler_valor())
                        + " " + sensor->unidade()
                        + " (limite: " + std::to_string(limite) + ")";

        // Registra via Singleton — um único ponto de log para todo o sistema.
        Logger::get_instancia()->erro(msg);

        std::cout << "[ALERTA DISPARADO] " << msg << std::endl;
    }
}
