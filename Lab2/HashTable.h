#pragma once

struct Data
{
    char name;
    int num;
    bool motivation;
    Data();
};

struct HashNode
{
    long long key;
    Data value;
    HashNode* next;
};

struct LinkedList
{
    HashNode* head;
    LinkedList();
    void pushFront(Data, long long);
};

struct HashTable
{
    int realSize, capacity;
    const int alpha = 2;
    float loadFactor;
    LinkedList* bucketsArray;
    HashTable();
    int hash(long long);
    void insert(long long, Data);
    HashNode* find(long long);
    void erase(long long);
    int size();
};
