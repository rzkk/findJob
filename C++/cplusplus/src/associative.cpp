#include<set>

#include<iostream>

using std::cout;
using std::endl;
using std::set;
namespace setTest{

void test1(){
    set<int>nums1;
    set<int>nums2{1,2,3,4,5,3,2,1};
    set<int>nums3(nums2);
    set<int>nums4(nums3.begin(),nums3.end());
    set<int>nums5(nums3.begin(),--nums3.end());

    for(auto & i : nums2){
        cout<<i <<" ";
    }

    cout<<endl;
    for(auto & i : nums5){
        cout<<i <<" ";
    }
    cout<<endl;
}
}
int main(){
    setTest::test1();
    return 0;
}
