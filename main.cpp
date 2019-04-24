/*
 * main.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: Mihai
 */
/*Install boost from here: https://www.boost.org/users/download/*/
#include "other.h"
#include "Router.h"
#include "Edge.h"
#include "routetable.h"
#include <regex>
#include "Router.h"
#include <iostream>
#include <iterator>
#include <cstdlib>
//#include <boost/filesystem.hpp>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include<set>
#include <sstream>

int number_neighbors = 0;
std::string current_name="";
double current_cost = 0.;
int number_routers=0;

#include <limits>
//const double INF = std::numeric_limits <double> ::max();
const unsigned INF = 999999999;
std::string FIRST_IF= "sudo ifconfig en0 alias 192.168.10." ;
std::string SECOND_IF = " netmask 255.255.255.0";

using namespace std;
//namespace fs = boost::filesystem;

const regex pat ("[\\w.]+");
set<string> routersMaps; //list of files a.dat with cost and links
set<string> routerNames;
std::map<string, Router> nodes; //list of existing nodes
void count_files(std::string directory, std::string ext);
std::map<std::string, Edge> getCostMap(std::sregex_iterator i, std::smatch match);
void getRoutingTable(std::map<std::string, Edge> costMap, map<string, RouteTableValue> &);
void visRoutingTable();
void exchangeTables();

int main(int argc, char const *argv[])
{
	struct Router_Params rout;
	rout.PORT = atoi(argv[2]);//port of communication between routers UDP

	std::cout << "INF value " << INF << "\n\n";

	//cout <<"Filename to retrieve is: " << file_name << endl;
	string exec_path = getexepath();
	count_files(exec_path,"dat");// get the files with neighbors data

	// declaring iterators
	cout<<"\n.dat files found: "<<  "\n";
	set<string>::iterator it1;
	for (it1 = routersMaps.begin(); it1!=routersMaps.end();  ++it1)
	        cout << *it1 << " ";//.dat files found
	//std::cout <<  routersMaps << std::endl;

	//number of routers in the network
	number_routers = routersMaps.size();
	cout<<"\nNumber of routers in the network: "<< number_routers << "\n";

	//creating interfaces for all the routers
	for (int i = 1; i<=number_routers;++i){
		std::string ip = FIRST_IF + to_string(i) + SECOND_IF;
		//strcpy(ip, (to_string(i)).c_str());
		//const char *last;
		//last = ;
		//strcat(ip, (to_string(i)).c_str());
		//strcat(ip, SECOND_IF);
		cout << ip << "\n";

		system(ip.c_str());
	}

	//creating IP addresses for the routers
	//map name -> IP like a -> 192.168.10.1
	std::map<string, string> nameToIp; //list of nodes names and ip addresses


	int dig =1;
	//std::stringstream ss;
	for (it1 = routersMaps.begin(); it1!=routersMaps.end();  ++it1){

		//ss << dig;
		//std::string addr = "192.168.10."+ ss.str();
		//std::cout<<"\n"<<ss.str()<<"\n";
		std::string addr = "192.168.10."+ std::to_string(dig);
		std::string n = *it1;
		nameToIp.insert(std::pair<string, string>(n.substr(0, n.size()-4),addr));
		routerNames.insert(n.substr(0, n.size()-4));
		++dig;
		//ss.flush();
		//ss.clear();
	}
	map<string, string>::iterator it2 = nameToIp.begin();
	for ( it2 = nameToIp.begin(); it2 != nameToIp.end();  ++it2)
		        cout <<  it2->first << " => " << it2->second << '\n';;

	for (it1 = routersMaps.begin(); it1!=routersMaps.end();  ++it1){
			//get neighbors
			string content = freader(exec_path+"/"+string(*it1));
			std::match_results< std::string::const_iterator > mr;
			auto words_begin = std::sregex_iterator(content.begin(), content.end(), pat);
			auto words_end = std::sregex_iterator();
			//number_routers = std::atoi(words_begin.c_str());

			std::regex_search(content, mr, pat);
			std::sregex_iterator i = words_begin;
			std::smatch match = *i;
			++i;
			number_neighbors = std::atoi(match.str().c_str());
			cout<<"Number of current neighbors: "<< number_neighbors << "\n";

			std::map<std::string, Edge> costMap = getCostMap(i, match); //cost to reach the neighboring linked nodes

			std::string n = *it1;
			current_name = n.substr(0, n.size()-4);
			cout<<"Current name: "<< current_name << "\n";
			//create node router
			//Router(neighbor link costs, routing table, ip, name)
			std::map<string, RouteTableValue> routingTableMap;
			getRoutingTable(costMap,routingTableMap);
			//Router(std::map<std::string, Edge> nl, std::map<string, RouteTableValue> rt,  std::string ip, std::string name)

			Router r(costMap, routingTableMap, nameToIp[current_name], current_name);
			nodes[current_name] = r;

	}
	//all other values receive infinite except for self which receives 0
	std::set<string>::iterator it = routerNames.begin();
	std::map<string,Router>::iterator it3 = nodes.begin();

	for (it3 = nodes.begin(); it3 != nodes.end(); it3++)
		{
			std::map<string, RouteTableValue> r = it3 ->second.routingTable;
			//r[it3 -> first] = RouteTableValue(it3 -> first, it3 -> first, 0);
			std::map<string, RouteTableValue>::iterator it4 = r.begin();
			std::cout<< "Current node update: " << it3->first<<"\n\n";

			for (it = routerNames.begin(); it != routerNames.end(); it++)
			{
				//else if (nodes.find(it->first) == nodes.end())//not found
				if (*it==it3->first)
					nodes[it3->first].routingTable[*it] = RouteTableValue(*it, *it, 0);
				else if (r.find(*it) == r.end())//not found
				{
					nodes[it3->first].routingTable[*it] = RouteTableValue(*it, *it, INF);
				}
				//std::cout <<nodes[it3->first].routingTable[*it].destination << " => " <<nodes[it3->first].routingTable[*it].cost << '\n';
			}
		}
	visRoutingTable();
	//std::cout << "Map of cost pairs: " << costMap <<"\n";
	//while(!mr.empty){
	//	std::cout << "current word: " << mr.str( 0 ) << '\n';
	//}
		     //std::cout << mr.str( 2 ) << '\n';
		//	 std::regex_search( temp, mr, e );
		 //    file_name = mr.str(1)+mr.str(2)+mr.str(3);
		 //    temp = mr.suffix().str();

		 //	std::cout << "regex filname isolated is: " << file_name << endl;
	//struct sockaddr_in address;
    //int sock = 0, valread;
    //struct sockaddr_in serv_addr;


    return 0;
}

