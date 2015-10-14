#pragma once

#include "enumerator.h"
#include <vector>

template <typename Vector, typename T>
struct vector_enumerator
{
    Vector& vector;
    size_t index;

    vector_enumerator(Vector& v) : vector(v), index(0) {}
    vector_enumerator(Vector& v, size_t i) : vector(v), index(i) {}
};

template <typename V, typename T>
struct typeclass::instance<vector_enumerator<V, T>, enumerator::readable > : enumerator::readable
{
    static T get(vector_enumerator<V, T>& e) { return e.vector[e.index]; }
};

template <typename T>
struct typeclass::instance<vector_enumerator<std::vector<T>, T>, enumerator::writeable > : enumerator::writeable
{
    static void set(vector_enumerator<std::vector<T>, T>& e, T const& v) { e.vector[e.index] = v; }
};

template <typename V, typename T>
struct typeclass::instance<vector_enumerator<V, T>, enumerator::incrementable > : enumerator::incrementable
{
    static void next(vector_enumerator<V, T>& e) { ++e.index; }
    static bool done(vector_enumerator<V, T> const& e) { return e.index >= e.vector.size(); }
};

template <typename V, typename T>
struct typeclass::instance<vector_enumerator<V, T>, enumerator::decrementable > : enumerator::decrementable
{
    static void prev(vector_enumerator<V, T>& e) { --e.index; }
    static bool prev_done(vector_enumerator<V, T> const& e)
    {
        typedef decltype(e.index) index_type;
        return e.index == ((index_type)0) - 1;
    }
};
