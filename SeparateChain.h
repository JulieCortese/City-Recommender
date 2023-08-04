//Created by Lia 8/2/23
#pragma once
#include <vector>
#include <list>
#include <utility>
#include <functional>
template<typename T>
class SeparateChain
{
    std::vector<std::list<std::pair<T,T>>> container;
    int capacity = 2;
    int size = 0;
    float maxLoadFactor = 0.8;

    void reHash()
    {
        std::vector<std::list<std::pair<T,T>>> temp = container;
        capacity *= 2;
        size = 0;
        for (int i = 0; i < capacity; i++)
        {
            container[i] = {};
        }
        for (int i = 0; i < temp.size(); i++)
        {
            if (!temp[i].empty())
            {
                for (auto it = temp[i].begin(); it < temp[i].end(); it++)
                {
                    container.insert(temp[i].first, temp[i].second);
                }
            }
        }


    }

public:

    SeparateChain()
    {
        for (int i = 0; i < capacity; i++)
        {
            container[i] = {};
        }
    }

    void insert(T key, T value)
    {
        int index = std::hash<T>(key) % capacity;
        container[index].insert(std::make_pair(key, value));
        size++;

        if ((float)size / capacity >= maxLoadFactor)
        {
            reHash();
        }

    }
    T find(T key)
    {
        for (int i = 0; i < container.size(); i++)
        {
            if (!container[i].empty())
            {
                for (auto it = container[i].begin(); it < container[i].end(); it++)
                {
                    if (container[i].first == key)
                    {
                        return container[i].second;
                    }
                }
            }
        }
        return "Not present";
    }
};