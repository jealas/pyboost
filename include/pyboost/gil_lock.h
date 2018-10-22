#ifndef PYBOOST_GIL_LOCK_H
#define PYBOOST_GIL_LOCK_H

#include <Python.h>


namespace pyboost {

struct gil_lock
{
    void lock() const {
        Py_END_ALLOW_THREADS
    }

    void unlock() const {
        Py_BEGIN_ALLOW_THREADS
    }
};

} // namespace pyboost

#endif //PYBOOST_GIL_LOCK_H
