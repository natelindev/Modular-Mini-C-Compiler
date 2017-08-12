//
//  Scanner.h
//  Scanner
//
//  Created by 林理露 on 29/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h
#define COMPATIBLE_MODE false
#include "word_recognizer.h"
#include "XML_generator.h"
#define handle_idt() \
{\
    if (!idt.empty()) { \
        node tk,v;\
        tk.add_attribute("token");\
        v.add_attribute("number");\
        v.add_attribute("value");\
        v.add_attribute("type");\
        v.add_attribute("line");\
        v.add_attribute("valid");\
        v.add_value(std::to_string(word_count));\
        v.add_value(idt);\
        if (is_keyword(idt)) { \
            v.add_value("keyword");\
        }else{\
            v.add_value("identifier");\
        }\
        v.add_value(std::to_string(line_count));\
        v.add_value("true");\
        tk.add_child(v);\
        token.push_back(tk);\
        ++word_count;\
        idt.clear();\
    }\
}

#define handle_opt() \
{\
    if (!opt.empty()) {\
        int _i = 0;\
        while( _i < opt.length())\
        {\
            for (int j = (int)opt.length()-1; j >= _i ; --j)\
            {\
                if (is_operator(opt.substr(_i,(j-_i+1))))\
                {\
                    node tk,v;\
                    tk.add_attribute("token");\
                    v.add_attribute("number");\
                    v.add_attribute("value");\
                    v.add_attribute("type");\
                    v.add_attribute("line");\
                    v.add_attribute("valid");\
                    v.add_value(std::to_string(word_count));\
                    v.add_value(opt.substr(_i,(j-_i+1)));\
                    v.add_value("operator");\
                    v.add_value(std::to_string(line_count));\
                    v.add_value("true");\
                    tk.add_child(v);\
                    token.push_back(tk);\
                    ++word_count;\
                    _i = j+1;\
                }\
            }\
        }\
    }\
    opt.clear();\
}

#define handle_dgt() \
{\
    if (!dgt.empty()) { \
        node tk,v;\
        tk.add_attribute("token");\
        v.add_attribute("number");\
        v.add_attribute("value");\
        v.add_attribute("type");\
        v.add_attribute("line");\
        v.add_attribute("valid");\
        v.add_value(std::to_string(word_count));\
        v.add_value(dgt);\
        if(COMPATIBLE_MODE){\
            if(is_int(dgt)||is_float(dgt)||is_hex(dgt)||is_oct(dgt))\
                v.add_value("const_i");\
            else\
                v.add_value("error");\
        }\
        else{\
            if (is_int(dgt)) { \
                v.add_value("const_i");\
            }else if (is_float(dgt)){\
                v.add_value("const_f");\
            }else if (is_hex(dgt)){\
                v.add_value("const_h");\
            }else if (is_oct(dgt)){\
                v.add_value("const_o");\
            }else{\
                v.add_value("error");\
            }\
        }\
        v.add_value(std::to_string(line_count));\
        v.add_value("true");\
        tk.add_child(v);\
        token.push_back(tk);\
        ++word_count;\
        dgt.clear();\
    }\
}

#define handle_str() \
{\
    if (!str.empty()) { \
        node tk,v;\
        tk.add_attribute("token");\
        v.add_attribute("number");\
        v.add_attribute("value");\
        v.add_attribute("type");\
        v.add_attribute("line");\
        v.add_attribute("valid");\
        v.add_value(std::to_string(word_count));\
        v.add_value(str+cur_char);\
        v.add_value("stringLiteral");\
        v.add_value(std::to_string(line_count));\
        v.add_value("true");\
        tk.add_child(v);\
        token.push_back(tk);\
        ++word_count;\
        str.clear();\
    }\
}

#define handle_spt() \
{\
    if(is_separator(cur_char)){\
        node tk,v;\
        tk.add_attribute("token");\
        v.add_attribute("number");\
        v.add_attribute("value");\
        v.add_attribute("type");\
        v.add_attribute("line");\
        v.add_attribute("valid");\
        v.add_value(std::to_string(word_count));\
        v.add_value(std::string(1,cur_char));\
        v.add_value("separator");\
        v.add_value(std::to_string(line_count));\
        v.add_value("true");\
        tk.add_child(v);\
        token.push_back(tk);\
        ++word_count;\
    }\
}

enum class states:unsigned int{
    DFT=0,//default state
    IDT=1,//identifier state
    OPT=2,//operator state
    SPT=3,//seprator state
    DGT=4,//digit state
    STR=6,//string literal state
    ERR=7//when something go wrong
};

#endif /* Scanner_h */
