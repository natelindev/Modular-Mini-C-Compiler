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
    
    if (values.empty()) {
        //donnot have values
        for(int i = 0;i < attributes.size() ;++i)
        {
            for (int j = 0; j < sps; ++j) {
                std::cout<<"  ";
            }
            std::cout<<"<"<<attributes[i]<<">"<<std::endl;
            for(node n: childs)
            {
                n.print(sps+1);
            }
            for (int j = 0; j < sps; ++j) {
                std::cout<<"  ";
            }
            std::cout<<"</"<<attributes[i]<<">"<<std::endl;
        }
    }
    else
    {
        //have values,then no childs
        for(int i = 0;i < attributes.size() ;++i)
        {
            for (int j = 0; j < sps; ++j) {
                std::cout<<"  ";
            }
            if (values[i] == "" && SPECIAL_EMPTY_TAG) {
                std::cout<<"<"<<attributes[i]<<" />"<<std::endl;
            }else{
                std::cout<<"<"<<attributes[i]<<">";
                if(values[i].front() == '<'){
                    std::cout<<"&lt;";
                }else if(values[i].front() == '>'){
                    std::cout<<"&gt;";
                }
                else{
                    std::cout<<values[i];
                }
                std::cout<<"</"<<attributes[i]<<">"<<std::endl;
            }
        }
    }
}
