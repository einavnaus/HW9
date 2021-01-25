#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"

//Initiates an empty string
String::String(){
	data=NULL;
	length=0;
}

//Initiates string from other string
String::String(const String &str){
	if(str.length==0){
		(this->data)=NULL;
	}else{
		(this->length)=str.length;
		data=new char[length+1];
		if(!data){
			return;
		}
		strcpy(data,str.data);
	}
}

//Initiates a string from char array
String::String(const char *str){
	if(!str){
		(this->length)=0;
		(this->data)=NULL;
		return;
	}
	(this->length)=strlen(str);
	data=new char[length+1];
	if(!data){
		return;
	}
	strcpy(data,str);
}

String::~String(){
	if (data!= NULL){
		delete[] data;
	}
}

//Changes this from String
String& String::operator=(const String &rhs){
	if(rhs.length==0){
		this->data=NULL;
		this->length=0;
	}else{
		char tmp[(rhs.length)+1];
		strcpy(tmp,rhs.data);
		if(data!=NULL){
			delete[] data;
		}
		this->length=rhs.length;
		data=new char[length+1];
		if(data!=NULL){
			strcpy(data,tmp);
		}
	}
	return *this;
}

//Changes this from char array
String& String::operator=(const char *str){
	if(!str){
		this->data=NULL;
		this->length=0;
	}else{
		if(data!=NULL){
			delete[] data;
		}
		this->length=strlen(str);
		data=new char[length+1];
		if(data!=NULL){
			strcpy(data,str);
		}
	}
	return *this;
}

//Returns true iff the contents of this equals to the contents of rhs
bool String::equals(const String &rhs) const{
	if(rhs.length==0 && (this->length)==0){
		return true;
	}
	
	if((this->data) == NULL || rhs.data == NULL){
		return false;
	}
	if(strcmp((this->data),rhs.data)==0){
		return true;
	}
	return false;
}

//Returns true iff the contents of this equals to rhs
bool String::equals(const char *rhs) const{
	if(!rhs){
		return NULL;
	}
	if(this->data == NULL){
		return false;
	}
	if(strcmp((this->data),rhs)==0){
		return true;
	}
	return false;
}

//Splits this to several sub-strings according to delimiters. 
//Allocates memory for output that the user must delete (using delete[])
void String::split(const char* delimiters, String** output, size_t* size) const{
	std::cout.flush();
	if(size == NULL) {
		return;
	}
	if((this->data) == NULL) {
		*size = 0;
		return;
	}
	int count_sub = 0;
	unsigned int i = 0;
	unsigned int prev_sub =0;
	if(delimiters != NULL) {
		while(i < (this->length)) {
			if(strchr(delimiters, data[i]) != NULL ) {
				if( prev_sub<i ){
					count_sub++;
				}
				prev_sub= i+1;
			}else if(strchr(delimiters, data[i]) == NULL &&
					i== ((this->length) -1)){
				count_sub++;
			}
			i++;
		}
	}

	*size = count_sub;
	if(!output) {
		return;
	}
	(*output) = new String[count_sub];
	if(!(*output)) {
		return;
	}
	
	int start_sub = 0;
	int index_sub_str = 0;
	int len_sub = 0;
	if(delimiters != NULL) {
		for(unsigned int i = 0; i < (this->length); ++i){
			if((strchr(delimiters, data[i]) != NULL) ||
				i == (((this->length) -1) )) {
				if(i == (((this->length) -1)) &&
					(strchr(delimiters, data[i]) == NULL) ){
					len_sub = i - start_sub +1;
				}else{
					len_sub = i - start_sub;
				}
				if(len_sub >0){
					char sub[len_sub + 1];
					strncpy(sub, &(this->data[start_sub]), len_sub);
					sub[len_sub] = '\0';
					(*output)[index_sub_str] = sub;
					index_sub_str++;
				}
				start_sub = i + 1;
				len_sub = 0;
				
			}
			
		}
	}
	return;
}

//Try to convert this to an integer. Returns 0 on error.
int String::to_integer() const{
	return atoi((this->trim()).data);
}

//Remove any leading or trailing white-spaces.
String String::trim() const{
	unsigned int index_head=0; 
	int index_tail=length-1;
	while(index_head<(this->length) && data[index_head]==' '){
		index_head++;
	}
	while(index_tail>=0 && data[index_tail]==' '){
		index_tail--;
	}
	int new_len=index_tail-index_head+1;
	char new_data[new_len+1];
	strncpy(new_data,data+index_head,new_len);
	new_data[new_len]='\0';

	String new_str(new_data);
	return new_str;
	
}