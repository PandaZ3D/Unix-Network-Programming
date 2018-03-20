/*
 * Allen Aboytes
 * CMPE156 - final
 * Parsa - Winter 18
 * 
 * ftp_client.c
 * client side of ftp server application
 */

#include "netlib.h"
#include "ftp.h"

/* client side terminal command line */
#include <readline/readline.h> /* used for readline() */
#include <readline/history.h> /* use GNU history commands */

#define IP			1
#define PORT	2

int main(int argc, char** argv)
{
	/* check command line arguments */
	if(argc != 3)
	{
		fprintf(stderr, "%s <server-ip> <server-listen-port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* get the server port number of server */
	int portno = atoi(argv[PORT]);
	/* get server IP information */
	struct sockaddr_in server_addr;
	bzero((char*) &server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = inet_addr(argv[IP]);
	socklen_t serverlen = sizeof server_addr;
	
	/* client opens up both command channel socket and data socket */
	int cmdsockfd = setsocket();
	/* open data socket that will listen for server's connection */
	int datasockfd = listensocket(portno);
	
	/* main part of program where client contacts server */
	int status = connect(cmdsockfd, (struct sockaddr*) &server_addr, serverlen);
		error(status, "client: main(): connect()");
	
	/**************** TESTNG *************************/
	char buf[20];
	int bytes = sprintf(buf, "hi");
	buf[bytes] = 0;
	
	bytes = write(cmdsockfd, buf, bytes + 1);
		error(bytes, "write()");

	bytes = read(cmdsockfd, buf, 20);
		error(bytes, "write()");
		
	buf[bytes] = 0;
	printf("recvd: %s\n", buf);
	/************************************************/
	
	/* create PORT packet and sent IP:PORT to server */
	
	close(datasockfd);
	close(cmdsockfd);
	return EXIT_SUCCESS;
}