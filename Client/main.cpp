static const int port = 8888;
#include "Client.cpp"
#include <thread>

Contacts contacts;
string myNick;


int main(int argc, char const *argv[]) {
    // Nick
    if(argc == 2) {
        myNick = argv[1];
    } else {
        std::cout << "Dime tu nombre:" << '\n';
        getline(cin, myNick);
    }

    // Inicialización
    NetworkManager* nm = new NetworkManager;
    if (!nm->init()) {
        std::cout << "Error de conexión" << '\n';
        return -1;
    }
    std::cout << "Hola " << myNick << ", bienvenido al Chat OP" << '\n';
    std::cout << "(introduce s para salir)" << '\n';

    thread receiver(receiving, nm);

    emitting(nm);

    receiver.join();
    // Finalización
    nm->end();
}
