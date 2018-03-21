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
	int serverfd = listensocket(INADDR_ANY);
	
	/* main part of program where client contacts server */
	int status = connect(cmdsockfd, (struct sockaddr*) &server_addr, serverlen);
		error(status, "client: main(): connect()");
	
	/**************** TESTNG *************************/
	/* client now gets their ip and port information to send to the server */
	packet_t* P = cmdpkt(serverfd, "PORT", NULL, 0, 0);
	
	/* client sends PORT packet to initialize connection */
	sendcmd(cmdsockfd, P);
		
	/* client now waits for server's connection to thier data port */
	printf("Waiting for server\n");
	bzero((char*) &server_addr, sizeof server_addr);
	serverlen = sizeof server_addr;
	int datasockfd = accept(serverfd, (struct sockaddr*) &server_addr, &serverlen);
		error(datasockfd, "client: main(): accept()");
	
	printf("recv'd server connection\n");
	/************************************************/
	
	/* create PORT packet and sent IP:PORT to server */
	
	close(datasockfd);
	close(cmdsockfd);
	return EXIT_SUCCESS;
}
