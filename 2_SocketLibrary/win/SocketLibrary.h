#pragma once
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996) 

#include <cstddef>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>

template <typename T> class SocketBase
{
public:
	SocketBase(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr );
	std::byte toByte(const T& data);
protected:
	SOCKET socSocket;
	sockaddr_in socAddress;
};

template <typename T> class SocketServer : public SocketBase<T>
{
public:
	SocketServer(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr);
	void startServer();
};

template <typename T> class SocketClient : public SocketBase<T>
{
public:
	SocketClient(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr);
	void sendData();
};

template <typename T>
SocketBase<T>::SocketBase(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr)
{
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    }

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
SocketServer<T>::SocketServer(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr)
    : SocketBase<T>(type, protocol, sinfamily, sinport, saddr)
{
}


template <typename T>
void SocketServer<T>::startServer()
{
    if (bind(this->socSocket, (struct sockaddr*)&this->socAddress,
        sizeof(this->socAddress)) == SOCKET_ERROR) {
        std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(this->socSocket);
        WSACleanup();
    }
    else {
        std::cout << "bind() is OK!" << std::endl;
    }

    if (listen(this->socSocket, 5) == SOCKET_ERROR) {
        std::cout << "listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "listen() is OK! I'm waiting for new connections..." << std::endl;
    }

    while (true) {
        int clientSocket = accept(this->socSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "accept failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
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

    closesocket(this->socSocket);
}

template <typename T>
SocketClient<T>::SocketClient(int type, int protocol, ADDRESS_FAMILY sinfamily, USHORT sinport, ULONG saddr)
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
    closesocket(this->socSocket);
}