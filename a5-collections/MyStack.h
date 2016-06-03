//
// Created by abelokon on 05.04.16.
// File: MyStack.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYSTACK_H
#define A5_COLLECTIONS_MYSTACK_H

template<typename T>
class MyStack {
    T *stackPtr; // reference to the region of allocated memory for the stack
    size_t _top; // the number of elements in stack
    size_t _capacity; // the current size of the stack

    void resize(const size_t _size);

    bool equal(const MyStack<T> &stack);

public:
    MyStack(size_t size = 2);

    MyStack(const MyStack<T> &other);

    ~MyStack();

    size_t size() const;

    size_t capacity() const;

    void push(const T &value);

    bool empty() const;

    void pop();

    T &top() const;

    void operator=(const MyStack<T> &other);

    bool operator==(const MyStack<T> &other);

    bool operator!=(const MyStack<T> &other);
};

/* Constructor */
template<typename T>
MyStack<T>::MyStack(size_t size) {
    if (size < 0) {
        std::cerr << "Error [size]. Use positive size of the stack." << std::endl;
    }

    stackPtr = new T[size];
    _top = 0;
    _capacity = size;

}

/* Copy constructor */
template<typename T>
MyStack<T>::MyStack(const MyStack<T> &other) {
    _top = other._top;
    _capacity = other._capacity;
    stackPtr = new T[_capacity];
    for (int i = 0; i < _top; ++i) {
        stackPtr[i] = other.stackPtr[i];
    }
}

/* Destructor */
template<typename T>
MyStack<T>::~MyStack() {
    delete[] stackPtr;
    _top = 0;
}

/* The number of elements in the stack */
template<typename T>
size_t MyStack<T>::size() const {
    return _top;
}

/* The capacity of the stack */
template<typename T>
size_t MyStack<T>::capacity() const {
    return _capacity;
}

/* Add element in stack */
template<typename T>
void MyStack<T>::push(const T &value) {
    if (_top >= _capacity) {
        resize(_top);
    }
    stackPtr[_top] = value;
    _top++;
}

/* Change the size of the current stack */
template<typename T>
void MyStack<T>::resize(const size_t _size = 0) {
    if (_size >= _capacity) {
        _capacity = (_size > _capacity) ? _size : _size * 2;
        T *tmpPtr = new T[_capacity];
        for (int i = 0; i < _top; ++i) {
            tmpPtr[i] = stackPtr[i];
        }
        T *tmp = stackPtr;
        stackPtr = tmpPtr;
        delete[]tmp;
    }

}

/* Delete element from the stack */
template<typename T>
void MyStack<T>::pop() {
    if (empty()) {
        std::cerr << "Error [pop]. stack is empty." << std::endl;
        exit(1);
    }
    _top--;
}

/* Check the stack is empty */
template<typename T>
bool MyStack<T>::empty() const {
    return _top == 0;
}

/* The top element in the stack */
template<typename T>
T &MyStack<T>::top() const {
    return stackPtr[_top - 1];
}

/* Overload operator = */
template<typename T>
void MyStack<T>::operator=(const MyStack<T> &other) {
    if (stackPtr != other.stackPtr) {
        if (other._top > _top) {
            resize(other._top);
        }
        for (int i = 0; i < other._top; ++i) {
            stackPtr[i] = other.stackPtr[i];
        }
        _top = other._top;
    }
}

/* Overload operator == */
template<typename T>
bool MyStack<T>::operator==(const MyStack &other) {
    return (stackPtr == other.stackPtr) ? true : (_top != other._top) ? false : equal(other);
}

/* Overload operator != */
template<typename T>
bool MyStack<T>::operator!=(const MyStack &other) {
    return (stackPtr == other.stackPtr) ? false : (_top != other._top) ? true : !equal(other);
}

/* A comparison of two objects */
template<typename T>
bool MyStack<T>::equal(const MyStack<T> &other) {
    for (int i = 0; i < _top; ++i) {
        if (stackPtr[i] != other.stackPtr[i]) {
            return false;
        }
    }
    return true;
}


#endif //A5_COLLECTIONS_MYSTACK_H