/**/
void getRoutingTable(std::map<std::string, Edge> costMap, map<string, RouteTableValue> &rt){
	//map<string, RouteTableValue> rt;
	for (auto const& [key, val] : costMap){
		rt[key] = RouteTableValue(key, key, val.cost);
		std::cout << key << " => " <<rt[key].destination << " => " <<rt[key].cost << '\n';
	}
	//return rt;
}

/*Ref: http://www.cplusplus.com/forum/beginner/70854/*/
void count_files(std::string directory, std::string ext)
{

	DIR *d;
	    char *p1,*p2;
	    int ret;
	    struct dirent *dir;
	    d = opendir(directory.c_str());
	    if (d)
	    {
	        while ((dir = readdir(d)) != NULL)
	        {
	            p1=strtok(dir->d_name,".");
	            p2=strtok(NULL,".");
	            if(p2!=NULL)
	            {
	                ret=strcmp(p2,ext.c_str());
	                if(ret==0)
	                {
	                    //printf("%s\t",p1);
	                	routersMaps.insert((p1+string("."))+ext);
	                }
	            }

	        }
	        closedir(d);
	    }
}

std::map<std::string, Edge> getCostMap(std::sregex_iterator i, std::smatch match){
	std::map<std::string, Edge> costMap;
	auto words_end =std::sregex_iterator();
	for ( ;i != words_end; ++i) {
			match = *i;
			current_name = match.str();
			//std::cout << match_str << '\n';
			++i;
			match =*i;
			current_cost = std::atof(match.str().c_str());
			Edge curr_edge = Edge(current_name, current_cost);
			costMap.insert(std::pair<string, Edge>(current_name, curr_edge));

	}
	//std::map<string,Edge>::iterator it = costMap.begin();
	//for (it=costMap.begin(); it!=costMap.end(); ++it)
	//	std::cout << it->first << " => " << it->second.cost << '\n';
	return costMap;
}

void visRoutingTable(){

	std::map<string,Router>::iterator it3 = nodes.begin();

	for (it3 = nodes.begin(); it3 != nodes.end(); it3++)
		{
			std::map<string, RouteTableValue> r = it3 ->second.routingTable;
			std::map<string, RouteTableValue>::iterator it4 = r.begin();

			std::cout<< "\nNode: " << it3->first<<"\n\n";
			for (it4 = r.begin(); it4 != r.end(); it4++)
			{
				std::cout <<it4->second.destination << " => " << it4->second.nextNode << " => " << it4->second.cost << '\n';
			}
		}
}

void exchangeTables(){
	std::map<string, Router>::iterator it = nodes.begin();
	std::map<string, Router>::iterator it2 = nodes.begin();
	for(it;it!=nodes.end();it++){
		for(it2;it2!=nodes.end();it2++){
			if(it2->first!=it->first){
				//if(it->second.routingTable[it]==INF);
			}
		}
	}
}
