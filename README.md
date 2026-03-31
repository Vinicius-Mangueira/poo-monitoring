# Sistema de Monitoramento Ambiental

Trabalho Prático da disciplina de Programação Orientada a Objetos (POO) — 2025.2  
Universidade Federal da Paraíba — UFPB  
Prof. Carlos Eduardo C. F. Batista

---

## Descrição

Sistema em C++ que simula uma estação de monitoramento ambiental com sensores de
temperatura, umidade e pressão atmosférica. O sistema registra todas as leituras em um
log centralizado e dispara alertas quando os valores ultrapassam limites configurados.

---

## Compilação e Execução

```bash
# Compilar
make

# Compilar e executar
make run

# Remover arquivos gerados
make clean
```

Requisitos: g++ com suporte a C++17 (`-std=c++17`).

---

## Estrutura do Projeto

```
monitoramento/
├── include/               ← Headers (.h)
│   ├── sensor.h           ← Classe base abstrata
│   ├── sensor_temperatura.h
│   ├── sensor_umidade.h
│   ├── sensor_pressao.h
│   ├── logger.h           ← Singleton
│   └── alerta.h
├── src/                   ← Implementações (.cpp)
│   ├── sensor.cpp
│   ├── sensor_temperatura.cpp
│   ├── sensor_umidade.cpp
│   ├── sensor_pressao.cpp
│   ├── logger.cpp
│   ├── alerta.cpp
│   └── main.cpp
├── docs/
│   └── llm-log.md
├── Makefile
├── README.md
└── .gitignore
```

---

## Decisões de Design

### Virtual pura em `Sensor`
`ler_valor()` e `unidade()` são declaradas como virtuais puras (`= 0`) porque não existe
uma implementação genérica de "leitura" — cada tipo de sensor tem seu próprio hardware e
unidade. Isso força o compilador a rejeitar instâncias diretas de `Sensor` e garante que
qualquer classe derivada concreta implemente esses comportamentos.

### `status()` virtual não pura
Fornece uma implementação padrão (id + localização) que todas as derivadas reutilizam via
`Sensor::status()`. Isso evita duplicação de código: cada derivada só acrescenta o que é
específico (tipo e leitura), sem reescrever a parte comum.

### Destrutor virtual na base
Sem `virtual ~Sensor()`, um `delete` por ponteiro `Sensor*` chamaria apenas o destrutor
da base, vazando recursos das classes derivadas. O destrutor virtual garante que a cadeia
de destruição correta seja executada.

### Logger Singleton
Garante um único ponto de log no sistema inteiro. O construtor privado e a deleção de
cópia/atribuição impedem que outras partes do código criem instâncias paralelas.  
A **lazy initialization** (`get_instancia()`) cria o objeto apenas na primeira chamada,
evitando dependência de ordem de inicialização de variáveis globais.

### `Alerta` com `Sensor*` polimórfico
A classe `Alerta` não conhece os tipos concretos de sensor. Ela opera exclusivamente pela
interface `Sensor*`, chamando `ler_valor()` que é despachada em tempo de execução para a
classe correta. Isso significa que novos tipos de sensores podem ser adicionados ao sistema
sem alterar `Alerta`.

### Função livre `maior_leitura`
Demonstra que o polimorfismo não se limita a métodos de classe: uma função livre que recebe
`vector<Sensor*>` consegue comparar leituras de tipos completamente diferentes sem saber
nada sobre eles além da interface `Sensor`.

---

## Exemplo de Saída

```
========================================
  Sistema de Monitoramento Ambiental
========================================

--- Status de todos os sensores ---
[Sensor] ID: TEMP-01 | Localização: Sala de Servidores | Tipo: Temperatura | Leitura: 38.5 C
[Sensor] ID: UMID-01 | Localização: Sala de Servidores | Tipo: Umidade | Leitura: 85 %
[Sensor] ID: PRES-01 | Localização: Telhado | Tipo: Pressão | Leitura: 1025.3 hPa
[Sensor] ID: TEMP-02 | Localização: Corredor | Tipo: Temperatura | Leitura: 22.1 C

--- Verificando alertas ---
[ALERTA DISPARADO] TEMPERATURA CRÍTICA na Sala de Servidores | Sensor: TEMP-01 | Leitura: 38.500000 C (limite: 35.000000)
[ALERTA DISPARADO] UMIDADE EXCESSIVA na Sala de Servidores | Sensor: UMID-01 | Leitura: 85.000000 % (limite: 80.000000)

--- Maior leitura registrada ---
Sensor: PRES-01 | Valor: 1025.3 hPa | Local: Telhado

===== LOG DO SISTEMA (6 registros) =====
  [INFO]  Sistema de monitoramento iniciado.
  [INFO]  Sensores carregados: 4
  [ERRO]  TEMPERATURA CRÍTICA na Sala de Servidores | ...
  [ERRO]  UMIDADE EXCESSIVA na Sala de Servidores | ...
  [INFO]  Verificação de alertas concluída.
  [INFO]  Maior leitura: sensor PRES-01 com 1025.300000 hPa
===========================================
Total de registros no log: 6

Sistema encerrado com sucesso.
```
