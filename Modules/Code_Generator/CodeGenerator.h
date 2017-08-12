//
//  CodeGenerator.h
//  CodeGenerator
//
//  Created by 林理露 on 31/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef CodeGenerator_h
#define CodeGenerator_h
#include <string>

void init_code_generate();
void func_code_generate(node root);
bool is_number(std::string s);
void register_allocate(node root);

#endif /* CodeGenerator_h */
