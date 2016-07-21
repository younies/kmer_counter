//
//  enumTree.cpp
//  count_k_mers
//
//  Created by Younies Mahmoud on 4/2/16.
//  Copyright © 2016 Younies Mahmoud. All rights reserved.
//

#include "enumTree.hpp"




int enum_difference(int k , enumNode node , string BWT , string reverse_BWT , vector<vector<int> > &occ_B , vector<vector<int> > &occ_reverse_B , vector<int> &C )
{
    int ret = 0;
    stack<enumNode> enum_stack;
    
    //enum node = make_pair(I, I_dag);
    
    enum_stack.push(node);
    
    while (!enum_stack.empty())
    {
        //cerr << enum_stack.size() << endl;
        node = enum_stack.top();
        enum_stack.pop();

        
        int differenc_bases = isRightMaximal(node, reverse_BWT , ret , k ,occ_reverse_B );
        if(differenc_bases < 1)
            cerr << "errrrror in differences" << endl;
        if(differenc_bases > 1)// Right maximal
        {
            if(node.depth >= k)// the node at depth more than k
                ret += 1 - differenc_bases ;// plus one for the node and minus the children
        
            vector<enumNode> newChilden(4);
            
            int maxpos = 0 , maxchildren = 0 ,  count = 0;
            
            for (int i = 1 ; i <= 4 ; ++i)
            {
                char base = i + '0';
                if(computing_child(node, base, occ_B, occ_reverse_B, C , newChilden[count] , ret , k))
                {
                    
                    int distance = newChilden[count].I.second - newChilden[count].I.first + 1;
                    count++;
                    if(distance > maxchildren)
                    {
                        maxchildren = distance;
                        maxpos = count - 1;//because the count is incremented
                    }
                    
                    
                }
                
            }// after enumerating the children
            
            if(count > 0)//there is at least one children
            {
                enum_stack.push(newChilden[maxpos]);//push the maximum one first
                for (int i = 0 ; i < count; ++i)
                {
                    if(i != maxpos)
                        enum_stack.push(newChilden[i]);
                }
            }//pushing all the children
            
        }
        

    }
    
    return ret;
}


int isRightMaximal(enumNode node , string & reverse_BWT, int &ret , int k , vector<vector<int> > &occ_r_b)
{
   /* pair<int, int> I_dag  = node.I_dag;
    vector<int> counts(5 , 0);
    for (int i = I_dag.first; i <= I_dag.second; ++i)
    {
        counts[reverse_BWT[i] - '0'] = 1;
    }
    */
    int finalCount = 0;
    
    for (int i = 0 ; i <  5 ; ++i)
    {
        if(node.I_dag.first > 0)
            finalCount += (int)(occ_r_b[i][node.I_dag.second] > occ_r_b[i][node.I_dag.first - 1]);
        else
            finalCount += (int)(occ_r_b[i][node.I_dag.second] > 0);
            
    }
    
    
   // cerr << finalCount << endl;
    
   /* if(counts[0] > 0 && node.depth >= k)
    {
      //  ret++;
        cerr << "leave stuck\n";
    }
    */
    return finalCount;/*
    
    for(int i = I_dag.first ; i < I_dag.second ; ++i)
        if(reverse_BWT[i] != reverse_BWT[i+1])
            return true;
    return false;
                       */
}


bool computing_child(enumNode parent, char base , vector<vector<int> > & occ_B , vector<vector<int> > & occ_reverse_B , vector<int>& C , enumNode &newChild , int &ret , int k)
{
    
    // building i , j
    pair<int, int> newI;
    if(parent.I.first != 0)
    {
        newI.first  = C[base - '0'] + occ_B[base - '0'][ parent.I.first - 1];// + 1;//i ← C[P[k]] + occB(P[k], i − 1) + 1
        newI.second = C[base - '0'] + occ_B[base - '0'][parent.I.second] - 1;//j ← C[P[k]] + occB(P[k], j)
    }
    else
    {
        newI.first  = C[base - '0'] ;//+ 1;//i ← C[P[k]] + occB(P[k], i − 1) + 1
        newI.second = C[base - '0'] + occ_B[base - '0'][parent.I.second] - 1;//j ← C[P[k]] + occB(P[k], j)
    }
   // if(newI.first > newI.second)
     //   cerr << "hhhhhhhhhh" << endl;
    
    //if(newI.first == newI.second && parent.depth  >= k -1)//leave
      // ret++;
    if(newI.first >= newI.second )
        return false;
    
    
    // computing i' , j'
    pair<int, int> newI_dag;
    
    //to calculate x
    int x = 0;
    for (int i = 0 ; i < base - '0' ; ++i)
    {
        if(parent.I.first == 0)
            x += occ_B[i][parent.I.second];
        else
            x += occ_B[i][parent.I.second] - occ_B[i][parent.I.first - 1];

    }
    
    //to calculate y
    int y;
    if(parent.I.first != 0)
        y = x + occ_B[base - '0'][parent.I.second] - occ_B[base - '0'][parent.I.first - 1];
    else
        y = x +  occ_B[base - '0'][parent.I.second];
    
    //cerr << x << "    " << y << endl;
    
    newI_dag.first = parent.I_dag.first + x;
    newI_dag.second = parent.I_dag.first + y - 1;
    
    
    newChild.I = newI;
    newChild.I_dag = newI_dag;
    newChild.depth = parent.depth + 1;
    
    
    /*cout << newI.first << "   " << newI.second << endl;
    cout << newI_dag.first << "   " << newI_dag.second << endl;
    cout <<  newI.second - newI.first + 1 << "   " << newI_dag.second - newI_dag.first + 1  << endl;
    if(newI.second - newI.first + 1  != newI_dag.second - newI_dag.first + 1)
        cout << "booooooom" << endl;
    cout << endl;
    */
    return true;
    
}




