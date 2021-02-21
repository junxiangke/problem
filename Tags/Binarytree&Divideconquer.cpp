#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include <float.h>
#include<map>
#include<set>
#include<numeric>
#include <string>
using namespace std;         //命名空间

// 144 二叉树的前序遍历      递归非递归都是DFS
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {         // 背下记下这个
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> results;
        stack<TreeNode*> s;
        TreeNode* cur=root;
        while(cur!=NULL || !s.empty()) {
            while(cur!=NULL) {
                results.push_back(cur->val);       // 处理好当前节点再入栈
                s.push(cur);
                cur = cur->left; 
            }
            cur = s.top();             // 弹出的说明他的左子树已经处理好了
            s.pop();
            cur = cur->right;
        }
        return results;
    }
};
// Traverse  特点是存在全局变量，每次迭代访问同一个变量
class Solution {         
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> results;
        helper(root, results);
        return results;
    }
private:
    void helper(TreeNode* root, vector<int>& results) {   
        // 1. 定义实现的功能，把以root为根的preorder 加入到results当中
        if(root==NULL) return ;     // 3. 定义出口
        // 2. 递归的拆分
        results.push_back(root->val); 
        helper(root->left, results);
        helper(root->right, results);
    }
};
// 分治法   分治法也是递归，与traverse不同是：traverse没有return value，共享同一个result，分治法每一层都有一个新的result，是有解释意义的局部解
class Solution {         
public:
    // 定义，返回以root为根的前序遍历
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> results;
        if(root==NULL) return results;   // 因为后面直接使用了root->left，所以需要判断是不是空

        // 把事情交给两个小弟，最后合并两个小弟的结果
        vector<int> leftres=preorderTraversal(root->left);
        vector<int> rightres = preorderTraversal(root->right);

        results.push_back(root->val);
        results.insert(results.end(), leftres.begin(), leftres.end());
        results.insert(results.end(), rightres.begin(), rightres.end());
        return results;
    }
};


// 94 二叉树的中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> results;
        if(root==NULL) return results;
        stack<TreeNode*> s;
        TreeNode* cur=root;
        while(cur!=NULL || !s.empty()) {
            while(cur!=NULL) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();                // 左子树后入栈，先弹出，先处理
            s.pop();
            results.push_back(cur->val);  // 左子树与根节点放入res中后，对右子树进行相同的遍历操作，先左子树全入栈，再放入根节点，最后遍历右子树
            cur = cur->right;
        }
        return results;
    }
};


// 145 二叉树的后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> results;
        if(root==NULL) return results;
        stack<TreeNode*> s;
    }
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode *> myStack;
        
        TreeNode *current = root, *lastVisited = NULL;  // 同时定义两个指针时，前面都要加*
        while (current != NULL || !myStack.empty()) {
            while (current != NULL) {
                myStack.push(current);          // 第一次经过根节点 
                current = current->left;
            }
            current = myStack.top();            // 第二次经过根节点，若右子树未被处理，则右子树入栈
            if (current->right == NULL || current->right == lastVisited) { // 判断右孩子有没有被放入res中
                // 因为根节点是最后被处理的，因此右子树最后一个被处理的是右子树的根节点，因此如果current->right == lastVisited，右子树全部被遍历了
                // 同时只有左子树已经被遍历完，才会弹出根节点，根节点会被经过三次
                myStack.pop();
                result.push_back(current->val);
                lastVisited = current;
                current = NULL;              // 否则会被再次压入栈
            } else {
                current = current->right;   // 对于有右孩子且未访问过的，要在下一轮中压入栈，进行同样的遍历
            }
        }
        return result;
    }
};

// 257 二叉树的所有路径  本题的重点在于递归的出口应该是左右孩子为空，而不是当前节点为空，否则会导致残缺的路径加入了results
class Solution {      
public:
    vector<string> binaryTreePaths(TreeNode* root) {   // Traverse
        string result;
        vector<string> results;
        if(root==NULL) return results;
        result = to_string(root->val);
        helper(root, result, results);
        return results;
    }
private:
    void helper(TreeNode* root, string result, vector<string> results) {
        if(root==NULL) {
            results.push_back(result);
            return ;
        }
        result += to_string(root->val);  // 与result.append()效率差不多，比result = result + 'a' 效果好
        if(root->left) helper(root->left, result, results);
        if(root->right) helper(root->right, result, results);            // 有问题，如果当前节点没有孩子，那会把当前路径加入两次
    }
};

