#pragma once

// Type classes for traversing tree structures.  Concepts here are similar to 
// enumerable concepts, but tailored for tree structures.

namespace traversable
{
    struct singlepass
    {
        template <typename T, typename Traverser>
        Traverser traverse(T& t);
    };

    struct downward
    {
        template <typename T, typename Traverser>
        Traverser traverse_downward(T& t);
    };

    struct vertical
    {
        template <typename T, typename Traverser>
        Traverser traverse_vertical(T& t);
    };
}

namespace traverser
{
    struct downward
    {
        template <typename T>
        void down(T&);

        template <typename T>
        bool is_bottom(const T&);
    };

    struct vertical
    {
        template <typename T>
        void up(T&);

        template <typename T>
        bool is_top(const T&);
    };
}