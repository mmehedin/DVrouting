/*
 * router.h
 *
 *  Created on: Apr 22, 2019
 *      Author: Mihai
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Util.h"
#include "Edge.h"
#include "routetable.h"
#include <map>
#include <set>
using namespace std;

string freader(string f);
string getFileName(string path, int ret);
void fsaver(string name, string f);
std::string getexepath();
void sendHeader(int socket, int leng);
int launchConnection(int number_clients);
void * getThreadConnection(void * tid);
void sendBadHeader(int socket);

struct Router_Params {

  static int const PORTSEND=21234;
  static int const PORTRECEIVE= 21235;
  //static int const BUFFER_SIZE = 1024;

  int sockfd;
  std::map<std::string, Edge> neighbourList;
  std::map<string, RouteTableValue> routingTable;
  string myRouterIPAddress;
  string myRouterName;
  bool sending=false;
  bool receiving=false;
};


class Router
{
	private:
		//string m;

	public:
		Router_Params parameters;
		//int PORT;
		//static int const BUFFER_SIZE = 1024;

		//int sockfd;
		//std::map<std::string, Edge> neighbourList;
		//std::map<string, RouteTableValue> routingTable;
		//string myRouterIPAddress;
		//string myRouterName;

		Router(){}
		Router(std::map<std::string, Edge> nl, std::map<string, RouteTableValue> rt,  std::string ip, std::string name){
			this->parameters.neighbourList = nl;
			this->parameters.routingTable = rt;
			this->parameters.myRouterIPAddress = ip;
			this->parameters.myRouterName = name;
		}
		vector<std::string> parseMessage (unsigned char[]);
		void printRouterInfo();

		int start_sender_router(void);//client
		int start_receiver_router(void);
		void updateCost(std::map<string, RouteTableValue> rt){

		};


	};



#endif /* ROUTER_H_ */
