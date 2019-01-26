#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <exception>
#include "substring.h"

using namespace std;

int substring_position(string arg1, string arg2){

  if(arg1.length() == 0){
    return 0;
  }
  
  unsigned i=0;

  for (unsigned j=0; j < arg2.length(); j++){
    
    if (arg1[i] == arg2[j]){

      if (!(i == (arg1.length() -1))){
	i++;
      } else {
	return j - arg1.length() + 1;
      }
      
      continue;

    } else {
      if (i == 0){
	continue;
      } else {
	i = 0;
	
	if (arg1[i] == arg2[j]){
	  
	  i++;
	}
      }
    }
  }
  
  return -1;
}

int substring_position_ptr(string arg1, string arg2){

  if(arg1.length() == 0){
    return 0;
  }
  
  const char* ptr1 = arg1.c_str();  
  const char* ptr2 = arg2.c_str();
  
  int count = 0;

  while (*ptr2 != '\0'){

    if (*ptr1 == *ptr2){

      if (*(ptr1 + 1) != '\0'){
	ptr1++;
      } else {
	return count - arg1.length() + 1;
      }
      
    } else {
      
      if (ptr1 != arg1.c_str()){

	ptr1 = arg1.c_str();
	
	if (*ptr1 == *ptr2){
	  
	  ptr1++;
	}
      }
    }

    count++;
    ptr2++;
  }
  
  return -1;

}

int substring_position_rec(string arg1, string arg2){

  if(arg1.length() == 0){
    return 0;
  }

  static unsigned length;
  length = arg1.length();
  int temp;
  temp = substring_position_rec2(arg1, arg2, length);
  length = 0;
  return temp;
}

int substring_position_rec2(string arg1, string arg2, unsigned length){

  unsigned i=0;
  int position = 0;
  
  for (unsigned j=0; j < arg2.length(); j++){

    if (arg1[i] == arg2[j]){

      if (!(i == (arg1.length() -1))){

	string arg1_substr = arg1.substr(1, arg1.length());
	string arg2_substr = arg2.substr(j+1, arg2.length());
	
	position = substring_position_rec2(arg1_substr, arg2_substr, length);

	if (position == -1){
	  if (length != arg1.length()){
	    break;
	  }
	} else {
	  if (length == arg1.length()){
	    return position + 1 - arg1.length() + j;
	  } else {
	  return position + 1;
	  }
	}

      } else {
	return 1;
      }
    } else {
      if (length != arg1.length()){

	break;
      }
    }
  }

  return -1;
}
int substring_position2(string arg1, string arg2){

  if (arg1.length() == 0){
    return 0;
  }
  
  const char* a = arg1.c_str();
  const char* b = arg2.c_str();
  const char* d = (strstr(b, a));

  if (d == nullptr){
    return -1;
  }
  
  string e = d;

  e = e.substr(0, arg1.length());

  const char* f = e.c_str();
  
  unsigned i = 0;
  
  while(i < arg2.length()){
    
    const char* c = (arg2.substr(i, arg1.length())).c_str();

    if (strcmp(c, f) == 0){
      return i;
    }
    
    i++;
  }

  return -1;
}
