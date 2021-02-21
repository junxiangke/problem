#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<unordered_set>
#include<map>
#include<set>
#include<numeric>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;         //命名空间


// 151 翻转字符串里面的单词               慢
class Solution {
public:
    string reverseWords(string s) {
        while(s.size()>0 && s.back()==' ') s.pop_back();    // 处理当前结尾的多余空格 
        if(s.size() == 0) return s;
        int end = s.size()-1;
        reverse(s.begin(), s.end());
        while(s.back() == ' ') s.pop_back(); // 处理翻转后的结尾的多余空格
        int lastindex = 0, index = 0;
        int length = 1;
        while(index < s.size()) {
            while(index < s.size() && s[index] != ' ') {
                index++; length++;
            }
            reverse(s.begin()+lastindex, s.begin()+index);      // 把空格堆积在每次翻转的前面，翻转后到了单词后面
            lastindex += length; length = 1;  
            while(index < s.size() && s[index] == ' ') index++; 
        }
        while(s.back() == ' ') s.pop_back();  // 不用整体移动，反转结束后空格都在最末尾
        return s;
    }
};

// 151 翻转字符串里面的单词   
class Solution {                     // 没有移动空格，直接把符合条件的放在前面，速度比上一个方法更快
public:
    string reverseWords(string s) {
        int storeindex = 0, index = 0;     // storindex指向下一个应该放置的位置
        reverse(s.begin(), s.end());       // 翻转 s
        for(index; index<s.size(); index++) {         
            if(s[index] == ' ') continue;       
            if(storeindex != 0) s[storeindex++] == ' ';
            int j = index;
            while(j < s.size() && s[j] != ' ') s[storeindex++] = s[j++];
            reverse(s.begin()+storeindex-(j-index), s.begin()+storeindex);     // 用于翻转[first,last)范围的元素
            index = j; 
        }
        s.resize(storeindex);         // 把当前字符串长度置为storeindex
        return s;
    }
};
class Solution {                     // 没有移动空格，直接把符合条件的放在前面，速度比上一个方法更快
public:
    string reverseWords(string s) {
        int storeindex = 0, index = 0;     // storindex指向下一个应该放置的位置
        reverse(s.begin(), s.end());       // 翻转 s
        while(index<s.size()) { 
            while(index<s.size() && s[index] == ' ') index++;                  // 如果直接走到了终点，storeindex++，并不能代表字符串的长度
            // 不满足条件 index<s.size() ，不应该执行下面的命令
            if(storeindex != 0) s[storeindex++] = ' ';                        
            int j = index;
            while(j < s.size() && s[j] != ' ') s[storeindex++] = s[j++];
            reverse(s.begin()+storeindex-(j-index), s.begin()+storeindex);     // 用于翻转[first,last)范围的元素
            index = j; 
        }
        s.resize(storeindex);
        return s;
    }
};
class Solution {                     // 没有移动空格，直接把符合条件的放在前面，速度比上一个方法更快
public:
    string reverseWords(string s) {
        int storeindex = 0, index = 0;     // storindex指向下一个应该放置的位置
        reverse(s.begin(), s.end());       // 翻转 s
        while(index<s.size()) { 
            while(index<s.size() && s[index] == ' ') index++;
            if(index>=s.size()) break;
            if(storeindex != 0) s[storeindex++] = ' ';
            int j = index;
            while(j < s.size() && s[j] != ' ') s[storeindex++] = s[j++];
            reverse(s.begin()+storeindex-(j-index), s.begin()+storeindex);     // 用于翻转[first,last)范围的元素
            index = j; 
        }
        s.resize(storeindex);
        return s;
    }
};


// 186 翻转字符串里的单词 2
class Solution {
public:
    void reverseWords(vector<char>& s) {
        int index = 0; 
        reverse(s, 0, s.size()-1);
        while(index < s.size()) {
            int j = index;
            while(j < s.size() && s[j] != ' ') j++;
            reverse(s, index, j-1);
            index = j+1;
        }
    }
private:
    void reverse(vector<char>& s, int start, int end) {
        if(start >= end) return;
        while(start < end)  swap(s[start++], s[end--]);
        return;
    }
};
