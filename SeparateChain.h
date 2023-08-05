//Created by Lia 8/2/23
#pragma once
#include <vector>
#include <utility>
#include <functional>
class SeparateChain
{
    std::vector<std::vector<std::pair<std::string, std::string>>> container;
    int capacity = 2;
    int size = 0;
    float maxLoadFactor = 0.8;

    void reHash()
    {
        std::vector<std::vector<std::pair<std::string,std::string>>> temp = container;
        capacity *= 2;
        size = 0;
        container = {};
        for (int i = 0; i < capacity; i++)
        {
            container.push_back({});
        }

        for (int i = 0; i < temp.size(); i++)
        {
            for (int j = 0; j < temp[i].size(); j++)
            {
                Insert(temp[i][j].first, temp[i][j].second);
            }
        }


    }

public:

    SeparateChain()
    {
        for (int i = 0; i < capacity; i++)
        {
            container.push_back({});
        }
    }

    void Insert(std::string key, std::string value)
    {
        int index = std::hash<std::string>{}(key) % capacity;
        container[index].push_back(std::make_pair(key, value));
        size++;

        if ((float)size / capacity >= maxLoadFactor)
        {
            reHash();
        }

    }
    std::string Find(std::string key)
    {
        for (int i = 0; i < container.size(); i++)
        {
            for (int j = 0; j < container[i].size(); j++)
            {
                if (container[i][j].first == key)
                {
                    return container[i][j].second;
                }
            }
        }
        return "Not present";
    }
};