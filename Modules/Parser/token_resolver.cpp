//
//  token_resolver.cpp
//  Parser
//
//  Created by 林理露 on 14/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include "token_resolver.h"
#include <iostream>
#include <sstream>
#include <string>

types get_type(std::string str)
{
    if (str == "identifier") {
        return types::IDT;
    }else if (str == "keyword"){
        return types::KWD;
    }else if (str == "const_i" || str == "const_f" || str == "const_h" || str == "const_o"){
        return types::DGT;
    }else if (str == "operator"){
        return types::OPT;
    }else if (str == "separator"){
        return types::SPT;
    }else if (str == "stringLiteral"){
        return types::STR;
    }else if (str == "#"){
        return types::EOT;
    }else{
        return types::ERR;
    }
}

void reslove(std::deque<token> &tokens)
{
    char cur_char;
    bool in_xml_tag = false;
    std::string tag_text,value_text;
    std::string _n,_val,_t,_l,_vld;
    token n_tkn;
    
    while (std::cin.get(cur_char)) {
        switch (cur_char) {
            case '<':
                tag_text.clear();
                in_xml_tag = true;
                break;
            case '>':
                in_xml_tag = false;
                break;
            default:
                if (in_xml_tag) {
                    tag_text.push_back(cur_char);
                }else{
                    if (tag_text == "token") {
                        //init token
                        n_tkn.number = 0;
                        n_tkn.line = 0;
                        n_tkn.type = types::ERR;
                        n_tkn.valid = false;
                        n_tkn.value = "";
                    }else if(tag_text == "/token"){
                        //collect tokens
                        tokens.push_back(n_tkn);
                        tag_text.clear();
                    }else if(tag_text == "number"){ //number
                        _n.push_back(cur_char);
                    }else if(tag_text == "/number"){
                        n_tkn.number = std::stoi(_n);
                        _n.clear();
                        tag_text.clear();
                    }else if(tag_text == "value"){  //value
                        _val.push_back(cur_char);
                    }else if(tag_text == "/value"){
                        //translate escaped characters
                        if (_val == "&gt;") {
                            _val = ">";
                        }else if (_val == "&lt;"){
                            _val = "<";
                        }
                        n_tkn.value = _val;
                        _val.clear();
                        tag_text.clear();
                    }else if(tag_text == "type"){   //type
                        _t.push_back(cur_char);
                    }else if(tag_text == "/type"){
                        n_tkn.type = get_type(_t);
                        _t.clear();
                        tag_text.clear();
                    }else if(tag_text == "line"){   //line
                        _l.push_back(cur_char);
                    }else if(tag_text == "/line"){
                        n_tkn.line = std::stoi(_l);
                        _l.clear();
                        tag_text.clear();
                    }else if(tag_text == "valid"){  //valid
                        _vld.push_back(cur_char);
                    }else if(tag_text == "/valid"){
                        std::istringstream is(_vld);
                        is>>std::boolalpha>>n_tkn.valid;
                        _vld.clear();
                        tag_text.clear();
                    }
                }
                break;
        }
    }
}
