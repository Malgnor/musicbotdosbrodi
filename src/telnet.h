#ifndef _TELNET_H_
#define _TELNET_H_

//#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <winsock2.h>
#include <string>

#pragma comment (lib,"ws2_32.lib") //Winsock library

class TelnetClient {
private:
	WSADATA wsa;
	SOCKET meuSocket;
	struct sockaddr_in server;
	bool conectado, inicializado;

public:
	TelnetClient();
	bool inicializar();
	bool conectar(std::string ip, int porta);
	int enviar(std::string mensagem);
	int receber(std::string &resposta, int tamanho);
	bool estaConectado();
	bool desconectar();
	~TelnetClient();
};


#endif