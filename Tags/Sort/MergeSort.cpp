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


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// 912 排序数组
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        if(nums.size() == 0) return nums;
        int size = nums.size();
        vector<int> tmp(size);
        mergesort(nums, 0, size-1, tmp);
        return nums;
    }
private:
    void mergesort(vector<int>& nums, int start, int end, vector<int>& tmp) {
        if(start == end) return;
        mergesort(nums, start, (start + end) / 2, tmp);
        mergesort(nums, (start + end) / 2 + 1, end, tmp);
        merge(nums, start, end, tmp);
    }
    void merge(vector<int>& nums, int start, int end, vector<int>& tmp) {
        int middle = (start + end) / 2;
        int leftindex = start;
        int rightindex = middle + 1;
        int index = leftindex;
        while(leftindex <= middle && rightindex <= end) {
            if(nums[leftindex] <= nums[rightindex]) tmp[index++] = nums[leftindex++];
            else tmp[index++] = nums[rightindex++];
        } 
        while(leftindex <= middle) tmp[index++] = nums[leftindex++];
        while(rightindex <= end) tmp[index++] = nums[rightindex++];
        for(int i = start; i<=end; i++) nums[i] = tmp[i];
    }
};


// 88 合并两个有序数组     由大到小合并，就不需要额外空间，也不需要移动数组，数组移动一定是o(n)的复杂度，题目简单，五分钟以内写完
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n==0) return;
        vector<int> tmp(m+n);
        int index1 = 0, index2 = 0, index = 0;                         // 多个变量的申明与赋值
        while(index1<m && index2<n) {
            if(nums1[index1] <= nums2[index2])  tmp[index++] = nums1[index1++];
            else tmp[index++] = nums2[index2++];
        }
        while(index1<m) tmp[index++] = nums1[index1++];
        while(index2<n) tmp[index++] = nums2[index2++];
        for(int i=0; i<m+n; i++) nums1[i] = tmp[i];
    }
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index1 = m-1, index2 = n-1, index = m+n-1;
        while(index1 >=0 && index2 >= 0) {
            if(nums2[index2] > nums1[index1]) nums1[index--] = nums2[index2--];
            else nums1[index--] = nums1[index1--];
        }
        while(index2 >= 0) nums1[index--] = nums2[index2--];
    }
};

// 349 两个数组的交集
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
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
        while(i <= j) {
            while(i <= j && nums[i] < pivot) i++;
            while(i <= j && nums[j] > pivot) j--;
            // 此时i指向的元素大于等于pivot，j指向的元素小于等于pivot，此时交换并指向下一个位置
            if(i <= j) swap(nums[i++], nums[j--]);
        }
        quickSort(nums, i, right);        
        quickSort(nums, left, j);         
    }
};


// 21 合并两个有序链表      小技巧，不需继续遍历，只要tail->next指向剩余节点
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        while(l1 != NULL && l2 != NULL) {
            if(l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1 != NULL) tail->next = l1;
        else tail->next = l2;
        return dummy->next;
    }
};
 

// 148 排序链表
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* mid = findMiddle(head);
        ListNode* right = sortList(mid->next);     // 如果前面没有加head->next == NULL，需要判断mid是否为空，可能会导致right没有定义。
        mid->next = NULL;
        head = sortList(head);
        return mergeTwoLists(head, right);
    }
private:
    ListNode* findMiddle(ListNode* head) {
        ListNode* fast = head->next, *slow = head;
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        while(l1 != NULL && l2 != NULL) {
            if(l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1 != NULL) tail->next = l1;
        else tail->next = l2;
        return dummy->next;
    }
};