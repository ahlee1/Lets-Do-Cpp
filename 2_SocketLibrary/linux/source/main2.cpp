#include "../include/socket.hpp"
#include <thread>
#include <stdio.h>
#include <string.h>

int main() 
{   
    char * myvariable = "blablabla";
    char * end = "end";
    try{
        for (int i = 0; i < 10; i++) {
        	SocketClient sockClient = SocketClient(SOCK_STREAM, 0, AF_INET, htons(8080), inet_addr("127.0.0.1"));
        	std::thread t2(&SocketClient::sendTCPData, sockClient, (void *)myvariable);

        	t2.join();
        } 
        SocketClient sockClient = SocketClient(SOCK_STREAM, 0, AF_INET, htons(8080), inet_addr("127.0.0.1"));
        sockClient.sendTCPData((void *)end);
        for (int i = 0; i < 10; i++) {
        	SocketClient sockClient = SocketClient(SOCK_DGRAM, 0, AF_INET, htons(8080), inet_addr("127.0.0.1"));
        	std::thread t2(&SocketClient::sendUDPData, sockClient, (void *)myvariable);

        	t2.join();
        } 
        sockClient = SocketClient(SOCK_DGRAM, 0, AF_INET, htons(8080), inet_addr("127.0.0.1"));
        sockClient.sendUDPData((void *)end);
    } catch(...){
        std::cout << "Error";
        throw;
    }


	return 0;
}
