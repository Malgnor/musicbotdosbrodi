#include "telnet.h"

using namespace std;

TelnetClient::TelnetClient() : conectado(false), inicializado(false)
{
}

bool TelnetClient::inicializar(){
	if (inicializado) return true;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Falha. Código de erro : %d", WSAGetLastError());
		return false;
	}

	if ((meuSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Não foi possível criar o socket : %d", WSAGetLastError());
		return false;
	}

	inicializado = true;
	return inicializado;
}

bool TelnetClient::conectar(string ip, int porta){
	if (inicializado && !conectado){
		server.sin_addr.s_addr = inet_addr(ip.c_str());
		server.sin_family = AF_INET;
		server.sin_port = htons(porta);

		if (connect(meuSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			printf("Não foi possível conectar : %d", WSAGetLastError());
			conectado = false;
			return false;
		}
		conectado = true;
		return true;
	}
	return false;
}

int TelnetClient::enviar(string mensagem){
	if (conectado)
		return send(meuSocket, mensagem.c_str(), strlen(mensagem.c_str()), 0);
	else
		return -1;
}

int TelnetClient::receber(string &resposta, int tamanho){
	if (conectado){
		int tamanhoRecebido;
		char* respostaRecebida = new char[tamanho+1];
		tamanhoRecebido = recv(meuSocket, respostaRecebida, tamanho, 0);
		if (tamanhoRecebido != -1){
			respostaRecebida[tamanhoRecebido] = '\0';
			resposta = respostaRecebida;
		}
		delete[] respostaRecebida;
		return tamanhoRecebido;
	}
	else
		return -1;
}

bool TelnetClient::estaConectado(){
	return conectado;
}

TelnetClient::~TelnetClient(){
	shutdown(meuSocket, SD_BOTH);
	closesocket(meuSocket);
	WSACleanup();
	conectado = inicializado = false;
}