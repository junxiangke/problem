#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<map>
#include<set>
using namespace std;         //命名空间


// 873. 最长的斐波那契子序列的长度
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {                // A是严格递增序列
        int size = A.size(), ans = 0;
        unordered_map<int, int> index;

        vector<vector<int>> dp(size, vector<int>(size, 0));  // dp[j][k]是结束在A[j], A[k]的最长路径，存在A[i]，使得A[i]+A[j]=A[k]
        for(int k=0; k<size; k++) {
            index[A[k]] = k;
            for(int j=0; j<k; j++) {
                if(A[k]-A[j]<A[j] && index.count(A[k]-A[j])) {
                    dp[j][k] = dp[index[A[k]-A[j]]][j] +1;                  // 发现的第一个斐波那契数列，长度由0变1
                    ans = max(ans, dp[j][k]+2);
                }
            }
        }
        return ans;
    }
};
// 第二次刷题没有想到用index查找可能的节点

// 1027 最差等差数列
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int res = 0;
        vector<vector<int>> dp(A.size(), vector<int>(20001, 1));
        for(int i = 0; i < A.size(); i++) {
            for(int j = 0; j<i; j++) {
                int diff = A[i]-A[j]+10000;
                dp[i][diff] = dp[j][diff] + 1;
                res = max(res, dp[i][diff]);
            }
        }
        return res;
    }
};

// 322 零钱兑换
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        for(int i=0; i<amount+1; i++) {
            for(int j = 0; j<coins.size(); j++) {
                if(coins[j]<=i) {
                    dp[i] = min(dp[i], dp[i-coins[j]]+1);
                }
            }
        }      
        return dp[amount]==amount+1? -1: dp[amount];
    }
};


// 983 最小票价
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // dp[i]表示第i天的最小钱数
        vector<int> dp(days.back()+1,0);
        vector<bool> travel(days.back()+1, false);
        for(auto i:days) travel[i] = true;
        for(int i=1; i<=days.back(); i++) {
            if(!travel[i]) dp[i] = dp[i-1];
            else {
                dp[i] = Min3(getdp(i-1, dp)+costs[0], getdp(i-7, dp)+costs[1], getdp(i-30, dp)+costs[2]);
            // 在不旅行的日期，dp继承前一天的票价
            // 是否会出现前一天的价格高于后一天的？
            // 1.第i天的票价的来自i-1，相等或加costs[0]，2.前七天内的某一天买了costs[1]，3.前30天内某一天买了costs[2]，在后两种情况下，覆盖了i的票价，一定会覆盖i-1，所以不存在i的票价小于i-1
            // 如果票价dp[i]是递增的，那么使用前一天，前7天，前30天的价格进行计算，就是最小的
            }
        }
        return dp.back();
    }
private:
    int Min3(int a, int b, int c) {
        int tmp = a<b?a:b;
        return tmp<c?tmp:c;
    }

    int getdp(int index, vector<int>& dp) {
        if(index<0) return 0;
        else return dp[index];
    }    
};
// 第二次刷题没有考虑到，没有旅行的日期是不需要买票的，需要跳过一些日期


// 1024 视频拼接
class Solution { 
// 和最低票价有一点像，都用到了前一个元素覆盖的区域，不同的是，这个题目的元素需要遍历才能得到覆盖的区域，且dp都是递增的，分析见最低票价
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        
        sort(clips.begin(), clips.end(), cmp);
        
        vector<int> dp(T+1, -1);                             // 0-i时间段当中需要最小的视频数量
        if(clips[0][0]!=0) return -1; 
        else dp[0] = 1;                                      // 用来检查首位是否为0，如果不是，说明0的位置视频无法剪辑，直接返回false

        for(int i=0; i<clips.size(); i++) {
            if(clips[i][0]>T) break;                         // 不判断会使dp越界
            if(dp[clips[i][0]]==-1) return -1;               // 如果当前视频剪辑的开头位置为-1，说明视频无法连接上，返回-1
            
            for(int j=clips[i][0]; j<=clips[i][1]; j++) {
                if(j>T) break;                               // 先到达终点，后面的也需要遍历[[0,1],[0,5],[1,2],[2,3],[3,7],[5,7]]
                if(clips[i][0]==0) dp[j] = 1;                // clips[0]相应的dp被全部初始化为1;其余以0开头的，同样被置为1
                if(dp[j]==-1) dp[j]=dp[clips[i][0]]+1;
                else dp[j] = min(dp[j], dp[clips[i][0]]+1);  // clips[i][0]必须被前面的视频覆盖，才可以连接后面的，dp[clips[i][0]]表示的是这个位置所需的最小视频数量
            } 
        }
        return dp[T];
    }
    static bool cmp(vector<int>& a, vector<int>& b)  {  
        return a[0]<b[0];	//升序排列
    }    
};


