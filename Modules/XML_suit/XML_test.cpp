//
//  XML_test.cpp
//  XML_suit
//
//  Created by 林理露 on 30/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include "XML_header.h"

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    node root;
    resolve(root);
    root = root.get_child(0).get_child(0).get_child(0);
    
    XML xml;
    xml.set_sub_header("XML_test");
    xml.add_child(root);
    xml.print_all(argv[2]);
    return 0;
}
