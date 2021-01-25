#include "string.h"
#include "field.h"
#include "ip.h"
#include <iostream>

#define MASK_SEGMENT 2
#define SEGMENTS 4
#define TOTAL_BITS 32

Ip::Ip(String pattern): Field(pattern){
}

//Set value of IP "low" and "high" members. The function divides the data of 
//the parameter "String val" to the segments and mask.   
bool Ip::set_value(String val){
	String *divide_parts;
	size_t size;
	val.split("/",&divide_parts,&size);
	if(size>MASK_SEGMENT){
		delete[] divide_parts;
		return false;
	}
	String *four_segments;
	size_t segment_count;
	divide_parts[0].split(".",&four_segments,&segment_count);
	if(segment_count!=SEGMENTS){
		delete[] divide_parts;
		delete[] four_segments;
		return false;
	}
	unsigned int number_ip=0;
	for (int i = 0; i < SEGMENTS; ++i){
		number_ip+=four_segments[i].to_integer();
		if(i!=SEGMENTS-1){
			number_ip=number_ip<<8;
		}
	}
	int relevant_bits=divide_parts[1].to_integer();
	int dont_care_bits=TOTAL_BITS-relevant_bits;
	if(dont_care_bits<0 || dont_care_bits>32){
		delete[] divide_parts;
		delete[] four_segments;
		return false;
	}
	unsigned int mask=1<<dont_care_bits;
	mask-=1;
	if(relevant_bits==0){
		mask=0xFFFFFFFF;
	}
	this->low=number_ip&(~mask);
	this->high=number_ip | mask; 
	delete[] divide_parts;
	delete[] four_segments;
	return true;
}
//The function checks if the data of parameter "String val" is between 
// "low" and "high" of "this" Ip instance.("this" instance is use as ip filter) 
bool Ip::match_value(String val) const{
	String *four_segments;
	size_t segment_count;
	val.split(".",&four_segments,&segment_count);
	if(segment_count!=SEGMENTS){
		delete[] four_segments;
		return false;
	}
	unsigned int number_ip=0;
	for (int i = 0; i < SEGMENTS; ++i){
		number_ip+=four_segments[i].to_integer();
		if(i!=SEGMENTS-1){
			number_ip=number_ip<<8;
		}
	}

	if((number_ip>=(this->low)) && (number_ip<=(this->high))){
		delete[] four_segments;
		return true;
	}
	delete[] four_segments;
	return false;
}