// 403 青蛙跳河
class Solution {
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, set<int>> dp;  // 如果用vector会出现重复的step

        if(stones[0]!=0 || stones[1]!=1) return false;
        for(auto i:stones)  dp[i].insert(-1);
	    // if(dp.empty())
	    // cout<<"该字典无元素"<<endl;
	    // else
	    // 	cout<<"该字典共有"<<dp.size()<<"个元素"<<endl;
        
        dp[stones[0]].insert(1);
        for(auto i:stones) {
            for(auto j:dp[i]) {
                if(j<0) continue;
                for(int step=j-1; step<=j+1; step++) {
                    if(step>0 && step+1<1100 && dp.count(i+step)) dp[i+step].insert(step);
                    if(i+step == stones.back()) return true;
                }
            }
        }
        return false;
    }
};


// 121 买卖股票的最佳时机
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        vector<int> dp = {0, INT_MIN};
        for(int i=0; i<size; i++) {
            dp[0] = max(dp[0], dp[1]+prices[i]);
            dp[1] = max(dp[1], -prices[i]);
        }
        return dp[0];
    }
};


// 122 买卖股票的最佳时机 2  k=inifity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        vector<int> dp = {0, INT_MIN};
        int tmp;
        for(int i=0; i<size; i++) {
            tmp = dp[0];
            dp[0] = max(dp[0], dp[1]+prices[i]);
            dp[1] = max(dp[1], tmp-prices[i]);
            tmp = dp[0];
        }
        return max(dp[0], dp[1]);
    }
};


// 123 买卖股票的最佳时机 3  k=2
class Solution {
public: 
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        vector<vector<vector<int>>> dp(size+1, vector<vector<int>>(3, vector<int>(2)));
        for (int j=0; j<2; j++) {
            dp[0][j][0] = 0;
            dp[0][j][1] = INT_MIN;
        }
        for(int i=1; i<size+1; i++) {
            dp[i][0][0] = 0;
            dp[i][0][1] = INT_MIN;
            for(int j=1; j<3; j++) {
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]+prices[i]);
                dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0]-prices[i]);
            }
        }
        int res = INT_MIN;
        for(int j=0; j<3; j++) {
            res = max(res, dp[size][j][0]);
            res = max(res, dp[size][j][1]);
        }
        return res;
    }
};


// 188 买卖股票的最佳时机 4    穷举所有状态
class Solution {
public: 
    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        vector<vector<vector<int>>> dp(size+1, vector<vector<int>>(k+1, vector<int>(2)));
        for (int j=0; j<k+1; j++) {
            dp[0][j][0] = 0;               // i=0 代表交易还没有开始
            dp[0][j][1] = INT_MIN;         // INT_MIN表示不可能出现
        }
        for(int i=1; i<size+1; i++) {
            dp[i][0][0] = 0;
            dp[i][0][1] = INT_MIN;
            for(int j=1; j<k+1; j++) {
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]+prices[i-1]);
                dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0]-prices[i-1]);
                // 注意prices 要减一，否则越界
            }
        }
        int res = INT_MIN;
        for(int j=0; j<k+1; j++) {
            res = max(res, dp[size][j][0]);
            res = max(res, dp[size][j][1]);
        }
        return res;
    }
};


// 714 买卖股票的最佳时机 交易费
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int size = prices.size();
        vector<long> dp = {0, INT_MIN};  //如果不申请为long, 后面可能会越界
        for(int i=0; i<size; i++) {
            dp[0] = max(dp[0], dp[1]+prices[i]-fee);
            dp[1] = max(dp[1], dp[0]-prices[i]);
        }
        return max(dp[0], dp[1]);
    }
};


