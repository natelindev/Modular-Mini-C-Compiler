//
//  IR_Generator.h
//  IR_Generator
//
//  Created by 林理露 on 29/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef IR_Generator_h
#define IR_Generator_h
#include <string>
#include "XML_header.h"
#include <vector>
class IR_3_Address
{
public:
    std::string op,arg1,arg2,res;
    IR_3_Address(){}
    IR_3_Address(std::string o,std::string a1,std::string a2,std::string r):op(o),arg1(a1),arg2(a2),res(r){}
};

std::string build_IR(node root);
std::string symbol_look_up(std::string s,std::string scope_name,node root);
std::string get_temp_val();
#endif /* IR_Generator_h */
