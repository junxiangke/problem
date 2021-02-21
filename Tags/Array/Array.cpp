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
 
int firstMissingPositive(vector<int>& nums) {
    if(nums.size()==0) return 1;
    int size = nums.size();
    int i = 0;
    while(i<size) {
        if(nums[i]==i+1) i++;
        else if(nums[i]<i+1 || nums[i]>size || nums[nums[i]-1] == nums[i]) nums[i] = nums[--size];
        else swap(nums[i],nums[nums[i]-1]);
    }
    return size+1;
}


int findMin(vector<int>& nums) {
    int left = 0, right = nums.size()-1;
    int middle;
    while(left<right) {
        middle = (left+right)/2; 
        if(nums[right]>nums[middle]) right = middle;  // 这里不使用nums[left]进行判断的原因是，left与middle有可能相等，此时无法判断与nums[right]的关系
        else left = middle+1;                         // 此时保证了，left总是指向更小的那个值
    }
    return left;
} 

int findMin(vector<int>& nums) {
    int left = 0, right = nums.size()-1;
    int middle;
    while(left<right-1) {
        middle = (left+right)/2; 
        if(nums[right]>nums[middle]) right = middle;  
        else left = middle;                         
    }
    return (left+right)/2;
} 


// 423
// 利用累加和
class Solution {
public:
    string originalDigits(string s) {
        
    }
};

// 425


// 915 分割数组

// 349 两个数组的交集      三种方法 还可以二分法，排序较小的数组，然后寻找大数组中的元素
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {          // 哈希
        unordered_set<int> visited;
        set<int> result;
        for(int i: nums1) visited.insert(i);
        for(int i: nums2) {
            if(visited.count(i)) result.insert(i);
        }
        vector<int> results(result.begin(), result.end());          // set转vector
        return results;
    }
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {           // 排序, merge sort 思想
        vector<int> results;
        quickSort(nums1, 0, nums1.size()-1);
        quickSort(nums2, 0, nums2.size()-1);
        int leftindex = 0, rightindex = 0;
        while(leftindex < nums1.size() && rightindex < nums2.size()) {
            if(nums1[leftindex] < nums2[rightindex]) leftindex++;
            else if(nums1[leftindex] > nums2[rightindex]) rightindex++;
            else if(nums1[leftindex] == nums2[rightindex]) {
                if(results.size()==0 || nums1[leftindex] != results[results.size()-1])
                    results.push_back(nums1[leftindex]);
                leftindex++; rightindex++;
            }
        }
        return results;
    }
private:
    void quickSort(vector<int>& nums, int left, int right) {
        if(left >= right) return;         
        int i = left, j = right;
        int pivot = nums[(i + j) / 2];        
        // key point 1: pivot is the value, not the index
        // key point 2: every time you compare left & right, it should be left <= right not left < right
        // key point 3: nums[i] <= pivot，会导致i一直走到末尾，每次切分都在最边缘，出现O(N**2)的复杂度
        while(i <= j) {              // 下一轮迭代需要i，j不同
            while(i <= j && nums[i] < pivot) i++;
            while(i <= j && nums[j] > pivot) j--;
            // 此时i指向的元素大于等于pivot，j指向的元素小于等于pivot，此时交换并指向下一个位置
            if(i <= j) swap(nums[i++], nums[j--]);
        }
        quickSort(nums, i, right);        // i只会向右边越界，在进入下一轮迭代时，判断 i >= right 则结束
        quickSort(nums, left, j);         // j只会向左边越界，在进入下一轮迭代时，判断 left <= j 则结束
    }
};


// 4 寻找两个有序数组的中位数           时间复杂度是O(logk)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        int k = (n + m) / 2, p = (n + m) % 2;
        if(p == 1) return helper(nums1, nums2, 0, 0, k+1);
        else return (helper(nums1, nums2, 0, 0, k) + helper(nums1, nums2, 0, 0, k+1)) / 2.0;
    }
private:
    double helper(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int k) {
        if(start1 >= nums1.size()) return nums2[start2+k-1];
        if(start2 >= nums2.size()) return nums1[start1+k-1];
        if(k == 1) return min(nums1[start1], nums2[start2]);
        
        int key1 = start1 + k/2 -1 >= nums1.size()? INT_MAX: nums1[start1 + k/2 -1];      // 因为从start1开始的，所以要-1 
        int key2 = start2 + k/2 -1 >= nums2.size()? INT_MAX: nums2[start2 + k/2 -1];
        if(key1 < key2) return helper(nums1, nums2, start1+k/2, start2, k-k/2);
        else return helper(nums1, nums2, start1, start2+k/2, k-k/2);
    }
};