// 309 买卖股票的最佳时机含冷冻期
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<2) return 0;
        int dp_i_0 = 0, dp_i_1 = INT_MIN, dp_i2_0 = 0;  //  dp_i2_0 表示i-2天未持有股票状态下的利润
        for(int i = 0; i<prices.size(); i++) {
            int tmp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1+prices[i]);
            dp_i_1 = max(dp_i_1, dp_i2_0-prices[i]);
            dp_i2_0 = tmp;
        }
        return dp_i_0;
    }
};


// 300 最长上升子序列 (LSI)       不连续
// 动态规划问题有一个性质是“无后效性”，是指“某阶段状态一旦确定，就不受之后阶段的决策影响”，因此，我们可以在遍历中记录最大值
// int* dp = new int[nums.size()];      数组的写法
// delete[] dp;
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size()<2) return nums.size();
        vector<int> dp(nums.size(), 1);             
        // dp[i]：表示以第 i 个数字为结尾的“最长上升子序列”的长度。
        // 如果表示的不是以i为结尾，那么在遍历到nums[j]<nums[i]时，dp[j]+1不代表dp[i]的最长子序列，因为可能是dp[j]前面存在比dp[j]大的数字形成的上升序列
        int res = INT_MIN;
        for(int i = 1; i<nums.size(); i++) {
            for(int j = 0; j<i; j++) {
                if(nums[j]<nums[i]) dp[i] = max(dp[j]+1, dp[i]);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

// 673 最长递增子序列的个数 (LSI)       不连续
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int res = 0, length = 1;
        vector<vector<int>> dp(nums.size(), {1, 1});    //dp[i]{1,1},以i为结尾的最长子序列的长度初始化为1，且个数为1
        for(int i = 0; i < nums.size(); i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i]<=nums[j]) continue;          //不是<
                if(dp[i][1] == dp[j][1]+1) {
                    dp[i][0] += dp[j][0];
                }
                else if(dp[i][1]<dp[j][1]+1) {          //dp[i][1]>dp[j][1]+1的情况，不更新结果
                    dp[i][0] = dp[j][0];                //最小为1，初始为1
                    dp[i][1] = dp[j][1] + 1;
                }
            }
            if(dp[i][1] == length) res += dp[i][0];
            else if(dp[i][1] > length) {
                res = dp[i][0];
                length = dp[i][1];
            }
        }
        return res;
    }
};

// 354 俄罗斯套娃信封问题                LSI问题
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if(envelopes.size()<2) return envelopes.size();
        sort(envelopes.begin(), envelopes.end());
        int size = envelopes.size();
        int res = 1;
        vector<int> dp(size, 1);
        for(int i = 1; i<size; i++) {
            for(int j = 0; j<i; j++) {
                if(envelopes[i][0]>envelopes[j][0] && envelopes[i][1]>envelopes[j][1]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        res = max(res, dp[i]);
        }
        return res;
    }
};

// 467 环绕字符串中唯一的子字符串      连续                     
// dp[i]含义是以第i个字母为结尾的子字符串的最大长度，即子字符串的个数
// abcd中以d为结尾的子字符串的最大长度是4，子字符串，abcd,bcd,cd,d，个数也为4
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int size = p.size(), maxlength = 1, res = 0;              
        vector<int> dp(26, 0);                              // 记录26个字母的最长子串长度
        for(int i = 0; i<size; i++) {
            if(i>0 && (p[i-1]+1==p[i] || p[i-1]-25==p[i])) maxlength +=1;
            else maxlength = 1;
            dp[p[i]-'a'] = max(dp[p[i]-'a'], maxlength);   // 题目要求子串唯一，则若g字符出现多次，保留最长的子串长度，这可以使以g为结尾的子字符串只出现一次
        }
        for(int i = 0; i<26; i++) res += dp[i];
        return res;
    }
};

