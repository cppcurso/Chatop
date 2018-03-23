static const int port = 8888;

#include "Contacts.cpp"
#include <thread>
#include <mutex>
#include <unistd.h>

Contacts contacts;
string myNick;
mutex mtx;
mutex mtx2;


string getMessage() {
    string message;
    std::cout << myNick + " >> ";
    getline(cin, message);
    return message;
}

string getNick() {
    string nick;
    std::cout << "¿Nick?";
    getline(cin, nick);
    return nick;
}

void send(Client* c, Message* message) {
    c->sendClient(message);
}

void receiving(Client* c) {
    while(true) {
        Message* message = new Message;


        if (message != NULL) {
            message = c->receive();
            std::cout << message->text << '\n';
        } else {
            std::cout << "No se pudo enviar" << '\n';
        }
        break;
    }
}

void sender(Client* c) {
    Message* message = new Message;

    while (true) {

        message->text = getMessage();
        if(message->text == "s") break;
        send(c, message); // Enviar a uno
        sleep(1);
    }
    terminate();
}

int main(int argc, char const *argv[]) {
    // Nick
    if(argc == 2) {
        myNick = argv[1];
    } else {
        std::cout << "Dime tu nombre:" << '\n';
        getline(cin, myNick);
    }

    // Inicialización
    Client* c = new Client;
    if (!c->initClient()) {
        std::cout << "Error de conexión" << '\n';
        return -1;
    }

    if (!c->connection()) {
        std::cout << "Error: fallo de conexión" << '\n';
        return -1;
    }

    std::cout << "Hola " << myNick << ", bienvenido al Chat OP" << '\n';
    std::cout << "(introduce s para salir)" << '\n';
    thread sender2 (sender ,c);
    thread receiver(receiving, c);

    sender2.join();

    receiver.join();


    // Finalización
    c->end();
}
