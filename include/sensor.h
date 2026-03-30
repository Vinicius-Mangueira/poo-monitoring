ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>

/**
 * @brief Classe base abstrata para todos os sensores ambientais.
 *
 * Define a interface comum: leitura de valor, unidade de medida e exibição
 * de status. As virtuais puras obrigam cada sensor concreto a fornecer sua
 * própria implementação, garantindo polimorfismo em tempo de execução.
 */
class Sensor {
protected:
    std::string id;
    std::string localizacao;

public:
    Sensor(const std::string& id, const std::string& localizacao);

    /// Retorna a leitura atual do sensor (virtual pura — cada tipo implementa a sua).
    virtual double ler_valor() const = 0;

    /// Retorna a unidade de medida da leitura (virtual pura).
    virtual std::string unidade() const = 0;

    /**
     * @brief Exibe id e localização do sensor.
     *
     * Virtual não pura: fornece implementação padrão que as classes derivadas
     * podem estender chamando Sensor::status() antes de adicionar detalhes.
     */
    virtual void status() const;

    /// Destrutor virtual garante que delete via ponteiro base chame o destrutor correto.
    virtual ~Sensor() = default;

    // Getters
    std::string get_id() const;
    std::string get_localizacao() const;
};

/// Função livre: retorna o sensor com o maior valor de leitura no vetor.
Sensor* maior_leitura(std::vector<Sensor*>& sensores);

#endif // SENSOR_H