class Solution {    
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        string result;
        vector<string> results;
        if(root == NULL) return results;
        helper(root, result, results);
        return results;
    }
private:
    void helper(TreeNode* root, string result, vector<string>& results) {  // 定义是 把root加入results中的所有路径
        if(root->left == NULL && root->right == NULL) {
            results.push_back(result+to_string(root->val));
        }
        if(root->left) helper(root->left, result+to_string(root->val)+"->", results);
        if(root->right) helper(root->right, result+to_string(root->val)+"->", results);
    }
};

class Solution {      // 分治法可解决绝大部分二叉树问题，记这个比较好，对于所有二叉树问题最后都要验证，叶子节点是否正确，以及只有一个节点时候是否正确（特殊情况）
public:
    vector<string> binaryTreePaths(TreeNode* root) {  
        vector<string> results;
        if(root == NULL) return results;

        if(root->left == NULL && root->right == NULL) results.push_back(to_string(root->val));

        vector<string> leftres = binaryTreePaths(root->left);
        vector<string> rightres = binaryTreePaths(root->right);
        
        for(auto result: leftres) results.push_back(to_string(root->val)+"->"+result);
        for(auto result: rightres) results.push_back(to_string(root->val)+"->"+result);
        return results;
    }
};

// minimum subtree    同时用到了分治法和traverse的思想
class Solution {
public:
    TreeNode* findSubtree(TreeNode* root) {  
        helper(root);
        return subtree;
    }
private:
    TreeNode* subtree;
    int minsum = INT_MAX;
    int helper(TreeNode* root) {
        int sum=0;
        // 出口
        if(root==NULL) return sum;

        // 拆分
        sum =  helper(root->left) + helper(root->right) + root->val;
        if(sum<minsum) {
            subtree = root;
            minsum = sum;
        }
        return sum;
    }
};


// 104 二叉树的最大深度    分治法
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==NULL) return 0;
        int depth;

        int leftd = maxDepth(root->left);
        int rightd = maxDepth(root->right);
        depth = leftd>rightd? leftd:rightd;
        return depth+1;
    }
};
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==NULL) return 0;
        int depth = 0;
        helper(root, depth);
        return maxd;
    }
private:
    int maxd = INT_MIN;
    void helper(TreeNode* root, int depth) {
        if(root == NULL) return;
        depth++;
        if(depth>maxd) maxd = depth;
        helper(root->left, depth);
        helper(root->right, depth);
    }
};


// 110 平衡二叉树 分治法加traverse
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root==NULL) return false;
        Depth(root);
        return res;
    }
private:
    int res=true;
    int Depth(TreeNode* root) {
        if(root==NULL) return 0;
        int depth;

        int leftd = Depth(root->left);
        int rightd = Depth(root->right);
        if(abs(rightd-leftd)>1) res = false;
        depth = leftd>rightd? leftd:rightd;
        return depth;
    }
};

// 1120 子树的最大平均值
class Solution {
public:
    double maximumAverageSubtree(TreeNode* root) {
        ResultType res = helper(root);
        return maxaverage == DBL_MIN? 0: maxaverage;
    }
private:
    class ResultType {
    public:
        int sum, size;
        ResultType(int _sum, int _size) {             // 参数要和变量名字区分开，否则出错
            sum = _sum;
            size = _size;
        }
    };
    double maxaverage = DBL_MIN;       // double类型是DBL_MIN，float类型是FLT_MIN，long型是LONG_MIN 要加入 #include <float.h>
    ResultType helper(TreeNode* root) {
        if(root == NULL) return ResultType(0,0);
        ResultType leftr = helper(root->left);
        ResultType rightr = helper(root->right);
        int sum = leftr.sum + rightr.sum + root->val;
        int size = leftr.size + rightr.size +1;
        maxaverage = max(maxaverage, 1.0*sum/size);
        return ResultType(sum, size);
    }
};
// 第二遍刷题，参数要和变量名字区分开，否则出错

// 124 二叉树的最大路径和
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        helper(root);
        return maxsum;
    }
