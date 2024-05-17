#pragma once

#include <iostream>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>

template <typename T> class SocketBase
{
public:
	SocketBase(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
	std::byte toByte(const T& data);
protected:
	int socSocket;
	sockaddr_in socAddress;
};

template <typename T> class SocketServer : public SocketBase<T>
{
public:
	SocketServer(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
	void startServer();
};

template <typename T> class SocketClient : public SocketBase<T>
{
public:
	SocketClient(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr );
	void sendData();
};

template <typename T>
SocketBase<T>::SocketBase(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr )
{
    socSocket = socket(sinfamily, type, protocol);
    socAddress.sin_family = sinfamily;
    socAddress.sin_port = sinport;
    socAddress.sin_addr.s_addr = saddr;
}

template <typename T>
std::byte SocketBase<T>::toByte(const T& data)
{
    return data;
}

template <typename T>
SocketServer<T>::SocketServer(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr)
    : SocketBase<T>(type, protocol, sinfamily, sinport, saddr)
{
}


template <typename T>
void SocketServer<T>::startServer()
{
    if (bind(this->socSocket, (struct sockaddr*)&this->socAddress,
        sizeof(this->socAddress)) < 0) {
        std::cout << "bind() failed: " << std::endl;
        close(this->socSocket);
    }
    else {
        std::cout << "bind() is OK!" << std::endl;
    }

    if (listen(this->socSocket, 5) < 0) {
        std::cout << "listen(): Error listening on socket: " << std::endl;
    }
    else {
        std::cout << "listen() is OK! I'm waiting for new connections..." << std::endl;
    }

    while (true) {
        int clientSocket = accept(this->socSocket, nullptr, nullptr);

        if (clientSocket < 0) {
            std::cout << "accept failed: " << std::endl;
        }
        else {
            std::cout << "accept() is OK!" << std::endl;
        }
        // recieving data 
        char buffer[1024] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << "Message from client: " << buffer
            << std::endl;

    }

    close(this->socSocket);
}

template <typename T>
SocketClient<T>::SocketClient(__socket_type type, int protocol, int sinfamily, uint16_t sinport, in_addr_t saddr )
    : SocketBase<int>(type, protocol, sinfamily, sinport, saddr)
{
}


template <typename T>
void SocketClient<T>::sendData()
{
    connect(this->socSocket, (struct sockaddr*)&this->socAddress,
        sizeof(this->socAddress));

    // sending data 
    const char* message = "Hello, server!";
    send(this->socSocket, message, 1024*sizeof(char), 0);
    // closing socket 
    close(this->socSocket);
}
