#define WIN32_LEAN_AND_MEAN
#define NOMIMAX
#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
#include <iostream>

//UDP
/*struct sockaddr_in {
	short sin_family; // Address family
	unsigned short sin_port; // Port
	struct in_addr sin_addr; // IP Address
	char sin_zero[8]; // Not used
};*/


int main(int argc, char** argv)
{
	//Init
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		// Log and handle error
		return false;
	}

	//Socket
	SOCKET succ = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in bindAddr;
	bindAddr.sin_family = AF_INET; // IPv4
	bindAddr.sin_port = htons(8080); // Port
	bindAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	int enable = 1;
	int res = setsockopt(succ, SOL_SOCKET, SO_REUSEADDR, (const char *)&enable, sizeof(int));
	if (res == SOCKET_ERROR) {
		// Log and handle error
	}

	res = bind(succ, (const struct sockaddr *)&bindAddr, sizeof(bindAddr));
	if (res == SOCKET_ERROR) {
		// Log and handle error
	}

	for (int i = 0; i < 5; i++)
	{

		char m_sent[5] = "Pong";
		char m_rect[10];

		int add_size = sizeof(bindAddr);
		int rect = recvfrom(succ, m_rect, sizeof(m_rect), 0, (struct sockaddr *)&bindAddr, &add_size);
		if (rect == SOCKET_ERROR)
		{
			//	Log error
		}

		std::cout << "+" << m_rect << std::endl;


		std::cout << "-" << m_sent << std::endl;
		
		int sent = sendto(succ, m_sent, sizeof(m_sent), 0, (const struct sockaddr *)&bindAddr, sizeof(bindAddr));
		if (sent == SOCKET_ERROR)
		{
			//	Log error
		}
	}
	//CleanUp
	return iResult = WSACleanup();
}

