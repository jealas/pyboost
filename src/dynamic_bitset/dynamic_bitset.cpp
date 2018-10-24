#include <cstdint>

#include <boost/python.hpp>
#include <boost/dynamic_bitset.hpp>

#include "pyboost/exceptions.h"
#include "pyboost/allocator.h"
#include "pyboost/string.h"


namespace {

template <class Block>
void register_dynamic_bitset(char const * const name) {
    using namespace boost::python;

    using dynamic_bitset = boost::dynamic_bitset<Block, pyboost::allocator<Block>>;
    using size_type = typename dynamic_bitset::size_type;

    class_<dynamic_bitset>(name, init<std::size_t, unsigned long>((arg("name"), arg("value") = 0)))
            .def("resize", &dynamic_bitset::resize, (arg("num_bits"), arg("value") = false))
            .def("clear", &dynamic_bitset::clear)
            .def("pop_back", +[](dynamic_bitset &bitset) {
                if (bitset.empty()) {
                    throw pyboost::index_error{"cannot pop_back from an empty dynamic bitset."};
                }

                bitset.pop_back();
            })
            .def("push_back", &dynamic_bitset::push_back)
            .def("append", static_cast<void (dynamic_bitset::*)(Block)>(&dynamic_bitset::append))
            .def("__iand__", +[](dynamic_bitset &bitset, dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot &= bitsets with different sizes."};
                }

                bitset &= other;
            })
            .def("__ior__", +[](dynamic_bitset &bitset, dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot |= bitsets with different sizes."};
                }

                bitset |= other;
            })
            .def("__ixor__", +[](dynamic_bitset &bitset, dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot ^= bitsets with different sizes."};
                }

                bitset ^= other;
            })
            .def("__isub__", +[](dynamic_bitset &bitset, dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot -= bitsets with different sizes."};
                }

                bitset -= other;
            })
            .def(self <<= size_type())
            .def(self >>= size_type())
            .def(self << size_type())
            .def(self >> size_type())
            .def("set", +[](dynamic_bitset& bitset) { bitset.set(); })
            .def("flip", +[](dynamic_bitset& bitset){ bitset.flip(); })
            .def(~self)
            .def("reset", +[](dynamic_bitset& bitset){ bitset.reset(); })
            .def("set", +[](dynamic_bitset& bitset, const size_type n, const bool val) { bitset.set(n, val); }, (arg("n"), arg("val") = true))
            .def("reset", +[](dynamic_bitset& bitset, size_type n){ bitset.reset(n); })
            .def("flip", +[](dynamic_bitset& bitset, size_type n){ bitset.flip(n); })
            .def("size", &dynamic_bitset::size)
            .def("num_blocks", &dynamic_bitset::num_blocks)
            .def("max_size", &dynamic_bitset::max_size)
            .def("empty", &dynamic_bitset::empty)
            .def("capacity", &dynamic_bitset::capacity)
            .def("reserve", &dynamic_bitset::reserve)
            .def("shrink_to_fit", &dynamic_bitset::shrink_to_fit)
            .def("count", &dynamic_bitset::count)
            .def("all", &dynamic_bitset::all)
            .def("any", &dynamic_bitset::any)
            .def("none", &dynamic_bitset::none)
            .def("test", +[](const dynamic_bitset &bitset, const size_type n) {
                if (n >= bitset.size()) {
                    throw pyboost::index_error{"bitset index out of range."};
                }

                return bitset.test(n);
            })
            .def("test_set", +[](dynamic_bitset &bitset, const size_type n, const bool value) {
                if (n >= bitset.size()) {
                    throw pyboost::index_error{"bitset index out of range."};
                }

                return bitset.test_set(n, value);

            }, (arg("n"), arg("val") = true))
            .def("__getitem__", +[](const dynamic_bitset &bitset, const size_type n) -> bool {
                if (n >= bitset.size()) {
                    throw pyboost::index_error{"bitset index out of range."};
                }

                return bitset[n];
            })
            .def("__setitem__", +[](dynamic_bitset &bitset, const size_type n, const bool value) {
                if (n >= bitset.size()) {
                    throw pyboost::index_error{"bitset index out of range."};
                }

                bitset[n] = value;
            })
            .def("to_ulong", +[](const dynamic_bitset &bitset) {
                try {
                    return bitset.to_ulong();
                }
                catch (const std::overflow_error oe) {
                    throw pyboost::overflow_error{oe.what()};
                }
            })
            .def("is_subset_of", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot check is_subset_of for bitsets of different sizes."};
                }

                return bitset.is_subset_of(other);
            })
            .def("is_proper_subset_of", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot check is_proper_subset_of for bitsets of different sizes."};
                }

                return bitset.is_proper_subset_of(other);
            })
            .def("intersects", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot check intersects for bitsets of different sizes."};
                }

                return bitset.intersects(other);
            })
            .def("find_first", &dynamic_bitset::find_first)
            .def("find_next", &dynamic_bitset::find_next)
            .def(self == self)
            .def(self != self)
            .def(self < self)
            .def(self > self)
            .def(self <= self)
            .def(self >= self)
            .def("__and__", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot & bitsets of different sizes."};
                }

                return bitset & other;
            })
            .def("__or__", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot | bitsets of different sizes."};
                }

                return bitset | other;
            })
            .def("__xor__", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot ^ bitsets of different sizes."};
                }

                return bitset ^ other;
            })
            .def("__sub__", +[](const dynamic_bitset &bitset, const dynamic_bitset &other) {
                if (bitset.size() != other.size()) {
                    throw pyboost::value_error{"cannot - bitsets of different sizes."};
                }

                return bitset - other;
            })
            .def("__str__", +[](const dynamic_bitset &bitset) {
                pyboost::string str;
                boost::to_string(bitset, str);

                return str;
            })
            ;
}

}

BOOST_PYTHON_MODULE(_pyboost_dynamic_bitset) {
    using namespace boost::python;

    register_dynamic_bitset<std::uint8_t>("DynamicBitset8");
    register_dynamic_bitset<std::uint16_t>("DynamicBitset16");
    register_dynamic_bitset<std::uint32_t>("DynamicBitset32");
    register_dynamic_bitset<std::uint64_t>("DynamicBitset64");
}
