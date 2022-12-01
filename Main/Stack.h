#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Stack
{
private:
    size_t top;
    size_t size;
    T* arr;
public:

    Stack(size_t sz = 1)
    {
        if (sz <= 0)
        {
            throw 1;
        }
        top = -1;
        size = sz;
        arr = new T[size];
    }

    Stack(const Stack& st)
    {
        top = st.top;
        size = st.size;
        copy(st.arr, st.arr + size, arr);
    }

    size_t Size()
    {
        return top + 1;
    }

    bool IsEmpty() const
    {
        return (top == -1);
    }

    bool IsFull() const
    {
        return (top == size - 1);
    }

    void Push(const T& val)
    {
        if (top == size - 1)
        {
            T* tmp = new T[size * 2];
            copy(arr, size + arr, tmp);
            delete[] arr;
            arr = tmp;
            size *= 2;
        }
        arr[++top] = val;
    }

    T Pop()
    {
        if (IsEmpty()) { throw 1; }
        return arr[top--];
    }

    T Top()
    {
        if (IsEmpty()){ throw 1; }
        return arr[top];
    }

    friend ostream& operator <<(ostream& out, Stack<T>& st)
    {
        if (st.IsEmpty())
        {
            out << "Empty" << endl;
            return out;
        }
        for (int i = 0; i < st.Size(); i++)
        {
            out << st.arr[i] << " ";
        }
        return out;
    }

    ~Stack()
    {
        delete[] arr;
    }
};