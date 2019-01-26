
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "soundex.h"

using namespace std;

void encode (string surname, char soundex[5]){

  static const char ones[] = {'b','f','p','v'};
  static const char twos[] = {'c','g','j','k','q','s','x','z'};
  static const char threes[] = {'d','t'};
  static const char fours[] = {'l'};
  static const char fives[] = {'m','n'};
  static const char sixes[] = {'r'};

  vector <char> ones_vec (ones, ones + sizeof(ones) / sizeof(char));
  vector <char> twos_vec (twos, twos + sizeof(twos) / sizeof(char));
  vector <char> threes_vec (threes, threes + sizeof(threes) / sizeof(char));
  vector <char> fours_vec (fours, fours + sizeof(fours) / sizeof(char));
  vector <char> fives_vec (fives, fives + sizeof(fives) / sizeof(char));
  vector <char> sixes_vec (sixes, sixes + sizeof(sixes) / sizeof(char));  
  
  soundex[0] = surname[0];

  unsigned j = 1;
  char previous_char = '0';
  char current_char;
  
  for (unsigned i = 1; i < surname.length(); i++){
    
    if (find(ones_vec.begin(), ones_vec.end(), surname[i]) != ones_vec.end()){
      current_char = '1';
    } else if (find(twos_vec.begin(), twos_vec.end(), surname[i]) != twos_vec.end()){
      current_char = '2';
    } else if (find(threes_vec.begin(), threes_vec.end(), surname[i]) != threes_vec.end()){
      current_char = '3';
    } else if (find(fours_vec.begin(), fours_vec.end(), surname[i]) != fours_vec.end()){
      current_char = '4';
    } else if (find(fives_vec.begin(), fives_vec.end(), surname[i]) != fives_vec.end()){
      current_char = '5';
    } else if (find(sixes_vec.begin(), sixes_vec.end(), surname[i]) != sixes_vec.end()){
      current_char = '6';
    } else {
      current_char = '0';
    }

    if (current_char != previous_char){
      if (current_char != '0'){
	soundex[j] = current_char;
	j++;
      }
      previous_char = current_char;
    }

    if (j == 4){
      soundex[j] = '\0';
      break;
    } else if (i == (surname.length() -1) && j < 4){
      while (j < 4){
	soundex[j] = '0';
	j++;
      }
      soundex[j] = '\0';
    } 	
  }
}

bool compare(const char one[5], const char two[5]){

  int i = 0;
  string one_s = one;
  string two_s = two;
  
  while (i < 4){
    if (one_s[i] == two_s[i]){
      if (one_s.length() != 1){
	one = (one_s.substr(1,one_s.length()-1)).c_str();
	two = (two_s.substr(1,two_s.length()-1)).c_str();
	
	if (compare(one, two) == false){
	  return false;
	} else {
	  break;
	}
      } else {
	break;
      }
    } else {
      return false;
    }
    i++;
  }

  return true;
}

unsigned count(string surname, string sentence){

  char surname_soundex[5];
  char comparison_soundex[5];
  string comparison_string;
  unsigned count = 0;

  encode(surname, surname_soundex);

  unsigned i = 0;
  unsigned boundary = 0;
  
  while(i < sentence.length()){

    if(sentence[i] == '.' ||
       sentence[i] == ',' ||
       sentence[i] == ' ' ||
       i == sentence.length() - 1){

      comparison_string = sentence.substr(boundary, i-boundary);
      encode(comparison_string, comparison_soundex);
      boundary = i+1;

      if (compare(surname_soundex, comparison_soundex) == true){
	count++;
      }
    }
    
    i++;
  }

  return count;
}
