#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <tchar.h>

using namespace std;

int main(int argc, char* argvp[]) {
	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;

	char RecvBuf[1024];
	int BufLen = 1024;

	char message[100];
	char incoming_message[100];

	printf("Mesazhi qe doni ta dergoni te klienti: ");
	fgets(message, 100, stdin);

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "bind() is OK!" << endl;
	}

	int SenderAddrSize = sizeof(service);
	if (recvfrom(serverSocket,
		incoming_message, sizeof(incoming_message), 0, (SOCKADDR*)&service, &SenderAddrSize) == SOCKET_ERROR) {
		cout << "recvfrom failed with error: " << WSAGetLastError() << endl;
	}
	else {
		cout << "Message from client: " << incoming_message << endl;
	}

	if (sendto(serverSocket,
		message, strlen(message), 0, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "sendto() failed with error: " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "sendto() is OK!" << endl;
	}

	if (closesocket(serverSocket) == SOCKET_ERROR) {
		cout << "closesocket() failed with error: " << WSAGetLastError() << endl;
		return 1;
	}
	else {
		cout << "closesocket() is OK!" << endl;
	}

	return 0;

}