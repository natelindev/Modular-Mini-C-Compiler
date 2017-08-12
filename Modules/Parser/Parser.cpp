//
//  Parser.cpp
//  Parser
//
//  Created by 林理露 on 14/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include "XML_generator.h"
#include "token_resolver.h"
#include "Parser.h"

std::deque<token> tokens;

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    reslove(tokens);
    
    XML xml;
    node root;
    if(!program(root))
    {
        std::cerr<<"Complie Error,meeting unexpected EOF."<<std::endl;
    }
    if (!tokens.empty()) {
        std::cerr<<"Potential Complie Error,input stream not empty."<<std::endl;
    }
    
    xml.add_child(root.get_child(0));
    
    xml.print_all(argv[2]);
    return 0;
}

bool program(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("PROGRAM");
    //PROGRAM -> FUNCTIONS #
    if (functions(temp)) {
        if (tokens.front().type == types::EOT) {
            res = true;
            tokens.pop_front();
        }
    }else{
        std::cerr<<"Complie Error,Program is not consist of functions near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool functions(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("FUNCTIONS");
    //FUNCTIONS -> FUNCTION FUNCTIONS
    //          -> NULL
    if (tokens.front().type == types::EOT) {
        //FUNCTIONS -> NULL
        temp.add_value("");
        res = true;
    }else{//FUNCTIONS -> FUNCTION FUNCTIONS
        if (function(temp)) {
            if (functions(temp)) {
                if (tokens.front().type == types::EOT) {
                    res = true;
                }
            }else{
                std::cerr<<"Complie Error,Program is not consist of functions near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid function structure near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool function(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("FUNCTION");
    //FUNCTION -> TYPE ID ( PARAMS ) ;
    //         -> TYPE ID ( PARAMS ) { STMTS }
    if (type(temp)) {//TYPE
        if (identifier(temp)) {//IDENTIFIER
            if(tokens.front().value.front() == '('){// (
                separator(temp);
                if (params(temp)) {// PARAMS
                    if(tokens.front().value.front() == ')'){ // )
                        separator(temp);
                        //function declaration
                        if (tokens.front().value.front() == ';') { // ;
                            if (separator(temp)) {
                                res = true;
                            }else{
                                std::cerr<<"Complie Error,Function Declaration not ended with ; near "; cast_context(CAST_LENGTH);
                            }
                            //function defination
                        }else if(tokens.front().value.front() == '{'){ // { STMTS }
                            separator(temp); // {
                            if(statements(temp)){ // STMTS
                                separator(temp); // }
                                res = true;
                            }else{
                                std::cerr<<"Complie Error,Invalid statments structure near "; cast_context(CAST_LENGTH);
                            }
                        }else{
                            std::cerr<<"Complie Error,Invalid token after function head near "; cast_context(CAST_LENGTH);
                        }
                    }else{
                        std::cerr<<"Complie Error, ) missing near "; cast_context(CAST_LENGTH);
                    }
                }else{
                    std::cerr<<"Complie Error, parameter list error near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error, ( missing near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid function identifier near "; cast_context(CAST_LENGTH);
        }
    }else{
        std::cerr<<"Complie Error,Invalid function return type near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}


bool type(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("TYPE");
    //TYPE -> "void" || v == "char" || v == "short" || v == "int" || v == "long" || v == "float" || v == "double"
    if (tokens.front().type == types::KWD && is_type(tokens.front().value)) {
        keyword(temp);
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a type near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool identifier(node &root){
    bool res = false;
    node temp;
    temp.add_attribute("identifier");
    if (tokens.front().type == types::IDT ) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a identifier near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool separator(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("separator");
    if (tokens.front().type == types::SPT && tokens.front().value.length() == 1) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a separator near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool _operator(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("operator");
    if (tokens.front().type == types::OPT && tokens.front().value.length() <= 3) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not an operator near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool keyword(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("keyword");
    if (tokens.front().type == types::KWD ) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a keyword near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool string_literal(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("StringLiteral");
    if (tokens.front().type == types::STR ) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a string near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool digit(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("const_i");
    if (tokens.front().type == types::DGT ) {
        temp.add_value(tokens.front().value);
        tokens.pop_front();
        res = true;
    }else{
        std::cerr<<"Complie Error,Not a digit near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool params(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("PARAMS");
    //PARAMS -> PARAM , PARAMS
    //     -> PARAM
    //     -> NULL
    if (tokens.front().value.front() == ')') {
        //PARAMS -> NULL
        temp.add_value("");
        res = true;
    }else{
        //PARAMS -> PARAM, PARAMS
        if (param(temp)) {
            if (look_ahead_str({")"}, [](std::string s){return (s == ",");})) {
                if (tokens.front().value == ",") {
                    _operator(temp);
                    if (params(temp)) {
                        res = true;
                    }else{
                        std::cerr<<"Complie Error,Invalid parameter near "; cast_context(CAST_LENGTH);
                    }
                }
            }else{
                //PARAMS -> PARAM
                res = true;
            }
            
        }
    }
    root.add_child(temp);
    return res;
}

bool param(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("PARAM");
    //PARAM -> TYPE ID
    if(type(temp))
    {
        if (tokens.front().type == types::IDT) {
            identifier(temp);
            res = true;
        }else{
            std::cerr<<"Complie Error,Expect identifier near "; cast_context(CAST_LENGTH);
        }
    }else{
        std::cerr<<"Complie Error,Invalid type near "; cast_context(CAST_LENGTH);
    }
    
    root.add_child(temp);
    return res;
}

bool statements(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("STMTS");
    //STMTS -> STMT STMTS
    //      -> NULL
    if (tokens.front().value.front() == '}') {
        //STMTS -> NULL
        temp.add_value("");
        res = true;
    }else{//STMTS -> STMT STMTS
        if (statement(temp)) {
            if (statements(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid statments near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid statment near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool statement(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("STMT");
    //STMT -> RET_STMT
    //     -> FOR_STMT
    //     -> IF_STMT
    //     -> EXP_STMT
    if (tokens.front().value == "return") {
        if (ret_stmt(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid return expression near "; cast_context(CAST_LENGTH);
        }
    }else if (tokens.front().value == "for"){
        if (for_stmt(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid for expression near "; cast_context(CAST_LENGTH);
        }
    }else if (tokens.front().value == "if"){
        if (if_stmt(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid if expression near "; cast_context(CAST_LENGTH);
        }
    }else{
        if (exp_stmt(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool ret_stmt(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("RET_STMT");
    //RET_STMT -> RETURN EXP_STMT
    if (tokens.front().value == "return") {
        keyword(temp);
        if (exp_stmt(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool if_stmt(node &root)
{
    //IF_STMT -> IF ( CND_EXP ) { STMTS }
    //        -> IF ( CND_EXP ) { STMTS } ELSE { STMTS }
    bool res = false;
    node temp;
    temp.add_attribute("IF_STMT");
    if (tokens.front().value == "if") { //if
        keyword(temp);
        if(tokens.front().value.front() == '('){// (
            separator(temp);
            if (cnd_exp(temp)) {  // COND
                if (tokens.front().value.front() == ')') { // )
                    separator(temp);
                    if (tokens.front().value.front() == '{') { // {
                        separator(temp);
                        if (statements(temp)) { // STMTS
                            if (tokens.front().value.front() == '}') { // }
                                separator(temp);
                                //IF_STMT -> IF ( COND ) { STMTS } ELSE { STMTS }
                                if (tokens.front().type == types::KWD && tokens.front().value == "else") {
                                    keyword(temp);
                                    if (tokens.front().value.front() == '{') { // {
                                        separator(temp);
                                        if (statements(temp)) { // STMTS
                                            if (tokens.front().value.front() == '}') { // }
                                                separator(temp);
                                                res = true;
                                            }else{
                                                std::cerr<<"Complie Error,Expected } near "; cast_context(CAST_LENGTH);
                                            }
                                        }else{
                                            std::cerr<<"Complie Error,Invalid statments near "; cast_context(CAST_LENGTH);
                                        }
                                    }else{
                                        std::cerr<<"Complie Error,Expected { near "; cast_context(CAST_LENGTH);
                                    }
                                }else{
                                    //IF_STMT -> IF ( COND ) { STMTS }
                                    res = true;
                                }
                            }else{
                                std::cerr<<"Complie Error,Expected } near "; cast_context(CAST_LENGTH);
                            }
                        }else{
                            std::cerr<<"Complie Error,if statement body is not consist of statements near "; cast_context(CAST_LENGTH);
                        }
                    }else{
                        std::cerr<<"Complie Error,Expected { near "; cast_context(CAST_LENGTH);
                    }
                }else{
                    std::cerr<<"Complie Error,Expected ) near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error,Invalid condition in if near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Expected ( near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool for_stmt(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("FOR_STMT");
    //FOR_STMT -> FOR( EXP ; EXP ; EXP ) { STMTS }
    if (tokens.front().value == "for") {
        keyword(temp);
        if (tokens.front().value.front() == '(') { // (
            separator(temp);
            if (exp(temp)) { //EXP
                if (tokens.front().value.front() == ';') { // ;
                    separator(temp);
                    if (exp(temp)) { // EXP
                        if (tokens.front().value.front() == ';') { // ;
                            separator(temp);
                            if (exp(temp)) { // EXP
                                if (tokens.front().value.front() == ')' ) { // ;
                                    separator(temp);
                                    if (tokens.front().value.front() == '{') { // {
                                        separator(temp);
                                        if (statements(temp)) { // STMTS
                                            if (tokens.front().value.front() == '}') { // }
                                                separator(temp);
                                                res = true;
                                            }else{
                                                std::cerr<<"Complie Error,Expected } near "; cast_context(CAST_LENGTH);
                                            }
                                        }else{
                                            std::cerr<<"Complie Error,Invalid statments near "; cast_context(CAST_LENGTH);
                                        }
                                    }else{
                                        std::cerr<<"Complie Error,Expected { near "; cast_context(CAST_LENGTH);
                                    }
                                }else{
                                    std::cerr<<"Complie Error,Expected ) near "; cast_context(CAST_LENGTH);
                                }
                            }else{
                                std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
                            }
                        }else{
                            std::cerr<<"Complie Error,Expected ; near "; cast_context(CAST_LENGTH);
                        }
                    }else{
                        std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
                    }
                }else{
                    std::cerr<<"Complie Error,Expected ; near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Expected ( near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool exp_stmt(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("EXP_STMT");
    //EXP_STMT -> EXP ;
    //         -> ;
    if (tokens.front().value.front() == ';') {
        separator(temp);
        res = true;
    }else{
        if (exp(temp)) {
            if (tokens.front().value.front() == ';') {
                separator(temp);
                res = true;
            }
        }
    }
    root.add_child(temp);
    return res;
}

bool exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("EXP");
    //EXP -> ASN_EXP
    //    -> DEF_EXP
    //    -> CND_EXP
    //    -> URY_EXP
    //    -> FUNC_CALL
    if (is_type(tokens.front().value)) {
        //EXP -> DEF_EXP
        if(def_exp(temp)){
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid definition expression near "; cast_context(CAST_LENGTH);
        }
    }else if (look_ahead_str({";",")","}"}, is_asn_opt)){
        //EXP -> ASN_EXP
        if(asn_exp(temp)){
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid assignment expression near "; cast_context(CAST_LENGTH);
        }
    }else if(look_ahead_str({";",")","}"},is_cmp_opt)){
        //EXP -> CND_EXP
        if(cnd_exp(temp)){
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid conditional expression near "; cast_context(CAST_LENGTH);
        }
    }else if(look_ahead_str({";",")","}"},[](std::string s){return (s =="++"||s=="--");})){
        //EXP -> URY_EXP
        if (ury_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid unary expression near "; cast_context(CAST_LENGTH);
        }
    }else if(look_ahead_func({";",")","}"}))
    {
        //Make sure that idt( pattern have appeared
        //EXP -> FUNC_CALL
        if (func_call(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid function call near "; cast_context(CAST_LENGTH);
        }
    }else{
        //EXP -> TERM ADD_EXP
        if (term(temp)) {
            if (add_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid additive expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid term near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool func_call(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("FUNC_CALL");
    //FUNC_CALL -> ID ( ARGS ) ;
    if (tokens.front().type == types::IDT) {
        identifier(temp);
        if (tokens.front().value.front() == '(') {
            separator(temp);
            if (args(temp)) {
                if (tokens.front().value.front() == ')') {
                    separator(temp);
                    res = true;
                }else{
                    std::cerr<<"Complie Error,Expected ) near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error,Invalid arguments near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Expected ( near "; cast_context(CAST_LENGTH);
        }
    }else{
        std::cerr<<"Complie Error,Expected identifier near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool args(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("ARGS");
    //ARGS -> ARG , ARGS
    //     -> ARG
    //     -> NULL
    if (tokens.front().value.front() == ')') {
        temp.add_value("");
        res = true;
    }else{
        if (arg(temp)) {
            if (look_ahead_str({")"}, [](std::string s){return (s == ",");})) {
                if (tokens.front().value == ",") {
                    _operator(temp);
                    if (args(temp)) {
                        res = true;
                    }else{
                        std::cerr<<"Complie Error,Invalid arguments near "; cast_context(CAST_LENGTH);
                    }
                }
            }else{
                res = true;
            }
            
        }
    }
    root.add_child(temp);
    return res;
}

bool arg(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("ARG");
    //ARG -> EXP
    if(exp(temp))
    {
        res = true;
    }else{
        std::cerr<<"Complie Error,Invalid argument near "; cast_context(CAST_LENGTH);
    }
    root.add_child(temp);
    return res;
}

bool ury_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("URY_EXP");
    //URY_EXP -> ++PMRY_EXP
    //        -> --PMRY_EXP
    //        -> POST_EXP
    if (tokens.front().type == types::OPT) {
        if (tokens.front().value == "++") {
            _operator(temp);
            if (pmry_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid unary expression near "; cast_context(CAST_LENGTH);
            }
        }else if (tokens.front().value == "--") {
            _operator(temp);
            if (pmry_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid unary expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Unexpected operator near "; cast_context(CAST_LENGTH);
        }
    }else{
        if (post_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid post expression near "; cast_context(CAST_LENGTH);
        }
    }
    
    root.add_child(temp);
    return res;
}

bool def_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("DEF_EXP");
    //DEF_EXP -> TYPE ASN_EXP
    //        -> TYPE PMRY_EXP
    if (type(temp)) {
        if (look_ahead_str({";",")","}"}, is_asn_opt)) {
            if(asn_exp(temp)){
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid primary expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            if (pmry_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid primary expression near "; cast_context(CAST_LENGTH);
            }
        }
    }
    
    root.add_child(temp);
    return res;
}

bool asn_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("ASN_EXP");
    //ASN_EXP -> CND_EXP
    //        -> URY_EXP ASN_OPT EXP
    //        -> PMRY_EXP
    
    //temporary solution
    if (look_ahead_str({";"}, is_asn_opt)) {
        //ASN_EXP -> URY_EXP ASN_OPT EXP
        if (ury_exp(temp)) {//URY_EXP
            if (is_asn_opt(tokens.front().value)) {//ASN_OPT
                _operator(temp);
                if (exp(temp)) {//EXP
                    res = true;
                }else{
                    std::cerr<<"Complie Error,Invalid ass expression near "; cast_context(CAST_LENGTH);
                }
            }
        }
    }else if(look_ahead_str({";"} , is_cmp_opt)){
        //ASN_EXP -> CND_EXP
        if (cnd_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid conditional expression near "; cast_context(CAST_LENGTH);
        }
    }else{
        //ASN_EXP -> PMRY_EXP
        if (pmry_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid primary expression near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool cnd_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("CND_EXP");
    //CND_EXP -> PMRY_EXP >  PMRY_EXP
    //        -> PMRY_EXP <  PMRY_EXP
    //        -> PMRY_EXP == PMRY_EXP
    //        -> PMRY_EXP >= PMRY_EXP
    //        -> PMRY_EXP <= PMRY_EXP
    //        -> PMRY_EXP != PMRY_EXP
    if (pmry_exp(temp)) {
        if (tokens.front().type == types::OPT) {
            if (is_cmp_opt(tokens.front().value)) {
                _operator(temp);
                if (pmry_exp(temp)) {
                    res = true;
                }else{
                    std::cerr<<"Complie Error,Invalid primiray expression near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error,Unexpected operator near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Expect operator near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool add_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("ADD_EXP");
    //ADD_EXP -> + TERM ADD_EXP
    //        -> - TERM ADD_EXP
    //        -> NULL
    if (tokens.front().value == "+" || tokens.front().value == "-")
    {
        //ADD_EXP -> + TERM ADD_EXP
        //        -> - TERM ADD_EXP
        _operator(temp);
        if (term(temp)) {
            if (add_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid additive expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid term near "; cast_context(CAST_LENGTH);
        }
    }else{
        //ADD_EXP -> NULL
        temp.add_value("");
        res = true;
    }
    root.add_child(temp);
    return res;
}

bool mul_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("MUL_EXP");
    //MUL_EXP -> NULL
    //        -> * PMRY_EXP MUL_EXP
    //        -> / PMRY_EXP MUL_EXP
    if (tokens.front().value == "*" || tokens.front().value == "/"){
        //MUL_EXP -> * PMRY_EXP MUL_EXP
        //        -> / PMRY_EXP MUL_EXP
        _operator(temp);
        if (pmry_exp(temp)) {
            if (mul_exp(temp)) {
                res = true;
            }else{
                std::cerr<<"Complie Error,Invalid additive expression near "; cast_context(CAST_LENGTH);
            }
        }else{
            std::cerr<<"Complie Error,Invalid primiray expression near "; cast_context(CAST_LENGTH);
        }
    }else{
        //MUL_EXP -> NULL
        temp.add_value("");
        res = true;
    }
    root.add_child(temp);
    return res;
}

bool post_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("POST_EXP");
    //POST_EXP -> PMRY_EXP
    //         -> PMRY_EXP++
    //         -> PMRY_EXP--
    //         -> PMRY_EXP[DGT]
    
    if (look_ahead_str({";",")"},[](std::string s){ return s == "++" || s == "--" || s == "[" || s == "]"; })) {
        if (tokens[1].value == "++") {
            //POST_EXP -> POST_EXP++
            if (pmry_exp(temp)) {
                if (tokens.front().value == "++") {
                    _operator(temp);
                    res = true;
                }
            }
        }else if (tokens[1].value == "--"){
            //POST_EXP -> POST_EXP--
            if (pmry_exp(temp)) {
                if (tokens.front().value == "--") {
                    _operator(temp);
                    res = true;
                }
            }
        }else if (tokens[1].value == "["){
            
            //POST_EXP -> PMRY_EXP [ DGT ]
            if (pmry_exp(temp)) {
                if (tokens.front().value.front() == '[') {
                    separator(temp);
                    if (tokens.front().type == types::DGT) {
                        digit(temp);
                        if (tokens.front().value.front() == ']') {
                            separator(temp);
                            res = true;
                        }else{
                            std::cerr<<"Complie Error,Expected ] near "; cast_context(CAST_LENGTH);
                        }
                    }else{
                        std::cerr<<"Complie Error,Expected digit near "; cast_context(CAST_LENGTH);
                    }
                }else{
                    std::cerr<<"Complie Error,Expected ] near "; cast_context(CAST_LENGTH);
                }
            }
        }else{
            //POST_EXP -> PMRY_EXP
            if (pmry_exp(temp)){
                res = true;
            }else{
                std::cerr<<"Complie Error,Primiray expression error near "; cast_context(CAST_LENGTH);
            }
        }
    }else{
        //POST_EXP -> PMRY_EXP
        if (pmry_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Primiray expression error near "; cast_context(CAST_LENGTH);
        }
    }
    root.add_child(temp);
    return res;
}

bool pmry_exp(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("PMRY_EXP");
    //PMRY_EXP -> ID
    //         -> STR
    //         -> DGT
    //         -> ( EXP )
    switch (tokens.front().type) {
        case types::IDT:
            //PMRY_EXP -> ID
            identifier(temp);
            res = true;
            break;
        case types::STR:
            //PMRY_EXP -> STR
            string_literal(temp);
            res = true;
            break;
        case types::DGT:
            //PMRY_EXP -> DGT
            digit(temp);
            res = true;
            break;
        case types::SPT:
            //PMRY_EXP -> ( EXP )
            if (tokens.front().value.front() == '(') {// (
                separator(temp);
                if (exp(temp)) { // EXP
                    if (tokens.front().value.front() == ')') { // )
                        separator(temp);
                        res = true;
                    }else{
                        std::cerr<<"Complie Error,Expected ) near "; cast_context(CAST_LENGTH);
                    }
                }else{
                    std::cerr<<"Complie Error,Invalid expression near "; cast_context(CAST_LENGTH);
                }
            }else{
                std::cerr<<"Complie Error,Expected ( near "; cast_context(CAST_LENGTH);
            }
            break;
            
        default:
            std::cerr<<"Complie Error,Unexpected type in primiray expression near "; cast_context(CAST_LENGTH);
            break;
    }
    root.add_child(temp);
    return res;
}

bool term(node &root)
{
    bool res = false;
    node temp;
    temp.add_attribute("TERM");
    //TERM -> PMRY_EXP MUL_EXP
    if (pmry_exp(temp)) {
        if (mul_exp(temp)) {
            res = true;
        }else{
            std::cerr<<"Complie Error,Invalid multiplicative expression near "; cast_context(CAST_LENGTH);
        }
    }else{
        std::cerr<<"Complie Error,Invalid primiray expression near "; cast_context(CAST_LENGTH);
    }
    
    root.add_child(temp);
    return res;
}

bool is_asn_opt(std::string opt)
{
    return (opt == "=" || opt == "+=" || opt == "-=" || opt == "*=" || opt == "/=");
}

bool is_type(std::string v)
{
    return (v == "void" || v == "char" || v == "short" || v == "int" || v == "long" || v == "float" || v == "double");
}

bool is_cmp_opt(std::string opt)
{
    return (opt == "<" || opt == ">" || opt == "==" || opt == "==" || opt == ">=" || opt == "<=");
}

bool look_ahead_str(std::vector<std::string> stop_symbols,bool (*is_target)(std::string))
{
    bool has_target = false,met_stop_symbol = false;
    
    int n;
    for (n = 0; n < tokens.size(); ++n)
    {
        for(std::string s : stop_symbols)
        {
            if (tokens[n].value == s) {
                met_stop_symbol = true;
            }
        }
        if (met_stop_symbol) {
            break;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (is_target(tokens[i].value)) {
            has_target = true;
            break;
        }
    }
    
    return has_target;
}

bool look_ahead_func(std::vector<std::string> stop_symbols)
{
    bool has_target = false,met_stop_symbol = false;
    
    int n;
    for (n = 0; n < tokens.size(); ++n)
    {
        for(std::string s : stop_symbols)
        {
            if (tokens[n].value == s) {
                met_stop_symbol = true;
            }
        }
        if (met_stop_symbol) {
            break;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (tokens[i].type == types::IDT && tokens[i+1].value == "(") {
            has_target = true;
            break;
        }
    }

    return has_target;
}

void cast_context(size_t n)
{
    if (tokens.size() < n) {
        n = tokens.size();
    }
    std::cerr<<"\"";
    for (int i = 0; i < n; ++i) {
        std::cerr<<tokens[i].value<<" ";
    }
    std::cerr<<"\"";
    std::cerr<<" at line "<<tokens.front().line<<std::endl;
    
}
