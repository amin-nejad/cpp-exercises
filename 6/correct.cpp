#include <iostream>
#include <string.h>
#include <cmath>
#include "correct.h"

using namespace std;

/* You are supplied with two helper functions */

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */


void text_to_binary(const char* str, char* binary){

  unsigned i = 0;
  char* binary_temp = new char;
  binary[0] = '\0';
  
  while (i < strlen(str)){

    ascii_to_binary(str[i], binary_temp);
    strcat (binary, binary_temp);
    i++;
  }

  delete [] binary_temp;
}

void binary_to_text(const char* binary, char* str){

  unsigned i = 0;
  unsigned j = 0;
  char* binary_temp = new char;
  string str_temp = "";
  
  while (i < strlen(binary) + 1){

    if (i % 8 == 0 && i != 0){
      
      str_temp += binary_to_ascii(binary_temp);
      binary_temp[0] = '\0';
      j = 0;
    }

    binary_temp[j] = binary[i];
    i++;
    j++;
  }

  strcpy(str, str_temp.c_str());
  
  delete [] binary_temp;
}

void add_error_correction(const char* data, char* corrected){

  unsigned i = 0;
  string temp;
  char c1, c2, c3, d1, d2, d3, d4;

  corrected[0] = '\0';
  
  while (i < strlen(data) + 1){

    if (i % 4 == 0 && i != 0){
     
      d1 = temp[0];
      d2 = temp[1];
      d3 = temp[2];
      d4 = temp[3];
      c1 = parity(d1, d2, d4);
      c2 = parity(d1, d3, d4);
      c3 = parity(d2, d3, d4);

      temp.clear();
      temp += string(1, c1) + c2 + d1 + c3 + d2 + d3 + d4;
      strcat(corrected, temp.c_str());
      temp.clear();
    }

    temp += data[i];
    i++;
  }
}

char parity(char a, char b, char c, char d){

  char return_val;
  
  int temp = a + b + c + d - (4 * '0');

  if (temp % 2 == 0){

    return_val = '0';
    return return_val;
  }

  return_val = '1';
  return return_val;
}

unsigned decode(const char* received, char* decoded){

  unsigned i = 0;
  unsigned errors = 0;
  string temp = "";
  char b1, b2, b3, b4, b5, b6, b7, p1, p2, p3;

  decoded[0] = '\0';
  
  while (i < strlen(received) + 1){

    if (i % 7 == 0 && i != 0){

      b1 = temp[0];
      b2 = temp[1];
      b3 = temp[2];
      b4 = temp[3];
      b5 = temp[4];
      b6 = temp[5];
      b7 = temp[6];
      p1 = parity(b4, b5, b6, b7);
      p2 = parity(b2, b3, b6, b7);
      p3 = parity(b1, b3, b5, b7);

      if ((p1 + p2 + p3 - (3 * '0')) == 0){

	temp.clear();
	temp += string(1, b3) + b5 + b6 + b7;
	strcat(decoded, temp.c_str());
	temp.clear();

      } else {

	int bit_error =
	  (((int)(p1 - '0')) * 4) +
	  (((int)(p2 - '0')) * 2) +
	  (((int)(p3 - '0')) * 1);

	if (temp[bit_error -1] == '0'){
	  temp[bit_error -1] = '1';
	} else {
	  temp[bit_error -1] = '0';
	}

	b1 = temp[0];
	b2 = temp[1];
	b3 = temp[2];
	b4 = temp[3];
	b5 = temp[4];
	b6 = temp[5];
	b7 = temp[6];

	temp.clear();
	temp += string(1, b3) + b5 + b6 + b7;
	strcat(decoded, temp.c_str());
	temp.clear();
	
	errors++;
      }
    }

    temp += received[i];
    i++;
  }
  
  return errors;
}
