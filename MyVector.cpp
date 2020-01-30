#include "MyVector.h"


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
bool operator==(const MyVector<T> &vector1, const MyVector<T> &vector2)
{
    if(vector1.size() != vector2.size())
        return false;
    for(int i = 0; i < vector1.size(); ++i)
    {
        if(vector1[i] != vector2[i])
        {
            return false;
        }
    }
    return true;
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


template<typename T>
class MyVector<T>::const_iterator: public some_iterator<std::forward_iterator_tag, T const>
{


public:

    T *ptr;

    const_iterator() :ptr(nullptr) {}
    explicit const_iterator(T* x) :ptr(x) {}
    const_iterator(const const_iterator& mit) : ptr(mit.ptr) {}
    const_iterator(const iterator& mit) : ptr(mit.ptr) {}
    const_iterator& operator++() {
        ++ptr;
        return *this;
    }

    const_iterator operator++(int) {
        const_iterator new_itr(*this);
        operator++();
        return new_itr;
    }

    const_iterator& operator--(){
        --ptr;
        return *this;
    }

    const_iterator operator--(int){
        const_iterator new_itr(*this);
        operator--();
        return new_itr;
    }


    const T& operator*()
    {
        return *ptr;
    }

    const_iterator operator+(int integer)
    {

        const_iterator new_it(ptr + integer);

        return new_it;
    }

    const_iterator operator+=(int integer)
    {
        *this = *this + integer;
        return *this;
    }

    const_iterator operator-(int integer)
    {
        const_iterator new_it(ptr - integer);
        return new_it;
    }

    const_iterator operator-=(int integer)
    {
        *this = *this - integer;
        return *this;
    }

    int operator-(const_iterator it)
    {
        return ptr - it.ptr;
    }

    bool operator==(const const_iterator& it)
    {
        return it.ptr == ptr;
    }

    bool operator!=(const const_iterator& it)
    {
        return it.ptr != ptr;
    }

    bool operator<(const const_iterator& it)
    {
        return ptr < it.ptr;
    }
    bool operator>(const const_iterator& it)
    {
        return ptr > it.ptr;
    }


};



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
