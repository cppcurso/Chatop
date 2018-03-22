
#include "NetworkManager.cpp"
#include <thread>

void communication(int sock, NetworkManager* nm, Contacts* contacts){
    Message* m = new Message;
    while(true){
        m = nm->recieveMessage(sock);
        if(m != NULL)
            nm->sendMessage(m, sock, contacts);

        else{
             std::cout << "Contacto desconectado." << '\n';
             return;
        }
    }
}

int main(){
    NetworkManager* nm = new NetworkManager;
    Contacts* contacts = new Contacts;
    nm->init();
    int sock;
    std::vector<thread*> threads;
    while (true){
        sock = nm->acceptConnection(contacts);
        if (sock < 0) {
            std::cerr << "Error de conexión" << '\n';
        }
        else{
            thread* t = new thread(communication, sock, nm, contacts);

            threads.push_back(t);
            std::cout << threads.size() << '\n';
        }
    }
}
