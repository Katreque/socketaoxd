# socketaoxd
Abstração para uso de Sockets no estilo de servidores DNS em C/C++.

## Como usar?
Basta adicionar o socketaoxd.h dentro da pasta do seu projeto e dar um include nela. (Vide na pasta exemplos)

## Métodos disponíveis
Para criar um novo cliente, basta chamar o método *iniciarCliente*, no qual possui dois parâmetros: uma array de char para o IP e um int para a porta do servidor no qual o cliente irá se conectar.

```c++
#include "socketaoxd.h"

int main() {
    char ip[9];
    strcpy(ip, "127.0.0.1");

    iniciarCliente(ip, 3000);
}
```

Para criar um servidor, existem duas opções: um servidor de middleware, no qual se conecta diretamente a outro, e um servidor própriamente dito no qual retorna informações para aquele que o requisitou. Para ambos os casos, é utilizado o método *iniciarServidor*.

No servidor padrão, passamos um int como id, um array de char para o IP, outros dois ints, um para a porta do servidor e o outro para a porta do servidor de saída (zero para indicar que não há servidor de saída). E por último, dois arrays de ints com chaves e valores que serão usados dentro de cada servidor na busca da informação passada pelo cliente.

```c++
#include "socketaoxd.h"

int main() {
    int chaves[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int valores[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    char ip[9];
    strcpy(ip, "127.0.0.1");

    iniciarServidor(1, ip, 3000, 0, chaves, valores);
}
```

 Para que o servidor passe a ser do tipo middleware, é necessário passar uma porta de conexão para o servidor de saída.

```c++
#include "socketaoxd.h"

int main() {
    int chaves[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int valores[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    char ip[9];
    strcpy(ip, "127.0.0.1");

    iniciarServidor(1, ip, 3000, 3001, chaves, valores);
}
```

## Recomendações
Apesar de atacar um problema em específico, é possível adaptar a biblioteca para funcionar da forma que precisar, utilizando sockets em C/C++. O projeto está sob a licença MIT, então sinta-se livre para dar um fork e utilizar da forma que desejar. Se gostou, deixe aquela estrela marota e qualquer dúvida/problema, abra uma issue.
