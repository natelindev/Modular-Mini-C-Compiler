//
//  Symbol_table.h
//  SemanticAnalyser
//
//  Created by 林理露 on 27/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef Symbol_table_h
#define Symbol_table_h
#include "XML_header.h"

extern node global_symbol_table;

void build_symbol_table(node root,node &father_table);
void add_attr(node &root,std::string name,std::string type,std::string id);

bool exist_in_table(std::string s,node t);

#endif /* Symbol_table_h */
