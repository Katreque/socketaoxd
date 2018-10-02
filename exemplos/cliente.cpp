#include "socketaoxd.h"

int main() {
    char ip[9];
    strcpy(ip, "127.0.0.1");

    // 1° Parâmetro -> IP do servidor
    // 2° Parâmetro -> Porta do servidor
    iniciarCliente(ip, 3000);
}