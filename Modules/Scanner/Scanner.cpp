//
//  Scanner.cpp
//  Scanner
//
//  Created by 林理露 on 23/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include "Scanner.h"
#include "state_map.h"

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input c filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    init_keymap();
    init_opmap();
    init_statemap();
    char cur_char;
    int line_count = 1,word_count = 1;
    std::string idt,opt,dgt,str;
    std::vector<node> token;
    states cur_state = states::DFT;
    
    while (std::cin.get(cur_char)) {
        switch (get_state(cur_state,cur_char)) {
            case states::DFT:
                handle_idt();
                handle_opt();
                handle_dgt();
                handle_str();
                handle_spt();
                if (cur_char == '\n') {
                    ++line_count;
                }
                cur_state = states::DFT;
                break;
            case states::IDT:
                handle_opt();
                handle_dgt();
                handle_spt();
                idt.push_back(cur_char);
                cur_state = states::IDT;
                break;
            case states::DGT:
                handle_idt();
                handle_opt();
                handle_spt();
                dgt.push_back(cur_char);
                cur_state = states::DGT;
                break;
            case states::OPT:
                handle_idt();
                handle_dgt();
                handle_spt();
                opt.push_back(cur_char);
                cur_state = states::OPT;
                break;
            case states::SPT:
                handle_idt();
                handle_dgt();
                handle_opt();
                handle_spt();
                cur_state = states::SPT;
                break;
            case states::STR:
                str.push_back(cur_char);
                cur_state = states::STR;
                break;
            case states::ERR:
            default:
                std::cerr<<"line "<<line_count<<":"<<word_count;
                std::cerr<<"token recognition error at: ";
                if(isgraph(cur_char))
                    std::cerr<<cur_char;
                else
                    std::cerr<<"(int value)-> ";
                    std::cerr<<static_cast<int>(cur_char);
                std::cerr<<std::endl;
                break;
        }
    }
    
    //XML output
    fflush(stdin);
    XML xml;
    node tks,end,tk;
    tks.add_attribute("tokens");
    tk.add_attribute("token");
    end.add_attribute("number");
    end.add_attribute("value");
    end.add_attribute("type");
    end.add_attribute("line");
    end.add_attribute("valid");
    end.add_value(std::to_string(word_count));
    end.add_value("#");
    end.add_value("#");
    end.add_value(std::to_string(line_count));
    end.add_value("true");
    tk.add_child(end);
    token.push_back(tk);
    for(node t: token)
    {
        tks.add_child(t);
    }
    xml.add_child(tks);
    xml.print_all(argv[2]);
    return 0;
}


