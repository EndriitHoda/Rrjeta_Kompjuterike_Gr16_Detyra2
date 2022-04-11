#include <iostream>
#include <fstream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996)
#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

int main()
{
    system("title UDP Server");

    sockaddr_in server, client;

    // initialise winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    // create a socket
    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");
    
    while (true)
    {
        
        printf("Waiting for data... \n");
        fflush(stdout);
        char message[BUFLEN] = {};
        //Receving from clien
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }
        

        // Login as Admin
        if (strcmp(message, "12345") == 0) {
            sendto(server_socket, "---Hello client you have all Permissin to continue---\n You can read files, write files and execute files \n Press 1) to read files \n Press 2) to write files \n Press 3) to delete files", strlen("---Hello client you have all Permissin to continue---\n You can read files, write files and execute files \n Press 1) to read files \n Press 2) to write files \n Press 3) to delete files"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
            printf("----This client has all Permissions---- \n");
            printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            printf("Data: %s\n", message);
            char message2[BUFLEN] = {};
            int slen2 = sizeof(sockaddr_in);
            recvfrom(server_socket, message2, BUFLEN, 0, (sockaddr*)&client, &slen2);
           // admin reading files
            if (strcmp(message2, "1") == 0) {
                cout << "Client choose to read files \n";
                sendto(server_socket, " \n Press 1) to read test1.txt \n Press 2) to read test2.txt", strlen(" \n Press 1) to read test1.txt \n Press 2) to read test2.txt"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                //Receving from clien
                char message3[BUFLEN] = {};
                int slen3 = sizeof(sockaddr_in);
                recvfrom(server_socket, message3, BUFLEN, 0, (sockaddr*)&client, &slen3);
                //admin reading file 1
                if (strcmp(message3, "1") == 0) {
                    cout << "Client selecet to read test1.tx \n";
                    ifstream input("test.txt");
                    char data[BUFLEN];
                    while (!input.eof()) {
                        input.getline(data, BUFLEN);
                        sendto(server_socket, data, strlen(data), 0, (sockaddr*)&client, sizeof(sockaddr_in));

                    }

                }
                //admin reading file 2
                else if (strcmp(message3, "2") == 0) {
                    cout << "Client selecet read file 2 \n";
                    ifstream input2("test2.txt");
                    char data[BUFLEN];
                    while (!input2.eof()) {
                        input2.getline(data, BUFLEN);
                        sendto(server_socket, data, strlen(data), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    }
                }
                //error command
                else {
                    sendto(server_socket, "You choose a wrong number \n", strlen("You choose a wrong number \n"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    cout << "Client choose a wrong input  \n";
                }

            }
           // admin write on file
            else if  (strcmp(message2, "2") == 0) {
                cout << "Client selecet to write files \n";
                sendto(server_socket, " \n Press 1) to write to test1.txt \n Press 2) to write to test2.txt", strlen("  \n Press 1) to write to test1.txt \n Press 2) to write to test2.txt"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                char message4[BUFLEN] = {};
                int slen4 = sizeof(sockaddr_in);
                recvfrom(server_socket, message4, BUFLEN, 0, (sockaddr*)&client, &slen4);
                //admin write file 1
                if (strcmp(message4, "1") == 0) {
                    cout << "Client selecet to write test1.tx \n";
                    ofstream myfile;
                    myfile.open("test.txt");
                    sendto(server_socket, "Write ...", strlen("Write ..."), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    char message5[BUFLEN] = {};
                    int slen5 = sizeof(sockaddr_in);
                    recvfrom(server_socket, message5, BUFLEN, 0, (sockaddr*)&client, &slen5);
                    myfile << message5;
                    myfile.close();
                    sendto(server_socket, "You have write to test1.txt sucssesfully", strlen("You have write to test1.txt sucssesfully"), 0, (sockaddr*)&client, sizeof(sockaddr_in));

                }
                //admin write file 2
                else if (strcmp(message4, "2") == 0) {
                    cout << "Client selecet write file 2 \n";
                    ofstream myfile;
                    myfile.open("test2.txt");
                    sendto(server_socket, "Write ...", strlen("Write ..."), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    char message6[BUFLEN] = {};
                    int slen6 = sizeof(sockaddr_in);
                    recvfrom(server_socket, message6, BUFLEN, 0, (sockaddr*)&client, &slen6);
                    myfile << message6;
                    myfile.close();
                    sendto(server_socket, "You have write to test2.txt sucssesfully", strlen("You have write to test2.txt sucssesfully"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                }
                //error command
                else {
                    sendto(server_socket, "You choose a wrong number \n", strlen("You choose a wrong number \n"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    cout << "Client choose a wrong input  \n";
                }
            }
            //admin deleting  file
             else if (strcmp(message2, "3") == 0) {
                cout << "client selecet delete files \n";
                sendto(server_socket, " \n Press 1) to delete test1.txt \n Press 2) to delete test2.txt", strlen(" \n Press 1) to delete test1.txt \n Press 2) to delete test2.txt"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                char message7[BUFLEN] = {};
                int slen7 = sizeof(sockaddr_in);
                recvfrom(server_socket, message7, BUFLEN, 0, (sockaddr*)&client, &slen7);
                //admin delete file 1
                if (strcmp(message7, "1") == 0) {
                    cout << "Client selecet to delete test1.tx \n";
                    int status;
                    status = remove("test.txt");
                    sendto(server_socket, "test1.txt is deleted", strlen("test1.txt is deleted"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                }
                //admin delete file 2
                else if (strcmp(message7, "2") == 0) {
                    cout << "Client selecet to delete test2.tx \n";
                    int status;
                    status = remove("test2.txt");
                    sendto(server_socket, "test2.txt is deleted", strlen("test2.txt is deleted"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                }
                //error command
                else {
                    sendto(server_socket, "You choose a wrong number \n", strlen("You choose a wrong number \n"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                    cout << "Client choose a wrong input  \n";
                }
            }else {
            sendto(server_socket, "You choose a wrong number \n", strlen("You choose a wrong number \n"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
            cout << "Client choose a wrong input  \n";
                }
          
        }
        //Login as guest
        else {
            sendto(server_socket, "---This client has limited Permissions---\n You can just read files \n Press 1) to read test1.txt \n Press 2) to read test2.txt", strlen("---This client has limited Permissions---\n You can just read files \n Press 1) to read test1.txt \n Press 2) to read test2.txt"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
            printf("----This client has limited Permissions ---- \n");
            printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            printf("Data: %s\n", message);
            char message8[BUFLEN] = {};
            int slen8 = sizeof(sockaddr_in);     
            recvfrom(server_socket, message8, BUFLEN, 0, (sockaddr*)&client, &slen8);
      
            if (strcmp(message8, "1") == 0) {
                cout << "Client selecet option 1 \n";
                ifstream input("test.txt");
                char data[BUFLEN];
                while (!input.eof()) {
                    input.getline(data, BUFLEN);
                    sendto(server_socket, data, strlen(data), 0, (sockaddr*)&client, sizeof(sockaddr_in));

                }

            }
            else if (strcmp(message8, "2") == 0) {
                cout << "Client selecet option 2 \n";
                ifstream input2("test2.txt");
                char data[BUFLEN];
                while (!input2.eof()) {
                    input2.getline(data, BUFLEN);
                    sendto(server_socket, data, strlen(data), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                }
            }
            else {
                sendto(server_socket, "You choose a wrong number \n", strlen("You choose a wrong number \n"), 0, (sockaddr*)&client, sizeof(sockaddr_in));
                cout << "Client choose a wrong input  \n";
            }
           
          
        }
        cin.getline(message, BUFLEN);
        


    }

    closesocket(server_socket);
    WSACleanup();
}