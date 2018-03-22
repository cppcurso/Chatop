
#include "NetworkManager.cpp"
#include <thread>

void communication(int sock, NetworkManager* nm){
    while(true){
        nm->sendMessage(nm->recieveMessage(sock), nm->contacts.users, sock);    
    }
}

int main(){
    NetworkManager* nm = new NetworkManager;
    nm->init();
    int sock;
    std::vector<thread*> threads;
    while (true){
        sock = nm->acceptConnection();
        if (sock < 0) {
            std::cerr << "Error de conexión" << '\n';
        }
        else{
            thread t(communication, sock, nm);
            threads.push_back(&t);
        }
    }
}
