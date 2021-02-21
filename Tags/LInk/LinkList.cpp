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


// 206 反转链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL;
        while(head != NULL) {
            ListNode* tmp = head->next;
            head->next = pre;
            pre = head;
            head = tmp;
        }
        return pre;
    }
};


// 138 复制带随即指针的链表
// 1. 复制得到1->1'->2->2'->3->3'->NULL；2.复制随机指针；3.拆开 
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL) return NULL;
        copyNext(head);
        cout<<"copyNext"<<endl;
        copyRandom(head);
        cout<<"copyRandom"<<endl;
        return split(head);
    }
public:
    void copyNext(Node* head) {
        while(head != NULL) {
            Node* tmp = head->next;
            head->next = new Node(head->val);
            head->next->next = tmp;
            head = tmp;
        }
    }
    void copyRandom(Node* head) {
        while(head != NULL) {
            if(head->random != NULL) head->next->random = head->random->next;
            else head->next->random = NULL;
            head = head->next->next;
        }
    }
    Node* split(Node* head) {
        Node dummy(0);
        Node* copyhead = &dummy;
        while(head != NULL) {
            copyhead->next = head->next;
            copyhead = copyhead->next;
            head->next = copyhead->next;
            head = head->next;
            
        }
        return dummy.next;
    }
};


// 143 重排链表 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head == NULL) return;
        ListNode* mid = findMiddle(head);
        ListNode* head2 = reverse(mid->next);
        mid->next = NULL;
        merge(head, head2);
        return;
    }
private:
    ListNode* findMiddle(ListNode* head) {          // 找的是middle前一个节点，不用背，画一下
        ListNode* fast = head->next, *slow = head;     //奇数点slow在最中央，偶数点在靠左边
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    ListNode* reverse(ListNode* head) {
        ListNode* pre = NULL;
        while(head != NULL) {
            ListNode* tmp = head->next;
            head->next = pre;
            pre = head;
            head = tmp;
        }
        return pre;
    }
    void merge(ListNode* head, ListNode* head2) {
        while(head != NULL && head2 != NULL) {
            ListNode* tmp = head->next;
            head->next = head2;
            head2 = head2->next;
            head->next->next = tmp;
            head = tmp;
        }
    }
};
// 第二遍刷题，没有思路


// 61 旋转链表
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {            // k比链表的长度大的时候，无法通过
        if(head == NULL) return head;
        head = reverse(head);
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        head = reverseK(head, k);
        head->next = reverse(head->next);
        return dummy->next;
    }
private:
    ListNode* reverse(ListNode* head) {
        ListNode* pre = NULL, *cur = head;
        while(cur != NULL) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
    ListNode* reverseK(ListNode* head, int k) {      // 比普通的reverse多两个指针，记录reverse的开端和再前一个节点 
        ListNode* pre = head, *cur = head->next;
        ListNode* n1 = cur;
        for(int i=0; i<k; i++) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        head->next = pre;
        n1->next = cur;
        return n1;
    }
};
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* cur = head;
        if(head == NULL) return head;
        int len = 1;
        while(cur->next != NULL) {
            cur = cur->next;
            len++;
        }
        cur->next = head;
        for(int i = 0; i < len-k%len; i++) {
            cur = cur->next;
        }
        head = cur->next;
        cur->next = NULL;
        return head;
    }
};
// 第二次刷题，一开始的思路是三步翻转法，很麻烦，写的时候把len-k%len直接写成k了


// 141 环形链表
class Solution {
public:
    bool hasCycle1(ListNode *head) {
        if(head == NULL || head->next == NULL) return false;
        ListNode* fast = head->next, *slow = head;           // 如果fast也等于head，从一开始两个指针就相等了
        while(fast != slow) {
            if(fast == NULL || fast->next == NULL) return false;
            fast = fast->next->next;
            slow = slow->next;
        } 
        return true;
    }
    bool hasCycle2(ListNode *head) {
        if(head == NULL || head->next == NULL) return false;
        ListNode* fast = head, *slow = head;          
        while(fast != NULL && fast->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        } 
        return false;
    }
};

// 142 环形链表2
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {               // 推导可得head到环起始处的距离，与慢指针到环起始处的距离相等
        if(head == NULL || head->next == NULL) return NULL;
        ListNode* fast = head, *slow = head;                // 需要fast与slow从同一个位置开始
        while(fast != NULL && fast->next != NULL) {       // fast 能到链表的终点说明没有环
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) {
                while(head != slow) {             
                    head = head->next;
                    slow = slow->next;
                }
                return head;
            }
        }
        return NULL;
    }
};
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {               // 推导可得head到环起始处的距离，与慢指针到环起始处的距离相等
        if(head == NULL || head->next == NULL) return NULL;
        ListNode* fast = head->next, *slow = head;          
        while(fast != slow) {
            if(fast == NULL || fast->next == NULL) return NULL;
            fast = fast->next->next;
            slow = slow->next;
        } 
        while(head != slow->next) {
            head = head->next;
            slow = slow->next;
        }
        return head;
    }
};


// 148 排序链表
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* mid = findMiddle(head);
        ListNode* right = sortList(mid->next);
        mid->next = NULL;
        head = sortList(head);
        return mergeTwoLists(head, right);
    }
private:
    ListNode* findMiddle(ListNode* head) {     // 错不错开都可以，middle偏左或者偏右
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

// 109 有序链表转换二叉搜索树
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(head == NULL) return NULL;
        if(head->next == NULL) return new TreeNode(head->val);
        ListNode* pre = findMiddle(head);
        if(pre == NULL) {
            TreeNode* root = new TreeNode(head->val);
            root->right = sortedListToBST(head->next);
            return root;
        }
        TreeNode* root = new TreeNode(pre->next->val);
        root->right = sortedListToBST(pre->next->next);
        pre->next = NULL;
        root->left = sortedListToBST(head);
        return root;
    }
private:
    
    ListNode* findMiddle(ListNode* head) {
        ListNode* pre = NULL;
        ListNode* fast = head->next, *slow = head;
        while(fast != NULL && fast->next != NULL) {
            pre = slow;
            fast = fast->next->next;
            slow = slow->next;
        }
        return pre;
    }
};
// 第二次刷题，中点找错了，奇数点root必须找正中间，所以需要返回正中间的前一个点

