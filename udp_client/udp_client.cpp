#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include<string.h>
#include <tchar.h>


using namespace std;

int main() {
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;

	char message[100];
	char incoming_message[100];

	printf("Mesazhi qe doni ta dergoni te serveri: ");
	fgets(message, 100, stdin);

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll not found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Client: connect() - failed to connect " << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Client: connect() is OK." << endl;
		cout << "Clien: Can start sending and receving data..." << endl;
	}

	if (sendto(clientSocket,
		message, strlen(message), 0, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "sendto() failed with error: " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "sendto() is OK!" << endl;
	}

	int SenderAddrSize = sizeof(clientService);
	if (recvfrom(clientSocket,
		incoming_message, sizeof(incoming_message), 0, (SOCKADDR*)&clientService, &SenderAddrSize) == SOCKET_ERROR) {
		cout << "recvfrom() failed with error: " << WSAGetLastError() << endl;
	}
	else {
		cout << "Message from server: " << incoming_message << endl;
	}

	if (closesocket(clientSocket) == SOCKET_ERROR) {
		cout << "closesocket() failed with error: " << WSAGetLastError() << endl;
		return 1;
	}
	else {
		cout << "closesocket() is OK!" << endl;
	}


	WSACleanup();
	return 0;
}