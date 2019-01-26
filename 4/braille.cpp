#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
#include "braille.h"

using namespace std;

const string CAPITAL_TYPE = ".....0";
const string NUMBER_TYPE = "..0000";
const string DEFAULT = "......";

map<char, string> braille_mapping =

  {
    {'a',"0....."},
    {'b',"00...."},
    {'c',"0..0.."},
    {'d',"0..00."},
    {'e',"0...0."},
    {'f',"00.0.."},
    {'g',"00.00."},
    {'h',"00..0."},
    {'i',".0.0.."},
    {'j',".0.00."},
    {'k',"0.0..."},
    {'l',"000..."},
    {'m',"0.00.."},
    {'n',"0.000."},
    {'o',"0.0.0."},
    {'p',"0000.."},
    {'q',"00000."},
    {'r',"000.0."},
    {'s',".000.."},
    {'t',".0000."},
    {'u',"0.0..0"},
    {'v',"000..0"},
    {'w',".0.000"},
    {'x',"0.00.0"},
    {'y',"0.0000"},
    {'z',"0.0.00"},
    {'.',".0..00"},
    {',',".0...."},
    {';',".00..."},
    {'-',"..0..0"},
    {'!',".00.0."},
    {'?',".00..0"},
    {'(',".00.00"},
    {')',".00.00"},
    {'1',"0....."},
    {'2',"00...."},
    {'3',"0..0.."},
    {'4',"0..00."},
    {'5',"0...0."},
    {'6',"00.0.."},
    {'7',"00.00."},
    {'8',"00..0."},
    {'9',".0.0.."},
    {'0',".0.00."}
  };

unsigned encode_character(char ch, char* braille){

  braille[0] = '\0';
  
  if (isdigit(ch)){
    strcat(braille, NUMBER_TYPE.c_str());
  }

  if (isupper(ch)){
    strcat(braille, CAPITAL_TYPE.c_str());
    ch = tolower(ch);
  }
  
  map<char, string>::iterator it = braille_mapping.begin();
  while(it != braille_mapping.end()) {

    if (it->first == ch){
      strcat(braille, (it->second).c_str());
      break;
    } else {
      it++;
    }
  }

  if (strlen(braille) == 0){
    strcat(braille, DEFAULT.c_str());
  }
  
  return strlen(braille);
}

void encode(string plaintext, char* braille){

  char* braille_char = new char;
  static bool new_word = false;

  if (new_word == true){
    braille[0] = '\0';
    new_word = false;
  }
  
  if (plaintext.length() > 0){

    char ch = plaintext[0];
    encode_character(ch, braille_char);
    strcat(braille, braille_char);

  } else {

    delete [] braille_char;
    new_word = true;
    return;
  }
  
  if (plaintext.length() == 1){

    delete [] braille_char;
    new_word = true;
    return;
    
  } else {

    plaintext = plaintext.substr(1, plaintext.length() - 1);
    encode(plaintext, braille);
  }
}

void print_braille(string plaintext, ostream& output){

  unsigned i = 0;
  unsigned j = 0;
  char* braille = new (nothrow) char;

  if (!braille){
    cerr << "Error allocating memory" << endl;
    return;
  }
  
  encode(plaintext, braille);

  while (i < 3){
  
    while (j < strlen(braille)){
      if (j % 6 == i){
	output << braille[j] << braille[j+3] << " ";
      }
      j++;
    }

    i++;
    j = 0;
    output << endl;
  } 

  while (j < plaintext.length()){

    if (isupper(plaintext[j]) ||
	isdigit(plaintext[j])){

      output << "   ";
    }
    
    output << plaintext[j] << "  ";
    j++;
  }

  cout << endl << endl;
  
  delete [] braille;
}
