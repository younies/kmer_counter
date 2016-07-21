//
//  main.cpp
//  count_k_mers
//
//  Created by Younies Mahmoud on 4/2/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

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
using namespace std;

#include "helpers.hpp"
#include "enumTree.hpp"




int calculate_KN(int k , string BWT_path , string reverse_BWT_path);

int main(int argc, const char * argv[]) {
    // insert code here...

    string BWT_path = "/Users/youniesmahmoud/Documents/spring2016/biosequence_algorithms/hw3/hu-chr1-bwts/hu-chr1.bwt";
    string reverse_BWT_path = "/Users/youniesmahmoud/Documents/spring2016/biosequence_algorithms/hw3/hu-chr1-bwts/hu-chr1-rev.bwt";


    int k = 15;
    
    for (k = 15 ; k <= 40 ; ++k) {
        int Kn = calculate_KN( k , BWT_path, reverse_BWT_path);
        
        cout << k << "    " <<Kn << endl;

    }
    
    
    
    return 0;
}


int calculate_KN(int k , string BWT_path , string reverse_BWT_path)
{
    string BWT , reverse_BWT;
    
    ifstream BWT_file(BWT_path);
    ifstream reverse_BWT_file(reverse_BWT_path);
    
    if (BWT_file.is_open())
    {
        getline(BWT_file,  BWT);
        
        BWT_file.close();
    }
    else
    {
        cerr << "no file " << endl;
    }
    
    if (reverse_BWT_file.is_open())
    {
        getline(reverse_BWT_file,  reverse_BWT);
        
        reverse_BWT_file.close();
    }
    
    
   //BWT = "AAAAAAAAA$";
    //reverse_BWT = "AAAAAAAAA$";
    
    int bwt_length = (int)BWT.size();
    
    vector<int> C(5,0);
    
    for (int i = 0 , n = (int)BWT.size() ; i < n ; ++i)/// building c arrays  and for making A C G T --> 1 2 3 4
    {
        BWT[i]          =   convert_DNA_to_number(BWT[i]);
        reverse_BWT[i]  =   convert_DNA_to_number(reverse_BWT[i]);
        if(BWT[i] - '0' + 1 >= 5)
            continue;
        C[BWT[i] - '0' + 1 ]++;
    }
    
    for (int i = 1 , n = (int)C.size();  i < n  ; ++i)// to complete C's
        C[i] += C[i -1];
    
    
    vector<vector<int> > occ_BWT( 5 , vector<int>(bwt_length , 0));// for occ in BWT
    vector<vector<int> > reverse_occ_BWT( 5 , vector<int>(bwt_length , 0));// for occ in reverse BWT
    
    for (int i = 0 , n = (int)occ_BWT.size(); i < n; ++i)
    {
        for(int j = 0 ; j < bwt_length ; ++j)
        {
            if(BWT[j] - '0' == i)
            {
                if(j > 0)
                    occ_BWT[i][j] = occ_BWT[i][j - 1] + 1;
                else
                    occ_BWT[i][j]++;
            }
            else if(j > 0)
                occ_BWT[i][j] = occ_BWT[i][j - 1];
            
            if (reverse_BWT[j] - '0' == i)
            {
                if(j > 0)
                    reverse_occ_BWT[i][j] = reverse_occ_BWT[i][j - 1] + 1;
                else
                    reverse_occ_BWT[i][j]++;
            }
            else if(j > 0)
                reverse_occ_BWT[i][j] = reverse_occ_BWT[i][j - 1];
        }
    }
    
    
    
    
    
    //Now we have 2BWT and C and occ for both 2BWT
    
    enumNode root;
    root.I.first = 0;
    root.I.second = bwt_length - 1;
    root.I_dag.first = 0;
    root.I_dag.second = bwt_length - 1;
    root.depth = 0;
    
    
    
    int nodes = enum_difference(k, root, BWT, reverse_BWT, occ_BWT, reverse_occ_BWT, C) ;
    int leaves = bwt_length - k ;

   /* for (k = 15; k <= 40; ++k)
    {
        leaves = bwt_length - k + 1;
        int Knn = enum_difference(k, root, BWT, reverse_BWT, occ_BWT, reverse_occ_BWT, C);
        cout << k<< "   " << leaves + Knn << endl;
    }
    
    */
    //cout << leaves << endl;
 
    
    
    return leaves + nodes ;
    
}

















