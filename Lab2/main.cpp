#include <iostream>
#include <cmath>
#include <ctime>
#include <unordered_map>
using namespace std;
#define P 9149658775000477
#define A 24
#define B 11

struct Data
{
    char name;
    int num;
    bool motivation;
    Data(){
        name = (char)(rand() % 26 + 65);
        num = rand() % 10001;
        motivation = rand() % 2;
    };
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

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::pushFront(Data newValue, long long newKey)
{
    HashNode* newNode = new HashNode();
    newNode->value = newValue;
    newNode->key = newKey;
    newNode->next = head;
    head = newNode;
}

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

HashTable::HashTable()
{
    capacity = 8;
    realSize = 0;
    loadFactor = 0.5;
    bucketsArray = new LinkedList[capacity];
}

int HashTable::hash(long long keyToHash)
{
    return ((A * keyToHash + B) % P) % capacity;
}

void HashTable::insert(long long keyToInsert, Data valueToInsert)
{
    if ((float)realSize / capacity > loadFactor) {
        int oldCapacity = capacity;
        capacity *= alpha;
        LinkedList* oldBucketsArray = bucketsArray;
        bucketsArray = new LinkedList[capacity];
        for (int i = 0; i < oldCapacity; i++)
        {
            if (oldBucketsArray[i].head != nullptr)
            {
                HashNode* Node = oldBucketsArray[i].head;
                while (Node->next != nullptr) {
                    int pos1 = hash(Node->key);
                    bucketsArray[pos1].pushFront(Node->value, Node->key);
                    Node = Node->next;
                }
                int pos1 = hash(Node->key);
                bucketsArray[pos1].pushFront(Node->value, Node->key);
            }
        }
        delete[] oldBucketsArray;
    }
    int pos = hash(keyToInsert);
    HashNode* Node = bucketsArray[pos].head;
    if (Node != nullptr) {
        while ((Node->next != nullptr) && (keyToInsert != Node->key))
            Node = Node->next;
        if (Node->key == keyToInsert)
            Node->value = valueToInsert;
        else {
            bucketsArray[pos].pushFront(valueToInsert, keyToInsert);
            realSize++;
        }
    }
    else {
        bucketsArray[pos].pushFront(valueToInsert, keyToInsert);
        realSize++;
    }
}

HashNode* HashTable::find(long long keyToFind)
{
    int pos = hash(keyToFind);
    HashNode* Node = bucketsArray[pos].head;
    if (Node != nullptr) {
        while ((Node->next != nullptr) && (keyToFind != Node->key))
            Node = Node->next;
        if (Node->key == keyToFind)
            return Node;
        else
            return nullptr;
    }
    else
        return nullptr;
}

void HashTable::erase(long long keyToErase)
{
    int pos = hash(keyToErase);
    HashNode* Node = bucketsArray[pos].head;
    if (Node != nullptr) {
        if (Node->key == keyToErase) {
            bucketsArray[pos].head = Node->next;
            realSize--;
            delete Node;
        }
        else if (Node->next != nullptr) {
            while ((Node->next != nullptr) && (keyToErase != Node->next->key))
                Node = Node->next;
            if ((Node->next != nullptr) && (Node->next->key == keyToErase)) {
                HashNode* save = Node->next;
                Node->next = Node->next->next;
                realSize--;
                delete save;
            }
        }
    }
}

int HashTable::size()
{
    return realSize;
}

long long generateRandLong()
{
    long long key = ((long long)rand() % 9) + 1;
    for (int i = 1; i < 13; i++)
        key = key * 10 + rand() % 10;
    return key;
}

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters];
    long long* keysToErase = new long long[iters];
    long long* keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
    // test my HashTable:
    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != nullptr)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    // test STL hash table:
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({ keysToInsert[i], Data() });
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
         ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
         << ", found amount: " << stlFoundAmount << endl << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
                                                                        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main()
{
    srand(time(nullptr));
    testHashTable();
    return 0;
}