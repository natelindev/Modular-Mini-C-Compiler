//
//  main.cpp
//  IR_Generator
//
//  Created by 林理露 on 29/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include "IR_Generator.h"
#include "XML_header.h"

std::vector<IR_3_Address> IRs;
node global_symbol_table;
std::vector<std::string> results;
std::string scope = "global";
int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    node root;
    resolve(root);
    global_symbol_table = root.get_child(0).get_child(0).get_child(1);
    root = root.get_child(0).get_child(0).get_child(0);
    
    build_IR(root);

    //convert IR to xml node
    node ir_root;
    int num = 0;
    for(IR_3_Address ir: IRs)
    {
        node t_root,temp;
        t_root.add_attribute("IR_"+std::to_string(num++));
        temp.add_attribute("op");
        temp.add_attribute("arg1");
        temp.add_attribute("arg2");
        temp.add_attribute("res");
        temp.add_value(ir.op);
        temp.add_value(ir.arg1);
        temp.add_value(ir.arg2);
        temp.add_value(ir.res);
        t_root.add_child(temp);
        ir_root.add_child(t_root);
    }
    
    XML xml;
    xml.set_sub_header("IR");
    ir_root.add_attribute("IR_3_Address");
    xml.add_child(ir_root);
    xml.add_child(global_symbol_table);
    xml.print_all(argv[2]);
    return 0;
}

std::string build_IR(node root){
//    std::cerr<<"Building "<<root.attributes[0]<<std::endl;
    std::string result = "";
    //IR_3_Address(op ,arg1 ,arg2 ,res)
    if (root.attributes[0] == "ASN_EXP") {
        //a = 1+3;
        //(=,build_IR(1+3), ,a)
        IR_3_Address asn_ir;
        asn_ir.op = root.childs[1].values[0];
        asn_ir.res = symbol_look_up(root.childs[0].values[0],scope, global_symbol_table);
//        if (asn_ir.res == "sid_1") {
//            asn_ir = asn_ir;
//        }
        asn_ir.arg1 = build_IR(root.childs[2]);
        IRs.push_back(asn_ir);
    }else if(root.attributes[0] == "ADD_EXP" || root.attributes[0] == "MUL_EXP"){
        // a + 2 * 3
        // (*,2,3,T1)
        // (+,a,T1,T2)
        IR_3_Address add_mul_ir;
        if (results.back().length() > 0) {
            add_mul_ir.op = root.childs[0].values[0];
            add_mul_ir.arg1 = results.back();
            add_mul_ir.arg2 = build_IR(root.childs[1]);
            add_mul_ir.res = get_temp_val();
            result = add_mul_ir.res;
            IRs.push_back(add_mul_ir);
        }else{
            std::cerr<<"IR generation error: prev_res is empty"<<std::endl;
        }
    }else if(root.attributes[0] == "FUNC_CALL"){
        // foo(a,b+c);
        // (push,build_IR(a),, )
        // (push,build_IR(b+c),, )
        // (call,foo, ,T3)
        IR_3_Address push_ir,call_ir;
        for(node n : root.childs[2].childs)
        {
            //push all the args
            if (n.values.size() == 0 || n.values[0] != ",") {
                push_ir.op = "push";
                push_ir.arg1 = build_IR(n);
                IRs.push_back(push_ir);
            }
        }
        //call the function
        call_ir.op = "call";
        call_ir.arg1 = symbol_look_up(root.childs[0].values[0], scope, global_symbol_table);
        call_ir.res = get_temp_val();
        result = call_ir.res;
        IRs.push_back(call_ir);
    }else if(root.attributes[0] == "RET_STMT"){
        IR_3_Address rtn_ir;
        rtn_ir.op = root.childs[0].values[0];
        rtn_ir.arg1 = build_IR(root.childs[1]);
        IRs.push_back(rtn_ir);
        scope = "global";
    }else if(root.attributes[0] == "const_i"){
        result = root.values[0];
    }else if(root.attributes[0] == "identifier"){
        result = symbol_look_up(root.values[0],scope, global_symbol_table);
    }else if(root.attributes[0] == "FUNCTION"){
        //switch context
        IR_3_Address func_ir;
        func_ir.op = "enter_func";
        func_ir.arg1 = root.childs[1].values[0];
        IRs.push_back(func_ir);
        scope = root.childs[1].values[0];
        for(node n : root.childs)
        {
            build_IR(n);
        }
    }else if(root.attributes[0] == "PROGRAM"    ||
             root.attributes[0] == "FUNCTIONS"  ||
             root.attributes[0] == "STMTS"      ||
             root.attributes[0] == "EXP_STMT"   ||
             root.attributes[0] == "EXP"        ||
             root.attributes[0] == "TERM"       
             ){
        std::string temp_res;
        for(node n : root.childs)
        {
            temp_res = build_IR(n);
            if (temp_res != "") {
                result = temp_res;
            }
        }
    }

    if (result != "") {
        results.push_back(result);
    }
    return result;
}

std::string symbol_look_up(std::string s,std::string scope_name,node root)
{
    std::string res = "";
    if (root.attributes[0] == "GLOBAL_SYMBOL_TABLE") {
        if (scope_name == "global") {
            //global variables
            for(node n : root.childs)
            {
                if (s == n.childs[0].values[0] ) {
                    res = n.childs[2].values[0];
                    break;
                }
            }
        }else{
            //iterate through functions
            for(node n : root.childs)
            {
                if (s == n.childs[0].values[0]) {
                    res = n.childs[2].values[0];
                    break;
                }
                if (n.attributes[0] == "func" && scope_name == n.childs[0].values[0]) {
                    //found the exact function
                    res = symbol_look_up(s, scope_name, n);
                    break;
                }
            }
        }
    }else if (root.attributes[0] == "func") {
        //In the exact function
        for(node n : root.childs){
            if(n.attributes[0] == "var" && s == n.childs[0].values[0] ){
                //found the exact variable
                res = n.childs[2].values[0];
            }else if(n.attributes[0] == "param" && s == n.childs[0].values[0] ){
                res = n.childs[2].values[0];
            }
        }
        //Didn't found in the function,try global
        if (res == "") {
            for(node n : global_symbol_table.childs)
            {
                if (s == n.childs[0].values[0] ) {
                    res = n.childs[2].values[0];
                    break;
                }
            }
        }
    }
    if (res == "") {
        std::cerr<<"IR generation error: Symbol lookup faild for "<<s<<std::endl;
    }
    return res;
}

std::string get_temp_val()
{
    static int temp_val_num = 0;
    return ("T" + std::to_string(temp_val_num++));
}
