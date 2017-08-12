//
//  main.cpp
//  IR_Generator
//
//  Created by 林理露 on 29/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include "Optimizer.h"
#include "XML_header.h"

node global_symbol_table;

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    node root;
    resolve(root);
    global_symbol_table = root.get_child(0).get_child(0).get_child(1);
    root = root.get_child(0).get_child(0).get_child(0);
    
    XML xml;
    xml.set_sub_header("IR");
    ir_root.add_attribute("Optmized_IR_3_Address");
    xml.add_child(ir_root);
    xml.add_child(global_symbol_table);
    xml.print_all(argv[2]);
    return 0;
}
