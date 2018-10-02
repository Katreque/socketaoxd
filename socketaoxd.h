#ifndef SOCKETAOXD_H
#define SOCKETAOXD_H

#include <winsock.h>
#include <bits/stdc++.h>

using namespace std;

void iniciarCliente(char* ip, int porta) {
    struct sockaddr_in SERVIDOR;
    int socket_local;
    int nPorta;
    char IP_SERVIDOR[128+1];
    char mensagemEnvio[128];
    char mensagemRecebida[128];
    WSADATA wsaData;

    while(1) {
        int erro;
        erro = WSAStartup(MAKEWORD(2, 2), &wsaData);

        strcpy(IP_SERVIDOR, ip);

        nPorta = porta;

        if((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            printf("Erro ao criar socket.\n");
            continue;
        }

        memset(&SERVIDOR,0,sizeof(SERVIDOR));

        unsigned long ip = inet_addr(IP_SERVIDOR);

        SERVIDOR.sin_addr.s_addr = ip;
        SERVIDOR.sin_port = htons(nPorta);
        SERVIDOR.sin_family = AF_INET;

        memset(&mensagemEnvio, 0, sizeof(mensagemEnvio));
        gets(mensagemEnvio);

        if(connect(socket_local, (struct sockaddr*)&SERVIDOR, sizeof(struct sockaddr)) == -1 ){
            printf("Erro ao conectar com o servidor.\n");
            continue;
	    }

        if(send(socket_local, (char*) mensagemEnvio, sizeof(mensagemEnvio), 0) <=0) {
            printf("Erro ao enviar a mensagem.\n");
            continue;
        }

        memset(mensagemRecebida, 0, sizeof(mensagemRecebida));
        int msg = recv(socket_local, (char *)mensagemRecebida, sizeof(mensagemRecebida), 0);

        if (msg < 0) {
            printf("Erro no retorno do servidor.\n");
        } else {
            printf("Retorno: ");
            cout << mensagemRecebida << endl;
        }

        closesocket (socket_local);

        WSACleanup();
        system("pause");
        system("CLS");
    }
}

void iniciarServidor(int idServidor, char* ip, int porta, int portaProximoServidor, int* keys, int* values) {
    int portaServidor;
    WSADATA wsaDataServidor;
    SOCKET socketServidor;
    sockaddr_in	SERV;
    char mensagemRecebidaServidor[128];
    char mensagemEnvioServidor[128];

    system("cls");

    char idServidorString [10];
    itoa(idServidor, idServidorString, 10);

    portaServidor = porta;

    int erro;

    erro = WSAStartup(MAKEWORD(2, 2), &wsaDataServidor);
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);

    if (socketServidor < 0) {
        printf("Erro ao criar socket.\n");
    }

    int tamanho_servidor = sizeof(SERV);
    SERV.sin_family = AF_INET;
    SERV.sin_addr.s_addr = INADDR_ANY;
    SERV.sin_port = htons((short)portaServidor);

    if (bind(socketServidor, (struct sockaddr *) &SERV, tamanho_servidor)) {
        printf("Erro ao bindar com o cliente.\n");
		closesocket(socketServidor);
    }

    if(listen(socketServidor, SOMAXCONN)) {
        printf("Erro no listener com o cliente.\n");
    }

    system("CLS");
    printf("Servidor ON na porta %i \n", portaServidor);

    while (1) {
        struct sockaddr_in CLIENTE;
        int socket_remoto;

        int tamanho_cliente = sizeof(CLIENTE);
        printf("Aguardando cliente.\n");

        socket_remoto = accept(socketServidor, (struct sockaddr *) &CLIENTE, &tamanho_cliente);

        if (socket_remoto == INVALID_SOCKET) {
            printf("Socket do cliente inválido.\n");
            continue;
        }

        memset(&mensagemRecebidaServidor, 0, sizeof(mensagemRecebidaServidor));
        memset(&mensagemEnvioServidor, 0, sizeof(mensagemEnvioServidor));
        int received = recv(socket_remoto, (char *) mensagemRecebidaServidor, sizeof(mensagemRecebidaServidor), 0);

        int chave;
        chave = atoi(mensagemRecebidaServidor);

        char valorString[50];
        memset(valorString, 0, sizeof(valorString));

        for (int i = 0; i < 10; i++) {
            if (chave == keys[i]) {
                itoa(values[i], valorString, 10);
                break;
            }
        }

        if (!strlen(valorString)) {
            if (!!portaProximoServidor) {
                struct sockaddr_in SERVIDORMID;
                int socketMid;
                int portaMid;
                char IpServidorMid[128+1];

                strcpy(IpServidorMid, ip);

                portaMid = portaProximoServidor;

                if((socketMid = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                    printf("Erro ao criar socket mid.\n");
                }

                memset(&SERVIDORMID,0,sizeof(SERVIDORMID));

                unsigned long ip = inet_addr(IpServidorMid);

                SERVIDORMID.sin_addr.s_addr = ip;
                SERVIDORMID.sin_port = htons(portaMid);
                SERVIDORMID.sin_family = AF_INET;

                if(connect(socketMid, (struct sockaddr*)&SERVIDORMID, sizeof(struct sockaddr)) == -1 ){
                    printf("Erro ao conectar com o servidor mid.\n");
                }

                if(send(socketMid, (char*) mensagemRecebidaServidor, sizeof(mensagemRecebidaServidor), 0) <=0) {
                    printf("Erro ao enviar a mensagem mid.\n");
                }

                int msg = recv(socketMid, (char *)mensagemEnvioServidor, sizeof(mensagemEnvioServidor), 0);
            } else {
                strcat(mensagemEnvioServidor, "Não foi encontrado valor referente a sua requisição.");
            }
        } else {
            strcat(mensagemEnvioServidor, valorString);
            strcat(mensagemEnvioServidor, " - Servidor ");
            strcat(mensagemEnvioServidor, idServidorString);
        }

	    if(send(socket_remoto,(char*) mensagemEnvioServidor, sizeof(mensagemEnvioServidor), 0) <=0) {
            printf("Erro ao realizar send para o cliente.\n");
	        continue;
        }

        printf("Mensagem enviada para o cliente: ");
        cout << mensagemEnvioServidor << endl;

        closesocket(socket_remoto);
    }

    closesocket(socketServidor);
}

#endif