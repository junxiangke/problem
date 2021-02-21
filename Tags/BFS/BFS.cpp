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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
// 662 二叉树的最大宽度    BFS问题
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 1, start, last;
        queue<pair<TreeNode*, int>> q;
        pair<TreeNode*, int> cur;
        q.push(pair<TreeNode*, int>(root, 1));
        while(!q.empty()) {
            int size = q.size();
            if(size == 1) q.front().second = 1;        // 如果该层只有一个节点，则重新作为根节点计算，否则容易溢出;
            start = q.front().second;
            for(int i = 0; i < size; i++) {
                cur = q.front();
                q.pop();
                last = cur.second;
                if(cur.first->left != NULL)  q.push(pair<TreeNode*, int>(cur.first->left, cur.second*2));
                if(cur.first->right != NULL) q.push(pair<TreeNode*, int>(cur.first->right, cur.second*2+1));
            }
            res = max(res, last-start+1);
        }
        return res;
    }
};

// 102 二叉树的层次遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> results;
        if(root==NULL) return results;
        queue<TreeNode*> q;
        TreeNode* node;
        q.push(root);
        while(!q.empty()) {
            vector<int> level;
            int size = q.size();
            for(int i=0; i<size; i++) {
                node = q.front();
                q.pop();
                level.push_back(node->val);
                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);
            }
            results.push_back(level);
            level.clear();
        }
        return results;
    }
};

// 449 序列化和反序列化二叉搜索树
class Codec {
public:
    string serialize(TreeNode* root) {
        if(root==NULL) return "{}";
        // 也可以使用队列，然后不断往另一个vector里面添加，最后去掉末尾空元素，使用队列会不断被弹出，没有记录下数据
        // 无论是使用队列还是vector，思想都是  顺序访问先进入容器的元素，先进入先访问
        vector<TreeNode*> q;      // 首先需要把所有数据排好序放在一起，再序列化
        q.push_back(root);
        for(int i=0; i<q.size(); i++) {
            if(q[i]==NULL) continue;
            q.push_back(q[i]->left);
            q.push_back(q[i]->right);
        } 
/*        // queue<TreeNode*> q;    
        // vector<TreeNode*> list;
        // list.push_back(root);
        // while(!q.empty()) {
        //     TreeNode* cur = q.front(); q.pop();
        //     if(cur==NULL) continue;
        //     q.push(cur->left);
        //     q.push(cur->right);
        //     list.push_back(cur->left);
        //     list.push_back(cur->right);
        // }
*/

        while(q.size() && q[q.size()-1]==NULL) q.pop_back();
        stringstream ss;
        ss<<"{"<<q[0]->val;
        for(int i=1; i<q.size(); i++) {
            if(q[i]==NULL) ss<<",#";
            else ss<<","<<q[i]->val;
        }
        ss<<"}";
        return ss.str();
    }

    TreeNode* deserialize(string data) {
        if(data=="{}") return NULL;
        vector<string> vals = split(data.substr(1, data.size()-2), ",");
        TreeNode* root = new TreeNode(stoi(vals[0]));
        queue<TreeNode*> q;
        q.push(root);
        bool isleftnode=true;
        for(int i=1; i<vals.size(); i++) {
            if(vals[i] != "#") {       // 若为#，说明当前节点的孩子为空，则!leftnode
                TreeNode* node = new TreeNode(stoi(vals[i]));
                q.push(node);
                if(isleftnode==true) q.front()->left = node;
                else q.front()->right = node;
            }
            if(!isleftnode) q.pop();    // 非空，非叶子节点，一定会在循环中经历两次，两次后，即可弹出当前节点
            isleftnode = !isleftnode;
        }
        return root;
    }
private:
    vector<string> split(const string &str, string delim) {
        int index, lastindex=0;
        vector<string> results;
        index = str.find(delim, lastindex);
        while(index!=string :: npos) {     // lastindex指向上一次分隔符结束的下一位，index指向当前分隔符
            results.push_back(str.substr(lastindex, index-lastindex));
            lastindex = index + delim.size();
            index = str.find(delim, lastindex);      // 寻找下一个分割位置
        }
        results.push_back(str.substr(lastindex, str.size()-lastindex));  
        return results;
    }
};
// 第二次刷题 1.stringsteam相关不会写,可直接输入int；2.str.substr写错;3.str.size()-lastindex写错导致stoi输入出错

