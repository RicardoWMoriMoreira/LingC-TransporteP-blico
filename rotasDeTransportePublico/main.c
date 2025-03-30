#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rotas.h"

int main() {
    No* listaRotas = NULL;
    char filtro[50];

    printf("Informe o tipo de transporte ou a região desejada: ");
    fgets(filtro, sizeof(filtro), stdin);
    filtro[strcspn(filtro, "\n")] = '\0';

    carregarRotasDeArquivo(&listaRotas, "rotas_de_transportes.txt", filtro);

    printf("\nRotas em ordem:\n");
    exibirListaEmOrdem(listaRotas);

    printf("\nRotas em ordem inversa:\n");
    exibirListaEmOrdemInversa(listaRotas);

    liberarLista(listaRotas);

    return 0;
}