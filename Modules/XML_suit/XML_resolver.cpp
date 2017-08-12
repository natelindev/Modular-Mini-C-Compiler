//
//  TreeBuilder.cpp
//  SemanticAnalyser
//
//  Created by 林理露 on 30/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include "XML_header.h"

void resolve(node &root)
{
    char cur_char;
    bool in_xml_tag = false;
    std::string tag_text,value;
    while (std::cin.get(cur_char)) {
        switch (cur_char) {
            case '<':
                tag_text.clear();
                in_xml_tag = true;
                if (value.length() > 0) {
                    unescape_xml_chars(value);
                }
                break;
            case '>':
                in_xml_tag = false;
                if (tag_text.front() != '/') {
                    //xml begining tag
                    node n;
                    std::vector<std::string> attrs_vals_pair;
                    std::string::size_type last_pos = 0,pos = 0;
                    while((pos = tag_text.find(" ", last_pos)) != std::string::npos){
                        attrs_vals_pair.push_back(tag_text.substr(last_pos,pos));
                    }
                    n.name = attrs_vals_pair.front();
                    
                    if (tag_text.back() != '/') {
                        resolve(n);
                    }
                    root.add_child(n);
                }else{
                    //xml ending tag
                    if (value.length() > 0) {
                        root.text = value;
                    }
                    value.clear();
                    return;
                }
                break;
            default:
                if(in_xml_tag){
                    tag_text.push_back(cur_char);
                }else{
                    if (isgraph(cur_char)) {
                        value.push_back(cur_char);
                    }
                }
                break;
        }
    }
}

void unescape_xml_chars(std::string &v)
{
    for(auto e_c : esc_chars)
    {
        std::string::size_type pos = 0;
        while((pos = v.find(e_c.second, pos)) != std::string::npos){
            v.replace(pos,e_c.second.length(), e_c.first);
            pos += e_c.first.length();
        }
    }
}
