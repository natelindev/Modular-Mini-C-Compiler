//
//  PreProcessor.cpp
//  PreProcessor
//
//  Created by 林理露 on 22/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE false
#endif

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cerr<<"Usage: "<<argv[0]<<" <input c filename> <output xml filename>"<<std::endl;
        return -1;
    }
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    string buffer,buffer_processed;
    bool in_block_comment =false,block_comment_begin = false;
    int ctr = 1;
    while (getline(cin, buffer)) {
        buffer_processed = buffer;
        for (string::iterator it = buffer.begin(); it<buffer.end() ; ++it) {
            if(!in_block_comment && *it == '#'){
                //look ahead
                if (it+1 < buffer.end()) {
                    if (*(it+1) == 'i') {
                        //#include
                        if (it+7 < buffer.end()) {
                            if (string(it,it+7).compare("include")){
                                if(DEBUG_ENABLE){
                                    cerr<<"#inlcude recognized at line "<<ctr<<endl;
                                }
                                //TODO: implement #inlcude here
                                buffer_processed.clear();
                            }
                        }
                        else{
                            if(DEBUG_ENABLE){
                                cerr<<"Unknown command "<<string(it,find(it, buffer.end(),' '))<<" at line "<<ctr<<endl;
                            }
                            buffer_processed.clear();
                        }
                    }
                    else if (*(it+1) == 'd'){
                        //#define
                        if (it+6 < buffer.end()) {
                            if (string(it,it+6).compare("define")) {
                                if(DEBUG_ENABLE){
                                    cerr<<"#define recognized at line "<<ctr<<endl;
                                }
                                //TODO: implement #define here
                                buffer_processed.clear();
                            }
                        }
                        else{
                            if(DEBUG_ENABLE){
                                cerr<<"Unknown command "<<string(it,find(it, buffer.end(),' '))<<" at line "<<ctr<<endl;
                            }
                            buffer_processed.clear();
                        }
                    }
                    else{
                        if(DEBUG_ENABLE){
                            cerr<<"Unknown command "<<string(it,find(it, buffer.end(),' '))<<" at line "<<ctr<<endl;
                        }
                        buffer_processed.clear();
                    }
                }
            }
            else if (!in_block_comment && *it == '/'){
                if (it+1 < buffer.end()) {
                    if (*(it+1) == '/') {
                        //line comment
                        if(DEBUG_ENABLE){
                            cerr<<"Line comment recognized at line "<<ctr<<endl;
                        }
                        buffer_processed = string(buffer.begin(),it);
                    }
                    else if(*(it+1) == '*'){
                        //block comment
                        if(DEBUG_ENABLE){
                            cerr<<"Block comment begin at line "<<ctr<<endl;
                        }
                        buffer_processed = string(buffer.begin(),it);
                        in_block_comment = true;
                        block_comment_begin = true;
                    }
                    
                }
            }
            else if (in_block_comment && *it == '*'){
                if (it+1 < buffer.end()) {
                    if (*(it+1) == '/') {
                        //block comment end
                        if(DEBUG_ENABLE){
                            cerr<<"Block comment end at line "<<ctr<<endl;
                        }
                        in_block_comment = false;
                        buffer_processed = string(it+2,buffer.end());
                    }
                }
            }
        }
        if (block_comment_begin) {
            if (buffer_processed.length()>0) {
                cout<<buffer_processed<<endl;
            }
            block_comment_begin = false;
        }
        if (!in_block_comment) {
            if (buffer_processed.length()>0) {
                cout<<buffer_processed<<endl;
            }
        }
        ++ctr;
    }
    return 0;
}

