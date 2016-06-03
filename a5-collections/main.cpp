#include <iostream>
#include "MyVector.h"
#include "MyList.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "MyDeque.h"

#define DEBUG_MyVector true
#define DEBUG_MyList false
#define DEBUG_MyStack false
#define DEBUG_MyQueue false
#define DEBUG_MyDeque false

void separator();

using namespace std;

int main() {

    if (DEBUG_MyDeque) {
        cout << "Create a first 'a' Deque and fill in pish_bakc {\"Java\",\"C++\"} " << endl;
        MyDeque<string> a;
        a.push_back("Java");
        a.push_back("C++");
        cout << "a.size(): " << a.size() << endl;
        cout << "head = a.front(): " << a.front() << endl;
        cout << "tail = a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.push_front(\"Ruby\");" << endl;
        a.push_front("Ruby");
        cout << "a.size(): " << a.size() << endl;
        cout << "head = a.front(): " << a.front() << endl;
        cout << "tail = a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.pop_back();" << endl;
        a.pop_back();
        cout << "a.size(): " << a.size() << endl;
        cout << "head = a.front(): " << a.front() << endl;
        cout << "tail = a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.clear();" << endl;
        a.clear();
        cout << "The called method a.empty(): " << boolalpha << a.empty() << endl;
        cout << "a.size(): " << a.size() << endl;
        cout << "head = a.front(): " << &a.front() << endl;
        cout << "tail = a.back(): " << a.back() << endl;

    }

    if (DEBUG_MyQueue) {
        cout << "Create a first 'a' queue and fill in {\"Java\",\"C++\"} " << endl;
        MyQueue<string> a;
        a.push("Java");
        a.push("C++");
        cout << "MyQueue a.size: " << a.size() << endl;
        cout << "MyQueue a.front(): " << a.front() << endl;
        cout << "MyQueue a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.push(\"Ruby\");" << endl;
        a.push("Ruby");
        cout << "MyQueue a.size: " << a.size() << endl;
        cout << "MyQueue a.front(): " << a.front() << endl;
        cout << "MyQueue a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.pop();" << endl;
        a.pop();
        cout << "MyQueue a.size: " << a.size() << endl;
        cout << "MyQueue a.front(): " << a.front() << endl;
        cout << "MyQueue a.back(): " << a.back() << endl;
        separator();
        cout << "Create a second 'b' queue and fill in {\"rshmelev\",\"abelokon\",\"shpp\"}" << endl;
        MyQueue<string> b;
        b.push("rshmelev");
        b.push("abelokon");
        b.push("shpp");
        cout << "MyQueue b.size: " << b.size() << endl;
        cout << "MyQueue b.front(): " << b.front() << endl;
        cout << "MyQueue b.back(): " << b.back() << endl;
        separator();
        cout << "Assign the queue \"a=b\": " << endl;
        a = b;
        cout << "MyQueue a.size: " << a.size() << endl;
        cout << "MyQueue a.front(): " << a.front() << endl;
        cout << "MyQueue a.back(): " << a.back() << endl;
        separator();
        cout << "The called method a.clear();" << endl;
        a.clear();
        cout << "The called method a.empty(): " << boolalpha << a.empty() << endl;
    }
    if (DEBUG_MyStack) {
        cout << "Create a first 'a' stack and fill in {\"Java\",\"C++\"} " << endl;
        MyStack<string> a;
        a.push("Java");
        a.push("C+");
        cout << "MyStack a.size: " << a.size() << endl;
        cout << "MyStack a.capacity: " << a.capacity() << endl;
        cout << "MyStack a.top(): " << a.top() << endl;
        separator();
        cout << "The called method a.push(\"Ruby\");" << endl;
        a.push("Ruby");
        cout << "MyStack a.size: " << a.size() << endl;
        cout << "MyStack a.capacity: " << a.capacity() << endl;
        cout << "MyStack a.top(): " << a.top() << endl;
        separator();
        cout << "The called method a.pop();" << endl;
        a.pop();
        cout << "MyStack a.size: " << a.size() << endl;
        cout << "MyStack a.capacity: " << a.capacity() << endl;
        cout << "MyStack a.top(): " << a.top() << endl;
        separator();
        cout << "Create a second 'b' stack and fill in {\"rshmelev\",\"abelokon\",\"shpp\"}" << endl;
        MyStack<string> b;
        b.push("rshmelev");
        b.push("abelokon");
        b.push("shpp");
        cout << "Compare the stack \"a==b\": " << boolalpha << (a == b) << endl;
        cout << "Compare the stack \"a!=b\": " << boolalpha << (a != b) << endl;
        separator();
        cout << "Assign the stack \"a=b\": " << endl;
        a = b;
        cout << "Compare the stack \"a==b\": " << boolalpha << (a == b) << endl;
        cout << "Compare the stack \"a!=b\": " << boolalpha << (a != b) << endl;
        cout << "The called method a.empty(): " << boolalpha << a.empty() << endl;
    }

    if (DEBUG_MyList) {

        MyList<string> b;
        b.push_back("Java");
        b.push_back("C++");
        MyList<string>::iterator itr;
        MyList<string>::iterator itr_end;
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "The called method p.front(\"Ruby\");" << endl;
        b.push_front("Ruby");
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "The called method b.insert(itr_end,\"C#\");" << endl;
        itr = b.begin();
        itr_end = b.end();
        b.insert(itr_end, "C#");
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "Create a second 'a' list and fill in {\"rshmelev\",\"abelokon\",\"shpp\"} " << endl;
        MyList<string> a;
        a.push_back("rshmelev");
        a.push_back("abelokon");
        a.push_back("shpp");
        cout << "The called method b.swap(a);" << endl;
        b.swap(a);
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "Assign the list \"b=a\": " << endl;
        b = a;
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "The called method b.erase(itr);" << endl;
        itr = b.begin();
        itr_end = b.end();
        b.erase(itr);
        itr = b.begin();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "The called method b.front(); " << b.front() << endl;
        cout << "The called method b.back(); " << b.back() << endl;
        cout << "The called method b.pop_front();" << endl;
        b.pop_front();
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
        separator();
        cout << "The called method b.pop_back();" << endl;
        b.pop_back();
        itr = b.begin();
        itr_end = b.end();
        for (int i = 0; itr != itr_end; ++itr, i++) {
            cout << "MyList b [" << i << "] " << *itr << endl;
        }
        cout << "MyList b.size: " << b.size() << endl;
    }

    if (DEBUG_MyVector) {
        MyVector<string> p;
        p.push_back("10");
        p.push_back("20");
        p.push_back("30");
        for (int i = 0; i < p.size(); ++i) {
            cout << "MyVector p [" << i << "] " << p[i] << endl;
        }
        cout << "The called method p.resize(6,\"40\");" << endl;
        p.resize(6, "40");
        for (int i = 0; i < p.size(); ++i) {
            cout << "MyVector p [" << i << "] " << p[i] << endl;
        }
        separator();
        cout << "MyVector p.front(): " << p.front() << endl;
        cout << "MyVector p.back(): " << p.back() << endl;
        cout << "MyVector p.at(1): " << p.at(1) << endl;
        cout << "MyVector p.size: " << p.size() << endl;
        cout << "MyVector p.capacity: " << p.capacity() << endl;
        separator();
        cout << "The called method p.resize(8);" << endl;
        p.resize(8);
        cout << "MyVector p.capacity: " << p.capacity() << endl;
        separator();
        cout << "The called method p.resize(8,\"resize_value\");" << endl;
        p.resize(8, "resize_value");
        for (int i = 0; i < p.size(); ++i) {
            cout << "MyVector p [" << i << "] " << p[i] << endl;
        }
        separator();
        cout << "The called method p.reserve(20);" << endl;
        p.reserve(20);
        cout << "MyVector p.capacity: " << p.capacity() << endl;
        cout << "MyVector p.size: " << p.size() << endl;
        separator();
        cout << "The called method p.emty();" << endl;
        cout << "MyVector p.emty: " << boolalpha << (p.empty()) << endl;
        separator();
        cout << "Create a second 'a' vector and fill in {\"rshmelev\",\"abelokon\",\"shpp\"} " << endl;
        MyVector<string> a;
        a.push_back("rshmelev");
        a.push_back("abelokon");
        a.push_back("shpp");
        cout << "Compare the vectors \"p==a\": " << boolalpha << (p == a) << endl;
        cout << "Compare the vectors \"p!=a\": " << boolalpha << (p != a) << endl;
        cout << "The called method p.swap(a); " << endl;
        p.swap(a);
        for (int j = 0; j < p.size(); ++j) {
            cout << "MyVector p [" << j << "] " << p[j] << endl;
        }
        separator();
        cout << "The called method p.max_size(); " << p.max_size() << endl;
        cout << "Print contents of the vector \"p\" using iterators " << endl;
        MyVector<string>::iterator itr = p.begin();
        MyVector<string>::iterator itr_end = p.end();
        for (int j = 0; itr != itr_end; ++itr, ++j) {
            cout << "MyVector p [" << j << "] " << *itr << endl;
        }
        separator();
        cout << "The called method p.erase(itr+1); " << endl;
        MyVector<string>::iterator itr2 = p.begin();
        p.erase(itr2 + 1);
        for (int j = 0; j < p.size(); ++j) {
            cout << "MyVector p [" << j << "] " << p[j] << endl;
        }
        separator();
        cout << "The called method p.insert(1,\"abelokon\"); " << endl;
        p.insert(1, "abelokon");
        for (int j = 0; j < p.size(); ++j) {
            cout << "MyVector p [" << j << "] " << p[j] << endl;
        }
        separator();
        cout << "The called method p.swap(a); " << endl;
        for (int j = 0; j < p.size(); ++j) {
            cout << "MyVector p [" << j << "] " << p[j] << endl;
        }
        cout << "Assign the vector \"p=a\": " << endl;
        p = a;
        for (int i = 0; i < p.size(); ++i) {
            cout << "MyVector p [" << i << "] " << p[i] << endl;
        }
        separator();
        cout << "MyVector p.capacity: " << p.capacity() << endl;
        cout << "MyVector p.size: " << p.size() << endl;
        cout << "The called method p.shrink_to_fit(); " << endl;
        p.shrink_to_fit();
        cout << "MyVector p.capacity: " << p.capacity() << endl;
        cout << "MyVector p.size: " << p.size() << endl;
        separator();
        cout << "The called method p.clear(); " << endl;
        p.clear();
        for (int i = 0; i < p.size(); ++i) {
            cout << "MyVector p [" << i << "] " << p[i] << endl;
        }
    }

    return 0;
}

void separator() {
    cout << "------------------------" << endl;
}