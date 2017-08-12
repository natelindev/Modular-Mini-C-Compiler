//
//  Paser.h
//  Parser
//
//  Created by 林理露 on 14/06/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef Paser_h
#define Paser_h

#ifndef CAST_LENGTH
#define CAST_LENGTH 5
#endif
bool program(node &root);
bool functions(node &root);
bool function(node &root);
bool statement(node &root);
bool type(node &root);
bool params(node &root);
bool param(node &root);
bool args(node &root);
bool arg(node &root);

bool identifier(node &root);
bool separator(node &root);
bool keyword(node &root);
bool _operator(node &root);
bool string_literal(node &root);
bool digit(node &root);

bool statements(node &root);
bool statement(node &root);

bool ret_stmt(node &root);
bool if_stmt(node &root);
bool for_stmt(node &root);
bool exp_stmt(node &root);

bool exp(node &root);

bool asn_exp(node &root);
bool def_exp(node &root);
bool cnd_exp(node &root);
bool ury_exp(node &root);
bool lgc_exp(node &root);
bool add_exp(node &root);
bool mul_exp(node &root);
bool post_exp(node &root);
bool pmry_exp(node &root);

bool func_call(node &root);
bool term(node &root);

bool is_asn_opt(std::string opt);
bool is_type(std::string v);
bool is_cmp_opt(std::string opt);
void cast_context(size_t n);
bool look_ahead_str(std::vector<std::string> stop_symbols,bool (*is_target)(std::string));
bool look_ahead_func(std::vector<std::string> stop_symbols);

#endif /* Paser_h */