private:
    int maxsum = INT_MIN;
    int helper(TreeNode* root) {
        if(root == NULL) return 0;   
        int leftres = helper(root->left);
        int rightres = helper(root->right); 
        maxsum = max(maxsum, leftres+rightres+root->val);  // 不加会错过根节点，左右子树的情况
        int child = max(leftres, rightres);
        int res = 0;
        if(child<=0)  res = root->val;           // 这里包含了root大于零或者小于零，只要child小于零，就不必加入左右子树了
        else if(child + root->val >0) res = child + root->val;
        else res = 0;
        maxsum = max(maxsum, res);
        return res;

    }
};

// 235 二叉搜索树的最近公共祖先
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
       int minval = min(p->val, q->val);
       int maxval = max(p->val, q->val);
       helper(root, minval, maxval);
       return res; 
    }
    TreeNode* res;
    void helper(TreeNode* root, int minval, int maxval) {
        if(root == NULL) return ;
        if(root->val >= minval && root->val <= maxval) {
            res = root;
            return;
        }
        helper(root->left, minval, maxval);
        helper(root->right, minval, maxval);
        return;
    }
};
// 236 二叉树的最近公共祖先    如果题目中说p，q其中一个不在树中，则必须使用result type
class ResultType {
public:
    bool a_exist, b_exist;
    TreeNode* node;
    ResultType(bool a, bool b, TreeNode* n) {
        a_exist = a;
        b_exist = b;
        node = n;            //未找到时是A或B出现的节点，都找到后是最近公共节点
    }
};
class Solution {     // 如果题目要求A，B可以重复出现，下面的方案只会找到最上层的最近公共祖先
public:
    TreeNode *lowestCommonAncestor3(TreeNode* root, TreeNode* A, TreeNode* B) {
        ResultType rt = helper(root, A, B);
        if (rt.a_exist && rt.b_exist)
            return rt.node;
        else
            return NULL;
    }
    ResultType helper(TreeNode* root, TreeNode* A, TreeNode* B) {
        if (root == NULL) return ResultType(false, false, NULL);
            
        ResultType left_rt = helper(root->left, A, B);
        ResultType right_rt = helper(root->right, A, B);
        
        bool a_exist = left_rt.a_exist || right_rt.a_exist || root == A;
        bool b_exist = left_rt.b_exist || right_rt.b_exist || root == B;
        // 此时的a_exist,b_exist 都包含了多种情况，不能一次判断LCA；
        
        if (root == A || root == B)   return ResultType(a_exist, b_exist, root);     
        // 当找到节点为A或B时，exist被置为1，同时node不再为空
        // 包含两种情况，1.此时A，B都被找到，一个是另一个的子孙；2.只找到了A，或者B

        if (left_rt.node != NULL && right_rt.node != NULL) return ResultType(a_exist, b_exist, root);      
        // 左右各找到一个，则当前节点为最近公共祖先
        if (left_rt.node != NULL) return ResultType(a_exist, b_exist, left_rt.node);    
        // 包含两种情况 1. 只找到一个孩子；2. ab都找到，但是当前节点不是最近公共祖先，无论一个是另一个的孩子，还是A，B在两个分支的情况
        // 这个判断条件隐含着，只要找到其中一个，node就不为空，至少为ab本身。
        if (right_rt.node != NULL) return ResultType(a_exist, b_exist, right_rt.node);

        return ResultType(false, false, NULL);
    }
};

// 98 验证二叉搜索树            或可以使用中序遍历
class ResultType1 {
public:
    bool isBST;
    int maxval, minval;
    ResultType1(bool a, int b, int c) {
        isBST = a;
        maxval = b;
        minval = c;
    }
};
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        ResultType1 res = helper(root);
        return res.isBST;
    }
private:
    ResultType1 helper(TreeNode* root) {
        if(root == NULL) return ResultType1(true, INT_MIN, INT_MAX);

        ResultType1 leftr = helper(root->left);
        ResultType1 rightr = helper(root->right);

        if(leftr.isBST == false || rightr.isBST == false) return ResultType1(false,0,0);
        if(leftr.maxval < root->val && rightr.minval > root->val) {
            int maxval = rightr.maxval == INT_MIN? root->val: rightr.maxval;
            int minval = leftr.minval == INT_MAX? root->val: leftr.minval;
            return ResultType1(true, maxval, minval);
        }
        else return ResultType1(false, 0, 0);
    }
};
// 第二次刷题，不能直接返回right_rt.maxval作为最大值

