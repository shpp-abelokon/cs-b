//
// Created by alex on 05.04.16.
//

#ifndef A5_COLLECTIONS_MYQUEUE_H
#define A5_COLLECTIONS_MYQUEUE_H


template<typename T>
class myQueue {
    struct Node {
        T data;
        Node *next;
    };
    size_t _size;
    Node *head;
    Node *tail;

public:
    myQueue();

    ~myQueue();

    void push(const T &value);

    T &front() const;

    bool empty() const;

    void pop();

    T &back() const;

    size_t size() const;

    void operator=(myQueue<T> &other);

    void clear();
};

template<typename T>
myQueue<T>::myQueue() {
    head = NULL;
    _size = 0;
}

template<typename T>
myQueue<T>::~myQueue() {
    clear();

}

template<typename T>
void myQueue<T>::push(const T &value) {
    Node *nodePtr = new Node;
    nodePtr->data = value;
    nodePtr->next = NULL;
    if (head == NULL) {
        head = tail = nodePtr;
    } else {
        tail->next = nodePtr;
        tail = nodePtr;
    }
    _size++;
}

template<typename T>
T &myQueue<T>::front() const {
    if (empty()) {
        std::cerr << "Error [front]. queue is empty!" << std::endl;
        exit(1);
    }
    return head->data;
}

template<typename T>
bool myQueue<T>::empty() const {
    return _size == 0;
}

template<typename T>
void myQueue<T>::pop() {
    if (empty()) {
        std::cerr << "Error [pop]. queue is empty!" << std::endl;
        exit(1);
    } else {
        Node *nodePtr = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        delete nodePtr;
        _size--;
    }
}

template<typename T>
T &myQueue<T>::back() const {
    if (empty()) {
        std::cerr << "Error [back]. queue is empty!" << std::endl;
    } else {
        return tail->data;
    }
}

template<typename T>
size_t myQueue<T>::size() const {
    return _size;
}

template<typename T>
void myQueue<T>::operator=(myQueue<T> &other) {
    if (head != other.head && tail != other.tail) {
        Node *nodePtr = new Node;
        nodePtr->data = other.head->data;
        nodePtr->next = other.head->next;
        tail = head;

        for (int i = 0; i < other._size; ++i) {
            if (i >= _size) {
                push(nodePtr->data);
                nodePtr = nodePtr->next;
            } else {
                tail->data = nodePtr->data;
                nodePtr = nodePtr->next;
                if (i != other._size - 1) {
                    tail = tail->next;
                }
            }
        }
        _size = other._size;
    }
}

template<typename T>
void myQueue<T>::clear() {
    while (_size > 0) {
        pop();
    }

}


#endif //A5_COLLECTIONS_MYQUEUE_H
