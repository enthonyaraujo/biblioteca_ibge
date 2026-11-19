# Como visualizar os fluxogramas

Este arquivo utiliza blocos de código `mermaid` para representar os fluxogramas.

No VS Code, abra este arquivo e pressione `Ctrl+Shift+V` para abrir a visualização do Markdown. Também é possível usar o comando **Markdown: Open Preview** na paleta de comandos (`Ctrl+Shift+P`). Os fluxogramas serão renderizados nessa visualização.

No site do GitHub, a visualização dos blocos Mermaid é automática: basta abrir ou acessar o arquivo `fluxograma.md` no repositório para ver os fluxogramas renderizados.

# Fluxogramas das funções não `static`

Este arquivo apresenta, em Mermaid, o fluxo das funções não `static` do projeto `atividade03`:

- `main`
- `ibgeBuscarMunicipio`
- `ibgeListarMunicipios`
- `ibgeStatusMensagem`

## `main`

```mermaid
flowchart TD
    A([Início]) --> B(argc == 2 e lerCodigo retorna sucesso?)
    B -- Não --> C[Exibe mensagem de uso]
    C --> D([Retorna 1])
    B -- Sim --> E[Chama ibgeBuscarMunicipio]
    E --> F(status == IBGE_OK?)
    F -- Não --> G[Exibe mensagem de erro com ibgeStatusMensagem]
    G --> H([Retorna 1])
    F -- Sim --> I[Exibe código, município, UF, região,<br/>latitude e longitude]
    I --> J([Retorna 0])
    classDef decisao fill:#ffffff,stroke:#3b82f6,stroke-width:1px,stroke-dasharray:2 2,color:#1d4ed8;
    class B,F decisao;
```

Legenda:

- **Argumentos válidos?**: verifica se foi informado exatamente um argumento e se `lerCodigo` conseguiu convertê-lo em um código válido.
- **Status == IBGE_OK?**: verifica se a consulta ao município foi concluída com sucesso.

## `ibgeBuscarMunicipio`

```mermaid
flowchart TD
    A([Início]) --> B(municipio == NULL ou código fora do intervalo válido?)
    B -- Sim --> C([Retorna IBGE_ERRO_ARGUMENTO])
    B -- Não --> D[Limpa a estrutura Municipio]
    D --> E[Monta comando curl da API de localidades]
    E --> F[Abre pipe com popen]
    F --> G(pipe == NULL?)
    G -- Sim --> H([Retorna IBGE_ERRO_CONEXAO])
    G -- Não --> I[Lê resposta e fecha pipe]
    I --> J(codigoSaida != 0 ou lidos == 0?)
    J -- Sim --> H
    J -- Não --> K[Chama extrairMunicipio]
    K --> L(extrairMunicipio retornou sucesso?)
    L -- Não --> M([Retorna IBGE_ERRO_RESPOSTA])
    L -- Sim --> N[Chama buscarLocalizacaoGps]
    N --> O([Retorna status da localização GPS])
    classDef decisao fill:#ffffff,stroke:#3b82f6,stroke-width:1px,stroke-dasharray:2 2,color:#1d4ed8;
    class B,G,J,L decisao;
```

Legenda:

- **municipio == NULL ou código fora do intervalo válido?**: verifica se os argumentos são inválidos.
- **pipe == NULL?**: verifica se não foi possível iniciar o comando `curl`.
- **codigoSaida != 0 ou lidos == 0?**: verifica se o `curl` falhou ou retornou uma resposta vazia.
- **extrairMunicipio retornou sucesso?**: verifica se a resposta contém os dados do município em formato reconhecido.

## `ibgeListarMunicipios`

```mermaid
flowchart TD
    A([Início]) --> B(Callback foi informada?)
    B -- Não --> C([Retorna erro de argumento])
    B -- Sim --> D[Consulta a lista de municípios na API do IBGE]
    D --> E(Consulta realizada?)
    E -- Não --> F([Retorna erro de conexão])
    E -- Sim --> G[Processa cada município recebido]
    G --> H(Próximo município disponível?)
    H -- Sim --> I[Chama a callback com os dados do município]
    I --> J(Continuar listagem?)
    J -- Sim --> G
    J -- Não --> K([Retorna listagem interrompida])
    H -- Não --> L([Retorna sucesso])
    classDef decisao fill:#ffffff,stroke:#3b82f6,stroke-width:1px,stroke-dasharray:2 2,color:#1d4ed8;
    class B,E,H,J decisao;
```

Legenda:

- **Callback foi informada?**: verifica se há uma função para receber os municípios listados.
- **Consulta realizada?**: verifica se foi possível obter a lista na API.
- **Próximo município disponível?**: verifica se ainda há municípios para processar.
- **Continuar listagem?**: a callback determina se a listagem continua ou é interrompida.

## `ibgeStatusMensagem`

```mermaid
flowchart TD
    A([Início]) --> B(Qual status?)
    B -- IBGE_OK --> C[Retorna: sucesso]
    B -- IBGE_ERRO_ARGUMENTO --> D[Retorna: argumento invalido]
    B -- IBGE_ERRO_CONEXAO --> E[Retorna: falha ao consultar a API do IBGE]
    B -- IBGE_ERRO_RESPOSTA --> F[Retorna: resposta da API em formato inesperado]
    B -- IBGE_ERRO_GPS --> G[Retorna: falha ao obter a localizacao GPS pela malha do IBGE]
    B -- IBGE_ERRO_CALLBACK --> H[Retorna: a listagem foi interrompida]
    B -- Outro valor --> I[Retorna: status desconhecido]
    classDef decisao fill:#ffffff,stroke:#3b82f6,stroke-width:1px,stroke-dasharray:2 2,color:#1d4ed8;
    class B decisao;
```

Legenda:

- **Qual status?**: seleciona a mensagem correspondente ao valor recebido em `status`; valores não reconhecidos produzem a mensagem de status desconhecido.
