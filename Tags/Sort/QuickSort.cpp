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


// 912 排序数组
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
private:
    void quickSort(vector<int>& nums, int left, int right) {
        if(left >= right) return;         
        int i = left, j = right;
        int pivot = nums[(i + j) / 2];        
        // key point 1: pivot is the value, not the index
        // key point 2: every time you compare left & right, it should be left <= right not left < right
        // 如果是left<right，输入[1,2]时，循环结束时i，j都指向1，下一层迭代，循环递归[1,2]
        // key point 3: nums[i] <= pivot，会导致i一直走到末尾，每次切分都在最边缘，出现O(N**2)的复杂度
        // i前与j后都是处理过的数字，两个指针都指向待处理的数字，循环结束时，j-i=1或j-i=2，等于1的情况下i指向的是j之前处理好的，所以i指向的大于j指向的
        // 等于2时，意味着最后一次循环时i，j指向的数字等于pivot，所以被分为了小于等于pivot，等于pivot，大于等于pivot，三部分
        while(i <= j) {
            while(i <= j && nums[i] < pivot) i++;
            while(i <= j && nums[j] > pivot) j--;
            // 此时i指向的元素大于等于pivot，j指向的元素小于等于pivot，此时交换并指向下一个位置
            if(i <= j) swap(nums[i++], nums[j--]);
        }
        quickSort(nums, i, right);        // i只会向右边越界，在进入下一轮迭代时，判断 i >= right 则结束
        quickSort(nums, left, j);         // j只会向左边越界，在进入下一轮迭代时，判断 left <= j 则结束
    }
    // 以下为错误写法
    void quickSort(vector<int>& nums, int left, int right) {    
        if(left >= right) return;
        int i = left, j = right;
        int pivot = nums[(i + j) / 2];
        while(i <= j) {
            while(nums[i] < pivot) i++;         // 需要加入对 i，j的判断，可以避免越界
            while(nums[j] > pivot) j--;
            if(i <= j) swap(nums[i++], nums[j--]);
        }
        quickSort(nums, left, j);
        quickSort(nums, i, right);
    }
    void helper(vector<int>& nums, int start, int end) {     
        if(start == end) return;                  // 有start>end的越界情况，要写start>=end
        int pivot = nums[(start + end)/2];
        int left = start, right = end;
        while(left <= right) {
            while(left<=right && nums[left]<pivot) left++;
            while(left<=right && nums[right]>pivot) right--;
            if(left<=right) swap(nums[left++], nums[right--]);        // 落下了++，--
        }
        helper(nums, start, right);
        helper(nums, left, end);
    }
};
// 第二次刷题，pivot写成了(nums[left]+nums[right])/2，虽然可以通过，但是速度慢一些

// 215 数组中的第K个最大元素
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if(k>nums.size()) return -1;
        return quickselect(nums, 0, nums.size()-1, k);
    }
    int quickselect(vector<int>& nums, int start, int end, int k) {
        if(start==end) return nums[start];
        int left = start, right = end;
        int pivot = nums[(left + right) / 2];
        while(left <= right) {                                 // 1.写错成<,导致循环递归；2.从小到大排序，得到第k个最小元素
            while(left<=right && nums[left] > pivot) left++;   // 是第k个最大元素，而不是第k大的元素，因此倒序排列
            while(left<=right && nums[right] < pivot) right--;
            if(left <= right) swap(nums[left++], nums[right--]);
        }
        if(start+k-1<=right) return quickselect(nums, start, right, k); // 理解为左侧数字的个数
        else if(start+k-1>=left) return quickselect(nums, left, end, k-(left-start));  // 这里一开始写错了left-start
        // start+k-1<=end，因此当left>end时，不满足条件语句，进入不了下一层递归
        else return nums[right+1];
    }
};
// 第二次刷题，没有思路

// 703 数据流中的第k个最大元素
class KthLargest {                       // priority queue 定义 priority_queue<Type, Container, Functional>
public:
    priority_queue<int, vector<int>, greater<int>> pq;     // 小顶堆，大顶堆是less<int>
    int size;

    KthLargest(int k, vector<int> nums) {    
        size=k;//将小根堆的大小控制在k
        for(int i=0;i<nums.size();i++) {     // 最后维护的是大小为k的堆，接近O(NlogK)
            pq.push(nums[i]);
            if(pq.size()>k) pq.pop();
        }
    }
    int add(int val) {           
        pq.push(val);                    // 时间复杂度O(logk)
        if(pq.size()>size) pq.pop();    //小顶堆pop是删除最小值，top是返回最小值
        // pq.size()的时间复杂度一定是O(1)，有专门的变量记录，不可能每次都数一遍
        return pq.top();
    }
};
// 第二次刷题，没有思路，且priority_queue的定义写错


// 905 按奇偶排序数组
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int size = A.size();
        if(size == 0 || size == 1) return A;
        int left = 0, right = size-1;
        while(left < right) {
            while(left < right && A[left]%2 == 0) left++;
            while(left < right && A[right]%2 == 1) right--;
            if(left < right) swap(A[left++], A[right--]);
        }
        return A;
    }
};

// 922 按奇偶排序数组 II
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int size = A.size(), even = 0, odd = 1;
        while(even < size && odd < size) {
            while(even < size && A[even]%2 == 0) even += 2;
            while(odd < size && A[odd]%2 == 1) odd += 2;
            if(even < size && odd < size)  {
                swap(A[even], A[odd]);
                even += 2; odd += 2;
            }
        }
        return A;
    }
};

// 75 颜色排序    使用counting sort 需要额外空间，O(N)时间复杂度
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size()-1, cur = 0;
        while(cur<=right) {     //right指向的数据没有处理过
            if(nums[cur] == 0) swap(nums[left++], nums[cur++]);
            else if(nums[cur] == 2) swap(nums[right--], nums[cur]); 
            // right 指向的数据没有处理过，因此cur应该在下一轮判断一下
            else cur++;
        }
    }
};

// 彩虹排序，有k种颜色排序，第一种方法使用counting sort，空间O(k),时间复杂度O(N)
// 运用归并排序的思路实现层次划分，运用快速排序的思路实现partition
class Solution {
public:
    void sortColors2(vector<int>& nums, int k) {
        helper(nums, 0, nums.size()-1, 1, k);
    }
private:
    void helper(vector<int>& nums, int start, int end, int k_start, int k_end) {
        if(k_start == k_end || start == end) return;
        int left = start, right = end, middle = (k_start + k_end)/2;
        while(left<=right) {   // 后续涉及到分成两个部分的,判断写left<=right
            while(left<=right && nums[left]<=middle) left++;  
            //此处与快排条件不同，不会出现left-right=2
            while(left<=right && nums[right]>middle) right--;
            if(left<=right) swap(nums[left++], nums[right--]);
        } 
        if(right>=start) helper(nums, start, right, k_start, middle);  
        if(end>=left) helper(nums, left, end, middle+1, k_end);
    }
    // 第二次刷题，nums[left] < pivot与快速排序条件不同，等于pivot的不可以同时出现在两个部分
    void helper2(vector<int>& nums, int start, int end, int k_start, int k_end) {
        if(start>=end || k_start == k_end) return;               // 两种结束方式
        int left = start, right = end, pivot = (k_start + k_end) / 2;
        while(left<=right) {
            while(left <= right && nums[left] < pivot) left++;
            while(left <= right && nums[right] > pivot) right--;
            if(left <= right) swap(nums[left++], nums[right--]);
        }
        helper(nums, start, right, k_start, pivot);
        helper(nums, left, end, pivot, k_end);        // 应该是pivot+1
    }
};