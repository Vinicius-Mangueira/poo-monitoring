#include "logger.h"
#include <iostream>

// Inicialização dos membros estáticos fora da classe (obrigatório em C++)
Logger* Logger::instancia = nullptr;
int     Logger::contador  = 0;

Logger* Logger::get_instancia() {
    // Lazy initialization: cria a instância apenas na primeira chamada.
    if (instancia == nullptr) {
        instancia = new Logger();
    }
    return instancia;
}

void Logger::info(const std::string& msg) {
    std::string entrada = "[INFO]  " + msg;
    registros.push_back(entrada);
    ++contador;
}

void Logger::erro(const std::string& msg) {
    std::string entrada = "[ERRO]  " + msg;
    registros.push_back(entrada);
    ++contador;
}

void Logger::exibir() const {
    std::cout << "\n===== LOG DO SISTEMA (" << contador << " registros) =====\n";
    for (const auto& r : registros) {
        std::cout << "  " << r << "\n";
    }
    std::cout << "===========================================\n";
}

int Logger::total() {
    return contador;
}

void Logger::destruir() {
    delete instancia;
    instancia = nullptr;
    // Mantém o contador para eventual exibição após a destruição — opcional;
    // zeramos aqui para deixar o estado consistente.
    contador = 0;
}