// 图的遍历问题
// 261 以图判树
// 判断图是否可以做树结构，1.出现环，2.有未连接到的节点则不是树
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n, unordered_set<int>());
        unordered_set<int> v;
        queue<int> q;
        q.push(0);
        v.insert(0);
        for(auto edge: edges) {                 
            // 建立的是无向图，添加两次，
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }
        while(!q.empty()){
            int cur=q.front();q.pop();
            for(auto neighbor: graph[cur]) {
                if(v.find(neighbor)!=v.end()) return false;    // 意味着出现了环形，a-b-c-a
                v.insert(neighbor);
                q.push(neighbor);
                graph[neighbor].erase(cur);        
                // 如果不是以图判树不需要去掉，当再次访问已经访问过的节点时，只需不进入queue即可
                // 比如a，b相连，a作为cur遍历了b以后，如果不把b中ab线去掉，在遍历b的时候，a会再次被遍历，会在上面的判断里被当成环
            }
        }
        if(v.size()==n) return true;
        else return false;
    }
};
// 第二遍刷题 1.set的添加操作是insert;2.graph中删掉某节点的某个邻居，需要erase


// 133 克隆图
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {}
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
// 三步走，1.找到所有点；2.clone node，即建立新旧节点映射；3.clone edges
class Solution {
public:
    Node* cloneGraph(Node* node) {   
        // 如果不使用map，只使用set判断是否访问过，在while循环中每一次新建的节点和之前的节点没有联系
        if(node==NULL) return NULL;
        queue<Node*> q;
        unordered_map<Node*, Node*> m;         // 新旧节点映射，同时起到了防止重复节点进入queue的作用
        q.push(node);
        Node* clone= new Node(node->val, vector<Node*>());
        m[node] = clone;
        while(!q.empty()) {
            Node* cur = q.front(); q.pop();
            for(auto neighbor: cur->neighbors) {
                // 1,2,3步骤同时进行，在找到新的节点时，判断是否已经建立映射，建立映射后，放入edges
                if(!m.count(neighbor)) {           
                    m[neighbor] = new Node(neighbor->val, vector<Node*>());
                    q.push(neighbor); 
                }
                m[cur]->neighbors.push_back(m[neighbor]);
            }
        }
        return clone;
    }
};

// 连通块问题
// 200 岛屿数量
class Solution {      // 遍历所有的点，遇到满足条件的进行bfs搜索
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0 || grid[0].size()==0) return 0;
        int num=0;
        for(int i=0; i<grid.size(); i++) {
            for(int j=0; j<grid[0].size(); j++) {
                if(grid[i][j]=='1') {
                    bfs(grid, i, j);
                    num++;
                }
            }
        }
        return num;
    }
private:
    vector<int> x_list{0,0,1,-1};
    vector<int> y_list{1,-1,0,0};
    void bfs(vector<vector<char>>& grid, int x, int y) {
        queue<vector<int>> q;
        q.push({x,y});
        grid[x][y]='0';
        while(!q.empty()) {
            vector<int> cur = q.front(); q.pop();
            for(int i=0; i<4; i++) {
                int x_new = cur[0] + x_list[i];
                int y_new = cur[1] + y_list[i];
                if(x_new<0 || x_new>=grid.size()) continue;
                if(y_new<0 || y_new>=grid[0].size()) continue;    // x，y的界限判断不要弄反
                if(grid[x_new][y_new]=='1') {
                    q.push({x_new, y_new});
                    grid[x_new][y_new]='0';
                }
            }
        }
    }
};
//第二遍刷题，1.如果只向前和下走得话，对于位于矩阵中央的十字形会错过左半部分;2.更新x_new使用了x

