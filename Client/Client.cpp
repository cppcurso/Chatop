#include <iostream> // cout
#include <sys/socket.h> // sockaddr, socklen_t
#include <stdlib.h> // atoi
#include <netinet/in.h> // sockaddr_in
#include <string.h> // strlen
#include <unistd.h> // read, close
#include <arpa/inet.h> // inet_ntoa
#include "Message.cpp"

class Client {
    int sock;
public:
    bool initClient() {
        //Crear el socket:
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;

        //Dirección del servidor:
        struct sockaddr_in serverAddress;
        memset(&serverAddress, '0', sizeof(serverAddress)); // Limpia estructura serverAddress
        serverAddress.sin_family = AF_INET; // Address Family IPv4
        serverAddress.sin_port = htons(port); // Puerto de Endian de Host a Endian de Network

        return true;
    }

    bool connection() {
        struct sockaddr_in serverAddress;
        if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) return false;
        return true;
    }

    Message* receive() {
        const int bufferSize = 1024;
        char buffer[bufferSize] = {0};

        // Recibir mensaje
        int n = read(sock, buffer, bufferSize);

        if (n > 0) {
            Message* m = new Message;
            m->text = buffer;
            m->user.address = address;
            return m;
        } else {
            return NULL;
        }
    }

    void sendClient(Message* message) {
        const char* m = message->text.c_str();

        send(sock, m, strlen(m), 0);
    }
};
