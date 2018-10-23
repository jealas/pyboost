#ifndef PYBOOST_HASH_OBJECT_H
#define PYBOOST_HASH_OBJECT_H

#include <Python.h>

#include <boost/python.hpp>

#include "pyboost/exceptions.h"


namespace boost {
namespace python {

std::size_t hash_value(const boost::python::object &obj) {
    const auto hash = PyObject_Hash(obj.ptr());
    if (hash == -1) {
        throw pyboost::type_error{"Unable to hash object."};
    }

    return static_cast<std::size_t>(hash);
}

}
}

#endif //PYBOOST_HASH_OBJECT_H
