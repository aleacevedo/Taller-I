#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <vector>

int main() {
    std::string palabra;
    std::vector<int> numeros;
    std::string bufferIP;
    std::string bufferPort;
    char inChar = '\0';
    addrinfo hints;
    addrinfo *results;
    int skt;
    bool is_connected = false;
    std::cout << "Ingrese la ip del servidor" << std::endl;
    std::cin >> bufferIP;
    std::cout << "Ingrese el puerto  del servidor" << std::endl;
    std::cin >> bufferPort;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    getaddrinfo(bufferIP.c_str(), bufferPort.c_str(), &hints, &results);

    for(struct addrinfo *ptr = results; ptr != NULL && !is_connected; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(skt != -1) {
            is_connected = (connect(skt, ptr->ai_addr, ptr->ai_addrlen) != -1 );
        };
    }



    freeaddrinfo(results);

    while(true) {
        recv(skt, &inChar, 1, 0);
        std::cout << "RECIBI: " << inChar << std::endl;
        if(inChar == ',') {
            numeros.push_back(std::stoi(palabra));
            palabra.clear();
        }
        else if(inChar == '=') {
            int res = 0;
            numeros.push_back(std::stoi(palabra));
            palabra.clear();
            std::cout << "Los numeros que recibi son: " << std::endl;
            for(auto num : numeros) {
                std::cout << num << std::endl;
                res += num;
            }
            numeros.clear();
            std::string res_str = std::to_string(res) + "\n";
            send(skt, res_str.c_str(), res_str.length(), MSG_NOSIGNAL);
        }else {
            if (inChar != '\n') palabra += inChar;
            if(palabra == "FIN") break;
        }
    }

    shutdown(skt, SHUT_RDWR);
    return 0;
}