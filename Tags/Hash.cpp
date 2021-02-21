#include<iostream>           //输入输出需要的库
#include<vector>             //STL库，容器
#include<algorithm>          //调sort函数，等
#include<queue>              //STL库，队列
#include<stack>              //STL库，栈
#include<unordered_map>      //哈希表，查找效率高，O(1)
#include<unordered_set>
#include<list>               //双向链表
#include<map>
#include<set>
#include<numeric>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;         //命名空间


// 146 LRU 缓存机制
class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    int get(int key) {
        auto it = m.find(key);
        if(it == m.end()) return -1;
        cache.splice(cache.begin(), cache, it->second);    // it是指向map元素的指针，若想要指向list中元素，需要指向map元素的第二个元素
        return it->second->second;
    }
    void put(int key, int value) {
        if(m.count(key) != 0) cache.erase(m[key]);
        cache.push_front(make_pair(key, value));
        m[key] = cache.begin();
        if(cache.size()>cap) {
            int k = cache.rbegin()->first;      // 返回链表最后一个元素中的key，使用pair的原因是，删除最后的元素时，需要获取删除的key
            m.erase(k);
            cache.pop_back();
        }
    }
private:
    int cap;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> m;    // map里面已经有key的信息了，为什么list里面要存key，value的pair

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
class LRUCache {
public:
    LRUCache(int capacity) {
        size = capacity;
    } 
    int get(int key) {
        if(!m.count(key)) return -1;
        cache.splice(cache.begin(), cache, m[key]);
        return m[key]->second;
    } 
    void put(int key, int value) {
        if(!m.count(key)) {
            cache.push_front(make_pair(key, value));   // make_pair<>写错
            m[key] = cache.begin();                    // 不加这句，哈希表中就没有这个key的映射
        }
        else {
            auto it = m[key];
            m[key]->second = value;
            cache.splice(cache.begin(), cache, it);
        }
        if(m.size()>size) {
            int k = cache.rbegin()->first;
            m.erase(k);
            cache.pop_back();   // 删除list末尾元素
        }
        
    }
private:
    int size;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> m;
};
