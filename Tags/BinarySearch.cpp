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

// 关注以下问题：1.看出是二分法；2.结束条件小于还是小于等于；3.提交超时的原因


// 702 搜索长度未知的有序数组   题目含义是big array 未知终点，算法要求时间复杂度O(logk)，k是target的first index
// Forward declaration of ArrayReader class.
// class ArrayReader;

// class Solution {
// public:
//     int search(const ArrayReader& reader, int target) {      // 实际为any位置的二分
//         int index=1;
//         while(reader.get(index-1)<target) index = index*2;   // 重点在于找到包含target在内的index，O(logk)

//         int left=0, right=index-1;
//         while(left+1<right) {                                // O(logk)
//             int mid = left+(right-left)/2;
//             if(reader.get(mid)==target) right=mid;
//             else if(reader.get(mid)>target) right=mid;
//             else left=mid;
//         } 
//         if(reader.get(left)==target) return left;
//         else if(reader.get(right)==target) return right;
//         return -1;
//     }
// };
// 第二遍刷题 reader.get写成了ArrayReader.get


// 34 在排序数组中查找元素的第一个和最后一个位置
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> results(2);
        results[0] = binarysearch(nums, target, 0);
        results[1] = binarysearch(nums, target, 1);
        return results;
    }
private:
    int binarysearch(vector<int>& nums, int target, int flag) {
        if(nums.size()==0) return -1;
        int left=0, right=nums.size()-1;
        while(left<right-1) {                // 在相邻时候结束，left!=right，可以避免死循环
        // 如[1,1] target=1 在搜索最后一次出现的位置时，start=mid，每次都得到相同的结果
            int mid = left+(right-left)/2;   // 在right,left都比较大的时候，会越界
            if(nums[mid] == target) {
                if(flag == 0) right=mid;
                else if(flag == 1) left=mid;
            }
            else if(nums[mid] > target) right=mid;
            else if(nums[mid] < target) left=mid;
        }
        if(flag==0) {
            if(nums[left]==target) return left;
            if(nums[right]==target) return right;
        }
        if(nums[right]==target) return right;
        if(nums[left]==target) return left;            
        return -1;
    }
};


// 74 搜索二维矩阵
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(!matrix.size() || !matrix[0].size()) return false; 
        int row=matrix.size(), col=matrix[0].size();
        int left=0, right=row*col-1,index;
        while(left+1<right) {
            index=left+(right-left)/2;
            if(target==matrix[index/col][index%col]) return true;   
            else if(target>matrix[index/col][index%col]) left=index;
            else right=index;
        }
        if(matrix[left/col][left%col]==target) return true;
        else if( matrix[right/col][right%col]==target) return true;
        return false;
    }
};
// 第二遍刷题，行列的计算写错了

// 240 搜索二维矩阵 2
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(!matrix.size() || !matrix[0].size()) return false;
        int row=matrix.size(), col=matrix[0].size();
        int i=0, j=col-1;
        while(i<row && j>=0) {
            if(matrix[i][j]==target) return true;
            else if(matrix[i][j]>target) j--;
            else i++;
        } 
        return false;
    }
};
// 最坏情况时间复杂度 O(row+col)

// 二分的意义在于将一个数组缩小范围，根据具体题目选定条件，最终结果在left与right之中

// 278 第一个错误的版本
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left=1, right=n;
        while(left+1<right) {
            int mid = left+(right-left)/2;
            if(isBadVersion(mid)) right=mid;
            else left=mid;
        }
        if(isBadVersion(left)) return left;        //当错误版本在第一个元素时，left始终指向错误版本 
        return right;
    }
};

// 153 寻找旋转排序数组中的最小值
class Solution {          
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        int middle;
        while(left+1<right) {
            middle = left+(right-left)/2; 
            if(nums[right]>nums[middle]) right = middle;  
            // 需要考虑特殊情况，完全递增，没有旋转的数组
            // 这里不使用nums[left]进行判断的原因是，如果出现了完全递增的数组，nums[left]<nums[middle]时，left=middle，会错过最小值
            // 且不存在nums[left]>nums[middle]
            else if(nums[right]<nums[middle]) left = middle;                       
        }
        return min(nums[left], nums[right]);     // 一般情况下 nums[right] 为结果，只有在完全递增数组时，nums[left]为结果
    }
};
// 第二遍刷题，没有写if(nums[left]<nums[right]) return nums[left]; 加不加都可以，加了对于完全递增序列会快一点

