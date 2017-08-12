//
//  word_recognizer.cpp
//  Scanner
//
//  Created by 林理露 on 23/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include "word_recognizer.h"
std::unordered_map<std::string, bool> key_map;
std::unordered_map<std::string, bool> opt_map;

bool is_keyword(std::string word)
{
    return key_map[word];
}

bool is_operator(std::string opt)
{
    return opt_map[opt];
}

bool is_int(std::string dgt)
{
    std::regex r("^[+-]?(?:0|[1-9]\\d*)(?:u|U|l|L|ll|LL)?$");
    std::smatch m;
    std::regex_search(dgt, m, r);
    return (m.size() > 0);
}

bool is_float(std::string dgt)
{
    std::regex r("^[+-]?\\d+(?:[.]\\d+[fFlL]?|[eE][+-]?\\d+)$");
    std::smatch m;
    std::regex_search(dgt, m, r);
    return (m.size() > 0);
}

bool is_hex(std::string dgt)
{
    std::regex r("^[+-]?0[xX][0-9a-fA-F]+$");
    std::smatch m;
    std::regex_search(dgt, m, r);
    return (m.size() > 0);
}

bool is_oct(std::string dgt)
{
    std::regex r("^[+-]?0[0-7]+$");
    std::smatch m;
    std::regex_search(dgt, m, r);
    return (m.size() > 0);
}

bool is_separator(const char c)
{
    return (c =='{' || c =='}' || c =='[' || c ==']' || c =='(' || c ==')' || c ==';');
}

void init_keymap()
{
    key_map["auto"]=true;
    key_map["break"]=true;
    key_map["case"]=true;
    key_map["char"]=true;
    key_map["const"]=true;
    key_map["continue"]=true;
    key_map["default"]=true;
    key_map["do"]=true;
    key_map["double"]=true;
    key_map["else"]=true;
    key_map["enum"]=true;
    key_map["extern"]=true;
    key_map["float"]=true;
    key_map["for"]=true;
    key_map["goto"]=true;
    key_map["if"]=true;
    key_map["int"]=true;
    key_map["long"]=true;
    key_map["register"]=true;
    key_map["return"]=true;
    key_map["short"]=true;
    key_map["signed"]=true;
    key_map["sizeof"]=true;
    key_map["static"]=true;
    key_map["struct"]=true;
    key_map["switch"]=true;
    key_map["typedef"]=true;
    key_map["union"]=true;
    key_map["unsigned"]=true;
    key_map["void"]=true;
    key_map["volatile"]=true;
    key_map["while"]=true;
}

void init_opmap()
{
    opt_map["++"] = true;
    opt_map["--"] = true;
    opt_map["."] = true;
    opt_map["->"] = true;
    opt_map["++"] = true;
    opt_map["--"] = true;
    opt_map["+ "] = true;
    opt_map["-"] = true;
    opt_map["!"] = true;
    opt_map["~"] = true;
    opt_map["*"] = true;
    opt_map["&"] = true;
    opt_map["*"] = true;
    opt_map["/"] = true;
    opt_map["%"] = true;
    opt_map["+"] = true;
    opt_map["-"] = true;
    opt_map["<<"] = true;
    opt_map[">>"] = true;
    opt_map["<"] = true;
    opt_map["<="] = true;
    opt_map[">"] = true;
    opt_map[">="] = true;
    opt_map["=="] = true;
    opt_map["!="] = true;
    opt_map["&"] = true;
    opt_map["^"] = true;
    opt_map["|"] = true;
    opt_map["&&"] = true;
    opt_map["||"] = true;
    opt_map["="] = true;
    opt_map["+="] = true;
    opt_map["-="] = true;
    opt_map["*="] = true;
    opt_map["/="] = true;
    opt_map["%="] = true;
    opt_map["<<="] = true;
    opt_map[">>="] = true;
    opt_map["&="] = true;
    opt_map["^="] = true;
    opt_map["|="] = true;
    opt_map[","] = true;
}

