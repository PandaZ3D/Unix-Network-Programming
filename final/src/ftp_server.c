/*
 * Allen Aboytes
 * CMPE156 - final
 * Parsa - Winter 18
 * 
 * ftp_server.c
 * client side of ftp server application
 */
 
#include "netlib.h"
#include "ftp.h"

#define PORT 1

int main(int argc, char** argv)
{
	/* check command line arguments */
	if(argc != 2)
	{
		fprintf(stderr, "%s <listen-port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* get the server port number of server */
	int portno = atoi(argv[PORT]);

	/* set up server IP information
	struct sockaddr_in server_addr;
	bzero((char*) &server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	socklen_t serverlen = sizeof server_addr;
	*/
	
	/* client opens up both command channel socket and data socket */
	int cmdsockfd = listensocket(portno);
	
	/* we now wait for a new client connection */
	struct sockaddr_in client_addr;
	socklen_t clientlen = sizeof client_addr;
	
	int newclientfd = accept(cmdsockfd, (struct sockaddr*) &client_addr, &clientlen);
	
    /**************** TESTNG *************************/
	char buf[20], buf2[20];
	int byte = sprintf(buf2, "hello");
	buf2[byte] = 0;
		
	int bytes = read(newclientfd, buf, 20);
		error(bytes, "read()");
		
	buf[bytes] = 0;
	printf("recvd: %s\n", buf);
	
	bytes = write(newclientfd, buf2, byte);
		error(bytes, "write()");
	
	/************************************************/
	
	close(cmdsockfd);
	return EXIT_SUCCESS;
}