// 154 寻找旋转排序数组中的最小值2
//  这道题目在面试中不会让写完整的程序
//  只需要知道最坏情况下 [1,1,1....,1] 里有一个0
//  这种情况使得时间复杂度必须是 O(n)
//  因此写一个for循环就好了。
//  如果你觉得，不是每个情况都是最坏情况，你想用二分法解决不是最坏情况的情况，那你就写一个二分吧。
//  反正面试考的不是你在这个题上会不会用二分法。这个题的考点是你想不想得到最坏情况。
class Solution {
public:
    int findMin(vector<int>& nums) {   
        int left = 0, right = nums.size()-1;
        int middle;
        while(left+1<right) {
            middle = left+(right-left)/2; 
            if(nums[right]>nums[middle]) right= middle;  
            else if(nums[right]<nums[middle]) left = middle; 
            else if(nums[right]==nums[middle]) right--;               
            // [1,0,1,1,1] 和 [1, 1, 1, 0, 1]无法判断mid属于前一个还是后一个数组
            // 即使nums[right]是最小值，由于nums[right]=nums[middle]，最小值仍然存在在另一个数组中
        }
        return min(nums[left], nums[right]);
    }

    int findMin(vector<int>& nums) {   
        int left = 0, right = nums.size()-1;
        if(nums[left]<nums[right]) return nums[left];          // 此时为完全递增序列
        int middle;
        while(left+1<right) {
            middle = left+(right-left)/2; 
            if(nums[right]>nums[middle]) right= middle;  
            // 这里不使用nums[left]进行判断的原因是，如果出现了完全递增的数组，left=middle，会错过最小值
            else if(nums[right]<nums[middle]) left = middle; 
            else if(nums[right]==nums[middle]) right--;               // [1,0,1,1,1] 和 [1, 1, 1, 0, 1]无法判断mid属于前一个还是后一个数组
        }
        // return min(nums[left], nums[right]);
        return nums[right];   // 因为left仅能定位在第一个递增序列，所以可以只返回right，而不比较
    }
};


// 第三层境界，不是严格的ooooxxxx类型数据，可以一分为二，终极目标，降低时间复杂度到 O(logN)，因此保留一半去掉一半

// 162 寻找峰值           lintcode当中有额外条件，LintCode 保证数据第一个数比第二个数小，倒数第一个数比到倒数第二个数小。因此 start, end 的范围要取 1, A.length - 2
// 不可以从1到length-2的原因是，第一个，最后一个元素也有可能是峰值
class Solution {    
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size()==0) return -1;       
        int left=0, right=nums.size()-1;
        while(left+1<right) {
            int mid = left + (right-left)/2;
            if(nums[mid]<nums[mid+1]) left = mid;          // 可能是上升区域或者波谷
            else if(nums[mid]>nums[mid+1]) right = mid;    // 可能是下降区域或者波峰，所以left，right直接一定有波峰
            // 题目要求没有相等的情况，有相等的情况只能for循环，[2,2,2,1,2,2],都是2没办法判断
        }
        if(nums[left]>nums[right]) return left;
        else return right;
    }
};
// 第二遍刷题，考虑到mid可能会等于start，可能位于首位，因此不使用mid-1做判断


// 33 搜索旋转排序数组      oooxooooxooooxooooxooooxoooo问题
// 设定条件，将数组一分为二
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size()==0) return -1;     // 不加的话对于[],5 会报错 
        int left=0, right=nums.size()-1, mid;

        while(left+1<right) {
            mid = left+(right-left)/2;
            if(nums[mid]==target) return mid;
            if(nums[right]<nums[mid]) {               // nums[left]<nums[mid] 使用left或者right都可以，不会错过结果，因为下面有再一次判断，确定更详细的区域
                if(nums[left]<=target && nums[mid]>=target) right = mid;
                else left = mid;
            }
            else if(nums[right]>nums[mid]) {
                if(nums[right]>=target && nums[mid]<=target) left = mid;    //nums[right]>=target等号必须有
                else right = mid;
            }
        }
        if(nums[left]==target) return left;
        else if(nums[right]==target) return right;
        return -1;
    }
};
// 第二遍刷题忘记思路，先确定mid在前半段还是后半段，然后再判断mid与target的关系，数组被分成一个完全递增与一个旋转数组，完全递增序列也是旋转数组，二分查找与递归相似，都是得到得到类似的结构，继续迭代
// 没有写 if(nums[mid]==target) return mid;
// 第三遍，二分以后会被分成三个区域，两个区域都是left=mid，一个区域是right=mid，因此只要一个条件就可以，知道如何划分。


