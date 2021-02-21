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

// 269 火星词典
class Solution { 
public:
    string alienOrder(vector<string>& words) {
        // 根据题意生成有向图
        unordered_map<int, unordered_set<int>> graph;
        for(int i=0; i<words.size()-1; i++) {
            for(int j=0; j<words[i].size() && j<words[i+1].size(); j++) {
                if(words[i][j]==words[i+1][j]) continue;
                else {
                    if(!graph.count(words[i][j]-'a')) {
                        unordered_set<int> s;
                        graph[words[i][j]-'a'] = s;
                    }
                    graph[words[i][j]-'a'].insert(words[i+1][j]-'a');
                    break;
                }     
            }
        }
        // 生成有向图的入度map，与简单拓扑排序的区别是，有可能出现单个字母入度，出度为0，没有出现在graph中，因此需要遍历每个字母
        unordered_map<int, int> degree;
        for(string str: words) {
            for(auto i: str) {
                degree[i-'a'] = 0;
            }
        }
        for(auto& v: graph) {
            for(auto i: v.second) {
                degree[i]++;
            }
        }
        // 初始化q时，由于当前degree已包含所有字母，与简单拓扑排序略有区别
        queue<int> q;
        string results="";
        for(auto& v: degree) {
            if(v.second==0) {
                q.push(v.first);
                results += v.first+'a';
            }
        }
        while(!q.empty()) {
            int cur=q.front(); q.pop();
            for(auto i:graph[cur]) {
                degree[i]--;
                if(degree[i]==0) {
                    q.push(i);
                    results += i+'a';
                }
            }
        }
        // 出现环时，即不合法
        if(results.size()<degree.size()) return "";
        else return results;
    }
};
// 第二次刷题 1.落下判断是否成环；2.落下一些字母；3.string的单个元素是char

// 1203 项目管理
class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<int> results;
        int maxgroup = m;
        for(int i=0; i<n; i++) {
            if(group[i]==-1) group[i] = maxgroup++;
            groupmember[group[i]].insert(i);
        }
        cout<<maxgroup<<endl;
        vector<int> groupdegree(maxgroup, 0);
        for(int i=0; i<group.size(); i++) {
            for(auto j: beforeItems[i]) {
                if(!groupgraph.count(group[j])) {
                    unordered_set<int> groupset;
                    groupgraph[group[j]] = groupset;
                }
                if(group[j] != group[i])  groupgraph[group[j]].insert(group[i]);
                else graph[group[j]][j].insert(i);
            }
        }
        for(auto items: groupgraph) {
            for(auto i: items.second) groupdegree[i]++;
        }
        queue<int> q;
        vector<int> groupresults;
        for(int i=0; i<groupdegree.size(); i++) {
            cout<<i<<groupdegree[i]<<endl;
            if(groupdegree[i]==0) {
                q.push(i);
                groupresults.push_back(i);
            }
        }
        int c;
        while(!q.empty()) {
            c=q.front(); q.pop();
            cout<<c<<endl;
            for(auto n: groupgraph[c]) {
                cout<<n<<endl;
                groupdegree[n]--;
                if(groupdegree[n]==0) {
                    q.push(n);
                    groupresults.push_back(n);
                }
            }
        }
        cout<<groupresults.size()<<endl;
        if(groupresults.size() < maxgroup) return results;
        for(auto g: groupresults) {
            cout<<g;
            int size = results.size();
            ingroup(results, group, g, beforeItems);
            if(results.size()-size<groupmember[g].size()) return  vector<int>(0);
        }
        return results;
    }
private:
    unordered_map<int, unordered_set<int>> groupmember;
    unordered_map<int, unordered_set<int>> groupgraph;
    unordered_map<int, unordered_map<int, unordered_set<int>>> graph;
    void ingroup(vector<int>& results, vector<int>& group, int g, vector<vector<int>>& beforeItems) {
        unordered_map<int, int> degree;
        queue<int> q;
        for(auto i: groupmember[g]) degree[i]=0; 
        for(auto item: graph[g]) {
            for(int i: item.second) {
                degree[i]++;
            }
        }
        for(auto item: degree) {
            if(item.second==0) {
                q.push(item.first);
                results.push_back(item.first);
            }
        }
        while(!q.empty()) {
            auto j=q.front(); q.pop();
            for(auto i: graph[g][j]) {
                degree[i]--;
                if(degree[i]==0) {
                    q.push(i);
                    results.push_back(i);
                }
            }
        }
    }
};

