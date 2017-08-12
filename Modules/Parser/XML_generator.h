//
//  XML_generator.h
//  Scanner
//
//  Created by 林理露 on 23/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef XML_generator_h
#define XML_generator_h
#include <string>
#include <vector>

class node{
    std::vector<std::string> attributes;
    std::vector<std::string> values;
    std::vector<node> childs;
    
public:
    void add_attribute(std::string attribute);
    void add_value(std::string value);
    void add_child(node n);
    
    //Check index range before calling
    node get_child(int n);
    std::string get_value(int n);
    void print(int sps);
};

class XML{
    std::string header;
    std::vector<node> childs;
    
public:
    void add_child(node n);
    void print_all(std::string xml_name);
    XML();
};

#endif /* XML_generator_h */
