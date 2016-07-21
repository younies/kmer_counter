//
//  enumTree.hpp
//  count_k_mers
//
//  Created by Younies Mahmoud on 4/2/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#ifndef enumTree_hpp
#define enumTree_hpp

#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <fstream>
#include <stdio.h>

using namespace std;

struct enumNode {
    pair<int, int>  I;
    pair<int, int> I_dag;
    int depth;
} ;

int enum_difference(int k , enumNode node , string BWT , string reverse_BWT , vector<vector<int> > &occ_B , vector<vector<int> > &occ_reverse_B , vector<int> &C );

int isRightMaximal(enumNode node , string & reverse_BWT, int &ret , int k , vector<vector<int> > &occ_r_b);

bool computing_child(enumNode parent, char base , vector<vector<int> > & occ_B , vector<vector<int> > & occ_reverse_B , vector<int>& C , enumNode &newChild , int & ret , int k);

#endif /* enumTree_hpp */
