//
//  main.cpp
//  CodeGenerator
//
//  Created by 林理露 on 31/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include "XML_header.h"
#include "CodeGenerator.h"
#include <unordered_map>

node global_symbol_table;
std::unordered_map<std::string, std::string> reg_map;
int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input xml filename> <output xml filename>"<<std::endl;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    
    node root;
    resolve(root);
    global_symbol_table = root.get_child(0).get_child(0).get_child(1);
    root = root.get_child(0).get_child(0).get_child(0);
    
    register_allocate(root);
    register_allocate(global_symbol_table);
    
    init_code_generate();
    func_code_generate(root);
    
    return 0;
}

void init_code_generate()
{
    //data section
    std::cout<<".data"<<std::endl;
    
    //text section
    std::cout<<".text"<<std::endl;
    
    //__init section
    std::cout<<"__init:"<<std::endl;
    std::cout<<"        # setup the base address of stack lui $sp, 0x8000"<<std::endl;
    std::cout<<"        addi $sp, $sp, 0x0000"<<std::endl;
    std::cout<<"        # allocate stack frame for main function"<<std::endl;
    std::cout<<"        addiu $sp, $sp, -64"<<std::endl;
    std::cout<<"        jal __main"<<std::endl;
    std::cout<<"        # make a system call and terminate the program"<<std::endl;
    std::cout<<"        li $v0, 10"<<std::endl;
    std::cout<<"        syscall"<<std::endl;
}

void func_code_generate(node root)
{
    int para_count = 0;
    for(node ir : root.childs)
    {
        //iterate through the IRs
        std::string op,arg1,arg2,res;
        op = ir.childs[0].values[0];
        if (ir.childs[1].values.size() > 0) {
            arg1 = ir.childs[1].values[0];
        }
        if (ir.childs[2].values.size() > 0) {
            arg2 = ir.childs[2].values[0];
        }
        if (ir.childs[3].values.size() > 0) {
            res = ir.childs[3].values[0];
        }
//        std::cerr<<"Building ("<<op<<","<<arg1<<","<<arg2<<","<<res<<")"<<std::endl;
        
        if (is_number(arg1)) {
            std::cout<<"        ";
            std::cout<<"li "<<"$t8"<<","<<arg1<<std::endl;
            reg_map[arg1] = "$t8";
        }
        if (is_number(arg2)) {
            std::cout<<"        ";
            std::cout<<"li "<<"$t9"<<","<<arg2<<std::endl;
            reg_map[arg2] = "$t9";
        }
        
        if (op == "enter_func") {
            std::cout<<std::endl;
            std::cout<<"__"<<arg1<<":"<<std::endl;
        }else if (op == "=") {
            std::cout<<"        ";
            std::cout<<"move "<<reg_map[res]<<","<<reg_map[arg1]<<std::endl;
        }else if (op == "+") {
            std::cout<<"        ";
            std::cout<<"add "<<reg_map[res]<<","<<reg_map[arg1]<<","<<reg_map[arg2]<<std::endl;
        }else if (op == "-") {
            std::cout<<"        ";
            std::cout<<"sub "<<reg_map[res]<<","<<reg_map[arg1]<<","<<reg_map[arg2]<<std::endl;
        }else if (op == "*") {
            std::cout<<"        ";
            std::cout<<"mul "<<reg_map[res]<<","<<reg_map[arg1]<<","<<reg_map[arg2]<<std::endl;
        }else if (op == "/") {
            std::cout<<"        ";
            std::cout<<"div "<<reg_map[arg1]<<","<<reg_map[arg2]<<std::endl;
            std::cout<<"        ";
            std::cout<<"move "<<reg_map[res]<<","<<"$LO"<<std::endl;
        }else if (op == "push") {
            std::cout<<"        ";
            if (para_count <= 3) {
                std::cout<<"        ";
                std::cout<<"move "<<"$a"<<para_count<<","<<reg_map[arg1]<<std::endl;
            }else{
                std::cerr<<"Register allocation error,not enough a registers"<<std::endl;
            }
        }else if (op == "return") {
            std::cout<<"        move $v0,"<<reg_map[arg1]<<std::endl;
            std::cout<<"        jr $ra"<<std::endl;
        }else if (op == "call") {
            std::cout<<"        # allocate stack frame for the callee"<<std::endl;
            std::cout<<"        addiu $sp, $sp, -64"<<std::endl;
            std::cout<<"        sw $ra, 0($sp)"<<std::endl;
            std::cout<<"        ";
            std::cout<<"jal "<<"__"<<arg1<<std::endl;
            std::cout<<"        # restore the $ra and deallocate the stack frame for the callee"<<std::endl;
            std::cout<<"        lw $ra, 0($sp)"<<std::endl;
            std::cout<<"        addiu $sp, $sp, 64"<<std::endl;
            std::cout<<"        move "<<reg_map[res]<<",$v0"<<std::endl;
        }
        
    }
    
}

void register_allocate(node root)
{
    if (root.attributes[0] == "id") {
        if (root.values[0].front() == 'v' && is_number(root.values[0].substr(4,root.values[0].length()))) {
            //varibles
            std::string num = root.values[0].substr(4,root.values[0].length());
            if (stoi(num,0,10) > 7) {
                std::cerr<<"Register allocation error,not enough s registers"<<std::endl;
            }
            reg_map[root.values[0]] = "$s"+num;
        }else if(root.values[0].front() == 'p' && is_number(root.values[0].substr(4,root.values[0].length()))){
            //parameters
            std::string num = root.values[0].substr(4,root.values[0].length());
            if (stoi(num,0,10) > 3) {
                std::cerr<<"Register allocation error,not enough a registers"<<std::endl;
            }
            reg_map[root.values[0]] = "$a"+num;
        }
    }else if(root.values.size() > 0 &&
             root.values[0].front() == 'T' &&
             is_number(root.values[0].substr(1,root.values[0].length()))){
        std::string num = root.values[0].substr(1,root.values[0].length());
        if (stoi(num,0,10) > 7) {
            std::cerr<<"Register allocation error,not enough t registers"<<std::endl;
        }
        reg_map[root.values[0]] = "$t"+num;
    }else{
        for(node n : root.childs)
        {
            register_allocate(n);
        }
    }
}

bool is_number(std::string s)
{
    return (!s.empty() && s.find_first_not_of("0123456789") == std::string::npos);
}
