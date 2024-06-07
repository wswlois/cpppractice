#include <iostream>
#include <unordered_map>
using namespace std;
class LRUCache {
private:
    int cap;
    unordered_map<int, int> cache;

public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        // 将 key 变为最近使用
        makeRecently(key);
        return cache[key];
    }

    void put(int key, int val) {
        if (cache.find(key) != cache.end()) {
            // 修改 key 的值
            cache[key] = val;
            // 将 key 变为最近使用
            makeRecently(key);
            return;
        }

        if (cache.size() >= this->cap) {
            /* auto it = cache.end(); */
            /* --it; */
            /* int oldestKey = it->first; */
            int oldestKey = cache.size();
            cache.erase(oldestKey);
        }
        // 将新的 key 添加链表尾部
        cache[key] = val;
    }

private:
    void makeRecently(int key) {
        int val = cache[key];
        // 删除 key，重新插入到队尾
        cache.erase(key);
        cache[key] = val;
    }
};
int main()
{
    LRUCache* obj = new LRUCache(2);
  obj->put(1,1);
  obj->put(2,2);
  int param_1 = obj->get(1);
  cout <<"预期结果"<<endl;
  cout <<param_1 <<endl;
  obj->put(3,3);
param_1 = obj->get(2);
  cout <<"预期结果"<<endl;
  cout <<param_1 <<endl;
  obj->put(4,4);
param_1 = obj->get(1);
  cout <<"预期结果"<<endl;
  cout <<param_1 <<endl;
param_1 = obj->get(3);
  cout <<"预期结果"<<endl;
  cout <<param_1 <<endl;
param_1 = obj->get(4);
  cout <<"预期结果"<<endl;
  cout <<param_1 <<endl;
}