// 1143 最长公共子序列           不连续
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
        // dp[i][j] 表示text1[:i+1]与text2[:j+1]的最长公共子序列
        if(text1[0]==text2[0]) dp[0][0]=1;
        for(int i=1; i<text1.size(); i++) {
            if(text1[i]==text2[0]) dp[i][0] = 1;       // 初始化容易出错
            else dp[i][0] = dp[i-1][0];
        }
        for(int i=1; i<text2.size(); i++) {
            if(text1[0]==text2[i]) dp[0][i] = 1;       // 初始化容易出错
            else dp[0][i] = dp[0][i-1];
        }
        for(int i=1; i<text1.size(); i++) {
            for(int j=1; j<text2.size(); j++) {
                if(text1[i]==text2[j]) {
                    dp[i][j] = max(dp[i-1][j-1]+1,dp[i-1][j]);
                    dp[i][j] = max(dp[i][j], dp[i][j-1]);
                }
                else dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
            }
        }
        return dp[text1.size()-1][text2.size()-1];
    }
};

// 最长公共子串   连续
class Solution {
public:
    int longestCommonSubstr(string text1, string text2) {                    // dp[i][j] 表示的是以text1[i]，text2[j]结尾的公共子串的长度
        vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 0));
        int res = 0;
        for(int i=0; i<text1.size(); i++) {
            if(text1[i]==text2[0]) dp[i][0] = 1;       // 初始化容易出错
        }
        for(int i=1; i<text2.size(); i++) {
            if(text1[0]==text2[i]) dp[0][i] = 1;       // 初始化容易出错
        }
        for(int i=1; i<text1.size(); i++) {
            for(int j=1; j<text2.size(); j++) {
                if(text1[i]==text2[j])  {
                    dp[i][j] = dp[i-1][j-1]+1;    
                    res = max(res, dp[i][j]);
                }
            }
        }
        return res;
    }
};

// 72 编辑距离     插入、删除、替换
class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word1.size() == 0 || word2.size() ==0) return word1.size()==0? word2.size(): word1.size();
        int size1 = word1.size(), size2 = word2.size();
        vector<vector<int>> dp(size1+1, vector<int>(size2+1, 0)); 
        for(int i = 1; i<size2+1; i++)  dp[0][i] = i;

        for(int i = 1; i<size1+1; i++) {
            dp[i][0] = i;
            for(int j = 1; j<size2+1; j++) {
                if(word1[i-1] == word2[j-1])  dp[i][j] = dp[i-1][j-1];        // 写错了word的index
                else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1]);
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1]) + 1;
                    // 删除操作是dp[i-1][j]+1(删除word1[i])，dp[i][j-1]+1，替换操作dp[i-1][j-1]+1，插入操作dp[i-1][j]+1，dp[i][j-1]+1
                    // 对于插入的dp[i][j-1]+1，在word1[i]后插入word2[j]，使得word2[j]与新增元素匹配成功，因此dp[i][j]=dp[i][j-1]+1
                }
            }
        }
        return dp[size1][size2];
    }
};

// 97 交错字符
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int n1 = s1.size(), n2 = s2.size();
        vector<vector<bool>> dp(n1+1, vector<bool>(n2+1, false));
        dp[0][0] = true;
        for(int i = 1; i < n1+1; i++) {
            dp[i][0] = (dp[i-1][0] && s1[i-1] == s3[i-1]);   // 初始化，dp[i][0]表示s3[i-1]由s1[0]到s1[i-1]组成，不包含s2
        }
        for(int i = 1; i < n2+1; i++) {
            dp[0][i] = (dp[0][i-1] && s2[i-1] == s3[i-1]);
        }
        for(int i = 1; i < n1+1; i++) {
            for(int j = 1; j < n2+1; j++) {
                dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
                // dp[i][j]代表截至s1[i-1],s2[j-1]可以构成s3[i+j-1]，s3由0开始，代表了s3[i+j-1]
                // 分别表示s3[i+j-1]的元素从s2 / s1得来
            }
        }
        return dp[n1][n2];
    }
};

// 131 分割回文串
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        if(s.size()==0) return results;
        Palindrome(s, s.size(), dp);
        vector<string> solution;
        help(s, s.size(), 0, solution, results, dp);
        return results;
    }
private:
    void Palindrome(string str, int size, vector<vector<bool>>& dp) {
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) {
                dp[i][j] = (str[i]==str[j]) && (j-i<=2 || dp[i+1][j-1]);
            }
        }      
    }
    void help(string str, int size, int start, vector<string>& solution, vector<vector<string>>& results, const vector<vector<bool>>& dp) {
        if(start==size) {
            results.push_back(solution);
            return;
        }
        for(int i=start; i<size; i++) {
            if(dp[start][i]) {
                solution.push_back(str.substr(start, i-start+1));
                help(str, size, i+1, solution, results, dp);
                solution.pop_back();
            }
        }
    }
};
// 第二次刷题 1.递归的结束条件写错，写成了solution.size()==s.size()；2.i-start+1写成了start-i+1;


