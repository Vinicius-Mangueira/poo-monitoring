# Registro de Uso de LLM — docs/llm-log.md

Disciplina: Programação Orientada a Objetos — 2025.2  
Ferramenta utilizada: Claude (Anthropic)

---

## Interação 1 — Estrutura geral do projeto

**Prompt:**  
"Preciso implementar um Sistema de Monitoramento Ambiental em C++ com a estrutura
de diretórios include/src/docs/build, seguindo o diagrama de classes fornecido.
Pode gerar todos os arquivos?"

**Resposta resumida:**  
O LLM gerou a estrutura completa: headers com include guards, arquivos .cpp separados,
Makefile com targets all/clean/run, .gitignore, README e llm-log.md.

**Decisão:**  
Aceitei a estrutura de diretórios e a separação header/source. Revisei cada arquivo
individualmente antes de incluir no repositório — itens verificados:
- Confirmei que todos os métodos usam `override` explicitamente.
- Confirmei que o construtor de cópia e `operator=` do Logger estão `= delete`.
- Confirmei que o destrutor de Sensor é `virtual ~Sensor() = default`.

---

## Interação 2 — Padrão Singleton no Logger

**Prompt:**  
"Como implementar corretamente o padrão Singleton em C++ com lazy initialization,
sem usar variável estática local (Meyer's Singleton), usando new/delete explícitos
como pede o enunciado?"

**Resposta resumida:**  
O LLM explicou a diferença entre Meyer's Singleton (variável estática local) e o
Singleton com ponteiro estático + new/delete. Gerou a implementação com `instancia`
inicializado como `nullptr` fora da classe e `get_instancia()` verificando antes de alocar.

**Decisão:**  
Aceitei a abordagem de ponteiro estático pois corresponde exatamente ao diagrama de
classes do enunciado (`instancia : Logger* (static)`). O Meyer's Singleton seria mais
seguro em ambientes multi-thread, mas não é o que o diagrama especifica.

---

## Interação 3 — Função livre `maior_leitura`

**Prompt:**  
"A função livre maior_leitura recebe vector<Sensor*> e deve funcionar sem conhecer
os tipos concretos. Como garantir que o polimorfismo seja exercitado corretamente?"

**Resposta resumida:**  
O LLM mostrou que basta chamar `s->ler_valor()` no loop — o despache virtual cuida
do resto. Também sugeriu retornar `nullptr` para vetor vazio em vez de lançar exceção.

**Decisão:**  
Aceitei o retorno `nullptr` para o caso de vetor vazio, pois o `main` já verifica antes
de usar o ponteiro retornado. Removi a sugestão de `std::max_element` com lambda porque
preferi o loop explícito para deixar mais legível para avaliação.

---

## Interação 4 — Comentários e documentação

**Prompt:**  
"Pode adicionar comentários Doxygen-style nos headers e comentários explicativos
inline nos .cpp, destacando onde cada conceito OOP (herança, polimorfismo, virtual,
Singleton) está sendo aplicado?"

**Resposta resumida:**  
O LLM adicionou comentários `@brief`, `@param` e blocos explicativos nos pontos-chave.
Também adicionou comentários de seção no `main()` alinhados com os 8 itens do enunciado.

**Decisão:**  
Aceitei os comentários dos headers. Nos .cpp reduzi alguns comentários redundantes que
explicavam o óbvio (ex.: "chama o construtor da base" no inicializador) para não poluir
o código — mantive apenas os que agregam informação sobre o *porquê*, não o *o quê*.

---

## Reflexão geral

O uso do LLM acelerou significativamente a geração do boilerplate (Makefile, include guards,
estrutura de diretórios). As partes que exigiram maior atenção crítica foram:

1. **Verificar a conformidade com o diagrama de classes** — o LLM às vezes sugeria nomes
   ligeiramente diferentes dos especificados (`getInstancia` vs `get_instancia`).
2. **Garantir que o Singleton fosse destruído corretamente** — a versão inicial do LLM
   não zeravaou `contador` em `destruir()`, o que causaria leituras incorretas em testes.
3. **Polimorfismo no Alerta** — o LLM inicialmente usava `dynamic_cast` desnecessário;
   corrigi para operar apenas via `Sensor*`, como o enunciado exige.

O LLM foi uma ferramenta de produtividade, não um substituto para o entendimento do código.
Cada trecho gerado foi lido, compreendido e validado antes de ser incluído no projeto.