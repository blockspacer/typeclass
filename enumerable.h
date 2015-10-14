#pragma once

#include "typeclass.h"
#include "reverse_enumerator.h"

namespace enumerable
{
    struct singlepass
    {
        template <typename T, typename SinglePassEnumerator>
        static SinglePassEnumerator enumerate(T&);
    };

    struct forward
    {
        template <typename T, typename ForwardEnumerator>
        static ForwardEnumerator enumerate_forward(T&);
    };

    struct bidirectional
    {
        template <typename T, typename BidirectionalEnumerator>
        static BidirectionalEnumerator enumerate_bidirectional(T&);
    };

    template <typename Enumerable>
    auto enumerate_bidirectional(Enumerable& e) ->
        decltype(instance<Enumerable, bidirectional>::enumerate_bidirectional(e))
    {
        static_assert(is_instanceof<Enumerable, bidirectional>::value, "Not a bidirectional enumerable");
        return instance<Enumerable, bidirectional>::enumerate_bidirectional(e);
    }

    struct finite
    {
        template <typename T, typename Size>
        static Size size(T&);
    };

    struct reverse
    {
        // Returns a bidirectional enumerator that goes in reverse.
        template <typename T>
        static auto enumerate_reverse(T& t) 
            -> decltype(enumerator::make_reverse_enumerator(enumerable::last(t)))
        {
            static_assert(always_false<decltype(enumerator::make_reverse_enumerator(enumerable::last(t)))>::value, "qwer");
            return enumerator::make_reverse_enumerator(enumerable::last(t));
        }

        // Returns a bidirectional enumerator that traverses the "normal" 
        // direction, but starts at the end.
        template <typename T, typename BidirectionalEnumerator>
        BidirectionalEnumerator last(T&);
    };

    template <typename Enumerable>
    auto enumerate(Enumerable& e) ->
        decltype(instance<Enumerable, singlepass>::enumerate(e))
    {
        static_assert(is_instanceof<Enumerable, singlepass>::value, "Not an enumerable");
        return instance<Enumerable, singlepass>::enumerate(e);
    }

    template <typename Enumerable>
    auto enumerate_forward(Enumerable& e) ->
        decltype(instance<Enumerable, forward>::enumerate_forward(e))
    {
        static_assert(is_instanceof<Enumerable, forward>::value, "Not a forward enumerable");
        return instance<Enumerable, forward>::enumerate_forward(e);
    }

    template <typename T>
    auto size(T& t) ->
        decltype(instance<T, finite>::size(t))
    {
        static_assert(is_instanceof<T, finite>::value, "Not a finite enumerable");
        return instance<T, finite>::size(t);
    }

    template <typename T>
    auto enumerate_reverse(T& t) ->
        decltype(instance<T, reverse>::enumerate_reverse(t))
    {
        static_assert(is_instanceof<T, reverse>::value, "Not a reverse enumerable");
        return instance<T, reverse>::enumerate_reverse(t);
    }

    template <typename T>
    auto last(T& t) ->
        decltype(instance<T, reverse>::last(t))
    {
        static_assert(is_instanceof<T, reverse>::value, "Not a reverse enumerable");
        return instance<T, reverse>::last(t);
    }
}

// Trivial implementations of singlepass implementation of forward enumerable
template <typename Type>
struct typeclass::instance<
    Type,
    enumerable::singlepass,
    typename std::enable_if<typeclass::is_instanceof<Type, enumerable::forward>::value>::type
>
{
    template <typename T>
    static auto enumerate(T& t) -> decltype(instance<Type, enumerable::forward>::enumerate_forward(t))
    {
        return instance<Type, enumerable::forward>::enumerate_forward(t);
    }
};

// Trivial implementations of singlepass implementation of bidirectional enumerable
template <typename Type>
struct typeclass::instance<
    Type,
    enumerable::singlepass,
    typename std::enable_if<typeclass::is_instanceof<Type, enumerable::bidirectional>::value>::type
>
{
    template <typename T>
    static auto enumerate(T& t) -> decltype(instance<Type, enumerable::bidirectional>::enumerate_bidirectional(t))
    {
        return instance<Type, enumerable::bidirectional>::enumerate_bidirectional(t);
    }
};