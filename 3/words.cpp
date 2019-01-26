#include <string.h>
#include <iostream>
#include <algorithm>
#include "words.h"

using namespace std;

void reverse(const char* str1, char* str2){

  unsigned j = strlen(str1) -1;

  for (unsigned i = 0; i < strlen(str1); i++){
    str2[i] = str1[j];
    j--;
  }
}

bool compare(string one, string two){
  
  char one_char;
  char two_char;

  unsigned i = 0;
  unsigned j = 0;
  
  while (i < one.length()){
    
    while (j < two.length()){
      
      if (isalpha(one[i]) && isalpha(two[j])){
	
	one_char = tolower(one[i]);
	two_char = tolower(two[j]);
	
	if (one_char != two_char){
	  return false;
	}
	  
	return compare(one.substr(i+1,one.length()),two.substr(j+1,two.length()));

      } else {

	if (!isalpha(two[j])){
	  if (j < two.length() -1){
	    j++;
	    continue;
	  }
	}

	if (!isalpha(one[i])){
	  if (i < one.length() -1){
	    i++;
	    continue;
	  }
	}

	if ((i == one.length()-1 && isalpha(two[j])) ||
	    (j == two.length()-1 && isalpha(one[i]))){

	  return false;
	}

	if (i == one.length() -1 && j == two.length() -1){
	  break;
	}
      }
    }
    
    if (i == one.length() -1 && j == two.length() -1){
      break;
    }
  }

  return true;
}

bool palindrome(string sentence){

  const char* c_sentence = sentence.c_str();
  char reverse_sentence[sentence.length()];

  strcpy(reverse_sentence, c_sentence);
  reverse(c_sentence, reverse_sentence);
  string reverse = reverse_sentence;
  
  return compare(sentence, reverse);
}

bool anagram(string str1, string str2){

  transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
  transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
  
  sort(str1.begin(), str1.end());
  sort(str2.begin(), str2.end());

  return compare(str1, str2);
}
