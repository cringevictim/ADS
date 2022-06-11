#include "HashTable.h"

#include <iostream>
#define P 9149187100477
#define A 24
#define B 11

Data::Data(){
    name = (char)(rand() % 26 + 65);
    num = rand() % 10001;
    motivation = rand() % 2;
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