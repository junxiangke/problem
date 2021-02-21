#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
using namespace std;         //命名空间


void PercDown(vector<int>& nums, int root, int size) {
    int child, parent;
    int tmp=nums[root];
    for(parent=root; 2*parent+1<size; parent=child) {
        child = 2*parent+1;
        if((child!=size-1) && (nums[child]<nums[child+1])) child++;
        if(nums[child]<tmp) break;
        else  nums[parent]=nums[child];
    }
    nums[parent]=tmp;
}

void BuildHeap(vector<int>& nums) {
    int size=nums.size();
    if(!size) return;
    for(int i=size/2-1; i>=0; i--) {
        PercDown(nums, i, size);
    }
}

void HeapSort(vector<int>& nums) {
    BuildHeap(nums);
    int size=nums.size();
    for(int i=size-1; i>0; i--) {
        swap(nums[i], nums[0]);
        PercDown(nums, 0, i);
    }
}

int main()
{
    int size, x;
    cin>>size;
    vector<int> nums(size);
    for(int i=0; i<size; i++) {
        cin>>x;
        nums[i]=x;
    }
    HeapSort(nums);
    for(int i=0; i<size; i++) {
        cout<<nums[i]<<endl;
    }
    
}