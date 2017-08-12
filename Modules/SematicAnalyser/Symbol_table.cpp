//
//  Symbol_table.cpp
//  SemanticAnalyser
//
//  Created by 林理露 on 27/07/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include "Symbol_table.h"

node global_symbol_table;
int val_num = 0;
int para_num = 0;
void build_symbol_table(node root,node &father_table)
{
//    std::cerr<<"Building: "<<root.attributes[0]<<std::endl;
    if (root.attributes[0] == "FUNCTION") {
        //Handle function
        //new scope
        node temp_table;
        temp_table.add_attribute("func");
        if (root.childs[0].values.size() > 0 && root.childs[1].values.size() > 0) {
            add_attr(temp_table, root.childs[1].values[0], root.childs[0].values[0],root.childs[1].values[0]);
//            std::cerr<<root.childs[1].values[0]<<" Added"<<std::endl;
        }else{
            std::cerr<<"Unexpected function format near "<<\
            root.childs[0].attributes[0]<<" "<<root.childs[1].attributes[0]<<std::endl;
        }
        
        //std::cerr<<"Change Table to "<<root.childs[1].values[0]<<std::endl;
        for(node n : root.childs)
        {
            build_symbol_table(n, temp_table);
        }
        father_table.add_child(temp_table);
    }else if(root.attributes[0] == "DEF_EXP") {
        //Handle definition
        node temp;
        temp.add_attribute("var");
        if (root.childs[0].values.size() > 0 && root.childs[1].values.size() > 0){
            add_attr(temp, root.childs[1].values[0], root.childs[0].values[0],"vid_"+std::to_string(val_num++));
//            std::cerr<<root.childs[1].values[0]<<" Added"<<std::endl;
        }else{
            std::cerr<<"Unexpected variable format near "<<\
            root.childs[0].attributes[0]<<" "<<root.childs[1].attributes[0]<<std::endl;
        }
        
        father_table.add_child(temp);
    }else if(root.attributes[0] == "PARAM"){
        //Handle parameters
        node temp;
        temp.add_attribute("param");
        if (root.childs[0].values.size() > 0 && root.childs[1].values.size() > 0){
            add_attr(temp, root.childs[1].values[0], root.childs[0].values[0],"pid_"+std::to_string(para_num++));
//            std::cerr<<root.childs[1].values[0]<<" Added"<<std::endl;
        }else{
            std::cerr<<"Unexpected parameter format near "<<\
            root.childs[0].attributes[0]<<" "<<root.childs[1].attributes[0]<<std::endl;
        }
        father_table.add_child(temp);
    }else if(root.attributes[0] == "identifier"){
        //Definition Check
//        std::cerr<<"Checking "<<root.values[0]<<std::endl;
        if (!exist_in_table(root.values[0], father_table)) {
            std::cerr<<"Compile Error! Undeifined identifier "<<root.values[0]<<std::endl;
        }
    }else{
        for(node n : root.childs)
        {
            build_symbol_table(n,father_table);
        }
    }
}

bool exist_in_table(std::string s,node t){
    bool res = false;
    if ((t.values.size() > 0) && (t.values[0] == s)) {
        res = true;
    }else{
        for(node n : t.childs)
        {
            res |= exist_in_table(s,n);
        }
    }
    return res;
}

void add_attr(node &root,std::string name,std::string type,std::string id)
{
    node temp1,temp2,temp3;
    temp1.add_attribute("name");
    temp2.add_attribute("type");
    temp3.add_attribute("id");
    temp1.add_value(name);
    temp2.add_value(type);
    temp3.add_value(id);
    root.add_child(temp1);
    root.add_child(temp2);
    root.add_child(temp3);
}
