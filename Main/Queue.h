#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Queue {
private:
    size_t start;
    size_t end;
    T* arr;
    size_t size;
    size_t next(size_t i) const { return ((i + 1) % size); }

    void ReWrite()
    {
        T* temp = new T[size * 2];
        size_t ind = 1;
        for (size_t i = start; i != next(end); i = next(i))
        {
            temp[ind] = arr[i];
            ind++;
        }
        delete[] arr;
        arr = temp;
        end = size - 1;
        size *= 2;
        start = 1;
    }
public:
    Queue(size_t s = 1)
    {
        size = s;
        arr = new T[size];
        end = 0;
        start = next(end);
    }

    Queue(const Queue<T>& q)
    {
        size = q.size;
        end = q.end;
        start = q.start;
        arr = new T[size]{};
        for (int i = start; i != next(end); i = next(i)) {
            arr[i] = q.arr[i];
        }
    }

    T Get_Element(int i)
    {
        return arr[i];
    }

    int Get_Size() const
    {
        int size = 0;
        for (int i = start; i != next(end); i = next(i))
        {
            size++;
        }
        return size;
    }

    bool Is_Empty() const
    {
        if (next(end) == start) { return true; }
        return false;
    }

    bool Is_Full() const
    {
        if (next(next(end)) == start) { return true; }
        return false;
    }

    void Push(T x)
    {
        if (Is_Full())
        {
            ReWrite();
        }
        end = next(end);
        arr[end] = x;
    }

    T Pop() {
        if (Is_Empty()) { throw exception(); }
        T v = arr[start];
        start = next(start);
        return v;
    }

    Queue<T>& operator =(const Queue<T>& q) {
        if (this == &q) { return *this; }
        delete[]arr;
        size = q.size;
        end = q.end;
        start = q.start;
        arr = new T[size]{};
        for (int i = start; i != next(end); i = next(i)) {
            arr[i] = q.arr[i];
        }
        return *this;
    }
    
    friend ostream& operator <<(ostream& out, Queue<T>& q)
    {
        if (q.Is_Empty())
        {
            out << "Empty" << endl;
            return out;
        }
        for (int i = q.start; i != q.next(q.end); i = q.next(i))
        {
            out << q.arr[i] << endl;
        }
        return out;
    }
    ~Queue()
    {
        if (size != 0)
            delete[] arr;
    }
};