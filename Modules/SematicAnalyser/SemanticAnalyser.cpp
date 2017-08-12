//
//  SemanticAnalyser.cpp
//  SemanticAnalyser
//
//  Created by 林理露 on 30/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include "XML_header.h"
#include "SemanticAnalyser.h"
#include "Symbol_table.h"
int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    node root;
    resolve(root);
    
    root = root.get_child(0).get_child(0).get_child(0);
    remove_empty(root);
    reduce_single(root);
    
    global_symbol_table.add_attribute("GLOBAL_SYMBOL_TABLE");
    build_symbol_table(root,global_symbol_table);
    
    XML xml;
    xml.set_sub_header("AbstractSyntaxTree");
    xml.add_child(root);
    xml.add_child(global_symbol_table);
    xml.print_all(argv[2]);
    return 0;
}


bool remove_empty(node &root)
{
    bool res = false;
//    std::cerr<<"Handling "<<root.attributes[0]<<std::endl;
    
    for(auto it = root.childs.begin() ; it != root.childs.end() ;)
    {
        if (remove_empty(*it)) {
            it = root.childs.erase(it);
//            std::cerr<<(*it).attributes[0]<<" removed."<<std::endl;
        }else{
            ++it;
        }
    }
    
    if (root.childs.size() == 0 && root.values.size() == 0) {
        res = true;
    }
    return res;
}

bool reduce_single(node &root)
{
    bool res = false;
    
    for(auto it = root.childs.begin() ; it != root.childs.end() ;++it){
        if (reduce_single(*it)) {
            (*it) = (*it).get_child(0);
        }
    }
    
    if (root.childs.size() == 1 && root.values.size() == 0) {
        res = true;
    }
    
    return res;
}
