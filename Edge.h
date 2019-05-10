/*
 * Edge.h
 *
 *  Created on: Apr 22, 2019
 *      Author: Mihai
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <string>
#include <errno.h>
#include <map>

class Edge{
public:
	std::string neighbor;
	int cost;
	//constructors
	Edge(){}
	Edge(std::string n, int c){
		this->neighbor = n;
		this->cost = c;
	}

	void setEdge(std::string n, int c){
		if (n==this->neighbor){
			this->cost = c;
		}
		else{
			perror("neighbor not found on this edge.");
			exit(EXIT_FAILURE);
		}

	}
};




#endif /* EDGE_H_ */
