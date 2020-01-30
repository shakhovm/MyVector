//
// Created by user on 27.08.2019.
//

#ifndef MY_VECTOR_MYVECTOR_H
#define MY_VECTOR_MYVECTOR_H



#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>

template <class Category, class T, class Distance = ptrdiff_t ,
        class Pointer = T*, class Reference = T&>
struct some_iterator {
    typedef T value_type;
    typedef Distance difference_type ;
    typedef Pointer pointer ;
    typedef Reference reference ;
    typedef Category iterator_category ;
};



template <typename T>
class MyVector {

public:
    class iterator: public some_iterator<std::forward_iterator_tag, T>
    {
    public:
        T *ptr;

        iterator();
        explicit iterator(T* x);
        iterator(const iterator& mit);
        iterator& operator++();

        iterator operator++(int);

        iterator& operator--();

        iterator operator--(int);


        T& operator*();

        iterator operator+(size_t integer);

        iterator operator+=(size_t integer);

        iterator operator-(size_t integer);

        iterator operator-=(size_t integer);

        size_t operator-(iterator it);

        bool operator==(const iterator& it);

        bool operator!=(const iterator& it);

        bool operator<(const iterator& it);
        bool operator>(const iterator& it);
    };

    class const_iterator;

private:

    static void array_copy(T* to, const T* from, size_t size);

    static void fill_array(T* to, const T& value, size_t size);

    static void move_array(iterator it, size_t size, size_t count);

    T* mass;
    size_t in_size;
    size_t main_capacity;



public:

    explicit MyVector(size_t size = 0, const T& value = T());
    MyVector(const MyVector& other);
    MyVector(std::initializer_list<T> il);

    ~MyVector();
    MyVector& operator=(const MyVector& other);

    void push_back(const T& value);

    iterator insert(iterator position, const T& value);

    iterator insert( iterator position, size_t count, const T& value );

    template< class InputIt>
    void insert(iterator position, InputIt first, InputIt last);

    iterator insert(iterator position, std::initializer_list<T> il);



    template<class... Args>
    void emplace_back(const Args&... args) {push_back(T(args...));}

    template<class... Args>
    void emplace(iterator position, const Args&... args) {insert(position, T(args...));}

    void pop_back();

    iterator erase(iterator position);

    void reserve(size_t size);

    inline int size() const {return in_size;}

    inline int capacity() const { return main_capacity; }

    inline bool empty() const{ return !in_size; }

    void resize(size_t size, const T& value = T());

    void shrink_to_fit();

    inline T& operator[](size_t index) { return mass[index]; }

    inline const T& operator[](size_t index) const { return mass[index]; }

    T& at(int index) { assert(index >= 0 && index < in_size); return mass[index]; }

    const T& at(size_t index) const { assert(index >= 0 && index < in_size); return mass[index]; }

    inline T& front() { return mass[0]; }

    inline const T& front() const { return mass[0]; }

    inline T& back() { return mass[in_size - 1]; }

    inline const T& back() const { return mass[in_size - 1]; }

    inline T *data() { return mass; }

    inline const T *data() const { return mass; }

    inline iterator begin() { return iterator(mass); }
    inline iterator end() { return iterator(mass + in_size); }

    inline const_iterator cbegin() const { return const_iterator(mass); }
    inline const_iterator cend() const { return const_iterator(mass + in_size); }

    void swap(MyVector &vector);

    void clear();


};

template<class InpIt, class OutIt, class Func>
OutIt my_transform(InpIt first, InpIt last, OutIt it,
                   Func operation);

template<class InpIt, class OutIt, class Func>
OutIt my_transform(InpIt first1, InpIt last, InpIt first2, OutIt out_it,
                   Func operation);



#endif //MY_VECTOR_MYVECTOR_H
