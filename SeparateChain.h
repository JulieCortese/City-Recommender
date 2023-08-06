//Created by Lia 8/2/23
#pragma once
#include <vector>
#include <utility>
#include <functional>
class SeparateChain
{
    std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> container;
    int capacity = 2;
    int size = 0;
    float maxLoadFactor = 0.8;

    void reHash()
    {
        std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> temp = container;
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

    void Insert(std::string key, std::vector<std::string> value)
    {
        int index = std::hash<std::string>{}(key) % capacity;
        container[index].push_back(std::make_pair(key, value));
        size++;

        if ((float)size / capacity >= maxLoadFactor)
        {
            reHash();
        }

    }
    std::vector<std::string> Find(std::string key)
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
        std::vector<std::string> temp;
        temp.push_back("Not present");
        return temp;
    }

    std::string FindTop()
    {
        std::string top = "-1";
        float NatWlkInd = -1;
        for (int i = 0; i < container.size(); i++)
        {
            for (int j = 0; j < container[i].size(); j++)
            {
                if (NatWlkInd < std::stof(container[i][j].second[18]))
                {
                    top = container[i][j].first;
                    NatWlkInd =  std::stof(container[i][j].second[18]);
                }
            }
        }
        return top + ". National Walkability Index: " + to_string(NatWlkInd);
    }

    std::string FindRank(std::vector<std::string> index)
    {
        float max = 0;
        std::string key;
        for (int i = 0; i < container.size(); i++)
        {
            for (int j = 0; j < container[i].size(); j++)
            {
                float sum = 0;
                for(int k = 0; k < 5; k++){
                    sum += stof(container[i][j].second[stoi(index[k]) - 1]) * (5 - k);
                }
                if (sum > max)
                {
                    key = container[i][j].first;
                    max = sum;
                }
            }

        }
        return key;
    }
};