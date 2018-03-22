static const int port = 8888;

#include "Contacts.cpp"
#include <thread>

Contacts contacts;
string myNick;

string getMessage() {
    string message;
    std::cout << myNick + " dice ";
    getline(cin, message);
    return message;
}

string getNick() {
    string nick;
    std::cout << "¿Nick?";
    getline(cin, nick);
    return nick;
}

void sendToAll(Client* c, Message* message) {
    message->text = myNick + ">" + message->text;
    for (auto& u : contacts.users) {
        message->user = *u;
        c->sendClient(message);
    }
}

void send(Client* c, Message* message, string nick) {
    message->text = myNick + ">" + message->text; // Enviar a uno

    User* u = contacts.get(nick);
    if (u != NULL) {
        message->user = *u;
        c->sendClient(message);
    } else {
        std::cerr << "Usuario no encontrado" << '\n';
    }
}

void receiving(Client* c) {
    while(true) {
        Message* message = c->receive();
        contacts.add(message);
        std::cout << message->getNick() << " dice " << message->getMessage() << '\n';
    }
}

void sender(Client* c) {
    Message* message = new Message;
    while (true) {
        message->text = getMessage();

        if(message->text == "s") break;
        string nick = getNick();
        if(nick == "t") {
            sendToAll(c, message); // Enviar a todos
        } else {
            send(c, message, nick); // Enviar a uno
        }

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

    thread receiver(receiving, c);

    sender(c);

    receiver.join();
    // Finalización
    c->end();
}
