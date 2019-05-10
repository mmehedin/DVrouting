/*
 * router.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Mihai
 */

#include "Router.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include "port.h"
#include <arpa/inet.h>
#include <iostream>

//----parser
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#define BUFLEN 2048
//#define MSGS 5	/* number of messages to send */
using namespace std;

int Router::start_sender_router(void) //client
{
	int MSGS = this->parameters.routingTable.size();
	struct sockaddr_in myaddr, remaddr;
	unsigned int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	/* message buffer */
	int recvlen;		/* # bytes in acknowledgement message */
	//char *server = "127.0.0.1";	/* change this to use a different server */
	char *server = (char *)this->parameters.myRouterIPAddress.c_str();


	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	//std::cout << "myaddr" << htonl(INADDR_ANY)<<endl;

	//struct sockaddr_in sa;
	//char str[INET_ADDRSTRLEN];
	// store this IP address in sa:
	//inet_pton(AF_INET, (char *)this->parameters.myRouterIPAddress.c_str(), &(sa.sin_addr));
	//myaddr.sin_addr.s_addr = sa.sin_addr.s_addr;

	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET, (char *)SERVICE_PORT, &(sa.sin_port));
	myaddr.sin_port = htons(0);
	//myaddr.sin_port = sa.sin_port;//htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}
	//Failing while trying to set the broadcast option
	//char broadcast = '1';



	//     This option is needed on the socket in order to be able to receive broadcast messages

	//   If not set the receiver will not receive broadcast messages in the local network.

	//    if(setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) < 0)

	//    {

	 //       cout<<"Error in setting Broadcast option";

	 //       close(fd);

	 //       return 0;

	  //  }


	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/* now let's send the messages */
	this->parameters.sending=true;
	//for (i=0; i < MSGS; i++) {
	for (auto const& [key, val] : this->parameters.routingTable){
		printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		//sprintf(buf, "This is packet %d", i);
		sprintf(buf, "%s %s %d",val.destination.c_str(), val.nextNode.c_str(), val.cost); //destination nextHop cost
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1) {
			perror("sendto");
			exit(1);
		}
		/* now receive an acknowledgement from the server */
		recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
                if (recvlen >= 0) {
                        buf[recvlen] = 0;	/* expect a printable string - terminate it */
                        printf("received message: \"%s\"\n", buf);
                }
	}
	close(fd);
	this->parameters.sending=false;
	return 0;
}

int Router::start_receiver_router(void) //server
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	int msgcnt = 0;			/* count # of messages we received */
	unsigned char buf[BUFLEN];	/* receive buffer */


	/* create a UDP socket */

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	//struct in_addr* ipAddress;
	//struct in_addr* ipAddress;

	//ipAddress = (struct in_addr*)this->parameters.myRouterIPAddress;//hostp->h_addr_list[0];
	//struct sockaddr_in sa;
	//char str[INET_ADDRSTRLEN];
	// store this IP address in sa:
	//inet_pton(AF_INET, (char *)this->parameters.myRouterIPAddress.c_str(), &(sa.sin_addr));
	//myaddr.sin_addr.s_addr = sa.sin_addr.s_addr;//inet_addr(t);//;htonl(INADDR_ANY);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		this->parameters.receiving=false;
		return 0;
	}

	/* now loop, receiving data and printing what we received */
	this->parameters.receiving=true;
	for (;;) {
		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\" (%d bytes)\n", buf, recvlen);
			vector<std::string> current = parseMessage(buf);
		}
		else
			printf("uh oh - something went wrong!\n");
		std::sprintf((char *)buf, "ack %d", msgcnt++);
		printf("sending response \"%s\"\n", buf);
		if (sendto(fd, buf, strlen((char*)buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
	}
	/* never exits */
	this->parameters.receiving=false;
};



vector<std::string> Router::parseMessage (unsigned char buf[]){
	memset(buf, 0, sizeof(buf));
	stringstream str;
	str<< buf;
	//string str =buf;
	//strcpy(buf, str);
	//std::string str=buf;
	istringstream iss(str.str());
	//set<std::string> tokens;
	vector<std::string> tokens;
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter(tokens));
		 //ostream_iterator<string>(cout, "\n"));
	return tokens;
}


void Router::printRouterInfo(){
	std::cout << "\n";
	std::cout << "_______________________" << std::endl;


	std::cout<<"Router name: " << this->parameters.myRouterName << std::endl;
	std::cout<<"Router IP: " << this->parameters.myRouterIPAddress << std::endl;
	std::cout<<"Sending: " << this->parameters.sending << std::endl;
	std::cout<<"Receiving: " << this->parameters.receiving <<std::endl;


	std::cout<<"Router neighbors list: " << std::endl;
	std::map<string, Edge>::iterator it = this->parameters.neighbourList.begin();
	//std::map<string, Router>::iterator it = this->parameters.neighbourList.end();
	for(it;it!=this->parameters.neighbourList.end();it++){
		//if(it2->first!=it->first){
				//if(it->second.routingTable[it]==INF);
		//}
		//std::cout << "" << << "\n";
		std::cout <<"key: "<< it->first << " -> " << it->second.neighbor << " => " << it->second.cost << std::endl;
	}


	std::cout<<"Router routing table: " << "\n";
		std::map<string, RouteTableValue>::iterator it2 = this->parameters.routingTable.begin();
		//std::map<string, Router>::iterator it = this->parameters.neighbourList.end();
		for(it2;it2!=this->parameters.routingTable.end();it2++){
			//if(it2->first!=it->first){
					//if(it->second.routingTable[it]==INF);
			//}
			//std::cout << "" << << "\n";
			std::cout <<"key: "<<it2->first << " => " <<" destination " << it2->second.destination << " => nextHop "<< it2 -> second.nextNode << " cost " << it2->second.cost << std::endl;
		}

	std::cout << "_______________________" << std::endl;
	std::cout << "\n";
}
