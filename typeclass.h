#ifndef TYPECLASS_H
#define TYPECLASS_H

#include <type_traits>

namespace typeclass
{
    template <typename T>
    struct always_false : std::true_type {};

    // Struct used as a tag for detecting whether a type has been specialized for 
    // the instance template.
    struct non_instance {};

    // Specialize this template in order to declare a type "Type" as an instance 
    // for some type class "Class".
    template <typename Type, typename Class, typename sfinae = void>
    struct instance : non_instance {};

    // Meta-function returns true if type "Type" is an instance of type class 
    // "Class".
    template <typename Type, typename Class>
    struct is_instanceof : std::integral_constant < bool,
        !std::is_base_of<non_instance, instance<Type, Class> >::value > {};

    // Type class product composition, e.g., type must meet all the given type classes.
    template <typename... Class>
    struct product {};
    
    template <typename Type, typename Class, typename... Rest>
    struct is_instanceof<Type, product<Class, Rest...> > : std::integral_constant < bool,
        is_instanceof<Type, Class>::value &&
        is_instanceof<Type, product<Rest...> >::value > {};

    template <typename Type, typename Class1, typename Class2>
    struct is_instanceof<Type, product<Class1, Class2> > : std::integral_constant < bool,
        is_instanceof<Type, Class1>::value &&
        is_instanceof<Type, Class2>::value >{};
}

#define typeclass_no_default static_assert(always_false<T>::value, "Method " __FUNCTION__ " not implemented")

#endif