// 333 最大BST子树
class ResultType2 {
public:
    bool isBST;
    int maxval, minval, nodenums;
    ResultType2 (bool isbst, int maxv, int minv, int nn) {
        isBST = isbst;
        maxval = maxv;
        minval = minv;
        nodenums = nn;
    }
};
class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        ResultType2 rt = helper(root);
        return rt.nodenums;
    }
private:
    ResultType2 helper(TreeNode* root) {
        if(root==NULL) return ResultType2(true, NULL, NULL, 0);

        ResultType2 left_rt = helper(root->left);
        ResultType2  right_rt = helper(root->right);

        if(!left_rt.isBST || !right_rt.isBST) return ResultType2(false, NULL, NULL, max(left_rt.nodenums, right_rt.nodenums));
        if(left_rt.maxval != NULL && left_rt.maxval>=root->val ) return ResultType2(false, NULL, NULL, max(left_rt.nodenums, right_rt.nodenums));
        if(right_rt.minval != NULL && right_rt.minval<=root->val) return ResultType2(false, NULL, NULL, max(left_rt.nodenums, right_rt.nodenums));

        int maxval = !right_rt.maxval? root->val:right_rt.maxval;   // 不能直接返回right_rt.maxval作为最大值，可能是空
        int minval = !left_rt.minval? root->val:left_rt.minval;     // 错了三次
        return ResultType2(true, maxval, minval, left_rt.nodenums+right_rt.nodenums+1);
    }
};

// 114 二叉树展开为链表                   结构类题目重点在于想象每一个子树结束以后，指针指向发生了什么改变
class Solution {                     // 实质是一个前序遍历，lastnode记录上一个遍历的节点
private:
    TreeNode *lastnode=NULL;
public:
    void flatten(TreeNode* root) {
        if(root==NULL) return ;
        
        if(lastnode != NULL) {
            lastnode->left = NULL;
            lastnode->right = root;
        }                                  // 相当于先序遍历，对根节点的操作，处理根节点以后，分别处理左右两子树
        lastnode = root;
        TreeNode* right = root->right;     // 需要保存right, 否则会被flatten(root->left)改掉
        flatten(root->left);              // lastnode->right = root; 在这一步right被改变
        flatten(right);
    }
};
class Solution {                     // 实质是一个前序遍历，lastnode记录上一个遍历的节点
public:
    void flatten(TreeNode* root) {
        if(root==NULL) return ;
        helper(root, NULL);
    }
private: 
    TreeNode* helper(TreeNode* root, TreeNode* lastnode) {     //返回的是上一次访问的节点
        if(root==NULL) return NULL;
        if(lastnode != NULL) {
            lastnode->left = NULL;
            lastnode->right = root;
        }   
        lastnode = root;
        TreeNode* right = root->right;
        lastnode = root->left!=NULL?  helper(root->left, root):root;
        lastnode = right!=NULL?  helper(right, lastnode):lastnode;
        return lastnode;
    }
};
// 第二次刷题没有思路


// 426. 将二叉搜索树转化为排序的双向链表
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node() {}
    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
class Solution {                   // 相当于中序遍历，与上一题区别是多一个节点记录头结点
public:
    Node* treeToDoublyList(Node* root) {
        if(root==NULL) return NULL;   // 不加会run time error
        helper(root);
        first->left = last;
        last->right = first;
        return first;               // 返回的是链表的头结点
    }
    
private:
    Node* first=NULL, *last=NULL;
    void helper(Node* root) {
        if(root==NULL) return ;
        
        helper(root->left);
        if(last!=NULL) {
            last->right = root;
            root->left = last;
        } 
        else first = root;
        last = root;            // 这句话应该放在处理过root以后，意味着已经放入链表，是链表最后一个节点
        helper(root->right);
    }
};
// 第二次刷题完全没有思路


