#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

template<typename K, typename V>
class LRUCache
{
public:
    LRUCache(size_t count): capacity(count) {}

    ~LRUCache() {}

    void put(const K& key, const V& value)
    {
        auto it = cache_map.find(key);
        if (it != cache_map.end())
        {
            it->second->second = value;
            cache_items.splice(cache_items.begin(), cache_items, it->second);
        }
        else
        {
            if (cache_items.size() == capacity)
            {
                auto last = cache_items.end();
                last--;
                cache_map.erase(last->first);
                cache_items.pop_back();
            }

            cache_items.emplace_front(key, value);
            cache_map[key] = cache_items.begin();
        }
    }

    V get(const K& key)
    {
        auto it = cache_map.find(key);
        if (it == cache_map.end())
            return V();
        else
        {
            cache_items.splice(cache_items.begin(), cache_items, it->second);
            return it->second->second;
        }
    }


private:
    size_t capacity;
    std::list<std::pair<K, V>> cache_items;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache_map;
};

int main ()
{
    LRUCache<int, std::string> lru(3);
    lru.put(1, "one");
    lru.put(2, "two");
    lru.put(3, "three");
    lru.put(4, "four");

    std::cout << lru.get(2) << std::endl;
    std::cout << lru.get(1) << std::endl;
    std::cout << lru.get(3) << std::endl;

    return 0;
}