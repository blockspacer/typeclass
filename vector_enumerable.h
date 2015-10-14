#pragma once

#include "typeclass.h"
#include "enumerable.h"
#include "vector_enumerator.h"

template <typename T>
struct typeclass::instance<std::vector<T>, enumerable::bidirectional > : enumerable::bidirectional
{
    template <typename Vector>
    static vector_enumerator<Vector, T> enumerate_bidirectional(Vector& v)
    {
        return vector_enumerator<Vector, T>(v);
    }
};

template <typename T>
struct typeclass::instance<std::vector<T>, enumerable::finite > : enumerable::finite
{
    template <typename T>
    static typename std::vector<T>::size_type size(std::vector<T> const& v)
    {
        return v.size();
    }
};

template <typename T>
struct typeclass::instance<std::vector<T>, enumerable::reverse> : enumerable::reverse
{
    template <typename Vector>
    static vector_enumerator<Vector, T> last(Vector& v)
    {
        return vector_enumerator<Vector, T>(v, v.size() - 1);
    }
};