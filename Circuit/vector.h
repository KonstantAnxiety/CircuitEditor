#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>

template <class T>
class Vector
{
private:
    T *data;
    size_t size;
    size_t capacity;
    void grow();
public:
    Vector();
    Vector(size_t n);
    Vector(const Vector<T> &object);
    ~Vector();
    void push_back(const T &object);
    void pop_back();
    void clear() { size = 0; };
    const T& at(size_t pos) const;
    void set(size_t pos, const T &object);
    void del(size_t pos);
    void insert(size_t pos, const T &object);
    bool empty() const;
    size_t getSize() const { return size; };
    size_t getCapacity() const {return capacity; };
    void badIndexMessage(bool ret) const;

    const T &operator[](size_t i) const;
    friend std::ostream& operator<<(std::ostream& out, const Vector &object)
    {
        for (size_t i = 0; i < object.size; ++i)
            out << object.data[i];
        return out;
    }
};

#endif // VECTOR_H