// 1036 逃离大迷宫
// 因为很大的迷宫中，只有少数点被blocked，因此需要找到trick，否则会超出时间限制
// 1. blocked围住的面积最大为M=len(blocked)*(len(blocked)-1),从target与source分别出发，如果可到达的面积都大于了M，即可返回true；
// 2. 把大迷宫变成小迷宫
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        set<int> srows{0, MAX_N - 1};
        set<int> scols{0, MAX_N - 1};
        addLineOfPoint(srows, scols, source[0], source[1]);
        addLineOfPoint(srows, scols, target[0], target[1]);
        for (auto& v : blocked) {
            addLineOfPoint(srows, scols, v[0], v[1]);
        }
        vector<int> rows(srows.begin(), srows.end());
        vector<int> cols(scols.begin(), scols.end());
        int R = rows.size();
        int C = cols.size();
        vector<vector<int> > grid(R, vector<int>(C, 0));
        set<vector<int> > b(blocked.begin(), blocked.end());
        int start_r;
        int start_c;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (rows[i] == source[0] && cols[j] == source[1]) {
                    grid[i][j] = 1;
                    start_r = i;
                    start_c = j;
                } else if (rows[i] == target[0] && cols[j] == target[1]) {
                    grid[i][j] = 2;
                } else if (b.count({rows[i], cols[j]})) {
                    grid[i][j] = -1;
                }
            }
        }
        return bfs(grid, start_r, start_c, R, C);
    }
private:
    vector<int> x_delta{0,0,1,-1};
    vector<int> y_delta{1,-1,0,0};
    const int MAX_N = 1e6;
    // bool dfs(vector<vector<int> >& grid, int i, int j, int R, int C) {
    //     for (int k = 0; k < 4; ++k) {
    //         int r = i + dirs[k][0];
    //         int c = j + dirs[k][1];
    //         if (r >= 0 && r < R && c >= 0 && c < C && grid[r][c] != -1 && grid[r][c] != 1) {
    //             if (grid[r][c] == 2) return true;
    //             grid[r][c] = 1;
    //             if (dfs(grid, r, c, R, C)) return true;
    //         }
    //     }
    //     return false;
    // }
    bool bfs(vector<vector<int> >& grid, int i, int j, int R, int C) {
        queue<vector<int>> q;
        q.push(vector<int>{i,j});
        while(!q.empty()) {
            vector<int> cur = q.front(); q.pop();
            for(int m=0; m<4; m++) {
                int x = cur[0] + x_delta[m];
                int y = cur[1] + y_delta[m];
                if(x<0 || x>=R || y<0 || y>=C || grid[x][y]==1 || grid[x][y]==-1) continue;
                if(grid[x][y]==2) return true;
                grid[x][y]=1;
                q.push(vector<int>{x,y});
            }
        }
        return false;
    }
    void addLineOfPoint(set<int>& rows, set<int>& cols, int i, int j) {
        for (int k = -1; k <= 0; ++k) {
            int r = i + k;
            if (r >= 0 && r < MAX_N) rows.insert(r);
            int c = j + k;
            if (c >= 0 && c < MAX_N) cols.insert(c);
        }
    }
};
// 第二次刷题，1.10^6的写法是1e6；2.忘记加入相邻的线；

// 最短路径问题
// 815 公交路线
// 1. 建立映射，每个站点可以到达的公交车；2. 起始车站如队列，遍历可乘坐的公交车可到达的车站，层次遍历
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if(S==T) return 0;
        int result=0;
        unordered_set<int> visited_bus;   
        unordered_set<int> visited_t; 
        queue<int> q;
        unordered_map<int, vector<int>> m;
        for(int i=0; i<routes.size(); i++) {
            for(int j=0; j<routes[i].size(); j++) {
                if(! m.count(routes[i][j])) m[routes[i][j]] = vector<int>();
                m[routes[i][j]].push_back(i);
            }
        }
        q.push(S); visited_t.insert(S);
        while(!q.empty()) {
            int size = q.size(); result++;
            for(int i=0; i<size; i++) {
                int c = q.front(); q.pop();
                for(int bus: m[c]) {
                    if(visited_bus.count(bus))  continue;
                    visited_bus.insert(bus);
                    for(auto t: routes[bus]) {
                        if(visited_t.count(t)) continue;
                        if(t==T) return result;
                        visited_t.insert(t); q.push(t);
                    }
                }
            }
        }
        return -1;
    }
};
// 第二次刷题，新建vector set 出错，使用vector<int>()


