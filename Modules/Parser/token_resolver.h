//
//  token_resolver.h
//  Parser
//
//  Created by 林理露 on 14/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef token_resolver_h
#define token_resolver_h
#include <string>
#include <deque>

enum class types:unsigned int{
    IDT = 0,//identifier
    KWD = 1,//keyword
    OPT = 2,//operator
    DGT = 3,//digits
    STR = 4,//StringLiteral
    SPT = 5,//separator
    EOT = 6,//end of tokens
    ERR = 7//error
};

class token
{
public:
    int number;
    std::string value;
    types type;
    int line;
    bool valid;
};

types get_type(std::string str);
    
void reslove(std::deque<token> &tokens);
    
#endif /* token_resolver_h */
