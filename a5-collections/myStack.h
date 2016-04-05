//
// Created by alex on 05.04.16.
//

#ifndef A5_COLLECTIONS_MYSTACK_H
#define A5_COLLECTIONS_MYSTACK_H

template<typename T>
class myStack {
    T *stackPtr;
    size_t _top;
    size_t _capacity;

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

    void operator=(const myStack<T>& other);

    bool operator==(const myStack<T>& other);
    bool operator!=(const myStack<T>& other);
};

template<typename T>
myStack<T>::myStack(size_t size) {
    if (size < 0) {
        std::cerr << "Error [size]. Use positive size of the stack." << std::endl;
    }
    stackPtr = new T[size];
    _top = 0;
    _capacity = size;

}

template<typename T>
myStack<T>::~myStack() {
    delete[] stackPtr;
}

template<typename T>
size_t myStack<T>::size() const {
    return _top;
}

template<typename T>
size_t myStack<T>::capacity() const {
    return _capacity;
}

template<typename T>
void myStack<T>::push(const T &value) {
    if (_top >= _capacity) {
        resize(_top);
    }
    stackPtr[_top] = value;
    _top++;
}

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

template<typename T>
void myStack<T>::pop() {
    if (empty()) {
        std::cerr << "Error [pop]. stack is empty." << std::endl;
        exit(1);
    }
    _top--;

}

template<typename T>
bool myStack<T>::empty() const {
    return _top == 0;
}

template<typename T>
T &myStack<T>::top() const {
    return stackPtr[_top - 1];
}

template <typename T>
void myStack<T>::operator=(const myStack<T> &other) {
    if(stackPtr!=other.stackPtr){
        if(other._top>_top){
            resize(other._top);
        }
        for (int i = 0; i <other._top ; ++i) {
            stackPtr[i]=other.stackPtr[i];
        }
        _top=other._top;
    }

}

template <typename T>
bool myStack<T>::operator==(const myStack &other) {
    return (stackPtr==other.stackPtr)? true : (_top!=other._top) ? false : equal(other);
}

template <typename T>
bool myStack<T>::operator!=(const myStack &other) {
    return (stackPtr!=other.stackPtr)? true : (_top==other._top) ? false : equal(other);
}

template <typename T>
bool myStack<T>::equal(const myStack<T> &other) {
    for (int i = 0; i <_top ; ++i) {
        if(stackPtr[i]!=other.stackPtr[i]){
            return false;
        }
    }
    return true;
}


#endif //A5_COLLECTIONS_MYSTACK_H
