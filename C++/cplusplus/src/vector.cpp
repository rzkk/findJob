#include<vector>
#include<iostream>

using std::cout;
using std::endl;
using std::vector;

void test1()
{
    //cout<<sizeof(bool)<<endl;
    int arr[] = {0,2,4,6,8};
    vector<int>vec1;
    //vec1.capacity();
    vector<int>vec2(10);   // 10个默认值
    vector<int>vec3(10,1); // 10个1
    vector<int>vec4 {1, 3, 5, 7, 9};  //initializer_list

    vector<int>vec5(vec4);
    vector<int>vec6 = vec5;
    vector<int>vec7(vec5.begin(),vec5.end());
    vector<int>vec8(arr,arr+10); //5是个数 ， 区间是 [ ) 
    for(auto &i:vec8)
    {
        cout<<i<<endl;
    }
}
void test2()
{
    vector<int>vec{1,3,5,7,9};
    // vector<int>::iterator it1 = vec.begin();
    // vector<int>::iterator it2 = vec.end();

    // vector<int>::reverse_iterator it3 = vec.rbegin();
    // vector<int>::reverse_iterator it4 = vec.rend();

    // vector<int>::const_iterator  it5 = vec.cbegin();
    // vector<int>::const_iterator  it6 = vec.cend();

    // vector<int>::const_reverse_iterator it7 = vec.crbegin();
    // vector<int>::const_reverse_iterator it8 = vec.crend();
  //苟富贵

}
void test3(){
    vector<int>vec1{1,3,5,7,9};
    vector<int>vec2 , vec3;

    vec1.reserve(10);

    vec2 = vec1;

    cout<<vec1.size()<<endl;
    cout<<vec1.capacity()<<endl;

    cout<<vec2.size()<<endl;
    cout<<vec2.capacity()<<endl;

    vec3.assign(vec1.begin(),vec1.end());
    cout<<vec3.size()<<endl;
    cout<<vec3.capacity()<<endl;

    // vec.resize(3);

    // for(auto & i:vec){
    //     cout<< i << " ";
    // }
    // cout<<endl;
    // cout<<vec.size()<<endl;
    // cout<<vec.capacity()<<endl;
    // cout<<endl;


}
class A{
public:

    A(int a = 0 , int b  = 0): _a(a) , _b(b)
    {

    }
    int _a, _b;
};
void test4()
{
    std::vector<int> vec{1,2};
    //第一种格式用法
    vec.insert(vec.begin() + 1, 3);  //{1,3,2}
  
    //第二种格式用法
    vec.insert(vec.end(), 2, 5);//{1,3,2,5,5}
    //第三种格式用法
    vector<int>test{ 7,8,9 };
    vec.insert(vec.end(), test.begin(), test.end());//{1,3,2,5,5,7,8,9}
    //第四种格式用法
    //demo.insert(demo.end(), { 10,11 });//{1,3,2,5,5,7,8,9,10,11}

    // for (size_t i = 0; i < vec.size(); i++) {
    //     cout << vec[i] << " ";
    // }
    // cout<<endl;

    vector<A>vecA(3);
    vecA.emplace(vecA.begin()+2 ,3);
    for(auto & i : vecA)
    {
        cout<<i._a<<" "<<i._b<<" \n";
    }
    cout<<endl;

}
#include<algorithm>
void test5(){
    vector<int> vec = {0,1,2,2,2,2,2,3,4};
    // for(auto iter=count.begin();iter!=count.end();iter++)
    // {
    //     if(2 == *iter)
    //     {
    //          count.erase(iter);
    //     }
    // }
    // 
    auto it = std::remove(vec.begin(),vec.end() , 2);
    
    for (auto& i:vec)
    {
        cout<<i<<" ";
        /* code */
    }
     cout<<endl;
    cout<<vec.size()<<" "<<vec.capacity()<<"\n";

    vec.erase(it, vec.end());
    for (auto& i:vec)
    {
        cout<<i<<" ";
        /* code */
    }
    cout<<endl;
    cout<<vec.size()<<" "<<vec.capacity()<<"\n";
     
    cout<<endl;
}
void test6()
{
    vector<int>vec{1,2,3,4,5,6};
    cout<<&vec<<endl;
    cout<<&(*vec.begin())<<endl;
    cout<<&(vec[0])<<endl;
}
int main()
{
    test6();
    return 0;
}