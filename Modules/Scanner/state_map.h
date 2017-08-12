//
//  state_map.h
//  Scanner
//
//  Created by 林理露 on 29/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#ifndef state_map_h
#define state_map_h

#include "Scanner.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        std::size_t h1 = static_cast<std::size_t>(p.first);
        std::size_t h2 = static_cast<std::size_t>(p.second);
        std::size_t h3 = static_cast<std::size_t>(states::ERR);
        return h1*h3+h2;
    }
};

extern std::unordered_map<std::pair<states,char>,states,pair_hash> state_map;

void init_statemap();
states get_state(states cur_state,const char cur_char);
#endif /* state_map_h */
