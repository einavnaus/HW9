#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

#include <stddef.h>
#include <iostream>
#include <cstring>
using namespace std;

Field::Field(String pattern, field_type type):
pattern(pattern), type(type){ }


//The constructor gets String after trim.
//In order to define the Field type it checks the patterns data and 
//compare it to the legal types.
Field::Field(String pattern){
	this->pattern=pattern;
	if(pattern.equals("src-port") || pattern.equals("dst-port")){
		this->type=PORT;
	} else if(pattern.equals("src-ip") || pattern.equals("dst-ip")){
		this->type=IP;
	}else{
		this->type=GENERIC;
	}
}

//no need
Field::~Field(){

}

//A getter to type private member.
field_type Field::get_type() const{
	return type;
}

//The function sends to the right "set_value" function of one of the childs, by
//checking the type memeber and casting the pointer to the right child class.
bool Field::set_value(String val){
	if(type==PORT){
		if((((Port*)this)->set_value(val))==false){
			return false;
		}
		return true;
	}
	if(type==IP){
		if((((Ip*)this)->set_value(val))==false){
			return false;
		}
		return true;
	}
	return false;
}

//The function sends to the right "match_value" function of one of the childs,by
//checking the type memeber and casting the pointer to the right child class.
bool Field::match_value(String val) const{
	if(type==PORT){
		if((((Port*)this)->match_value(val))==false){
			return false;
		}
		return true;
	}
	if(type==IP){
		if((((Ip*)this)->match_value(val))==false){
			return false;
		}
		return true;
	}
	return false;
}

//The function checks whether the data in the packet matches to "this" pattern.
bool Field::match(String packet){
	String *sub_strings = NULL;
	size_t size=0;
	packet.split(",",&sub_strings,&size);
	unsigned int counter=0;
	while(counter<size){
		size_t size_val=0;
		String *sub_val;
		sub_strings[counter].split("=",&sub_val,&size_val);
		if((size_val==MASK_SEGMENT) &&
			(sub_val[0].trim().equals(this->pattern))){
			if(match_value(sub_val[1].trim()) == true){
				delete[] sub_strings;
				delete[] sub_val;
				return true;
			}	
		}
		counter++;
		delete[] sub_val;
	}
	delete[] sub_strings;
	return false;
}