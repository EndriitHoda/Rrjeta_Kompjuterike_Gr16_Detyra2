#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data

int main()
{
    system("title UDP Client");

    // initialise winsock
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // create socket
    sockaddr_in server;
    int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);

    // start communication
    while (true)
    {
        //Choossing role to server
        char message[BUFLEN];
       
        printf("Select how do you want to continue \n As guest enter guest \n As admin write code \n -> ");
       
        cin.getline(message, BUFLEN);
        if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }
        if (strcmp(message, "guest") == 0) {
            //Receving first message from server
            char answer[BUFLEN] = {};
            int answer_len;
            int alen = sizeof(sockaddr_in);
            if (answer_len = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &alen) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code: %d", WSAGetLastError());
                exit(0);
            }
            printf("Server: %s\n", answer);
            //Chossing which file to read
            char message1[BUFLEN];
            printf("Press the option you want to chose: ");
            cin.getline(message1, BUFLEN);
            if (sendto(client_socket, message1, strlen(message1), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return 3;
            }
            // Receving last data as guest from server
            char answer1[BUFLEN] = {};
            int answer1_len;
            int alen1 = sizeof(sockaddr_in);
            if (answer1_len = recvfrom(client_socket, answer1, BUFLEN, 0, (sockaddr*)&server, &alen1) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code: %d", WSAGetLastError());
                exit(0);
            }
            printf("Server: %s\n", answer1);
            exit(0);
        }

else if (strcmp(message, "12345") == 0) {
            //Receving first data from server as admin
            char answer2[BUFLEN] = {};
            int answer2_len;
            int alen2 = sizeof(sockaddr_in);
            if (answer2_len = recvfrom(client_socket, answer2, BUFLEN, 0, (sockaddr*)&server, &alen2) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code: %d", WSAGetLastError());
                exit(0);
            }
            printf("Server: %s\n", answer2);
            //Chossing to read, write, or delete file
            printf("Press the option you want to chose: ");
            char message2[BUFLEN]={};
            cin.getline(message2, BUFLEN);
            //if choosing to write
            if (strcmp(message2, "2") == 0) {
               
                if (sendto(client_socket, message2, strlen(message2), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
                //Receving from server
                char answer3[BUFLEN] = {};
                int answer3_len;
                int alen3 = sizeof(sockaddr_in);
                if (answer3_len = recvfrom(client_socket, answer3, BUFLEN, 0, (sockaddr*)&server, &alen3) == SOCKET_ERROR)
                {
                    printf("recvfrom() failed with error code: %d", WSAGetLastError());
                    exit(0);
                }
                printf("Server: %s\n", answer3);
                //Chossing with which file to continue
             
                printf("Whith wich file do you want to continue: ");
                char message3[BUFLEN] = {};
                cin.getline(message3, BUFLEN);
                if (sendto(client_socket, message3, strlen(message3), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
                //Receving from server
                char answer4[BUFLEN] = {};
                int answer4_len;
                int alen4 = sizeof(sockaddr_in);
                if (answer4_len = recvfrom(client_socket, answer4, BUFLEN, 0, (sockaddr*)&server, &alen4) == SOCKET_ERROR)
                {
                    printf("recvfrom() failed with error code: %d", WSAGetLastError());
                    exit(0);
                }
                printf("Server: %s\n", answer4);
               
                //Choose with which file to continue
                printf("Write: ");
                char message4[BUFLEN] = {};
                cin.getline(message4, BUFLEN);
                if (sendto(client_socket, message4, strlen(message4), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code: %d", WSAGetLastError());
                    return 3;
                }
                //Receving from server
                char answer5[BUFLEN] = {};
                int answer5_len;
                int alen5 = sizeof(sockaddr_in);
                if (answer5_len = recvfrom(client_socket, answer5, BUFLEN, 0, (sockaddr*)&server, &alen5) == SOCKET_ERROR)
                {
                    printf("recvfrom() failed with error code: %d", WSAGetLastError());
                    exit(0);
                }
                printf("Server: %s\n", answer5);
             
                exit(0);
               


            }

            //IF choose to delete or read
            else  {
         
            if (sendto(client_socket, message2, strlen(message2), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return 3;
            }
            //Receving from server
            char answer6[BUFLEN] = {};
            int answer6_len;
            int alen6 = sizeof(sockaddr_in);
            if (answer6_len = recvfrom(client_socket, answer6, BUFLEN, 0, (sockaddr*)&server, &alen6) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code: %d", WSAGetLastError());
                exit(0);
            }
            printf("Server: %s\n", answer6);
            //Chossing with which file to continue
            char message5[BUFLEN];
            printf("With which file do you want to continue: ");
            cin.getline(message5, BUFLEN);
            if (sendto(client_socket, message5, strlen(message5), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code: %d", WSAGetLastError());
                return 3;
            }
            //Receving from server
            char answer7[BUFLEN] = {};
            int answer7_len;
            int alen7 = sizeof(sockaddr_in);
            if (answer7_len = recvfrom(client_socket, answer7, BUFLEN, 0, (sockaddr*)&server, &alen7) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code: %d", WSAGetLastError());
                exit(0);
            }
            printf("Server: %s\n", answer7);
            exit(0);
            }
        }

//


        
    }

    closesocket(client_socket);
    WSACleanup();
}