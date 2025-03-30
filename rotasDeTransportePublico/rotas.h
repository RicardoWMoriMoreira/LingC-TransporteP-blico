#ifndef ROTAS_H
#define ROTAS_H

// Definição da estrutura do nó da lista duplamente encadeada
typedef struct No {
    int id;
    char nomeLinha[100];
    char tipo[50];
    char regiao[50];
    struct No *anterior;
    struct No *proximo;
} No;

// Protótipos das funções
No* criarNo(int id, const char* nomeLinha, const char* tipo, const char* regiao);
void inserirNaListaDupla(No** cabeca, int id, const char* nomeLinha, const char* tipo, const char* regiao);
void carregarRotasDeArquivo(No** cabeca, const char* nomeArquivo, const char* filtro);
void exibirListaEmOrdem(No* cabeca);
void exibirListaEmOrdemInversa(No* cabeca);
void liberarLista(No* cabeca);

#endif