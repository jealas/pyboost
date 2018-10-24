#ifndef PYBOOST_STRING_H
#define PYBOOST_STRING_H

#include <string>

#include <boost/python.hpp>

#include "pyboost/allocator.h"


namespace pyboost {

    using string = std::basic_string<char, std::char_traits<char>, pyboost::allocator<char>>;

    struct string_to_str
    {
        static PyObject* convert(const string &s)
        {
            using namespace boost::python;

            return incref(str(s.data(), s.length()).ptr());
        }
    };
}

#endif //PYBOOST_STRING_H
