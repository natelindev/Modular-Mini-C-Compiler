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
                    if (value == "&lt") {
                        value = "<";
                    }else if (value == "&gt"){
                        value = ">";
                    }
                }
                break;
            case '>':
                in_xml_tag = false;
                if (tag_text.front() != '/') {
                    //begin of xml tag
                    node n;
                    n.add_attribute(tag_text);
                    if (tag_text.back() != '/') {
                        resolve(n);
                    }
                    root.add_child(n);
                }else{
                    ///end of xml tag
                    if (value.length() > 0) {
                        root.add_value(value);
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
