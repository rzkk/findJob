#include<iostream>

#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

int minCost1(vector<vector<int>>& costs) {
    int n = costs.size();
    int k = costs[0].size();
    vector<vector<int>> dp(2 , vector<int>(k , 0)) ; 

    for(int i = 0;i<k;++i){
        dp[0][i] = costs[0][i];
    }
    for(int i = 1;i<n ;++i){

        for(int j = 0 ; j< k;++j){
            int minValue = INT32_MAX;
            for(int z = 0 ; z < k;++z){
                if(z == j) continue;
                minValue = min(minValue ,dp[ (i-1)%2][ z] );
            }
            dp[i%2][ j ] = minValue + costs[i][j];
        }
    }
    int res = dp[(n-1)%2][0];
    for(int i = 1 ;i< k;++i)
    {
        res = min( res,dp[(n-1)%2][i]);
    }
     return res;
 
 }
 
int minCost2(vector<vector<int>>& costs) { // climts
    int n = costs.size() ; // 房屋数
    int k = costs[0].size() ; // 颜色数

    vector<vector<int>> dp( 2  , vector<int>( k ,0 ));

    int minindex = -1, secindex = -1; //minindex1 最小 ，minindex2 次小
    int minValue = INT_MAX , secValue = INT_MAX;
    for(int i=0;i< k ;i++){    // costs[0][i] 如果小于最小的 ，更新最小的 ， 
                                //如果小于次小，大于最小 ， 更新次小
        if( costs[0][i] <  minValue ){ 
            secindex = minindex; 
            secValue = minValue;
            minValue = costs[0][i];
            minindex = i;
        }else if( costs[0][i] < secValue  ){
            secValue = costs[0][i];
            secindex = i;
        }
        dp[0][i]=costs[0][i];
    }

    //cout<<costs[0][minindex] <<"  " << costs[0][secindex]<<endl;
    for(int i = 1;i < n;i++){

        for(int j=0;j<k;j++){
            if( j == minindex) 
                dp[i%2][j]= dp[(i-1)%2][ secindex] + costs[i][j];
            else 
                dp[i%2][j]= dp[(i-1)%2][ minindex] + costs[i][j];
        }
        minValue = INT_MAX , secValue = INT_MAX;
        for(int j=0;j< k ;j++){    
            if( dp[i%2][j] <  minValue ){ 
                secindex = minindex; 
                secValue = minValue;
                minValue = dp[i%2][j];
                minindex = j;
            }else if( dp[i%2][j] < secValue  ){
                secValue = dp[i%2][j];
                secindex = j;
            }
        }
    }
    //int res=INT_MAX;
    // for(int i=0;i<costs[0].size();i++){
    //     res=min(res,dp[costs.size()-1][i]);
    // }
    return minValue;
}
 int main(){
    //vector<vector<int>>costs{{1,5,3 , 5,3,2,6} ,{2,9,4 ,5,3,2,8} ,{3,2,5,3,2,5,9,} ,{3,2,3,5,3,7,9,}};
    //[17,2,17],[16,16,5],[14,3,19]
    //vector<vector<int>>costs{{17,2,17},{16,16,5} ,{14,3,19}};
    vector<vector<int>>costs{{1,3},{2,4}};
    cout<<minCost1(costs)<<endl;
    cout<<minCost2(costs)<<endl;

 }