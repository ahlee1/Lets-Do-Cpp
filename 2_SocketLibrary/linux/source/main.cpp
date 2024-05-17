#include "../include/socket.hpp"
#include <thread>

int main() 
{
	SocketServer sockServer = SocketServer<int>(SOCK_STREAM, 0, AF_INET, htons(8080), INADDR_ANY);
	std::thread t1(&SocketServer<int>::startServer, sockServer);


	for (int i = 0; i < 10; i++) {
		std::cout << i << std::endl;
		SocketClient sockClient = SocketClient<int>(SOCK_STREAM, 0, AF_INET, htons(8080), inet_addr("8.8.8.8"));
		std::thread t2(&SocketClient<int>::sendData, sockClient);

		t2.join();
	}

	t1.join();

	return 0;
}
