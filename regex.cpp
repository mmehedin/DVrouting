/*
 * regex.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Mihai
 */
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <regex>
#include <iostream>
#include "other.h"

#define PORT 8080
using namespace std;

const char *regex_str  = "\\d{10};[\\d,-]{10} [\\d,:]{8}";
const regex e ("(\\w+)(\\.)(doc|docx|pdf|html|jpeg|png)");
const regex m ("(\\w+))");
//const regex q ("((?<=content\\=).*)"); //capture anything following "content="
const regex q ("((content\\=).*)"); //capture anything following "content="
const regex c ("((name\\=).*)");
string getFileName(string path, int ret){
	 std::string temp =path;
	 string file_name = "";
	 string method_name = "";
	 string content="";
	 //ƒ << "ret is " <<ret <<endl;
	 if (ret==1){
		 std::match_results< std::string::const_iterator > mr;
		 //while( std::regex_search( temp, mr, e ) ){
			 //std::cout << mr.str( 1 ) << '\n';
		 //}
	     //std::cout << mr.str( 2 ) << '\n';
		 std::regex_search( temp, mr, e );
	     file_name = mr.str(1)+mr.str(2)+mr.str(3);
	     temp = mr.suffix().str();

	 	std::cout << "regex filname isolated is: " << file_name << endl;
	 	return file_name;
	 }
	 else if(ret==0){
		 std::match_results< std::string::const_iterator > mr;
		 std::regex_search( temp, mr, m );
		 method_name = mr.str(1);
		 temp = mr.suffix().str();

		 std::cout << "Method name is: " << method_name<<endl;
		 return method_name;
	 }else if (ret==2){
		 std::match_results< std::string::const_iterator > mr;
		 std::regex_search( temp, mr, q );
		 content = mr.str(1);
		 temp = mr.suffix().str();

		 //std::cout << "Method name is: " << content<<endl;
		 return content.substr(8,content.length());
	 }else{
		 std::match_results< std::string::const_iterator > mr;
		 std::regex_search( temp, mr, c );
		 content = mr.str(1);
		 temp = mr.suffix().str();

		 //std::cout << "Method name is: " << content<<endl;
		 return content.substr(8,content.length());

	 }

	}




