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
#include <unordered_map>
#include <iostream>
class node{
    
public:
    std::vector<std::string> attributes;
    std::vector<node> childs;
    std::vector<std::string> values;
    
    std::string name,text;
    
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
    std::string sub_header;
    std::vector<node> childs;
    
public:
    void add_child(node n);
    void set_sub_header(std::string s);
    void print_all(std::string xml_name);
    XML();
};

extern std::unordered_map<std::string,std::string> esc_chars;

void resolve(node &root);
void escpae_xml_chars(std::string &v);
void unescape_xml_chars(std::string &v);
#endif /* XML_generator_h */
