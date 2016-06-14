//
// Created by abelokon on 07.04.16.
// File: MyDeque.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYDEQUE_H
#define A5_COLLECTIONS_MYDEQUE_H


template<typename T>
class MyDeque {

    struct Node {
        T *dequePtr;
        Node *next;
        Node *prev;
        int count;
        int capacity;
    };
    Node *tail = new Node;
    Node *head = new Node;


    int _size;
    int _capacity;
    int _capacity_tail;
    int _capacity_head;
    int _count_tail;
    int _count_head;

    void resize_head(const int size);

    void resize_tail(const int size);

public:


    MyDeque(const int = 0);

    ~MyDeque();

    int size() const;

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
MyDeque<T>::MyDeque(const int s) {
    _capacity = (s <= 1) ? 3 : s;
    head->dequePtr = new T[_capacity];
    tail->dequePtr = new T[_capacity];

    head->prev = tail;
    tail->prev = head;
    tail->next = head->next = NULL;
    _capacity_head = head->capacity = _capacity;
    _capacity_tail = tail->capacity = _capacity;
    _capacity *= 2;
    _size = _count_tail = _count_head = head->count = tail->count = 0;
}

/* Destructor */
template<typename T>
MyDeque<T>::~MyDeque() {
    clear();
    delete [] head->dequePtr;
    delete [] tail->dequePtr;
}

/* The number of elements in the deque */
template<typename T>
int MyDeque<T>::size() const {
    return _size;
}

/* Check the deque is empty */
template<typename T>
bool MyDeque<T>::empty() {
    return _size <= 0;
}

/* Add element to the front of deque */
template<typename T>
void MyDeque<T>::push_front(const T &value) {
    if (_count_head == _capacity_head) {
        resize_head(_capacity_head);
    }
    if (head->count != 0) {
        head->dequePtr++;
    }
    *head->dequePtr = value;
    _count_head++;
    _size++;
    head->count++;
}

/* Add element to the end of deque */
template<typename T>
void MyDeque<T>::push_back(const T &value) {
    if (_count_tail == _capacity_tail) {
        resize_tail(_capacity_tail);
    }
    if (tail->count != 0) {
        tail->dequePtr++;
    }
    *tail->dequePtr = value;
    _count_tail++;
    _size++;
    tail->count++;
}

/* Change the size head of the current deque */
template<typename T>
void MyDeque<T>::resize_head(const int size) {
    Node *tmp = new Node;
    int newSize = size * 2;
    tmp->dequePtr = new T[newSize];
    tmp->count = 0;
    tmp->capacity = newSize;
    head->next = tmp;
    tmp->prev = head;

    head = tmp;
    _capacity_head += newSize;
    _capacity += newSize;
}

/* Change the size tail of the current deque */
template<typename T>
void MyDeque<T>::resize_tail(const int size) {
    Node *tmp = new Node;
    int newSize = size * 2;
    tmp->dequePtr = new T[newSize];
    tmp->count = 0;
    tmp->capacity = newSize;
    tail->next = tmp;
    tmp->prev = tail;

    tail = tmp;
    _capacity_tail += newSize;
    _capacity += newSize;
}

/* The first element of the deque */
template<typename T>
T &MyDeque<T>::front() const {
    return *head->dequePtr;
}

/* The last element of the deque */
template<typename T>
T &MyDeque<T>::back() const {
    return *tail->dequePtr;
}

/* Delete the first element from the deque */
template<typename T>
void MyDeque<T>::pop_front() {
    if (empty()) {
        std::cerr << "Error [pop_back]. deque is empty!" << std::endl;
        exit(1);
    } else if (_count_head > 1) {
        if (head->count > 1) {
            head->dequePtr--;
            head->count--;
        } else if (head->count == 1) {
            delete[] head->dequePtr;
            _capacity -= head->capacity;
            _capacity_head -= head->capacity;
            head = head->prev;
            head->next = NULL;
        }
        _count_head--;
        _size--;
    } else if(_count_head == 1){
        head->count--;
        _count_head--;
        _size--;
    }
}

/* Delete the last element from the deque */
template<typename T>
void MyDeque<T>::pop_back() {
    if (empty()) {
        std::cerr << "Error [pop_back]. deque is empty!" << std::endl;
        exit(1);
    }else if (_count_tail > 1) {
        if (tail->count > 1) {
            tail->dequePtr--;
            tail->count--;
        } else if (tail->count == 1) {
            delete[] tail->dequePtr;
            _capacity -= tail->capacity;
            _capacity_tail -= tail->capacity;
            tail = tail->prev;
            tail->next = NULL;
        }
        _count_tail--;
        _size--;
    } else if(_count_tail == 1){
        tail->count--;
        _count_tail--;
        _size--;
    }
}

/* Delete all elements of the deque */
template<typename T>
void MyDeque<T>::clear() {
    while (_count_tail != 0) {
        pop_back();
    }
    while (_count_head != 0) {
        pop_front();
    }
}


#endif //A5_COLLECTIONS_MYDEQUE_H
