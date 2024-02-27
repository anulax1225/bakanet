#include <iostream>
#include <string>

//C socket includes
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() 
{
	int server_fd;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
	
	//Socket creation step
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(80);

    //Binding step
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    //Listening step
    if (listen(server_fd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::string msg = "HTTP/1.1 200 OK\r\n"
    				  "Content-Type: text/html\r\n\r\n"
    				  "<p>Hello World!</p>";
    while (true) 
    {
    	int socket;
    	//Accepting connections step
    	if ((socket
         = accept(server_fd, (struct sockaddr*)&address,
                  &addrlen))
        > 0) 
        {
        	//Sending data step
        	send(socket, msg.c_str(), msg.length(), 0);
        	close(socket);
    	}
    }
    close(server_fd);
	return 0;
}