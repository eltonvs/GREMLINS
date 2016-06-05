# GREMLINS
GREMLINS - GeREnciador de Memória com LIsta eNcadeada Simples

## Sobre o Projeto
GREMLINS é um acrônimo para **G**e**RE**nciador de **M**emória com **LI**sta eNcadeada **S**imples.
Ele, basicamente, requisita ao Sistema Operacional um bloco grande de memória e o gerencia, entregando blocos menores para a aplicação quando é solicitado.

## Como ele funciona?
A classe `SLPool` é baseada basicamente em duas funções, a `Allocate` e a `Free`. A primeira é a encarregada de alocar um bloco de memória dentro da "Memory Pool" e entregá-lo à aplicação (retorna um ponteiro para o início do bloco alocado). Já o segundo libera a memória e um bloco que estava sendo utilizado na aplicação (recebe um ponteiro para o início do bloco a ser liberado).

## Compilação e Execução dos Testes
Foram desenvolvidos 3 testes diferentes para essa aplicação.

 - **1:** Validação da Classe `StoragePool` e de suas funções (verifica se tudo está funcionando corretamente).
 - **2:** Faz um teste de performance (tentando alocar uma determinada quantidade de memória em um certo período de tempo).
 - **3:** Faz um teste comparando a performance da classe `StoragePool` com o `new` e `delete` da biblioteca padrão.

Para compilar e testar, basta digitar os seguintes comandos:
```shell
make clean
make TEST_TYPE=teste_a_ser_realizado
./bin/gremlins
```

No qual o `teste_a_ser_realizado` é um número entre 1 e 3 que representa o teste a ser feito.

## Autor
Esse projeto foi desenvolvido por **Elton de Souza Vieira**
 - [GitHub](https://github.com/eltonvs)
 - [Webpage](http://www.eltonviana.com)

## Contribua
O código fonte do Projeto GREMLINS está disponível no [GitHub](https://github.com/eltonvs/GREMLINS).