// 536 从字符串生成二叉树
class Solution {
public:
    TreeNode* str2tree(string s) {
        if(s.empty()) return NULL;
        string::size_type found = s.find('(');
        int val = (found == string::npos) ? stoi(s) : stoi(s.substr(0, found));  
        // 如果是负数，或两位数三位数会占用多位字符，所以不可以s.substr(0, 1)
        TreeNode* cur = new TreeNode(val);
        if (found == string::npos) return cur;
        int start = found, cnt = 0;
        for(int i=start; i<s.size(); i++) {
            if(s[i] == '(') cnt++;
            else if(s[i] == ')') cnt--;
            if(cnt==0 && start==found) {
                cur->left = str2tree(s.substr(start+1, i-start-1));
                start = i+1;
            } 
            else if(cnt==0) // 如果写if，在进入上一层if以后，再次进入下一个if
            {             
                // cout<<s.substr(start, i-start-1)<<endl;
                cur->right = str2tree(s.substr(start+1, i-start-1));  
            }
        }
        return cur;
    }
};
class Solution {          // 错误答案，丢掉了左子树
public:
    TreeNode* str2tree(string s) {
        if(s.empty()) return NULL;
        string::size_type found = s.find('('); 
        int val = found == string::npos? stoi(s.substr(0,found)):stoi(s);   // 判断是否为单根树
        TreeNode* root = new TreeNode(val);
        if(found == string::npos) return root;
        int start = found, cnt = 0; 
        for(int i = start; i<s.size(); i++) {
            if(s[i]=='(') {
                cnt++; start = i;   // 若嵌套了子树，中间会遇到很多次的（），但start不应该改变
            }
            if(s[i]==')') cnt--;
            if(cnt == 0 && start == found) root->left = str2tree(s.substr(start+1, i-start-1));
            else if(cnt == 0) root->right = str2tree(s.substr(start+1, i-start+1));
        }
        return root;
    }
};
// 第二遍刷题，没有思路
// 1. s[i] == '(' 单引号而不是双引号；2.string::npos，string::size_type found = s.find('(');
// 3.substr 而不是 substring


// 606 根据二叉树创建字符串
class Solution {                        // 分治法，小技巧是如何处理括号
public:
    string tree2str(TreeNode* t) {
        if(t==NULL) return "";
        string res = to_string(t->val);
        if(t->left == NULL && t->right == NULL) return res;
        res += "(" + tree2str(t->left) + ")";              // 左子树的括号不能省略，无论是不是空的，都要加上
        if(t->right) res += "(" + tree2str(t->right) + ")";
        return res;
    }
};
// 第二遍刷题，看了答案以后写的，没有想清楚什么时候括号省略

// 428 序列反序列化N叉树   N叉树不区分左右子树，二叉树在只有右子树的情况下，需要把左子树置为()，来区分左右子树
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if(root == NULL) return "";
        stringstream ss;
        ss<<root->val;
        for(Node* node: root->children) {
            if(node != NULL) ss<<"("<<serialize(node)<<")";
        }
        return ss.str();        
    }
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if(data == "") return NULL;
        string::size_type found = data.find("(");
        int val = found == string::npos? stoi(data):stoi(data.substr(0,found));
        Node* root = new Node(val);
        int cnt = 0, start = found;
        for(int i=found; i<data.size(); i++) {
            if(data[i]=='(') cnt ++;
            if(data[i]==')') cnt --;
            if(cnt == 0) {
                root->children.push_back(deserialize(data.substr(start+1, i-start-1)));
                start = i+1;
            }
        }
        return root;
    }
};

// 298 二叉树最长连续序列
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        if(root == NULL) return 0;        // 若不判断，ans=INT_MIN
        helper(root);
        return ans;
    }
private:
    int ans = INT_MIN;
    // 返回包含当前节点在内的最长连续路径长度
    int helper(TreeNode* root) {
        if(root == NULL) return 0;

        int res = 0;
        int leftres = helper(root->left);
        int rightres = helper(root->right);
        ans = max(max(leftres, ans), rightres);

        if(!leftres && !rightres) res = 1;       // 当前节点为叶子节点，不可以直接返回，没有更新ans
        if(leftres) {
            if(root->left->val != root->val+1) leftres = 0;
        }
        if(rightres) {
            if(root->right->val != root->val+1) rightres = 0;
        }
        res = max(leftres, rightres) + 1;
        ans = max(ans, res);
        return res;
    }
};

// 572 另一个树的子树
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(s == NULL) return false;
        return check(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
    }
private:
    bool check(TreeNode* root, TreeNode* t) {
        if(!root && !t) return true;
        if(!root && t || root && !t || root->val != t->val) return false;
        return check(root->left, t->left) && check(root->right, t->right);
    }
};