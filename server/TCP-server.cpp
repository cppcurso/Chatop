
#include "NetworkManager.cpp"
#include <thread>

User* findUser(int sock, Contacts* contacts){
    for (size_t i = 0; i < contacts->users.size(); i++){
        if(sock != contacts->users[i]->sock){
            return contacts->users[i];
        }
    }
}


void communication(int sock, NetworkManager* nm, Contacts* contacts){
    Message* m = new Message;
    while(true){
        m = nm->recieveMessage(sock);
        m->user = findUser(sock, contacts);
        for (size_t i = 0; i < contacts->users.size(); i++) {
            if(m != NULL){
                if(sock != contacts->users[i]->sock){
                    nm->sendMessage(m);
                }

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
