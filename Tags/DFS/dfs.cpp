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
#include <string>
#include<cstring>
#include<sstream>
using namespace std;         //命名空间


// 499 迷宫 3
class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        vector<string> results;
        dfs(maze, ball[0], ball[1], hole, "", results);
        if(results.size() == 0) return "impossible";
        else return results[0];
    }
private:
    vector<int> x_list = {0, -1, 1, 0};
    vector<int> y_list = {-1, 0, 0, 1};
    vector<string> dic = {"d", "l", "r", "u"};
    // dfs 超出时间限制
    void dfs(vector<vector<int>>& maze, int x, int y, vector<int>& hole, string result, vector<string>& results) {
        for(int m = 0; m<4; m++) {
            int new_x = x+x_list[m], new_y=y+y_list[m];
            while(new_x>=0 && new_x<maze.size() && new_y>=0 && new_y<maze[0].size() && maze[new_x][new_y]==0) {
                if(new_x==hole[0] && new_y==hole[1]) {
                    results.push_back(result);
                    return;
                }
                dfs(maze, new_x, new_y, hole, result+dic[m], results);        // 不对的，没有墙壁，球不会停下转弯
                new_x = new_x + x_list[m]; new_y = new_y+y_list[m];
            }
        }
        return ;
    }
    // 如果对于某一个位置，在字典序靠前的第五层，在字典序靠后的第二层，就没有办法得到字典序靠前的结果了
    string bfs(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        string result;
        queue<vector<int>> q;
        unordered_set<vector<int>> visited;
        q.push(ball);
        visited.insert(ball);
        while(!q.empty) {
            int x = q.front()[0], y = q.front()[1]; q.pop();
            for(int m = 0; m<4; m++) {
            int new_x = x+x_list[m], new_y=y+y_list[m];
            while(new_x>=0 && new_x<maze.size() && new_y>=0 && new_y<maze[0].size() && maze[new_x][new_y]==0) {
                if(new_x==hole[0] && new_y==hole[1])  return result;
                new_x = new_x + x_list[m]; new_y = new_y+y_list[m];
            }
        }
        }
        return "impossible";
    }
};

// 490 迷宫 1
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        return bfs(maze, start, destination);
    }
private:
    vector<int> x_list = {0, -1, 1, 0};
    vector<int> y_list = {-1, 0, 0, 1};
    bool bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        queue<vector<int>> q;
        vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size(), 0));
        q.push(start);
        visited[start[0]][start[1]] = 1;
        while(!q.empty()) {
            int x = q.front()[0], y = q.front()[1]; q.pop();
            for(int m = 0; m<4; m++) {
                vector<int> s = stop(maze, x, y, x_list[m], y_list[m]);   // 有墙壁才能停下来，destination需要停下来
                if(s[0]==destination[0] && s[1]==destination[1])  return true;
                if(visited[s[0]][s[1]] == 1) continue;
                q.push(s); visited[s[0]][s[1]] = 1;
            }
        }
        return false;
    }
    vector<int> stop(vector<vector<int>>& maze, int x, int y, int delta_x, int delta_y) {
        int new_x = x + delta_x, new_y = y + delta_y;
        while(new_x>=0 && new_x<maze.size() && new_y>=0 && new_y<maze[0].size() && maze[new_x][new_y]==0) {
            x = new_x; y = new_y;
            new_x = new_x + delta_x; new_y = new_y + delta_y;
        }
        return {x, y};
    }
};

// 505 迷宫 2
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size(), INT_MAX));
        bfs(maze, start, destination, visited);
        return visited[destination[0]][destination[1]]==INT_MAX? -1: visited[destination[0]][destination[1]];
    }
private:
    vector<int> x_list = {0, -1, 1, 0};
    vector<int> y_list = {-1, 0, 0, 1};
    void bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination, vector<vector<int>>& visited) {
        queue<vector<int>> q;
        q.push(start);
        visited[start[0]][start[1]] = 0;
        while(!q.empty()) {
            int x = q.front()[0], y = q.front()[1]; q.pop();
            for(int m = 0; m<4; m++) {
                vector<int> s = stop(maze, x, y, x_list[m], y_list[m]);   // 有墙壁才能停下来，destination需要停下来
                if(visited[s[0]][s[1]] > visited[x][y]+s[2]) { 
                    // 即使已经遍历过的位置，如果再次碰到，并且距离更短，要再次走一遍
                    // 要遍历所有的解法，以免在前一次走到了终点但不是最优解，就结束了，所以终点不能入栈
                    if(!(s[0]==destination[0] && s[1]==destination[1])) q.push(s); 
                    visited[s[0]][s[1]] = min(visited[s[0]][s[1]], visited[x][y]+s[2]);
                }
            }
        }
        return;
    }
    vector<int> stop(vector<vector<int>>& maze, int x, int y, int delta_x, int delta_y) {
        int new_x = x + delta_x, new_y = y + delta_y;
        int i = 0;
        while(new_x>=0 && new_x<maze.size() && new_y>=0 && new_y<maze[0].size() && maze[new_x][new_y]==0) {
            x = new_x; y = new_y; i++;
            new_x = new_x + delta_x; new_y = new_y + delta_y;
        }
        return {x, y, i};
    }
};

// 499 迷宫 3
 class Solution {
public:
    int findShortestWay(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<string>> visited(maze.size(), vector<string>(maze[0].size()));
        bfs(maze, start, destination, visited);
        return visited[destination[0]][destination[1]]==INT_MAX? -1: visited[destination[0]][destination[1]];
    }
private:
    vector<int> x_list = {0, -1, 1, 0};
    vector<int> y_list = {-1, 0, 0, 1};
    vector<string> dic = {"d", "l", "r", "u"};
    void bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination, vector<vector<string>>& visited) {
        queue<vector<int>> q;
        q.push(start);
        visited[start[0]][start[1]] = "";
        while(!q.empty()) {
            int x = q.front()[0], y = q.front()[1]; q.pop();
            for(int m = 0; m<4; m++) {
                vector<int> s = stop(maze, x, y, x_list[m], y_list[m]);   // 有墙壁才能停下来，destination需要停下来
                if(visited[s[0]][s[1]] > visited[x][y]+dic[m]) { 
                    // 即使已经遍历过的位置，如果再次碰到，并且距离更短，要再次走一遍
                    // 要遍历所有的解法，以免在前一次走到了终点但不是最优解，就结束了，所以终点不能入栈
                    if(!(s[0]==destination[0] && s[1]==destination[1])) q.push(s); 
                    visited[s[0]][s[1]] = min(visited[s[0]][s[1]], visited[x][y]+s[2]);
                }
            }
        }
        return;
    }
    vector<int> stop(vector<vector<int>>& maze, int x, int y, int delta_x, int delta_y) {
        int new_x = x + delta_x, new_y = y + delta_y;
        while(new_x>=0 && new_x<maze.size() && new_y>=0 && new_y<maze[0].size() && maze[new_x][new_y]==0) {
            x = new_x; y = new_y; 
            new_x = new_x + delta_x; new_y = new_y + delta_y;
        }
        return {x, y};
    }


};