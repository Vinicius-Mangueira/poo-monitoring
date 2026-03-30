#include "sensor.h"
#include "sensor_temperatura.h"
#include "sensor_umidade.h"
#include "sensor_pressao.h"
#include "logger.h"
#include "alerta.h"

#include <iostream>
#include <vector>

int main() {
    std::cout << "========================================\n";
    std::cout << "  Sistema de Monitoramento Ambiental\n";
    std::cout << "========================================\n\n";

    // -------------------------------------------------------------------------
    // 1. Criar pelo menos um sensor de cada tipo
    // -------------------------------------------------------------------------
    SensorTemperatura* st = new SensorTemperatura("TEMP-01", "Sala de Servidores", 38.5);
    SensorUmidade*     su = new SensorUmidade    ("UMID-01", "Sala de Servidores", 85.0);
    SensorPressao*     sp = new SensorPressao    ("PRES-01", "Telhado",            1025.3);

    // Sensor adicional para tornar o polimorfismo mais interessante
    SensorTemperatura* st2 = new SensorTemperatura("TEMP-02", "Corredor",          22.1);

    // -------------------------------------------------------------------------
    // 2. Armazenar em vector<Sensor*> — polimorfismo via ponteiro base
    // -------------------------------------------------------------------------
    std::vector<Sensor*> sensores = { st, su, sp, st2 };

    // -------------------------------------------------------------------------
    // 3. Chamar status() de cada sensor via ponteiro base
    //    O despache virtual garante que a versão correta de cada derivada é chamada.
    // -------------------------------------------------------------------------
    std::cout << "--- Status de todos os sensores ---\n";
    for (Sensor* s : sensores) {
        s->status(); // chamada polimórfica
    }

    // -------------------------------------------------------------------------
    // 4. Usar o Logger (Singleton) para registrar eventos
    // -------------------------------------------------------------------------
    Logger* log = Logger::get_instancia();
    log->info("Sistema de monitoramento iniciado.");
    log->info("Sensores carregados: " + std::to_string(sensores.size()));

    // -------------------------------------------------------------------------
    // 5. Configurar alertas e dispará-los
    //    Alerta usa Sensor* polimorficamente — não precisa saber o tipo concreto.
    // -------------------------------------------------------------------------
    std::cout << "\n--- Verificando alertas ---\n";

    Alerta alertaTemp (st,  35.0, "TEMPERATURA CRÍTICA na Sala de Servidores");
    Alerta alertaUmid (su,  80.0, "UMIDADE EXCESSIVA na Sala de Servidores");
    Alerta alertaPres (sp, 1030.0,"Pressão acima do normal no Telhado");
    Alerta alertaTemp2(st2, 30.0, "Temperatura elevada no Corredor"); // não deve disparar

    alertaTemp.disparar();
    alertaUmid.disparar();
    alertaPres.disparar();
    alertaTemp2.disparar(); // leitura 22.1 < limite 30 — silencioso

    log->info("Verificação de alertas concluída.");

    // -------------------------------------------------------------------------
    // 6. Chamar maior_leitura() e exibir o resultado
    //    A função livre opera sem conhecer os tipos concretos.
    // -------------------------------------------------------------------------
    std::cout << "\n--- Maior leitura registrada ---\n";
    Sensor* maior = maior_leitura(sensores);
    if (maior) {
        std::cout << "Sensor: " << maior->get_id()
                  << " | Valor: " << maior->ler_valor()
                  << " " << maior->unidade()
                  << " | Local: " << maior->get_localizacao()
                  << std::endl;
        log->info("Maior leitura: sensor " + maior->get_id()
                  + " com " + std::to_string(maior->ler_valor())
                  + " " + maior->unidade());
    }

    // -------------------------------------------------------------------------
    // 7. Exibir o log completo e o total de registros
    // -------------------------------------------------------------------------
    log->exibir();
    std::cout << "Total de registros no log: " << Logger::total() << "\n\n";

    // -------------------------------------------------------------------------
    // 8. Liberar memória — delete nos sensores e destruir o Singleton
    // -------------------------------------------------------------------------
    for (Sensor* s : sensores) {
        delete s; // destrutor virtual garante a destruição correta
    }
    sensores.clear();

    Logger::destruir(); // encerra o Singleton de forma segura

    std::cout << "Sistema encerrado com sucesso.\n";
    return 0;
}
