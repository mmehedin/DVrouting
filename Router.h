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

  int PORT;
  static int const BUFFER_SIZE = 1024;

  int sockfd;
  std::map<std::string, Edge> neighbourList;
  std::map<string, RouteTableValue> routingTable;
  string myRouterIPAddress;
  string myRouterName;
};


class Router
{
	private:
		string m;
	public:
		int PORT;
		static int const BUFFER_SIZE = 1024;

		int sockfd;
		std::map<std::string, Edge> neighbourList;
		std::map<string, RouteTableValue> routingTable;
		string myRouterIPAddress;
		string myRouterName;

		Router(){}
		Router(std::map<std::string, Edge> nl, std::map<string, RouteTableValue> rt,  std::string ip, std::string name){
			this->neighbourList = nl;
			this->routingTable = rt;
			this->myRouterIPAddress = ip;
			this->myRouterName = name;
		}

		void updateCost(std::map<string, RouteTableValue> rt){

		}

	};



#endif /* ROUTER_H_ */
