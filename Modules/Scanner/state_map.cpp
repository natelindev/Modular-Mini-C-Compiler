//
//  state_map.cpp
//  Scanner
//
//  Created by 林理露 on 29/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <unordered_map>
#include "Scanner.h"
#include "state_map.h"

std::unordered_map<std::pair<states,char>,states,pair_hash> state_map;

states get_state(states cur_state,const char cur_char)
{
    static bool next_sign_digit =false;
    if (next_sign_digit && (cur_char == '-' || cur_char == '+')){
        next_sign_digit = false;
        return states::DGT;
    }
    if (cur_state == states::STR && cur_char!= '\"' && cur_char != '\'' && cur_char != '\n') {
        return states::STR;
    }
    else{
        if(cur_state == states::DGT && (cur_char == 'e' || cur_char == 'E'))
        {
            next_sign_digit = true;
        }
        return state_map[std::pair<states,char>(cur_state,cur_char)];
    }
}

void init_statemap()
{
    //TABLE for DFA states
    //operator signs
    state_map[std::pair<states,char>(states::DFT,'+')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'-')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'*')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'/')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'%')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'<')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'>')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'=')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'!')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'~')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'&')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'^')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'|')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,',')] = states::OPT;
    state_map[std::pair<states,char>(states::DFT,'.')] = states::OPT;
    
    state_map[std::pair<states,char>(states::IDT,'+')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'-')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'*')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'/')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'%')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'<')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'>')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'=')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'!')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'~')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'&')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'^')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'|')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,',')] = states::OPT;
    state_map[std::pair<states,char>(states::IDT,'.')] = states::OPT;
    
    state_map[std::pair<states,char>(states::OPT,'+')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'-')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'*')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'/')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'%')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'<')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'>')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'=')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'!')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'~')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'&')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'^')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'|')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,',')] = states::OPT;
    state_map[std::pair<states,char>(states::OPT,'.')] = states::OPT;
    
    state_map[std::pair<states,char>(states::SPT,'+')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'-')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'*')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'/')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'%')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'<')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'>')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'=')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'!')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'~')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'&')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'^')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'|')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,',')] = states::OPT;
    state_map[std::pair<states,char>(states::SPT,'.')] = states::OPT;
    
    state_map[std::pair<states,char>(states::DGT,'+')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'-')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'*')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'/')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'%')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'<')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'>')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'=')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'!')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'~')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'&')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'^')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'|')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,',')] = states::OPT;
    state_map[std::pair<states,char>(states::DGT,'.')] = states::DGT;
    
    //separator signs
    
    state_map[std::pair<states,char>(states::DFT,'{')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,'}')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,'[')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,']')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,'(')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,')')] = states::SPT;
    state_map[std::pair<states,char>(states::DFT,';')] = states::SPT;
    
    state_map[std::pair<states,char>(states::IDT,'{')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,'}')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,'[')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,']')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,'(')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,')')] = states::SPT;
    state_map[std::pair<states,char>(states::IDT,';')] = states::SPT;
    
    state_map[std::pair<states,char>(states::OPT,'{')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,'}')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,'[')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,']')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,'(')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,')')] = states::SPT;
    state_map[std::pair<states,char>(states::OPT,';')] = states::SPT;
    
    state_map[std::pair<states,char>(states::SPT,'{')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,'}')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,'[')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,']')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,'(')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,')')] = states::SPT;
    state_map[std::pair<states,char>(states::SPT,';')] = states::SPT;
    
    state_map[std::pair<states,char>(states::DGT,'{')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,'}')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,'[')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,']')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,'(')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,')')] = states::SPT;
    state_map[std::pair<states,char>(states::DGT,';')] = states::SPT;
    
    //identifier signs
    
    state_map[std::pair<states,char>(states::DFT,'A')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'B')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'C')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'D')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'E')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'F')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'G')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'H')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'I')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'J')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'K')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'L')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'M')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'N')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'O')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'P')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'Q')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'R')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'S')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'T')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'U')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'V')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'W')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'X')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'Y')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'Z')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'a')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'b')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'c')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'d')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'e')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'f')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'g')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'h')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'i')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'j')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'k')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'l')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'m')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'n')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'o')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'p')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'q')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'r')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'s')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'t')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'u')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'v')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'w')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'x')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'y')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'z')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'_')] = states::IDT;
    state_map[std::pair<states,char>(states::DFT,'1')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'2')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'3')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'4')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'5')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'6')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'7')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'8')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'9')] = states::DGT;
    state_map[std::pair<states,char>(states::DFT,'0')] = states::DGT;
    
    state_map[std::pair<states,char>(states::IDT,'A')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'B')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'C')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'D')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'E')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'F')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'G')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'H')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'I')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'J')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'K')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'L')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'M')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'N')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'O')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'P')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'Q')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'R')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'S')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'T')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'U')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'V')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'W')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'X')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'Y')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'Z')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'a')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'b')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'c')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'d')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'e')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'f')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'g')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'h')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'i')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'j')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'k')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'l')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'m')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'n')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'o')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'p')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'q')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'r')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'s')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'t')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'u')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'v')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'w')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'x')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'y')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'z')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'_')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'1')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'2')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'3')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'4')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'5')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'6')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'7')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'8')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'9')] = states::IDT;
    state_map[std::pair<states,char>(states::IDT,'0')] = states::IDT;
    
    state_map[std::pair<states,char>(states::OPT,'A')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'B')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'C')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'D')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'E')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'F')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'G')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'H')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'I')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'J')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'K')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'L')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'M')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'N')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'O')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'P')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'Q')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'R')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'S')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'T')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'U')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'V')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'W')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'X')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'Y')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'Z')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'a')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'b')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'c')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'d')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'e')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'f')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'g')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'h')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'i')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'j')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'k')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'l')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'m')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'n')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'o')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'p')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'q')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'r')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'s')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'t')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'u')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'v')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'w')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'x')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'y')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'z')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'_')] = states::IDT;
    state_map[std::pair<states,char>(states::OPT,'1')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'2')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'3')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'4')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'5')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'6')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'7')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'8')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'9')] = states::DGT;
    state_map[std::pair<states,char>(states::OPT,'0')] = states::DGT;
    
    state_map[std::pair<states,char>(states::SPT,'A')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'B')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'C')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'D')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'E')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'F')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'G')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'H')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'I')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'J')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'K')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'L')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'M')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'N')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'O')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'P')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'Q')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'R')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'S')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'T')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'U')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'V')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'W')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'X')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'Y')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'Z')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'a')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'b')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'c')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'d')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'e')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'f')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'g')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'h')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'i')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'j')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'k')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'l')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'m')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'n')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'o')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'p')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'q')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'r')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'s')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'t')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'u')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'v')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'w')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'x')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'y')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'z')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'_')] = states::IDT;
    state_map[std::pair<states,char>(states::SPT,'1')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'2')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'3')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'4')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'5')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'6')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'7')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'8')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'9')] = states::DGT;
    state_map[std::pair<states,char>(states::SPT,'0')] = states::DGT;
    
    state_map[std::pair<states,char>(states::DGT,'A')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'B')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'C')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'D')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'E')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'F')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'G')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'H')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'I')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'J')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'K')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'L')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'M')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'N')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'O')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'P')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'Q')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'R')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'S')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'T')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'U')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'V')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'W')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'X')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'Y')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'Z')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'a')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'b')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'c')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'d')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'e')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'f')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'g')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'h')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'i')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'j')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'k')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'l')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'m')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'n')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'o')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'p')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'q')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'r')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'s')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'t')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'u')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'v')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'w')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'x')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'y')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'z')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'_')] = states::ERR;
    state_map[std::pair<states,char>(states::DGT,'1')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'2')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'3')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'4')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'5')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'6')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'7')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'8')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'9')] = states::DGT;
    state_map[std::pair<states,char>(states::DGT,'0')] = states::DGT;
    
    // string literal signs
    state_map[std::pair<states,char>(states::DFT,'\"')] = states::STR;
    state_map[std::pair<states,char>(states::IDT,'\"')] = states::STR;
    state_map[std::pair<states,char>(states::OPT,'\"')] = states::STR;
    state_map[std::pair<states,char>(states::DGT,'\"')] = states::STR;
    state_map[std::pair<states,char>(states::SPT,'\"')] = states::STR;
    state_map[std::pair<states,char>(states::STR,'\"')] = states::DFT;
    
    state_map[std::pair<states,char>(states::DFT,'\'')] = states::STR;
    state_map[std::pair<states,char>(states::IDT,'\'')] = states::STR;
    state_map[std::pair<states,char>(states::OPT,'\'')] = states::STR;
    state_map[std::pair<states,char>(states::DGT,'\'')] = states::STR;
    state_map[std::pair<states,char>(states::SPT,'\'')] = states::STR;
    state_map[std::pair<states,char>(states::STR,'\'')] = states::DFT;
    
    //space signs
    state_map[std::pair<states,char>(states::DFT,' ')] = states::DFT;
    state_map[std::pair<states,char>(states::DFT,'\t')] = states::DFT;
    state_map[std::pair<states,char>(states::DFT,'\n')] = states::DFT;
    
    state_map[std::pair<states,char>(states::OPT,' ')] = states::DFT;
    state_map[std::pair<states,char>(states::OPT,'\t')] = states::DFT;
    state_map[std::pair<states,char>(states::OPT,'\n')] = states::DFT;
    
    state_map[std::pair<states,char>(states::SPT,' ')] = states::DFT;
    state_map[std::pair<states,char>(states::SPT,'\t')] = states::DFT;
    state_map[std::pair<states,char>(states::SPT,'\n')] = states::DFT;
    
    state_map[std::pair<states,char>(states::DGT,' ')] = states::DFT;
    state_map[std::pair<states,char>(states::DGT,'\t')] = states::DFT;
    state_map[std::pair<states,char>(states::DGT,'\n')] = states::DFT;
    
    state_map[std::pair<states,char>(states::STR,'\n')] = states::ERR;
}
