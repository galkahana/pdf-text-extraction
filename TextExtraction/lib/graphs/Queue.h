#pragma once

#include "Result.h"

template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
class Queue {
    public:

        Queue();
        virtual ~Queue();

        bool IsEmpty();
        Result<T> Top();
        Result<T> Dequeue();
        void Enqueue(T inValue);

    private:
        Node<T>* root;
        Node<T>* last;

};

template <typename T>
Queue<T>::Queue() {
    root = NULL;
    last = NULL;
}

template <typename T>
Queue<T>::~Queue() {
    // destroy any nodes remaining in the queue
    Node<T>* current = root;

    while(current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    root = NULL;
    last = NULL; // for good order...though not necessary
}

template <typename T>
bool Queue<T>::IsEmpty() {
    return !root;
}

template <typename T>
Result<T> Queue<T>::Top() {
    return !root ? Result<T>() : Result<T>(root->value);
}

template <typename T>
Result<T> Queue<T>::Dequeue() {
    if(!root)
        return Result<T>();

    Result<T> result(root->value);

    root = root->next;
    if(!root)
        last = NULL;

    return result;
}

template <typename T>
void Queue<T>::Enqueue(T inValue) {
    Node<T>* node = new Node<T>();
    node->value = inValue;

    if(!last) {
        root = node;
    } else {
        last->next = node;
    }
    last = node;
}

