/*
 * freader.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: Mihai
 */

//export string fread(string f)
#include "other.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define F "example.txt"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;


string freader(string f) {
  //ofstream myfile;
  ifstream myfile;
  string line;
  string content;
  //cout << f <<endl;
  myfile.open (f);//("a.dat");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      //cout << line << '\n';
      content.append(line);
      content+=' ';
    }

    myfile.close();
    cout << "Read file " << f <<endl;
    cout << "Content is: " << content<<endl;
    return content;
  }
  else cout << "Unable to open file";

  return content;

}

std::string getexepath()
  {
	string s_cwd(getcwd(NULL,0));
	cout << "CWD is: " << s_cwd << endl;
	return s_cwd;
  }

void fsaver(string name, string f) {
	string exec_path = getexepath();
	std::ofstream out(exec_path+"/"+name);
	out << f;
	out.close();

}