// 81 搜索旋转排序数组 2
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.size()==0) return false;     // 不加的话对于[],5 会报错 
        int left=0, right=nums.size()-1, mid;

        while(left+1<right) {
            mid = left+(right-left)/2;
            if(nums[mid]==target) return true;
            if(nums[right]<nums[mid]) {
                if(nums[left]<=target && nums[mid]>=target) right = mid;
                else left = mid;
            }
            else if(nums[right]>nums[mid]) {
                if(nums[right]>=target && nums[mid]<=target) left = mid;
                else right = mid;
            }
            else right--;
        }
        if(nums[left]==target) return true;
        else if(nums[right]==target) return true;
        return false;
    }
};

// 658 找到 K 个最接近的元素
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        
        if(arr.size()==1) return arr;

        int left=0, right=arr.size()-k;                  
        // 输入right=arr.size()-k-1，mid取不到right的值，最后k个数字遍历不到
        // right=arr.size()-k也不会越界，因为left与right不相等，所以不会为arr.size()-k造成越界
        while(left+1<right) {
            int mid = left + (right - left)/2;
            cout<<left<<mid<<right<<endl;
            if(abs(arr[mid]-x)<=abs(arr[mid+k]-x)) right=mid;   
            // 比较的是以mid开头的k个元素和以mid+1为开头的k个数，两者的差别是，mid和mid+k
            else left = mid;
        }
        cout<<left<<endl;
        if(abs(arr[left]-x)<=abs(arr[left+k]-x)) return vector<int>(arr.begin() + left, arr.begin() + left + k);
        else return vector<int>(arr.begin() + right, arr.begin() + right+ k);
    }
};
// 第二遍刷题，只想到了双指针的解法，二分法也是在寻找起始点，在写的时候对于arr.size()==1的判断写错了，二分的条件也写错了，right的范围也错了


// 378 有序矩阵中第K小的元素
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while(left<right) {
            int mid = left+(right-left)/2, cnt=0;
            for(int i=0; i<matrix.size(); i++) {
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
                // upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。
                // 通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
            }
            if(cnt>k) right=mid;                        // 答案在左半部分，并且如果存在重复数字，则有可能是mid，
            else if(cnt==k) right = mid;                // 对于while(left<right)，left的更新一定要为mid+1，否则会陷入死循环
            else if(cnt<k) left = mid+1;                // 答案在右半部分，并且一定非mid
        }
        return left;
    }
};
// 第二遍刷题，没有思路，看答案后upper_bound没有减起始地址，left更新写错，right更新思考mid-1不可行
// 求第一个或者最后一个target出现的位置，left<right会导致死循环


// 668 乘法表中第k小的数
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m*n;
        while(left<right) {
            int mid = left+(right-left)/2, cnt=0;;
            for(int i=1; i<=m; i++) {
                cnt += (mid>=n*i)? n:mid/i;
            }
            if(cnt<k) left = mid+1;
            else right = mid;
        }
        return left;
    }
};
// 第二次刷题，mid的目的是定位到第k小的数字，mid=n*i时cnt=cnt+n，意味着cnt中计算了等于mid的数，cnt去和k比较才有意义
// 若有重复数字，mid就是结果，但cnt>k，则right=mid后保持不变，left不断逼近right
// 最后一次更新的mid=right-1，cnt仍旧小于k，则left=mid+1，left=right


// 209 长度最小的子数组    双指针题目
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int left=0, right=0, res=INT_MAX, sums=0;

        while(right<nums.size()) {
            while(sums<s && right<nums.size()) sums += nums[right++];
            // right不断往前走，此时left不需要往回走是因为，在上一次遍历时已经取得了，上一个left的最优解
            while(sums>=s ) {                     
                // 此时不需要判断left是否越界的原因是，left == right时 sums为0，不会进入循环
                res = min(res, right-left);       
                // 因为前面求sum的时候right++了，所以这边不需要+1
                sums -= nums[left++];
            }
        }
        return res==INT_MAX? 0:res;
    }
};
class Solution {          // 更好一点，最外层的都是对right的限制，符合逻辑，先走right，再走left，与53 最大子序和的逻辑很像
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX, left = 0, sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            while (left <= i && sum >= s) {           // 子序包含left，right指向的元素
                res = min(res, i - left + 1);
                sum -= nums[left++];
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

// 69 x的平方根
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x;
        while(left < right-1) {
            int mid = left + (right - left) / 2;
            if(mid == x/mid) return mid;
            else if(mid < x / mid) left = mid;
            else right = mid-1;
        }
        if(right * right <= x) return right;
        else return left;
        
    }
};

// 287 寻找重复数
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1, right = nums.size();
        while(left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for(int num: nums) {
                if(num <= mid) cnt++;
            }
            if(cnt <= mid) left = mid + 1;     // target 一定不是mid，若是mid的话，cnt会超过mid
            else right = mid;
        }
        return right;
    }
};










