//
// Created by user on 27.08.2019.
//

#ifndef MY_VECTOR_MYVECTOR_H
#define MY_VECTOR_MYVECTOR_H

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

    class const_iterator : public some_iterator<std::forward_iterator_tag, T const>{
    public:

        T *ptr;

        const_iterator();
        explicit const_iterator(T* x);
        const_iterator(const const_iterator& mit);
        const_iterator(const iterator& mit);
        const_iterator& operator++();

        const_iterator operator++(int);

        const_iterator& operator--();

        const_iterator operator--(int);


        const T& operator*();

        const_iterator operator+(int integer);

        const_iterator operator+=(int integer);

        const_iterator operator-(int integer);

        const_iterator operator-=(int integer);
        int operator-(const_iterator it);

        bool operator==(const const_iterator& it);

        bool operator!=(const const_iterator& it);

        bool operator<(const const_iterator& it);
        bool operator>(const const_iterator& it);


    };

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


//Definitions
template <typename T>
inline bool operator==(const MyVector<T> &vector1, const MyVector<T>& vector2)
{
    return std::equal(vector1.cbegin(), vector1.cend(), vector2.cbegin());
}

template <typename T>
inline bool operator!=(const MyVector<T> &vector1, const MyVector<T>& vector2)
{
    return !(vector1 == vector2);
}

template <typename T>
inline bool operator<(const MyVector<T> &vector1, const MyVector<T> &vector2)
{
    return std::lexicographical_compare(vector1.cbegin(), vector1.cend(),
                                        vector2.cbegin(), vector2.cend());
}

template <typename T>
inline bool operator<=(const MyVector<T> &vector1, const MyVector<T> &vector2)
{
    return !(vector1 > vector2);
}

template <typename T>
inline bool operator>(const MyVector<T> &vector1, const MyVector<T> &vector2)
{
    return std::lexicographical_compare(vector2.cbegin(), vector2.cend(),
                                        vector1.cbegin(), vector1.cend());
}

template <typename T>
inline bool operator>=(const MyVector<T> &vector1, const MyVector<T> &vector2)
{
    return !(vector1 < vector2);
}

template<class InpIt, class OutIt, class Func>
OutIt my_transform(InpIt first, InpIt last, OutIt it,
                   Func operation)
{
    while (first != last) {
        *it++ = operation(*first++);
    }
    return it;
}

template<class InpIt, class OutIt, class Func>
OutIt my_transform(InpIt first1, InpIt last, InpIt first2, OutIt out_it,
                   Func operation)
{
    while(first1 != last)
    {
        *out_it++ = operation(*first1++, *first2++);
    }
    return out_it;
}

template <typename T>
void MyVector<T>::array_copy(T* to, const T *from, size_t size)  {
    for (size_t i = 0; i < size; i++) {
        new (to + i) T(from[i]);
    }
}

template<typename T>
void MyVector<T>::fill_array(T *to, const T &value, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        new (to + i) T (value);
    }
}


template<typename T>
void MyVector<T>::move_array(MyVector<T>::iterator it, size_t size, size_t count) {
    for(size_t i = 0; i < size; ++i)
    {
        new(it.ptr) T (*(it - count));
        --it;
    }
}


template <typename T>
MyVector<T>::MyVector(size_t size, const T& value)
{
    main_capacity = size ? size*2 : 1;
    mass = new T[main_capacity + 1];
    in_size = size;
    fill_array(mass, value, size);
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other)
{
    main_capacity = other.main_capacity;
    mass = new T[main_capacity + 1];
    in_size = other.in_size;
    array_copy(mass, other.mass, in_size);
}

template <typename T>
MyVector<T>::~MyVector()
{

    delete[] mass;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector &other)
{
    MyVector<T> new_vector(other);
    swap(new_vector);
    return *this;
}


template<typename T>
void MyVector<T>::shrink_to_fit() {
    reserve(in_size);
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (++in_size > main_capacity) {
        reserve(in_size*2);
    }

    new(mass + in_size - 1) T(value);
}


template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(MyVector<T>::iterator position, const T &value)
{
    size_t dist = std::distance(begin(), position);
    if (++in_size > main_capacity) {
        reserve(in_size*2);
    }

    auto new_it = end();
    for(size_t i = 0; i < in_size - dist; ++i)
    {
        new(new_it.ptr) T (*(new_it - 1));
        --new_it;
    }

    new(mass + dist) T (value);
    return iterator(mass + dist);
}


template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(MyVector<T>::iterator position, size_t count, const T &value)
{
    if(count == 0)
        return position;

    size_t dist = std::distance(begin(), position);
    if ((in_size += count) > main_capacity) {
        reserve(in_size*2);
    }

    auto new_it = end();
    move_array(new_it, in_size - dist, count);

    fill_array(mass + dist, value, count);

    return iterator(mass + dist);
}

