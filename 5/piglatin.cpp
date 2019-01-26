#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "piglatin.h"

using namespace std;

const char vowels[6] = {'a','e','i','o','u','y'};

int findFirstVowel(string word){

  unsigned i = 0;
  unsigned j = 0;
  
  while (i < word.length()){

    while(j < strlen(vowels)){

      if(word[i] == vowels[j]){

	if (j == 5 && i == 0){ 
	  j++;
	  continue;
	} else if (j == 5 && i == (word.length() -1)){
	  break;
	} else {
	  return (int)i;
	}
      }
      
      j++;
    }
    
    j = 0;
    i++;
  }

  return -1;
}

void translateWord(string english, char* piglatin){
  
  int first_vowel;
  string first_part;
  string second_part;
  string translated_word;

  if (isdigit(english[0]) || english.length() == 0){

    strcpy(piglatin, english.c_str());
    return;
  }
  
  first_vowel = findFirstVowel(english);

  if (first_vowel != -1){

    first_part = english.substr(0, first_vowel);
    second_part = english.substr(first_vowel, english.length() - first_vowel);

  } else {

    english += "ay";
    strcpy(piglatin, english.c_str());
    return;
  }

  if (first_vowel == 0){

    english += "way";
    strcpy(piglatin, english.c_str());
    return;

  } else {
    
    translated_word = second_part + first_part + "ay";

    if (isupper(english[0])){

      transform(translated_word.begin(),
		translated_word.end(),
		translated_word.begin(),
		::tolower);

      translated_word[0] = toupper(translated_word[0]);
      strcpy(piglatin, translated_word.c_str());

    } else {

      strcpy(piglatin, translated_word.c_str());
    }
  }
}

void translateStreamIteratively(ifstream& inputStream, ostream& outputStream){

  char character;
  string word;
  char* translated_word = new char;
  
  if (inputStream.fail()){
    cout << "Sorry, the file couldn't be opened!\n";
    return;
  }
  
  while (!inputStream.eof()){

    inputStream.get(character);

    if (isspace(character)){

      translateWord(word, translated_word);
      outputStream << translated_word << character;
      word.clear();

    } else if (!isalnum(character)){

      if (word.length() > 0){

	translateWord(word, translated_word);
	outputStream << translated_word << character;
	word.clear();

      } else {

	outputStream << character;
      }
      
    } else {

      word += character;
    }
  }
  
  outputStream << word;
  delete [] translated_word;
}

void translateStream(ifstream& inputStream, ostream& outputStream){

  if (inputStream.eof()){
    return;
  }
  
  if (inputStream.fail()){
    cout << "Sorry, the file couldn't be opened!\n";
    return;
  }

  char character;
  string word;  
  inputStream >> word;

  if (inputStream.eof()){
    return;
  }
  
  char* translated_word = new char;
  inputStream.get(character);

  if (!isalnum(word[0])){

    translateWord(word.substr(1, word.length() - 1), translated_word);
    outputStream << word[0] << translated_word << character;

  } else if (!isalnum(word[word.length() -1])){

    translateWord(word.substr(0, word.length() - 1), translated_word);
    outputStream << translated_word << word[word.length() - 1] << character;

  } else {

    translateWord (word, translated_word);
    outputStream << translated_word << character;
  }
    
  translateStream(inputStream, outputStream);
    
  delete [] translated_word;
}
