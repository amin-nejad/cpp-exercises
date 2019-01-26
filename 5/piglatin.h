#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <fstream>
#include <iostream>

extern const char vowels[6];

int findFirstVowel(std::string word);

void translateWord(std::string english, char* piglatin);

void translateStreamIteratively(std::ifstream& inputStream, std::ostream& outputStream);

void translateStream(std::ifstream& inputStream, std::ostream& outputStream);

#endif
