/*
 * routetable.h
 *
 *  Created on: Apr 22, 2019
 *      Author: Mihai
 */

#ifndef ROUTETABLE_H_
#define ROUTETABLE_H_
#include <string>
#include <map>
class RouteTableValue{
public:

	std::string destination;
	std::string nextNode;//next best hop
	int cost;
	RouteTableValue(){}

	RouteTableValue(std::string d, std::string n, int c){
		this-> destination = d;
		this->nextNode = n;
		this->cost = c;

	}

	RouteTableValue(RouteTableValue const &v){
		this->destination = v.destination;
		this->nextNode = v.nextNode;
		this->cost = v.cost;
	}
};

class RouteTable{
public:
	std::map<std::string, RouteTableValue> RoutingTable;
};

#endif /* ROUTETABLE_H_ */
