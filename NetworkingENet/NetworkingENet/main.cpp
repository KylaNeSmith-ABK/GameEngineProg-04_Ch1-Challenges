#include <enet/enet.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

#include <iostream>

ENetAddress address;
ENetHost* server = nullptr;
ENetHost* client = nullptr;

bool CreateServer();
bool CreateClient();

int main( int argc, char ** argv)
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	atexit(enet_deinitialize);

	std::cout << "1) Create Server " << std::endl;
	std::cout << "2) Create Client " << std::endl;
	int UserInput = 0;
	std::cin >> UserInput;

	switch (UserInput)
	{
		case 1:
		{
			if (!CreateServer())
			{

				fprintf(stderr,
					"An error occurred while trying to create an ENet server host.\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
		case 2:
		{
			if (!CreateClient())
			{
				fprintf(stderr,
					"An error occurred while trying to create an ENet client host.\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
		default:
			std::cout << "Invalid Input" << std::endl;
	}
	
	if (server != nullptr)
	{
		enet_host_destroy(server);
	}

	if (client != nullptr)
	{
		enet_host_destroy(client);
	}
	
	return EXIT_SUCCESS;
}

bool CreateServer()
{
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);

	return server != nullptr;
}

bool CreateClient()
{
	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);

	return client != nullptr;
}