// 125 单词接龙    简单图的最短路径问题，难点在于找neighbors
// 1. for循环暴力一个单词的时间复杂度是 n*l=10w n=1w,l=10 
// 2. hash_map方法，每一个单词的可能的邻居有25*l个(每次只能改变一个字母)，得到的可能的邻居再去构造的hashset中判别是否在内，与n无关，与l有关，25*l*l=2500
// 在hashset/hashmap中查找字符串，时间复杂度最差是l
// 超时的原因是，1.不需要构造出全部graph；2.传入函数的参数尽量能用引用就用引用 ******出问题的原因是没有用引用，即使构造了所有graph，也可以通过
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(beginWord == endWord) return 1;
        if(beginWord.size() != endWord.size()) return 0;
        unordered_set<string> dictionary;
        for(string word: wordList) dictionary.insert(word);  
        // 比unordered_set<string> wordSet(wordList.begin(), wordList.end())  快
        int len = bfs(dictionary, beginWord, endWord);
        return len;
    }
private:
    vector<string> generate_neiborghs(string word, unordered_set<string>& dictionary) {
        vector<string> neighbors;
        for(int i=0; i<word.size(); i++) {
            string new_word = word;
            for(char c = 'a'; c<='z'; c++) {
                if(c!=word[i]) {
                    new_word[i]=c;
                    if(dictionary.count(new_word)) neighbors.push_back(new_word);
                }
            }   
        }
        return neighbors;
    }
    int bfs(unordered_set<string>& dictionary, string begin, string end) {
        int len = 1;
        queue<string> q;
        q.push(begin); dictionary.erase(begin);
        vector<string> neighbors;
        while(!q.empty()) {
            int size = q.size(); len++;
            for(int i=0; i<size; i++) {
                string word=q.front(); q.pop();
                neighbors = generate_neiborghs(word, dictionary);   
                // 每一次生成的neighbors，都是未进入过queue的
                for(string neighbor: neighbors) {
                    if(neighbor == end) return len;
                    q.push(neighbor);
                    dictionary.erase(neighbor);
                }
            }
        }
        return 0;
    }
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(beginWord.size() != endWord.size()) return 0;
        // 没有判断两者是否相等，题设中不相等，才碰巧通过
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        return bfs(beginWord, endWord, wordSet);
    }
private:
    int bfs(string beginWord, string endWord, unordered_set<string>& wordSet) {
        unordered_map<string, set<string>> graph;
        queue<string> q; int res = 1; 
        q.push(beginWord); 
        unordered_set<string> visited; visited.insert(beginWord);
        // 必须使用，对于同一层同一个word可能新增两次，graph不能完全判断是否进入了queue
        while(!q.empty()) {
            int size = q.size();
            res++;
            for(int i = 0; i<size; i++) {
                string cur = q.front(); q.pop();
                genGraph(cur, wordSet, graph);           // neighbors包含了所有提供的单词
                for(string w: graph[cur]) {
                    if(w == endWord) return res;
                    if(!visited.count(w)) {              // 筛选未进入queue的单词
                        q.push(w); visited.insert(w);
                    }
                }
            }
        }
        return 0;
    }
    void genGraph(string word, unordered_set<string>& wordSet, unordered_map<string, set<string>>& graph) { 
        set<string> s;
        graph[word] = s; 
        for(int i = 0; i<word.size(); i++) {
            string new_word = word;
            for(char j = 'a'; j<='z'; j++) {
                if(word[i] != j) new_word[i] = j;    // 忘记排除自己
                if(wordSet.count(new_word)) {
                    graph[word].insert(new_word);
                }
            }
        }
        return;
    }
};
// 第二次刷题，用时是之前写法的三倍，每次找邻居的时候，遍历了之前入queue的单词，浪费时间


// 125 单词接龙2
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> distance;
        vector<vector<string>> results;
        unordered_map<string, vector<string>> graph;
        if(beginWord.size() != endWord.size()) return results;
        unordered_set<string> dictionary;
        for(string word: wordList) dictionary.insert(word);
        if(!dictionary.count(endWord)) return results;
        dictionary.insert(beginWord);
        for(string word: dictionary) graph[word] = generate_neiborghs(word, dictionary);
        bfs(graph, endWord, beginWord, distance);    // 终点的距离是0
        if(!distance.count(beginWord)) return results;
        int len = distance[beginWord]+1;
        cout<<len<<endl;
        vector<string> tmp;
        dfs(graph, results, tmp, beginWord, endWord, distance);
        return results;
    }
