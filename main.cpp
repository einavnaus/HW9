#include <stddef.h>
#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "string.h"

#define FAIL 1

extern int check_args(int,char**);
extern void parse_input(Field&);

using namespace std;

//The function main gets "argv" parameter from the user that contains single 
//rule and packets. The method creating appropriate filter and checks the
// whole packet. 
int main(int argc, char** argv){
	if(check_args(argc,argv)!=0){
		return FAIL;
	}
	String filter_rule(argv[1]);
	size_t size=0;
	String *sub_strings;
	filter_rule.split("=",&sub_strings,&size);
	String name=sub_strings[0].trim();
	String val=sub_strings[1].trim();
	if(name.equals(String("src-ip")) || name.equals(String("dst-ip"))){
		Ip ip_rule(name);
		ip_rule.set_value(val);
		parse_input(ip_rule);
	} else if(name.equals(String("src-port")) ||
			name.equals(String("dst-port"))){
		Port port_rule(name);
		port_rule.set_value(val);
		parse_input(port_rule);
	}else{
		delete[] sub_strings;
		return FAIL;
	}
	delete[] sub_strings;
	return 0;
}