// 516 最长回文子序列              不连续，和最长上升子序列一样的遍历方式
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int size = s.size();
        vector<vector<int>> dp(size, vector<int>(size, 1));      // 全部初始化为1，因为单个字符的子序列也是回文串，则至少为1
        // dp[i][j]表示子串i,j中最长回文子序列的长度
        // 如果表示的是以i，j结尾的最长回文子序列的长度，那么dp[i][j]=dp[i+1][j-1]+2不成立，需要遍历出内部最长的回文子序列，且知道他们的起点终点
        
        for(int i=size-1; i>=0; i--) {
            for(int j=i+1; j<size; j++) {
                if(s[i]==s[j]) dp[i][j] = j-i>1? dp[i+1][j-1]+2: 2;         // 检查更新初始状态的时候，是否成立
                else dp[i][j]=max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[0][size-1];
    }
};

// 5 最长回文子串           连续
class Solution {
public:
    string longestPalindrome(string s) {
        int size = s.size();
        string res;
        vector<vector<bool>> dp(size, vector<bool>(size));   //dp[i][j]以i为开始j结束的子字符串是否为回文串
        for(int l=size-1; l>=0; l--) {
            for(int r=l; r<size; r++) {
                dp[l][r] = s[l]==s[r] && (r-l<=1 || dp[l+1][r-1]);
                if(dp[l][r] && r-l+1>res.size()) res = s.substr(l, r-l+1);
            }
        }
        return res;
    }
};


// 688 “马”在棋盘上的概率
class Solution {                // 直接BFS记录所有走法总数，会对部分位置记录多次，TLE
public:
    double knightProbability(int N, int K, int r, int c) {
        int x, y;
        vector<vector<double>> dp(N, vector<double>(N, 1));      // 初始化表示K=0，int，long，long long都不可以
        // dp[i][j] 表示进行到第k步还留在棋盘上的走法总和
        // 只依赖上一步的走法，因此三维数组的表示可以改用二维
        vector<vector<int>> dirct={{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};

        for(int k=0; k<K; k++) {
            vector<vector<double>> tmp(N, vector<double>(N, 0)); 
            for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                    for(auto item: dirct) {
                        x = item[0]+i;  y = item[1]+j;
                        if(x<0 || x>=N || y<0 || y>=N) continue;
                        tmp[i][j] += dp[x][y];                    // 由x，y走向i，j，一次计算完所有i,j的方案，同时若后续需要用到dp[i][j]k-1次的走法，不可以直接更新dp[i][j]，tmp是第k次，dp是k-1次的走法数目，是所有k-1步后留在棋盘上的走法总和的加和
                     // tmp_dp[x][y] += dp[i][j];               // 表示由i，j走向x，y，tmp_dp[x][y]是k步后还留在棋盘的走法，需要加上dp[i][j][k-1]
                    }
                }
            }
            dp = tmp;
        }
        return dp[r][c]/pow(8, K);
    }
};

// 576 出界的路径数
// 给定一个 m × n 的网格和一个球。球的起始坐标为 (i,j) ，你可以将球移到相邻的单元格内，或者往上、下、左、右四个方向上移动使球穿过网格边界。
// 但是，你最多可以移动 N 次。找出可以将球移出边界的路径数量。答案可能非常大，返回 结果 mod 109 + 7 的值。
// 对于dp[k][i][j]，走k步出边界的总路径数等于其周围四个位置的走k-1步出边界的总路径数之和，如果周围某个位置已经出边界了，那么就直接加上1，否则就在dp数组中找出该值
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(m, vector<int>(n, 0)));
        for (int k = 1; k <= N; ++k) {
            for (int x = 0; x < m; ++x) {
                for (int y = 0; y < n; ++y) {
                    long long v1 = (x == 0) ? 1 : dp[k - 1][x - 1][y];
                    long long v2 = (x == m - 1) ? 1 : dp[k - 1][x + 1][y];
                    long long v3 = (y == 0) ? 1 : dp[k - 1][x][y - 1];
                    long long v4 = (y == n - 1) ? 1 : dp[k - 1][x][y + 1];
                    dp[k][x][y] = (v1 + v2 + v3 + v4) % 1000000007;
                }
            }
        } 
        return dp[N][i][j];
    }
};
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for(int k = 0; k<N; k++) {
            vector<vector<int>> tmp_dp(m, vector<int>(n, 0));
            for(int x = 0; x<m; x++) {
                for(int y = 0; y<n; y++) {
                    long long v1 = x-1<0? 1: dp[x-1][y];
                    long long v2 = y-1<0? 1: dp[x][y-1];
                    long long v3 = x+1>=m? 1: dp[x+1][y];
                    long long v4 = y+1>=n? 1: dp[x][y+1];
                    tmp_dp[x][y] = (v1+v2+v3+v4) % 1000000007;
                }
            }
            dp = tmp_dp;
        }
        return dp[i][j];
    }
};