template<typename T>
template< class InputIt >
void MyVector<T>::insert(MyVector<T>::iterator position, InputIt first, InputIt last)
{
    if(first == last)
        return;
    size_t dist = std::distance(begin(), position);
    size_t count = std::distance(first, last);
    in_size += count;
    if (in_size >= main_capacity) {
        reserve(in_size*2);
    }
    auto new_it = end();
    for(int i = 0; i < size() - dist; ++i)
    {
        new(new_it.ptr) T (*(new_it - count));
        --new_it;
    }


    for(size_t i = 0; i < count; ++i)
    {
        new(mass + dist + i) T (*first++);
    }
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::insert(MyVector<T>::iterator position, std::initializer_list<T> il)
{
    size_t dist = std::distance(begin(), position);
    in_size += il.size();
    if (in_size >= main_capacity) {
        reserve(in_size*2);
    }

    auto new_it = end();
    for(int i = 0; i < size() - dist; ++i)
    {
        new(new_it.ptr) T (*(new_it - il.size()));
        --new_it;
    }

    for(size_t i = 0; i < il.size(); ++i)
    {
        new(mass + dist + i) T (*(il.begin() + i));
    }
    return iterator(mass + dist);
}


template <typename T>
void MyVector<T>::pop_back()
{
    end().ptr->~T();
    --in_size;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(MyVector::iterator position)
{
    for(auto i = position; i != end(); ++i)
    {
        new(i.ptr) T (*(i + 1));
    }
    pop_back();
    return iterator(mass + std::distance(begin(), position));
}

template <typename T>
void MyVector<T>::reserve(size_t size)
{

    T* new_mass = new T[size + 1];
    array_copy(new_mass, mass, in_size);
    main_capacity = size;
    delete[] mass;
    mass = new_mass;
}

template <typename T>
void MyVector<T>::resize(size_t size, const T& value) {
    if (in_size > size) {
        for (auto i = begin() + in_size; i != end(); ++i) {
            i.ptr->~T();
        }
        in_size = size;
    }

    else if (in_size < size) {
        if (main_capacity < size) {
            reserve(size*2);
        }

        for (size_t i = in_size; i < size; ++i)
        {
            new(mass + i) T (value);
        }
        in_size = size;
    }
}

template <typename T>
void MyVector<T>::clear()
{
    in_size = 0;
    for(auto i = begin(); i != end(); ++i)
        i.ptr->~T();
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> il)
{

    in_size = il.size();
    main_capacity = in_size*2;
    mass = new T[main_capacity];

    size_t i = 0;
    for(auto& item: il){
        new (mass + i++) T(item);
    }
}


template<typename T>
void MyVector<T>::swap(MyVector &vector)
{
    std::swap(mass, vector.mass);
    std::swap(in_size, vector.in_size);
    std::swap(main_capacity, vector.main_capacity);
}

template <typename T>
MyVector<T>::const_iterator::const_iterator() :ptr(nullptr) {}

template <typename T>
MyVector<T>::const_iterator::const_iterator(T* x) :ptr(x) {}

template <typename T>
MyVector<T>::const_iterator::const_iterator(const const_iterator& mit) : ptr(mit.ptr) {}

template <typename T>
MyVector<T>::const_iterator::const_iterator(const iterator& mit) : ptr(mit.ptr) {}

template <typename T>
typename MyVector<T>::const_iterator& MyVector<T>::const_iterator::operator++() {
    ++ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator:: operator++(int) {
    const_iterator new_itr(*this);
    operator++();
    return new_itr;
}

template <typename T>
typename MyVector<T>::const_iterator& MyVector<T>::const_iterator:: operator--(){
    --ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator:: operator--(int){
    const_iterator new_itr(*this);
    operator--();
    return new_itr;
}

template <typename T>
const T& MyVector<T>::const_iterator::operator*()
{
    return *ptr;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator::operator+(int integer)
{

    const_iterator new_it(ptr + integer);

    return new_it;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator:: operator+=(int integer)
{
    *this = *this + integer;
    return *this;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator:: operator-(int integer)
{
    const_iterator new_it(ptr - integer);
    return new_it;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator:: operator-=(int integer)
{
    *this = *this - integer;
    return *this;
}

template <typename T>
int MyVector<T>::const_iterator::operator-(const_iterator it)
{
    return ptr - it.ptr;
}

template <typename T>
bool MyVector<T>::const_iterator::operator==(const const_iterator& it)
{
    return it.ptr == ptr;
}

template <typename T>
bool MyVector<T>::const_iterator::operator!=(const const_iterator& it)
{
    return it.ptr != ptr;
}

template <typename T>
bool MyVector<T>::const_iterator::operator<(const const_iterator& it)
{
    return ptr < it.ptr;
}

template <typename T>
bool MyVector<T>::const_iterator::operator>(const const_iterator& it)
{
    return ptr > it.ptr;
}






template<typename T>
MyVector<T>::iterator::iterator(): ptr(nullptr) {}

template<typename T>
MyVector<T>::iterator::iterator(T *x): ptr(x) {}

template<typename T>
MyVector<T>::iterator::iterator(const MyVector::iterator &mit): ptr(mit.ptr) {}

template<typename T>
typename MyVector<T>::iterator& MyVector<T>::iterator::operator++() {
    ++ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator++(int) {
    iterator new_itr(*this);
    operator++();
    return new_itr;
}

template<typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator--() {
    --ptr;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator--(int) {
    iterator new_itr(*this);
    operator--();
    return new_itr;
}

template<typename T>
T& MyVector<T>::iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator+(size_t integer) {

    iterator new_it(ptr + integer);
    return new_it;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator+=(size_t integer) {
    *this = *this + integer;
    return *this;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator-(size_t integer) {
    iterator new_it(ptr - integer);
    return new_it;
}

template<typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator-=(size_t integer) {
    *this = *this - integer;
    return *this;
}

template<typename T>
size_t MyVector<T>::iterator::operator-(MyVector::iterator it) {
    return ptr - it.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator==(const MyVector::iterator &it) {
    return it.ptr == ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator!=(const MyVector::iterator &it) {
    return it.ptr != ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator<(const MyVector::iterator &it) {
    return ptr < it.ptr;
}

template<typename T>
bool MyVector<T>::iterator::operator>(const MyVector::iterator &it) {
    return ptr > it.ptr;
}
#endif //MY_VECTOR_MYVECTOR_H
