//
// Created by alex on 07.04.16.
//

#ifndef A5_COLLECTIONS_MYDEQUE_H
#define A5_COLLECTIONS_MYDEQUE_H

#include <glob.h>

template<typename T>
class myDeque {
    T *dequePtr;
    size_t _size;
    size_t _capacity;

    T *head;
    T *tail;
public:
    myDeque(size_t = 0);

    ~myDeque();

    size_t size() const;

    size_t capacity() const;

    void push_back(const T &value);

    T &front() const;

    T &back() const;

};

template<typename T>
myDeque<T>::myDeque(size_t s) {
    _size = s;
    (_size != 0) ? _capacity = _size : _capacity = 2;
    dequePtr = new T[_capacity];
    head = tail = dequePtr + (_capacity / 2);
}

template<typename T>
myDeque<T>::~myDeque() {

}

template<typename T>
size_t myDeque<T>::size() const {
    return _size;
}

template<typename T>
size_t myDeque<T>::capacity() const {
    return _capacity;
}

template<typename T>
void myDeque<T>::push_back(const T &value) {
    if (_size == 0) {
        *head = *tail = value;
    } else {
        tail++;
        *tail = value;
    }
    _size++;
}

template<typename T>
T &myDeque<T>::front() const {
    return *head;
}

template<typename T>
T &myDeque<T>::back() const {
    return *tail;
}


#endif //A5_COLLECTIONS_MYDEQUE_H
