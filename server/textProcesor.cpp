#include <string>
#include <iostream>
using namespace std;

string textProcessorMessage(string text) {
    int j;
    string newText;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '.') j = i;
        if(i > j) newText += text[i];
    }
    return newText;
}

string textProcessorUser(string text) {
    int j;
    string newText;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '.') break;
        newText += text[i];
    }
    return newText;
}

int main() {
    string text = "laura.que tal estas?";
    string message = textProcessorMessage(text);
    string message2 = textProcessorUser(text);
    std::cout << message << '\n';
    std::cout << message2 << '\n';
}
