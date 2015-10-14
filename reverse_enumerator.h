#pragma once

#include "typeclass.h"
#include "enumerator.h"

// This class implements a wrapper around a bidirectional enumerator that 
// turns it into another bidirectional enumerator that enumerates in reverse.

namespace enumerator
{
    template <typename BidirectionalEnumerator>
    struct reverse_enumerator
    {
        BidirectionalEnumerator bi;

        reverse_enumerator(BidirectionalEnumerator const& e) : bi(e) {}
    };

    template <typename T>
    reverse_enumerator<T> make_reverse_enumerator(T& e)
    {
        return reverse_enumerator<T>(e);
    }
}

template <typename T>
struct typeclass::instance<enumerator::reverse_enumerator<T>, enumerator::incrementable> : enumerator::incrementable
{
    template <typename T>
    static void next(enumerator::reverse_enumerator<T>& e) { return enumerator::prev(e.bi); }

    template <typename T>
    static bool done(enumerator::reverse_enumerator<T> const& e) { return enumerator::prev_done(e.bi); }
};

template <typename T>
struct typeclass::instance<enumerator::reverse_enumerator<T>, enumerator::decrementable> : enumerator::decrementable
{
    template <typename T>
    static void prev(enumerator::reverse_enumerator<T>& e) { return enumerator::next(e.bi); }

    template <typename T>
    static bool prev_done(enumerator::reverse_enumerator<T> const& e) { return enumerator::done(e.bi); }
};

template <typename T>
struct typeclass::instance<enumerator::reverse_enumerator<T>, enumerator::readable> : enumerator::readable
{
    template <typename T>
    static auto get(enumerator::reverse_enumerator<T>& e)
        -> decltype(enumerator::get(e.bi))
    {
        return enumerator::get(e.bi);
    }
};