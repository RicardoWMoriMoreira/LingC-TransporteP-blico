#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rotas.h"

// Converte uma string para lowercase
void stringToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Cria um novo nó para a lista duplamente encadeada
No* criarNo(int id, const char* nomeLinha, const char* tipo, const char* regiao) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(EXIT_FAILURE); // Encerra o programa em caso de falha na alocação
    }
    novoNo->id = id;
    strncpy(novoNo->nomeLinha, nomeLinha, sizeof(novoNo->nomeLinha) - 1);
    novoNo->nomeLinha[sizeof(novoNo->nomeLinha) - 1] = '\0'; // Garante que a string seja terminada corretamente
    strncpy(novoNo->tipo, tipo, sizeof(novoNo->tipo) - 1);
    novoNo->tipo[sizeof(novoNo->tipo) - 1] = '\0'; // Garante que a string seja terminada corretamente
    strncpy(novoNo->regiao, regiao, sizeof(novoNo->regiao) - 1);
    novoNo->regiao[sizeof(novoNo->regiao) - 1] = '\0'; // Garante que a string seja terminada corretamente
    novoNo->anterior = NULL;
    novoNo->proximo = NULL;
    return novoNo;
}

// Insere um novo nó na lista duplamente encadeada
void inserirNaListaDupla(No** cabeca, int id, const char* nomeLinha, const char* tipo, const char* regiao) {
    No* novoNo = criarNo(id, nomeLinha, tipo, regiao);
    if (*cabeca == NULL) {
        // Se a lista estiver vazia, o novo nó se torna a cabeça
        *cabeca = novoNo;
    } else {
        // Caso contrário, encontra o último nó e adiciona o novo nó ao final
        No* temp = *cabeca;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
        novoNo->anterior = temp;
    }
}

// Carrega as rotas do arquivo, aplicando o filtro especificado
void carregarRotasDeArquivo(No** cabeca, const char* nomeArquivo, const char* filtro) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return; // Retorna em caso de erro ao abrir o arquivo
    }

    int id;
    char nomeLinha[100];
    char tipo[50];
    char regiao[50];
    char filtroLower[50];

    strncpy(filtroLower, filtro, sizeof(filtroLower) - 1);
    filtroLower[sizeof(filtroLower) - 1] = '\0';
    stringToLower(filtroLower);

    // Lê o arquivo linha por linha, buscando rotas que correspondam ao filtro
    while (fscanf(arquivo, "%d;%99[^;];%49[^;];%49[^\n]", &id, nomeLinha, tipo, regiao) == 4) {
        char tipoLower[50];
        char regiaoLower[50];

        strncpy(tipoLower, tipo, sizeof(tipoLower) - 1);
        tipoLower[sizeof(tipoLower) - 1] = '\0';
        stringToLower(tipoLower);

        strncpy(regiaoLower, regiao, sizeof(regiaoLower) - 1);
        regiaoLower[sizeof(regiaoLower) - 1] = '\0';
        stringToLower(regiaoLower);

        // Verifica se o filtro corresponde ao tipo ou à região (case-insensitive)
        if (strstr(tipoLower, filtroLower) != NULL || strstr(regiaoLower, filtroLower) != NULL) {
            inserirNaListaDupla(cabeca, id, nomeLinha, tipo, regiao);
        }
    }

    fclose(arquivo); // Fecha o arquivo após a leitura
}

// Exibe a lista de rotas na ordem em que foram inseridas
void exibirListaEmOrdem(No* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma rota encontrada.\n");
        return;
    }
    No* temp = cabeca;
    while (temp != NULL) {
        printf("ID: %d, Linha: %s, Tipo: %s, Região: %s\n", temp->id, temp->nomeLinha, temp->tipo, temp->regiao);
        temp = temp->proximo;
    }
}

// Exibe a lista de rotas na ordem inversa em que foram inseridas
void exibirListaEmOrdemInversa(No* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma rota encontrada.\n");
        return;
    }
    No* temp = cabeca;
    // Encontra o último nó da lista
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    // Percorre a lista do último nó até o primeiro
    while (temp != NULL) {
        printf("ID: %d, Linha: %s, Tipo: %s, Região: %s\n", temp->id, temp->nomeLinha, temp->tipo, temp->regiao);
        temp = temp->anterior;
    }
}

// Libera a memória alocada para a lista de rotas
void liberarLista(No* cabeca) {
    No* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp); // Libera a memória do nó atual
    }
}