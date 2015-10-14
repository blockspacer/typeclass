#pragma once

#include "typeclass.h"

namespace enumerator
{
    struct readable
    {
        template <typename Enumerator, typename T>
        static T get(Enumerator const&);
    };

    struct writeable
    {
        template <typename Enumerator, typename T>
        static void set(Enumerator&, T const&);
    };

    struct incrementable
    {
        template <typename Enumerator>
        static void next(Enumerator&);

        template <typename Enumerator>
        static bool done(Enumerator const&);
    };

    struct decrementable
    {
        template <typename T>
        static void prev(T&);

        template <typename T>
        static bool prev_done(T const&);
    };

    typedef typeclass::product<incrementable, decrementable> bidirectional;

    template <typename T>
    auto get(T& e) ->
        decltype(instance<T, readable>::get(e))
    {
        static_assert(is_instanceof<T, readable>::value, "Not a Readable");
        return instance<T, readable>::get(e);
    }

    template <typename T, typename Value>
    void set(T& e, Value const& v)
    {
        static_assert(is_instanceof<T, writeable>::value, "Not a Writeable");
        instance<T, writeable>::set(e, v);
    }

    template <typename T>
    auto next(T& e) ->
        decltype(instance<T, incrementable>::next(e))
    {
        static_assert(is_instanceof<T, incrementable>::value, "Not an Incrementable");
        return instance<T, incrementable>::next(e);
    }

    template <typename T>
    auto done(T const& e) ->
        decltype(instance<T, incrementable>::done(e))
    {
        static_assert(is_instanceof<T, incrementable>::value, "Not an Incrementable");
        return instance<T, incrementable>::done(e);
    }

    template <typename T>
    auto prev(T& e) ->
        decltype(instance<T, decrementable>::prev(e))
    {
        static_assert(is_instanceof<T, decrementable>::value, "Not a Decrementable");
        return instance<T, decrementable>::prev(e);
    }

    template <typename T>
    auto prev_done(T const& e) ->
        decltype(instance<T, decrementable>::prev_done(e))
    {
        static_assert(is_instanceof<T, decrementable>::value, "Not a Decrementable");
        return instance<T, decrementable>::prev_done(e);
    }
}