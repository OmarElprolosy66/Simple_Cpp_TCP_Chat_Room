#include<iostream>
#include<string>
#include<sstream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 4096

int main()
{
	const char* ipAddress = "127.0.0.1";

	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	if (WSAStartup(version, &data) != 0)
	{
		std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
		return -1;
	}

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		std::cerr << "socket creation failed: " << WSAGetLastError() << std::endl;

		WSACleanup();

		return -1;
	}

	sockaddr_in hint;

	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);

	inet_pton(AF_INET, ipAddress, &hint.sin_addr);

	if (bind(server, (sockaddr*)&hint, sizeof(hint)) == INVALID_SOCKET)
	{
		std::cerr << "bind failed: " << WSAGetLastError() << std::endl;

		closesocket(server);
		WSACleanup();

		return -1;
	}

	if (listen(server, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "listen failed: " << WSAGetLastError() << std::endl;

		closesocket(server);

		return -1;
	}

	fd_set master;

	FD_ZERO(&master);
	FD_SET(server, &master);

	bool running = true;
	while (running)
	{
		fd_set copy = master;

		int sockCount = select(0, &copy, nullptr, nullptr, nullptr);
		for (int i = 0;i < sockCount;i++)
		{
			SOCKET sock = copy.fd_array[i];

			if (sock == server)
			{
				SOCKET client = accept(server, nullptr, nullptr);

				
				FD_SET(client, &master);

				
				std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else
			{
				char buf[MAX_BUFFER_SIZE];
				ZeroMemory(buf, 4096);

				int byteRecived = recv(sock, buf, MAX_BUFFER_SIZE, 0);
				if (byteRecived <= 0)
				{
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					if (buf[0] == '\\')
					{
						std::string command(buf, byteRecived);
						if (command == "\\quit" || "\\quit\n")
						{
							running = false;
							break;
						}
						continue;
					}

					for (int i = 0;i < master.fd_count;i++)
					{
						SOCKET out = master.fd_array[i];
						if (out != server)
						{
							std::ostringstream ss;
							std::string strOut;

							if (out != sock)
							{
								ss << "SOCKET #" << sock << ": " << buf << "\r\n";

								strOut = ss.str();
							}
							else
							{
								ss.clear();
								ss << "YOU#" << ": " << buf << "\r\n";

								strOut = ss.str();
							}

							send(out, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	FD_CLR(server, &master);
	closesocket(server);

	std::string msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		SOCKET sock = master.fd_array[0];

		send(sock, msg.c_str(), msg.size() + 1, 0);

		FD_CLR(sock, &master);
		closesocket(sock);
	}

	WSACleanup();

	return 0;
}