#ifndef BRAILLE_H
#define BRAILLE_H

#include <map>
#include <iostream>

extern const std::string CAPITAL_TYPE;
extern const std::string NUMBER_TYPE;
extern const std::string DEFAULT;
extern std::map<char, std::string> braille_mapping;

unsigned encode_character(char ch, char* braille);

void encode(std::string plaintext, char* braille);

void print_braille(std::string plaintext, std::ostream& output);

#endif
