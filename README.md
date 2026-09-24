# Jogo Torcido 

O **Jogo Torcido** é um jogo interativo de anagramas e rápida associação de palavras com interface gráfica 2D e efeitos sonoros imersivos. Desenvolvido em grupo no **terceiro período** de **Sistemas de Informação da Universidade Federal de Sergipe** para a disciplina de **Estruturas de Dados I**, o projeto combina lógica de programação, manipulação de arquivos e aplicação prática da **Estrutura de Dados Pilha (Stack)**.


## Objetivos e Dinâmica do Jogo

O jogo sorteia uma palavra aleatória de um dicionário selecionado (Português ou Inglês) e apresenta suas letras de forma completamente embaralhada.

* **Objetivo:** Formar o maior número possível de palavras válidas antes que o tempo acabe.
* **Tempo Regressivo:** O jogador inicia com 15 segundos.
* **Sistema de Recompensas:**
  * **Palavra secundária válida (presente no dicionário):** +10 pontos e +2 segundos extras.
  * **Palavra principal sorteada (descoberta completa do anagrama):** +100 pontos, tempo resetado para 15s e sorteio de uma nova palavra base.
* **Histórico e Recorde:** Salva a maior pontuação de forma persistente em arquivo de texto.


## Estrutura de Dados: Pilha por Arranjo

A estrutura fundamental do projeto é o Tipos Abstratos de Dados (TAD) **Pilha**, implementado de forma estática sequencial (arranjo).

### Operações Implementadas (`include/pilha.h`):
- `Cria(TPilha &Pilha)`: Inicializa o topo da pilha (`Topo = -1`).
- `Vazia(TPilha Pilha)` / `Cheia(TPilha Pilha)`: Verificam os limites da pilha.
- `Empilha(TPilha &Pilha, TInfo Item)`: Adiciona um novo elemento no topo.
- `Desempilha(TPilha &Pilha)`: Remove o elemento no topo.
- `TopoPilha(TPilha Pilha)`: Retorna a informação contida no topo.

### Aplicações no Jogo:
1. **Banco de Palavras:** Armazenamento sequencial do dicionário carregado em memória.
2. **Histórico de Palavras Digitadas:** Controle das palavras já acertadas durante a partida para evitar pontuações duplicadas e exibi-las dinamicamente em colunas na tela.



## Interface Gráfica e Áudio (Raylib)

O jogo utiliza a biblioteca **Raylib** para criar uma experiência multimídia fluida:
- **Interface 2D:** Navegação por telas (`MENU`, `JOGO`, `AJUDA`), botões interativos com efeito hover e captura de teclado em tempo real.
- **Efeitos Sonoros & Música:** Trilha de fundo em loop, som nos botões e alarme ao esgotar o tempo.



##  Estrutura de Diretórios

```
Jogo-Torcido/
├── assets/                  # Recursos multimídia do jogo
│   └── audio/               # Músicas de fundo e efeitos sonoros (.mp3, .wav)
├── data/                    # Dados e persistência do jogo
│   ├── dictionaries/        # Arquivos de dicionários (portugues.txt, ingles.txt)
│   └── scores/              # Arquivos de recordes mantidos entre sessões
├── include/                 # Módulos de cabeçalho C++ (.h)
│   ├── interface.h          # Funções de renderização visual e botões Raylib
│   ├── nucleo_jogo.h        # Regras do jogo, embaralhamento e validação
│   └── pilha.h              # Implementação do TAD Pilha
├── src/                     # Código-fonte principal
│   └── main.cpp             # Loop principal e gerenciamento de estados do jogo
├── Jogo_Torcido.cbp         # Arquivo de projeto para IDE Code::Blocks
├── LICENSE                  # Licença de uso do software
└── README.md                # Documentação técnica do projeto
```



## Requisitos e Compilação

### Pré-requisitos
- Compilador C++ com suporte a **C++17** (`g++`, `clang` ou `MSVC`).
- Biblioteca gráfica **[raylib](https://www.raylib.com/)** (v4.0 ou superior).

---

### Compilação via Terminal (GCC / MinGW)

No Windows (PowerShell/CMD) ou Linux, execute a compilação a partir da raiz do repositório:

```bash
g++ -Iinclude src/main.cpp -o build/bin/Jogo_Torcido.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Para executar:
```bash
.\build\bin\Jogo_Torcido.exe
```

> **Nota:** Certifique-se de executar o programa sempre a partir do diretório raiz para que as pastas `assets/` e `data/` sejam carregadas corretamente.
> 
> 📌 **Caso ocorra o erro `raylib.h: No such file or directory`:**
> O `g++` precisa saber onde a biblioteca Raylib está instalada na sua máquina. Você pode incluir o caminho da biblioteca no comando com `-I<caminho_include>` e `-L<caminho_lib>`, ou utilizar a compilação direta via **Code::Blocks** abrindo o arquivo `Jogo_Torcido.cbp`.

