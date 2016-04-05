//
// Created by abelokon on 05.04.16.
// File: myStack.h
// Author abelokon
//

#ifndef A5_COLLECTIONS_MYSTACK_H
#define A5_COLLECTIONS_MYSTACK_H

template<typename T>
class myStack {
    T *stackPtr; // reference to the region of allocated memory for the stack
    size_t _top; // the number of elements in stack
    size_t _capacity; // the current size of the stack

    void resize(const size_t _size);

    bool equal(const myStack<T> &stack);

public:
    myStack(size_t size = 1);

    ~myStack();

    size_t size() const;

    size_t capacity() const;

    void push(const T &value);

    bool empty() const;

    void pop();

    T &top() const;

    void operator=(const myStack<T> &other);

    bool operator==(const myStack<T> &other);

    bool operator!=(const myStack<T> &other);
};

/* Constructor */
template<typename T>
myStack<T>::myStack(size_t size) {
    if (size < 0) {
        std::cerr << "Error [size]. Use positive size of the stack." << std::endl;
    }
    stackPtr = new T[size];
    _top = 0;
    _capacity = size;

}

/* Destructor */
template<typename T>
myStack<T>::~myStack() {
    delete[] stackPtr;
}

/* The number of elements in the stack */
template<typename T>
size_t myStack<T>::size() const {
    return _top;
}

/* The capacity of the stack */
template<typename T>
size_t myStack<T>::capacity() const {
    return _capacity;
}

/* Add element in stack */
template<typename T>
void myStack<T>::push(const T &value) {
    if (_top >= _capacity) {
        resize(_top);
    }
    stackPtr[_top] = value;
    _top++;
}

/* Change the size of the current stack */
template<typename T>
void myStack<T>::resize(const size_t _size) {
    _capacity = _size * 2;
    T *tmpPtr = new T[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        tmpPtr[i] = stackPtr[i];
    }
    T *tmp = stackPtr;
    stackPtr = tmpPtr;
    delete[]tmp;
}

/* Delete element from the stack */
template<typename T>
void myStack<T>::pop() {
    if (empty()) {
        std::cerr << "Error [pop]. stack is empty." << std::endl;
        exit(1);
    }
    _top--;
}

/* Check the stack is empty */
template<typename T>
bool myStack<T>::empty() const {
    return _top == 0;
}

/* The top element in the stack */
template<typename T>
T &myStack<T>::top() const {
    return stackPtr[_top - 1];
}

/* Overload operator = */
template<typename T>
void myStack<T>::operator=(const myStack<T> &other) {
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
bool myStack<T>::operator==(const myStack &other) {
    return (stackPtr == other.stackPtr) ? true : (_top != other._top) ? false : equal(other);
}

/* Overload operator != */
template<typename T>
bool myStack<T>::operator!=(const myStack &other) {
    return (stackPtr != other.stackPtr) ? true : (_top == other._top) ? false : equal(other);
}

/* A comparison of two objects */
template<typename T>
bool myStack<T>::equal(const myStack<T> &other) {
    for (int i = 0; i < _top; ++i) {
        if (stackPtr[i] != other.stackPtr[i]) {
            return false;
        }
    }
    return true;
}


#endif //A5_COLLECTIONS_MYSTACK_H
