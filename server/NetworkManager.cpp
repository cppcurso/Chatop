int const port = 8888;
#include <iostream> // cout
#include <sys/socket.h> // sockaddr, socklen_t
#include <stdlib.h> // atoi
#include <netinet/in.h> // sockaddr_in
#include <string.h> // strlen
#include <unistd.h> // read, close
#include <arpa/inet.h> // inet_ntoa
#include "Contacts.cpp"


using namespace std;

class NetworkManager {
    int listeningSocket;

    std::vector<int> sockets;

public:
    static const int maxConections = 8;
    //static int count;
    Contacts contacts;
    bool init() {
        // Crear socket
        listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (listeningSocket < 0) return false;

        // Reutilizar IP y puerto
        int enable = 1;
        if (setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable))) {
            return false;
        }

        // Asignar IP y puerto
        struct sockaddr_in address;
        address.sin_family = AF_INET; // Address Family IPv4
        address.sin_addr.s_addr = INADDR_ANY; // IP de esta máquina
        address.sin_port = htons(port); // Puerto de Endian de Host a Endian de Network

        // Asociar IP y puerto al socket
        if (bind(listeningSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
            return false;
        }

        if (listen(listeningSocket, maxConections) < 0) { // only once
            std::cerr << "Error: listen fallido" << '\n';
            return false;
        }

        return true;
    }

    int acceptConnection(){
        int commSocket;
        struct sockaddr_in address;
        std::cout << "Esperando conexiones..." << '\n';
        socklen_t addrlen = sizeof(address);
        commSocket = accept(listeningSocket, (struct sockaddr *)&address, &addrlen); //client address

        User* u = new User;
        u->address = address;
        contacts.users.push_back(u);
        // sockets.push_back(commSocket);

        cout << "Recibida conexión de " << inet_ntoa(address.sin_addr) << '\n';
        return commSocket;
    }

    Message* recieveMessage(int sock) {
        const int bufferSize = 1024;
        char buffer[bufferSize] = {0};

        // Recibir mensaje
        //int n = recvfrom(commSocket, buffer, bufferSize, 0, (struct sockaddr *)&address, &addrlen);

        int n = read(sock, buffer, bufferSize);

        if (n > 0) {
            Message* m = new Message;
            m->text = buffer;

            return m;
        } else {
            return NULL;
        }
    }

    void sendMessage(Message* message, std::vector<User*> u, int sock) {
        struct sockaddr_in address;
        const char* m = message->text.c_str();
        for (size_t i = 0; i < u.size(); i++) {
            address = u[i]->address;
            send(sock, m, strlen(m), 0);
            cout<<"¡Enviado! \n";
        }
    }

    void end(int sock) {
        close(sock);
    }
};

//static int NetworkManager::count=0;
