#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<map>
#include<set>
#include<numeric>
#include <string>
using namespace std;         //命名空间

// 323  无向图中连通分量的数目
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n);
        for(int i=0; i<n; i++) parent[i] = i;

        for(auto& edge : edges) Union(parent, edge[0], edge[1], n);
        set<int> results;
        for(int i=0; i<n; i++) results.insert(parent[i]);
        return results.size();
    }
private:
    int Find(int i, vector<int>& parent) {
        int root = i;
        while(root != parent[root]) root = parent[root];     // 对于根节点，自己指向自己  root = parent[root]

        int tmp=i, p;
        while(tmp != root) {                                 // 压缩路径优化
            p = parent[tmp];
            parent[tmp] = root;
            tmp = p;
        }
        return root;
    }
    void Union(vector<int>& parent, int i, int j, int n) {
        if(i<0 || i>=n || j<0 || j>=n) return;
        int root_i = Find(i, parent);
        int root_j = Find(j, parent);
        if(root_i != root_j) parent[root_i] = root_j;
    }
};


// 547 朋友圈
class Solution {                        // O(logN*M)，通过额外的空间rank记录子集的中元素个数，可以在Uion时，将短的子集接到长子集的后面，从而使得Find的时候不至于趋向O(N)
public:
    int findCircleNum(vector<vector<int>>& M) {
        if(!M.size() || !M[0].size()) return -1;
        int n = M.size();
        vector<int> parent(n);
        for(int i=0; i<n; i++) parent[i] = i;

        for(int i=0; i<n; i++) {
            for(int j=0; j<i; j++) {
                if(M[i][j]) Union(parent, n, i, j);
            }
        }

        int result = 0;
        for(int i=0; i<n; i++) {
            if(parent[i]==i) result++;
        }
        return result;
    }
private:
    int Find(vector<int>& parent,  int i) {
        int root = i;
        while(root != parent[root]) root = parent[root];

        int tmp=i, p;
        while(tmp!=root) {
            p = parent[tmp];
            parent[tmp] = root;
            tmp = p;
        } 
        return root;
    }

    void Union(vector<int>& parent, int n, int i, int j) {
        if(i<0 || i>=n || j<0 || j>=n) return ;
        int root_i = Find(parent, i);
        int root_j = Find(parent, j);
        if(root_i != root_j) parent[root_i] = root_j;
    }
};


// 200. 岛屿数量        O(logN*M)，通过额外的空间rank记录子集的中元素个数，可以在Uion时，将短的子集接到长子集的后面，从而使得Find的时候不至于趋向O(N)  
class Solution {       // 还可以用DFS，BFS，对于类似迷宫的题目，使用并查集有些复杂了
public:
    int numIslands(vector<vector<char>>& grid) {
        if(!grid.size() || !grid[0].size()) return 0;
        int row=grid.size(), col=grid[0].size();
        int index, x, y, index_;
        vector<vector<int>> directions={{0,1}, {1,0}};       // 两个方向，右，下即可，因为遍历时，其他方向都会遍历到
        vector<int> parent(row*col, -1);
        for(int i=0; i<parent.size(); i++) parent[i] = i;
        for(int i=0; i<row; i++) {
            for(int j=0; j<col; j++) {
                index = i*col+j;
                if(grid[i][j]=='0') {                            // 确认为节点则初始化为与自己连通，不是节点的，则抛弃置为-1（不是岛屿则置为-1）
                    parent[index] = -1;
                    continue;
                }
                for(auto direction : directions) {
                    x = i+direction[0];
                    y = j+direction[1];
                    if(x<0 || x>=row || y<0 || y>=col || grid[x][y]=='0') continue;
                    index_ = x*col+y;
                    Union(parent, index, index_);                 //对于连通的两个岛，进行合并，即指向同一个根节点
                }
            }
        }
        int result=0;                          // 不能忘记初始化
        for(int i=0; i<parent.size(); i++) {
            if(i==parent[i]) result++;
        }
        return result;
    }
private:
    int Find(vector<int>& parent,  int i) {
        int root = i;
        while(root != parent[root]) root = parent[root];

        int tmp=i, p;
        while(tmp!=root) {
            p = parent[tmp];
            parent[tmp] = root;
            tmp = p;
        } 
        return root;
    }

    void Union(vector<int>& parent, int i, int j) {
        int root_i = Find(parent, i);
        int root_j = Find(parent, j);
        if(root_i != root_j) parent[root_i] = root_j;
    }
};