## Sobre projeto

Projeto de faculdade dedicado a estudo de algoritmos utilizando a linguagem de programação C

### V1
Lançamento de conta desenvolvido no `Windons`

### V2

# Problema

O arquivo principal não compila no `UNIX`
O arquivo `principal` estava importando um lib de outro compilador atualmente estou usando o `Linux` esse aquivo inicialmente havia sido escrito no `Windons`

Dessa forma `conio.h` foi removida poís não havia chamada de função da lib, arquivo compilado no UNIX.

## Estrutura do projeto

O projeto é simple em pequeno mais aproveitando o momento da refatoração o ideal seria ter uma boa estrutura de pastas organizadas.

Responsta gerada por IA

Uma boa estrutura de pasta para projetos em C pode variar dependendo do tamanho e complexidade do projeto, mas aqui está uma estrutura básica que você pode usar como ponto de partida:

```
projeto/
│
├── src/
│   ├── arquivo1.c
│   ├── arquivo2.c
│   └── ...
│
├── include/
│   ├── arquivo1.h
│   ├── arquivo2.h
│   └── ...
│
└── Makefile
```

src/: Pasta contendo os arquivos de código-fonte (.c). É aqui que você coloca todos os arquivos .c do seu projeto.

include/: Pasta contendo os arquivos de cabeçalho (.h). Você coloca os arquivos .h aqui, que são os cabeçalhos para os seus arquivos .c. Isso ajuda a manter uma separação clara entre a interface pública (definida nos arquivos .h) e a implementação privada (nos arquivos .c).

Makefile: Este é o arquivo Makefile que você usará para compilar seu projeto. Ele contém as regras para compilar os arquivos .c em seu projeto e criar o executável final.

## Comandos 

No GCC e em compiladores compatíveis, você pode usar a opção -dM para gerar uma lista de todas as macros definidas:

bash
Copiar código
gcc -dM -E - < /dev/null