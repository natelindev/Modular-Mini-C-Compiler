//
//  word_recognizer.h
//  Scanner
//
//  Created by 林理露 on 23/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef word_recognizer_h
#define word_recognizer_h

#include <unordered_map>
#include <string>
#include <regex>

void init_keymap();
void init_opmap();

bool is_int(std::string dgt);
bool is_float(std::string dgt);
bool is_hex(std::string dgt);
bool is_oct(std::string dgt);
bool is_separator(const char c);
bool is_keyword(std::string word);
bool is_operator(std::string op);

#endif /* word_recognizer_h */