private:
    vector<string> generate_neiborghs(string word, unordered_set<string>& dictionary) {
        vector<string> neighbors;
        for(int i=0; i<word.size(); i++) {
            string new_word = word;
            for(char c = 'a'; c<='z'; c++) {
                if(c!=word[i]) {
                    new_word[i]=c;
                    if(dictionary.count(new_word)) neighbors.push_back(new_word);
                }
            }   
        }
        return neighbors;
    }
    void bfs(unordered_map<string, vector<string>>& graph, string begin, string end, unordered_map<string, int>& distance) {
        queue<string> q;
        unordered_set<string> visited;
        q.push(begin); visited.insert(begin);
        distance[begin] = 0;
        while(!q.empty()) {
            string cur = q.front(); q.pop();
            for(string neighbor: graph[cur]) {
                if(visited.count(neighbor)) continue;
                q.push(neighbor);
                distance[neighbor] = distance[cur]+1;
                if(neighbor == end) return;
                visited.insert(neighbor);
            }
        }
    }
    void dfs(unordered_map<string, vector<string>>& graph, vector<vector<string>>& results, vector<string>& tmp, 
             string cur, string end, unordered_map<string, int>& distance) {
        tmp.push_back(cur);
        if(cur == end)  results.push_back(tmp); 
        else {
            for(string next: graph[cur]) {
                if(distance.count(next) && distance[next] == distance[cur]-1) 
                    dfs(graph, results, tmp, next, end, distance);
            }
        }
        tmp.pop_back();
    }
};

// 第二次刷题，for(string word: dictionary) graph[word] = generate_neiborghs(word, dictionary); 写成了wordList，导致生成图的时候没有beginWord

// *********  速度变慢了四倍，原因是使用的是map，set，而不是unordered_map, unordered_set
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> results;
        if(beginWord.size() != endWord.size() || wordList.size() == 0) return results;
        set<string> dictionary;
        for(string word: wordList) dictionary.insert(word);
        dictionary.insert(beginWord);
        map<string, vector<string>> graph;
        for(string word: dictionary) graph[word] = genneighbors(word, dictionary);  // 生成图
        cout<<graph.size()<<graph[beginWord].size()<<endl;
        map<string, int> distance;
        bfs(endWord, beginWord, graph, distance);               // 生成图中各节点到终点的距离,无需生成与起点同层或距离更大的节点距离
        cout<<distance.size()<<distance[endWord]<<distance[beginWord]<<endl;
        vector<string> result;
        dfs(beginWord, endWord, graph, distance, results, result);          // dfs从起点开始，不断走向到终点距离小的节点，需要从起点开始，因为输出的结果是起点到终点的顺序
        return results;
    }
private:
    vector<string> genneighbors(string word, set<string>& dictionary) {
        vector<string> neighbors;
        for(int i = 0; i< word.size(); i++) {
            string new_word = word;
            for(char c='a'; c<='z'; c++) {
                if(word[i] == c) continue;
                new_word[i] = c;
                if(dictionary.count(new_word)) neighbors.push_back(new_word); 
            }
        }
        return neighbors;
    }
    void bfs(string beginWord, string endWord, map<string, vector<string>>& graph, map<string, int>& distance) {
        queue<string> q; int len = 1;
        unordered_set<string> visited;
        q.push(beginWord); 
        visited.insert(beginWord);
        distance[beginWord] = len;
        while(!q.empty()) {
            int size = q.size(); len++;
            for(int i = 0; i<size; i++) {
                string cur = q.front(); q.pop();
                for(string neighbor: graph[cur]) {
                    // if(neighbor == endWord) {
                    //     distance[endWord] = len;
                    //     return;                      // 如果不跳出，再次遇到以后会更新distance
                    // }
                    if(visited.count(neighbor)) continue;
                    distance[neighbor] = len;
                    if(neighbor == endWord) return;          // 写在这里比较好
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        return;
    }
    void dfs(string word, string endWord, map<string, vector<string>>& graph, map<string, int>& distance, vector<vector<string>>& results, vector<string>& result) {
        result.push_back(word);
        if(word == endWord) results.push_back(result);
        else {
            for(string neighbor: graph[word]) {
                if(distance.count(neighbor) && distance[word] == distance[neighbor]+1) dfs(neighbor, endWord, graph, distance, results, result);
            }
        }
        result.pop_back();
    }
};