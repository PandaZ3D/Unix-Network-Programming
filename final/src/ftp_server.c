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
	
	int status, datasockfd;
	/* get the server port number of server */
	int portno = atoi(argv[PORT]);
	
	/* client opens up both command channel socket and data socket */
	int cmdsockfd = listensocket(portno);
	
	/* we now wait for a new client connection */
	struct sockaddr_in client_addr;
	socklen_t clientlen = sizeof client_addr;
	
	/* start of communication loop */
	int newclientfd = accept(cmdsockfd, (struct sockaddr*) &client_addr, &clientlen);
		error(newclientfd, "server: main(): accept()");
	
	/* now we fork for concurrency */
	packet_t* P = recvcmd(newclientfd);
		printpkt(P);
	/* send client ok packet */
	packet_t* OK = cmdpkt(newclientfd, "OKAY", "Command OK", 10, 200);
	sendcmd(newclientfd, OK);
	
	/* get client IP and port info */
	struct sockaddr_in clientdata;
	bzero((char*) &clientdata, sizeof clientdata);
	clientlen	= parseport(P, &clientdata);
	
	/* create socket to send client data */
	datasockfd = setsocket();
	
	/* connect to client */
	status = connect(datasockfd, (struct sockaddr*) &clientdata, clientlen);
		error(status, "server: main(): connect()");
	
	/* we now begin the process of the file transfer */
	int bytes;
	char buf[MAXPAY];
	
	/* wait for a command from the client */
	while(TRUE)
	{
		P = recvcmd(newclientfd);
		
		/* check if there is a valid command */
		if(strncmp(P->cmd, "QUIT", CMDLEN) == 0)
		{
			/* make sure client closed connections */
			bytes = read(newclientfd, buf, MAXPAY);
			if(bytes == 0)
				break;
		} 
		else if(strncmp(P->cmd, "LIST", CMDLEN) == 0)
		{
		/**************** TESTNG *************************/
			printf("got LIST\n");
			/* try to list files */
			printpkt(P);
			sendcmd(newclientfd, OK);
		}
		/************************************************/
	
	}
	
	/* close all connections */
	close(cmdsockfd);
	close(newclientfd);
	return EXIT_SUCCESS;
}
