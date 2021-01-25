#include "string.h"
#include "field.h"
#include "port.h"

Port::Port(String pattern):Field(pattern){
}

//Set values of Port array range. The function divides the data of 
//the parameter "String val" to the range[0] and range[1].
bool Port::set_value(String val){
	String *sub_strings;
	size_t size;
	String after_trim=val.trim();
	after_trim.split("-",&sub_strings,&size);
	if(size!=2){
		delete[] sub_strings;
		return false;
	}
	range[0]=(sub_strings[0]).to_integer();
	range[1]=(sub_strings[1]).to_integer();
	if(range[0]>range[1]){
		delete[] sub_strings;
		return false;
	}
	delete[] sub_strings;
	return true;
}

//The function checks if the data of parameter "String val" is between 
// "low" and "high" of "this" Port instance.
//("this" instance is use as port filter) 
bool Port::match_value(String val) const{
	if((val.to_integer()>=range[0])
		&& (val.to_integer()<=range[1])){
		return true;
	}
	return false;
}