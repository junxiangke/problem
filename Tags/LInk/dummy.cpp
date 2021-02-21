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


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 92 反转链表2
// 需要改变链表结构的题目，加入dummy节点，始终指向head，返回dummy->next
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(head == NULL || n <= m) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        for(int i = 0; i < m-1; i++) {
            head = head->next;
        }
        ListNode* n1 = head->next;
        ListNode* pre = NULL, *cur = n1;
        for(int i=0; i<n-m+1; i++) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        n1->next = cur;
        head->next = pre;
        return dummy->next;
    }
};


// 25 K 个一组翻转链表  可以使用多个节点更加清晰，如nk记录第k个节点，是pre
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == NULL || k < 2) return head; 
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        while(head != NULL) {
            head = reverseNextK(head, k);    // 进入函数的是需要反转的前一个节点
        }
        return dummy->next;
    }
private:
    ListNode* reverseNextK(ListNode* head, int k) {
        ListNode* next = head;
        for(int i = 0; i<k; i++) {
            if(next->next == NULL) return NULL;
            next = next->next;
        }
        ListNode* n1 = head->next;
        ListNode* pre = NULL, *cur = n1;
        for(int i = 0; i<k; i++) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur; 
            cur = tmp;
        }
        n1->next = cur;
        head->next = pre;
        return n1;
    }
};
// 第二次刷题，重点是函数的输入和输出，输入是翻转的前一个节点，输出是翻转的最后一个节点


// 24 两两交换链表中的节点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        while(head->next != NULL && head->next->next != NULL) {
            ListNode* n1 = head->next, *pre = head, *cur = head->next;
            for(int i = 0; i<2; i++) {
                ListNode* tmp = cur->next;
                cur->next = pre;
                pre = cur; 
                cur = tmp;
            }
            n1->next = cur;
            head->next = pre;
            head = n1;
        }
        return  dummy->next;
    }
};


// 86 分割链表
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head == NULL) return head;
        ListNode* larger_dummy = new ListNode(0);
        ListNode* smaller_dummy = new ListNode(0);
        ListNode* larger = larger_dummy, *smaller = smaller_dummy;
        ListNode* cur = head;
        while(cur != NULL) {
            if(cur->val >= x) {
                larger->next = cur;
                larger = cur;                     // 一开始忘记加
            }
            else {
                smaller->next = cur;
                smaller = cur;
            }
            cur = cur->next;
        }
        larger->next = NULL;                    // 不加会成环
        smaller->next = larger_dummy->next;
        return smaller_dummy->next;
    }
};


// 21 合并两个有序链表
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;
        while(l1 != NULL && l2 != NULL) {
            if(l1->val < l2->val) {
                head->next = l1;
                l1 = l1->next;
            }
            else {
                head->next = l2;
                l2 = l2->next;
            }
            head = head->next;
        }
        while(l1 != NULL) {
            head->next = l1;
            l1 = l1->next;
            head = head->next;
        }
        while(l2 != NULL) {
            head->next = l2;
            l2 = l2->next;
            head = head->next;
        }
        return dummy->next;
    }
};
