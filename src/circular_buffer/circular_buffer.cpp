#include <string>

#include <boost/python.hpp>
#include <boost/circular_buffer.hpp>

#include "pyboost/allocator.h"
#include "pyboost/exceptions.h"


namespace {

    template <class T>
    void register_circular_buffer(char const * const name) {
        using namespace boost::python;

        using circular_buffer = boost::circular_buffer<T, pyboost::allocator<T>>;

        class_<circular_buffer>(name, init<typename circular_buffer::size_type>())
                .def("clear", &circular_buffer::clear)
                .def("push_back", static_cast<void (circular_buffer::*)(typename circular_buffer::param_value_type)>(&circular_buffer::push_back))
                .def("push_front", static_cast<void (circular_buffer::*)(typename circular_buffer::param_value_type)>(&circular_buffer::push_front))
                .def("pop_back", +[](circular_buffer &buffer) {
                    if (buffer.empty()) {
                        throw pyboost::index_error{"Unable to pop_back because the circular buffer is empty."};
                    }

                    buffer.pop_back();
                })
                .def("pop_front", +[](circular_buffer &buffer) {
                    if (buffer.empty()) {
                        throw pyboost::index_error{"Unable to pop_front because the circular buffer is empty."};
                    }

                    buffer.pop_front();
                })
                .def("front", +[](circular_buffer &buffer) -> T {
                    if (buffer.empty()) {
                        throw pyboost::index_error{"Unable to retrieve front because the circular buffer is empty."};
                    }

                    return buffer.front();
                })
                .def("back", +[](const circular_buffer &buffer) -> T {
                    if (buffer.empty()) {
                        throw pyboost::index_error{"Unable to retrieve back because the circular buffer is empty."};
                    }

                    return buffer.back();
                })
                .def("full", &circular_buffer::full)
                .def("empty", &circular_buffer::empty)
                .def("size", &circular_buffer::size)
                .def("capacity", &circular_buffer::capacity)
                .def("at", +[](const circular_buffer &buffer, const typename circular_buffer::size_type index) -> T {
                    try {
                        return buffer.at(index);
                    }
                    catch (const std::out_of_range &oor) {
                        throw pyboost::index_error{oor.what()};
                    }
                })
                .def("erase_begin", +[](circular_buffer &buffer, const typename circular_buffer::size_type index) {
                    buffer.erase_begin(index);
                })
                .def("erase_end", +[](circular_buffer &buffer, const typename circular_buffer::size_type index) {
                    buffer.erase_end(index);
                })
                .def("__len__", &circular_buffer::size)
                .def("__getitem__", +[](circular_buffer &buffer, const typename circular_buffer::size_type index) -> T {
                    try {
                        return buffer.at(index);
                    }
                    catch (const std::out_of_range &oor) {
                        throw pyboost::index_error{oor.what()};
                    }
                })
                .def("__setitem__", +[](circular_buffer &buffer, const typename circular_buffer::size_type index, T obj) -> T {
                    try {
                        return buffer.at(index) = obj;
                    }
                    catch (const std::out_of_range &oor) {
                        throw pyboost::index_error{oor.what()};
                    }
                })
                .def("__iter__", iterator<circular_buffer>());
    }

}

BOOST_PYTHON_MODULE(_pyboost_circular_buffer)
{
    using namespace boost::python;

    register_circular_buffer<object>("CircularBuffer");
}