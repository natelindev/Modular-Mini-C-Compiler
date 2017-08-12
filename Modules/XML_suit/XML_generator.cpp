//
//  XML_generator.cpp
//  Scanner
//
//  Created by 林理露 on 23/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//
#include <iostream>
#include "XML_header.h"

XML::XML():header("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"){}
std::unordered_map<std::string,std::string> esc_chars = {
    {"<","&lt;"},
    {">","&gt;"},
    {"\'","&apos;"},
    {"\"","&quot"},
    {"&","&amp;"}
};

void XML::set_sub_header(std::string s)
{
    sub_header = s;
}

void XML::add_child(node n)
{
    childs.push_back(n);
}

void XML::print_all(std::string xml_name)
{
    std::cout<<header<<std::endl;
    std::cout<<"<"<<sub_header<<" name=\""<<xml_name<<"\">"<<std::endl;
    for(node n:childs)
    {
        n.print(1);
    }
    std::cout<<"</"<<sub_header<<">"<<std::endl;
}

void node::add_attribute(std::string attribute)
{
    attributes.push_back(attribute);
}

void node::add_value(std::string value)
{
    values.push_back(value);
}

std::string node::get_value(int n)
{
    return values[n];
}

void node::add_child(node n)
{
    childs.push_back(n);
}

node node::get_child(int n)
{
    return childs[n];
}

void node::print(int sps)
{
    if (!values.empty() && values.size() != attributes.size()) {
        std::cerr<<"Attributes and values are not corresponding!"<<std::endl;
        exit(1);
    }
    
    //handle all the escape characters in values
    for(std::string &v : values){
        escpae_xml_chars(v);
    }
    //escape in tag_text
    escpae_xml_chars(text);
    
    //print xml tag head
    bool is_empty_tag = false;
    // <xxx a="a" b="b" >
    std::cout<<"<"<<name;
    for (int i = 0; i < values.size() ; ++i) {
        std::cout<<" "<<attributes[i]<<"=\""<<values[i]<<"\"";
    }
    if (text == "" && childs.size() == 0) {
        //empty xml case <xx />
        is_empty_tag = true;
        std::cout<<" /";
    }
    std::cout<<">"<<std::endl;
    
    if (text == "") {
        //pirnt all childs
        // <c>
        // </c>
        for (int j = 0; j < sps; ++j) {
            std::cout<<"  ";
        }
        for(node n: childs)
        {
            n.print(sps+1);
        }
    }else{
        //have tag_text,then no childs
        std::cout<<text;
    }
    
    //print xml tag tail
    if (!is_empty_tag) {
        std::cout<<"</"<<name<<">"<<std::endl;
    }
}

void escpae_xml_chars(std::string &v)
{
    for(auto e_c : esc_chars)
    {
        std::string::size_type pos = 0;
        while((pos = v.find(e_c.first, pos)) != std::string::npos){
            v.replace(pos,e_c.first.length(), e_c.second);
            pos += e_c.second.length();
        }
    }
}