// 264 丑数
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n <= 1) return n;
        vector<int> dp(n);                    // dp为丑数列表，每一个丑数都是由之前的某个丑数乘以2/3/5，记录因子已经乘到了之前的哪一个丑数，不断比较新生成的丑数，哪个最小用哪个
        dp[0] = 1;
        int i2 = 0, i3 = 0, i5 = 0;
        for(int i=1; i<n; i++) {
            int m = min(dp[i2]*2, min(dp[i3]*3, dp[i5]*5));
            if(m == dp[i2]*2) i2++;
            if(m == 3*dp[i3]) i3++;
            if(m == dp[i5]*5) i5++;             // 不可以if else，因为可能有重复数字，比如dp[i2]*2和dp[i5]*5相等的话，这次相乘都被用掉了，需要都++
            dp[i] = m;
        }
        return dp[n-1];
    }
};

// 887 鸡蛋掉落
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K+1, vector<int>(N+1));  // dp[i][j]表示i个鸡蛋，j层楼，需要的最小次数
        for(int j = 1; j<N+1; j++) dp[1][j] = j;   // 若只有一个鸡蛋，则必须从下到上，一层一层尝试
        for(int i = 2; i<K+1; i++) {
            int s = 1;
            for(int j = 1;j<N+1; j++) {
                dp[i][j] = j;
                while(s < j && dp[i][j - s] > dp[i - 1][s - 1]) s++;
                dp[i][j] = min(dp[i][j], max(dp[i][j-s], dp[i-1][s-1])+1);   
                // 希望找到最优的中间楼层s，因为dp[i][j-s]随s递减， dp[i-1][s-1]随s递增，且每次变化的值最多为1，所以最优的s一定发生在dp[i-1][s-1]首次大于等于dp[i][j-s]时
                // 在j增长时，s会随之增长得到对应的最优中间楼层，因此j变化后，s在从前的基础上继续查找即可
                // 为什么递增递减每次变化最差为1，多了一层楼最差的情况多测试一次，比如测试得到前四层的最小次数，把第五层再测一下
            }
        }
        return dp[K][N];
    }
};

// 279 完全平方数

// 三角形最小路径和
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int res = INT_MAX;
        // triverse(triangle, 0, 0, 0, res);
        // res = divideconquer(triangle, 0, 0);
        res = dp_helper(triangle);
        return res;
    }
private:
    // find a whole path from x,y to bottom
    void triverse(vector<vector<int>>& triangle, int x, int y, int sum, int& res) {
        if(x == triangle.size()) {
            res = min(res, sum);
            return;
        }
        triverse(triangle, x+1, y, sum + triangle[x][y], res);
        triverse(triangle, x+1, y+1, sum + triangle[x][y], res);
    }
    // return minimum path from x,y to bottom
    int divideconquer(vector<vector<int>>& triangle, int x, int y) {
        if(x == triangle.size()) return 0;

        return triangle[x][y] + min(divideconquer(triangle, x+1, y), divideconquer(triangle, x+1, y+1));
    }
    
    int dp_helper(vector<vector<int>>& triangle) {
        int n = triangle.size(); 
        vector<int> dp(n);

        for(int i = 0; i<n; i++) dp[i] = triangle[n-1][i];
        for(int i = n-2; i>=0; i--) {
            for(int j = 0; j<=i; j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
    }
};