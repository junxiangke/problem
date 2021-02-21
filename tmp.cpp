#include <iostream>
#include<vector>
using namespace std;

void helper(vector<int>& nums, int left, int right) {
  if(left >= right) return;
  int pivot = nums[(left + right) / 2];
  int i = left, j = right;
  
  while(i <= j) {
    while(i <= j && nums[i] <= pivot) i++;
    while(i <= j && nums[j] >= pivot) j--;
    if(i <= j) swap(nums[i++], nums[j--]);

    helper(nums, left, j);
    helper(nums, right, i);
  }
}

void quicksort(vector<int>& nums) {
  if(nums.size() == 0) return;
  helper(nums, 0, nums.size()-1);
 }

int main()
{
    cout << "Hello, World!" << endl;
    
    cout<< (1<<5) <<endl;
}