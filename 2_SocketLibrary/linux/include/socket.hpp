#pragma once

#include <iostream>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/sockios.h>
#include <ctime>
#include <chrono>

class SocketBase
{
public:
	SocketBase(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
	//std::byte toByte(const T& data);
protected:
	int socSocket;
	struct sockaddr_in socAddress;
};

class SocketServer : public SocketBase
{
public:
	SocketServer(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
    bool running = true;
    void set_running(bool val){this->running = val;}
	void startUDPServer();
    void startTCPServer();
};

class SocketClient : public SocketBase
{
public:
	SocketClient(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
	void sendUDPData(void* message);
    void sendTCPData(void* message);
};

SocketBase::SocketBase(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr )
{
    socSocket = socket(sinfamily, type, protocol);
    setsockopt(socSocket, SOL_SOCKET, SO_TIMESTAMP, 0, NULL);
    socAddress.sin_family = sinfamily;
    socAddress.sin_port = sinport;
    socAddress.sin_addr.s_addr = saddr;
}

// std::byte SocketBase:toByte(const T& data)
// {
//     return data;
// }

SocketServer::SocketServer(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr)
    : SocketBase(type, protocol, sinfamily, sinport, saddr)
{
}

void SocketServer::startUDPServer()
{
    if (bind(this->socSocket, (struct sockaddr*)&this->socAddress, sizeof(this->socAddress)) < 0) {
        std::cout << "bind() failed: " << std::endl;
        close(this->socSocket);
    }
    while (this->running) {
        char* buffer = new char[1024];
        struct sockaddr_in cliaddr;
        int n = recvfrom(this->socSocket, (char *)buffer, 1024*sizeof(char), 0, NULL, NULL);
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        if(n==-1){
            perror("recvfrom");
            throw;
        }
        auto duration = now.time_since_epoch();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        printf("Server: %lld\n", nanoseconds.count());
        if(buffer[0] == 'e'){
            break;
        }
    }

    close(this->socSocket);
}

void SocketServer::startTCPServer()
{
    if (bind(this->socSocket, (struct sockaddr*)&this->socAddress, sizeof(this->socAddress)) < 0) {
        std::cout << "bind() failed: " << std::endl;
        close(this->socSocket);
    }

    if (listen(this->socSocket, 5) < 0) {
        std::cout << "listen(): Error listening on socket: " << std::endl;
    }
    while (this->running) {
        int clientSocket = accept(this->socSocket, nullptr, nullptr);

        if (clientSocket < 0) {
            std::cout << "accept failed: " << std::endl;
            exit(0);
        }
        char buffer[1024] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        printf("Server: %lld\n", nanoseconds.count());
        if(buffer[0] == 'e'){
            break;
        }
    }

    close(this->socSocket);
}

SocketClient::SocketClient(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr )
    : SocketBase(type, protocol, sinfamily, sinport, saddr)
{
}

void SocketClient::sendUDPData(void* message)
{
    // sending data
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

    sendto(this->socSocket, message, 1024*sizeof(char), 
        0, (const struct sockaddr *) &this->socAddress,  
            sizeof(this->socAddress));
    auto duration = now.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    printf("Client: %lld\n", nanoseconds.count());
    // closing socket 
    close(this->socSocket);
}

void SocketClient::sendTCPData(void* message)
{
    connect(this->socSocket, (struct sockaddr*)&this->socAddress,
        sizeof(this->socAddress));

    // sending data 
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    send(this->socSocket, message, 1024*sizeof(char), 0);
    auto duration = now.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    printf("Client: %lld\n", nanoseconds.count());
    send(this->socSocket, message, 1024*sizeof(char), 0);
    // closing socket 
    close(this->socSocket);
}
