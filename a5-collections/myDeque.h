//
// Created by abelokon on 07.04.16.
// File: myDeque.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYDEQUE_H
#define A5_COLLECTIONS_MYDEQUE_H


template<typename T>
class myDeque {

    struct Node {
        T *dequePtr;
        T *next;
        T *prev;
        size_t count;
        size_t capacity;
    };
    Node *tail = new Node;
    Node *head = new Node;


    size_t _size;
    size_t _capacity;
    size_t _capacity_tail;
    size_t _capacity_head;
    size_t _count_tail;
    size_t _count_head;

    void resize_head(const size_t size);

    void resize_tail(const size_t size);

public:

    myDeque(const size_t = 0);

    ~myDeque();

    size_t size() const;

    bool empty();

    void push_front(const T &value);

    void push_back(const T &value);

    void pop_front();

    void pop_back();

    T &front() const;

    T &back() const;

    void clear();

};

/* Constructor */
template<typename T>
myDeque<T>::myDeque(const size_t s) {
    (s <= 0) ? _capacity = 2 : _capacity = s;
    head->dequePtr = new T[_capacity];
    tail->dequePtr = new T[_capacity];
    head->prev = tail->dequePtr;
    tail->prev = head->dequePtr;
    _capacity_head = head->capacity = _capacity;
    _capacity_tail = tail->capacity = _capacity;
    _size = _count_tail = _count_head = head->count = tail->count = 0;

}

/* Destructor */
template<typename T>
myDeque<T>::~myDeque() {

}

/* The number of elements in the deque */
template<typename T>
size_t myDeque<T>::size() const {
    return _size;
}

/* Check the deque is empty */
template<typename T>
bool myDeque<T>::empty() {
    return _size <= 0;
}

/* Add element to the front of deque */
template<typename T>
void myDeque<T>::push_front(const T &value) {
    if (_count_head == _capacity_head) {
        resize_head(_capacity_head);
    }
    if (_count_head != 0) {
        head->dequePtr++;
    } else if (_count_head == 0 && _count_tail > 0) {
        head->dequePtr = head->prev;
    } else if (_size == 0) {
        tail->prev = tail->dequePtr;
        tail->dequePtr = head->dequePtr;
    }
    *head->dequePtr = value;
    _count_head++;
    _size++;
    head->count++;
}

/* Add element to the end of deque */
template<typename T>
void myDeque<T>::push_back(const T &value) {
    if (_count_tail == _capacity_tail) {
        resize_tail(_capacity_tail);
    }
    if (_count_tail != 0) {
        tail->dequePtr++;
    } else if (_count_tail == 0 && _count_head > 0) {
        tail->dequePtr = tail->prev;
    } else if (_size == 0) {
        head->prev = head->dequePtr;
        head->dequePtr = tail->dequePtr;
    }
    *tail->dequePtr = value;
    _count_tail++;
    _size++;
    tail->count++;
}

/* Change the size head of the current deque */
template<typename T>
void myDeque<T>::resize_head(const size_t size) {
    Node *tmp = new Node;
    size_t newSize = size * 2;
    tmp->dequePtr = new T[newSize];
    head->next = tmp->dequePtr;
    tmp->prev = head->dequePtr;
    tmp->count = 0;
    tmp->capacity = newSize;
    head = tmp;
    _capacity_head += newSize;
    _capacity += newSize;

}

/* Change the size tail of the current deque */
template<typename T>
void myDeque<T>::resize_tail(const size_t size) {
    Node *tmp = new Node;
    size_t newSize = size * 2;
    tmp->dequePtr = new T[newSize];
    tail->next = tmp->dequePtr;
    tmp->prev = tail->dequePtr;
    tmp->count = 0;
    tmp->capacity = newSize;
    tail = tmp;
    _capacity_tail += newSize;
    _capacity += newSize;
}

/* The first element of the deque */
template<typename T>
T &myDeque<T>::front() const {
    return *head->dequePtr;
}

/* The last element of the deque */
template<typename T>
T &myDeque<T>::back() const {
    return *tail->dequePtr;
}

/* Delete the first element from the deque */
template<typename T>
void myDeque<T>::pop_front() {
    if (empty()) {
        std::cerr << "Error [pop_front]. deque is empty!" << std::endl;
        exit(1);
    } else if (head->count != 0) {
        head->dequePtr--;
    } else if (head->count == 0 && _count_head != 0) {
        _capacity_head -= head->capacity;
        head->dequePtr = head->prev;
        delete[] head->next;
    }
    if (_count_head != 0) {
        _count_head--;
        head->count--;
        _size--;
    }

}

/* Delete the last element from the deque */
template<typename T>
void myDeque<T>::pop_back() {
    if (empty()) {
        std::cerr << "Error [pop_back]. deque is empty!" << std::endl;
        exit(1);
    } else if (tail->count != 0) {
        tail->dequePtr--;
    } else if (tail->count == 0 && _count_tail != 0) {
        _capacity_tail -= tail->capacity;
        tail->dequePtr = tail->prev;
        delete[] tail->next;
    }
    if (_count_tail != 0) {
        _count_tail--;
        tail->count--;
        _size--;
    }
}

/* Delete all elements of the deque */
template<typename T>
void myDeque<T>::clear() {
    while (_count_tail != 0) {
        pop_back();
    }
    while (_count_head != 0) {
        pop_front();
    }
}


#endif //A5_COLLECTIONS_MYDEQUE_H
