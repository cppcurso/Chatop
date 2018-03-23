
#include "NetworkManager.cpp"
#include <thread>

void communication(int sock, NetworkManager* nm, Contacts* contacts){
    Message* m = new Message;
    while(true){
        m = nm->recieveMessage(sock);
        for (size_t i = 0; i < contacts->users.size(); i++) {
            if(m != NULL){
                m->user = contacts->users[i];
                nm->sendMessage(m);
            }
            else{
                contacts->users[i]->conect = false;
                 std::cout << "Contacto desconectado." << '\n';
                 return;
            }
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
            std::cout << "hilos "<<threads.size() << '\n';
        }
    }
}
