#include "socketaoxd.h"

int main() {
    int chaves[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int valores[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    char ip[9];
    strcpy(ip, "127.0.0.1");

    // 1° Parâmetro -> ID do servidor
    // 2° Parâmetro -> IP do servidor
    // 3° Parâmetro -> Porta do servidor
    // 4° Parâmetro -> Porta do servidor de saída (0 para caso não tenha)
    // 5° Parâmetro -> Listagem de chaves
    // 6° Parâmetro -> Listaem de valores referente a sua respectiva chave.
    iniciarServidor(1, ip, 3000, 3001, chaves, valores);
}