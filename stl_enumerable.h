#pragma once

// Instances of enumerable and enumerator type classes for STL containers

#include "enumerable.h"

namespace enumerator
{
    template <typename Iterator>
    struct stl_enumerator
    {
        Iterator current;
        Iterator end;
    };

    template <typename Iterator>
    struct stl_bidirectional_enumerator : stl_enumerator<Iterator>
    {
        Iterator start;
    };
}

template <typename Iterator>
struct typeclass::instance<
    enumerator::stl_enumerator<Iterator>, 
    enumerator::incrementable> : enumerator::incrementable
{
    void next(enumerator::stl_enumerator<Iterator>& e) { ++e.current; }
    bool done(enumerator::stl_enumerator<Iterator> const& e) { e.current == e.end; }
};

template <typename Iterator>
struct typeclass::instance<
    enumerator::stl_bidirectional_enumerator<Iterator>, 
    enumerator::decrementable> : enumerator::decrementable
{
    void prev(enumerator::stl_bidirectional_enumerator<Iterator>& e) { --e.current; }
    bool prev_done(enumerator::stl_bidirectional_enumerator<Iterator> const& e) { e.current == e.start; }
};

template <typename Iterator>
struct typeclass::instance<
    enumerator::stl_enumerator<Iterator>,
    enumerator::readable> : enumerator::readable
{
    auto get(stl_enumerator<Iterator> const& iter) 
        -> decltype(*iter)
    {
        return *iter; 
    }
};

template <typename Iterator>
struct typeclass::instance<
    enumerator::stl_enumerator<Iterator>,
    enumerator::writeable> : enumerator::writeable
{
    typedef typename Iterator::value_type value_type;
    void next(enumerator::stl_enumerator<Iterator>& e, value_type const& v) { *e.current = v; }
};