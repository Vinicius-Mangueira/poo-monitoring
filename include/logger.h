#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

/**
 * @brief Sistema de log centralizado — padrão Singleton.
 *
 * Garante uma única instância durante toda a execução.  O construtor é privado
 * e o construtor de cópia / operador de atribuição são deletados para impedir
 * que o objeto seja duplicado acidentalmente.
 *
 * Uso típico:
 *   Logger::get_instancia()->info("Mensagem de informação");
 *   Logger::get_instancia()->erro("Erro detectado");
 *   Logger::get_instancia()->exibir();
 *   Logger::destruir();  // ao final do programa
 */
class Logger {
private:
    static Logger* instancia;      ///< Ponteiro para a única instância (lazy init)
    static int     contador;       ///< Total de registros armazenados

    std::vector<std::string> registros; ///< Histórico de mensagens

    /// Construtor privado — instanciação apenas via get_instancia().
    Logger() = default;

    // Impede cópia e atribuição
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

public:
    /// Retorna (ou cria) a única instância do Logger (lazy initialization).
    static Logger* get_instancia();

    /// Registra uma mensagem informativa com prefixo [INFO].
    void info(const std::string& msg);

    /// Registra uma mensagem de erro com prefixo [ERRO].
    void erro(const std::string& msg);

    /// Imprime todos os registros armazenados no console.
    void exibir() const;

    /// Retorna o total de registros acumulados.
    static int total();

    /// Libera a memória da instância e redefine o ponteiro para nullptr.
    static void destruir();
};

#endif // LOGGER_H
