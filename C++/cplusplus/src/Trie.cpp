#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Trie {
    private:
        vector<Trie*>children;
        bool isEnd;
        
        Trie* searchPrefix(string prefix)  //找前缀存在吗
        {
            Trie*node = this;
            for(char ch :prefix)
            {
                ch = ch -'a';
                if(node->children[ch] == nullptr) 
                    return nullptr;
                node = node-> children[ch];
            }
            return node;
        }
    public:
        Trie():children(26),isEnd(false) {} //初始化
        
        void insert(string word) {
            Trie* node = this;
            for(auto ch : word)
            {
                ch -= 'a';
                if(node->children[ch] == nullptr)
                {
                    node->children[ch] = new Trie();
                }
                node = node->children[ch];
            }
            node->isEnd = true;
        }
        
        bool search(string word) { // 找是否存在
            Trie *node = this->searchPrefix(word);
            return node != nullptr && node->isEnd;
        }

        int searchcnt(string word) { //找这个words 存在几次
            Trie *node = this->searchPrefix(word);
            return node != nullptr && node->isEnd;
        }

        bool startsWith(string prefix)   //返回树中以prefix为前缀的字符串个数 / 是否存在
        {
            return searchPrefix(prefix) != nullptr;
        }

        void  earse( string word){

        }
    };