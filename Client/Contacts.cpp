#include <vector>


class Contacts {
    std::vector<User*> user;

    void add(User user) {
      string nick;
        std::cout << "Nuevo usuario, nick?: " << '\n';
        getline(cin, nick);
        users.push_back(new User(nick, user.address));
    }
    string get(string nick) {
        for(auto& u : users) {
          if (u->nick == nick) {
            return u->
          }
        }
    }
};
