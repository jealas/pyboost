#include <type_traits>

#include <boost/python.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/mpl/int.hpp>
#include <boost/make_shared.hpp>

#include "pyboost/exceptions.h"
#include "pyboost/allocator.h"
#include "pyboost/string.h"


namespace {
    template<unsigned MinBits = 0,
            unsigned MaxBits = 0,
            boost::multiprecision::cpp_integer_type SignType = boost::multiprecision::signed_magnitude,
            boost::multiprecision::cpp_int_check_type Checked = boost::multiprecision::unchecked,
            class Allocator = pyboost::allocator<boost::multiprecision::limb_type>>
    using custom_cpp_int = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, boost::multiprecision::et_off>;

    template <class>
    struct get_precision;

    template<unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator>
    struct get_precision<custom_cpp_int<MinBits, MaxBits, SignType, Checked, Allocator>> {
        static constexpr auto min_bits = MinBits;
        static constexpr auto max_bits = MaxBits;

        static constexpr bool is_fixed_precision() {
            return min_bits != 0 && max_bits != 0;
        }
    };

    template <class CppInt, bool IsFixedPrecision>
    struct register_custom_cpp_precision_int_methods;

    template <class CppInt>
    struct register_custom_cpp_precision_int_methods<CppInt, false> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
        }
    };

    template <class CppInt>
    struct register_custom_cpp_precision_int_methods<CppInt, true> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
            cpp_int_class
                .def("num_bits", +[]() {
                    static_assert(get_precision<CppInt>::min_bits == get_precision<CppInt>::max_bits, "MinBits must be equal to MaxBits.");

                    return get_precision<CppInt>::max_bits;
                })
                .staticmethod("num_bits")
                ;
        }
    };

    template<class CppInt, bool IsSigned, bool IsChecked>
    struct register_custom_cpp_fixed_int_methods;

    template<class CppInt>
    struct register_custom_cpp_fixed_int_methods<CppInt, false, false> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
            using namespace boost::python;

            cpp_int_class
                .def(self += self)
                .def(self -= self)
                .def(self *= self)
                .def(self /= self)
                .def(self %= self)
                .def(self &= self)
                .def(self |= self)
                .def(self ^= self)
                .def("__ilshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def("__irshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def(self % self)
                .def(self & self)
                .def(self | self)
                .def(self ^ self)
                .def("__lshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def("__rshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def(+self)
                .def(self + self)
                .def(self - self)
                .def(self * self)
                .def(self / self)
                ;
        }
    };

    template<class CppInt>
    struct register_custom_cpp_fixed_int_methods<CppInt, false, true> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
            using namespace boost::python;

            cpp_int_class
                    ;
        }
    };

    template<class CppInt>
    struct register_custom_cpp_fixed_int_methods<CppInt, true, false> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
            using namespace boost::python;

            cpp_int_class
                    .def(self += self)
                    .def(self -= self)
                    .def(self *= self)
                    .def(self /= self)
                    .def(self %= self)
                    .def(self &= self)
                    .def(self |= self)
                    .def(self ^= self)
                    .def("__ilshift__", +[](CppInt &i, const long_ n) {
                        // TODO: This needs conversion from long_ -> self
                    })
                    .def("__irshift__", +[](CppInt &i, const long_ n) {
                        // TODO: This needs conversion from long_ -> self
                    })
                    .def(self % self)
                    .def(self & self)
                    .def(self | self)
                    .def(self ^ self)
                    .def("__lshift__", +[](CppInt &i, const long_ n) {
                        // TODO: This needs conversion from long_ -> self
                    })
                    .def("__rshift__", +[](CppInt &i, const long_ n) {
                        // TODO: This needs conversion from long_ -> self
                    })
                    .def(+self)
                    .def(-self)
                    .def(self + self)
                    .def(self - self)
                    .def(self * self)
                    .def(self / self)
                    ;
        }
    };

    template<class CppInt>
    struct register_custom_cpp_fixed_int_methods<CppInt, true, true> {
        void operator()(boost::python::class_<CppInt> &cpp_int_class) {
            using namespace boost::python;

            cpp_int_class
                .def("__iadd__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i += other;
                    }
                    catch (const std::overflow_error &oe) {
                        throw pyboost::overflow_error{oe.what()};
                    }
                }, return_internal_reference<>())
                .def("__isub__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i -= other;
                    }
                    catch (const std::overflow_error &e) {
                        throw pyboost::overflow_error{e.what()};
                    }
                }, return_internal_reference<>())
                .def("__imul__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i *= other;
                    }
                    catch (const std::exception &e) {
                        throw pyboost::exception{e.what()};
                    }
                }, return_internal_reference<>())
                .def("__idiv__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i /= other;
                    }
                    catch (const std::overflow_error &oe) {
                        throw pyboost::zero_division_error{oe.what()};
                    }
                }, return_internal_reference<>())
                .def("__imod__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i %= other;
                    }
                    catch (const std::exception &e) {
                        throw pyboost::exception{e.what()};
                    }
                }, return_internal_reference<>())
                .def("__iand__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i &= other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                }, return_internal_reference<>())
                .def("__ior__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i |= other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                }, return_internal_reference<>())
                .def("__ixor__", +[](CppInt &i, const CppInt &other) -> CppInt& {
                    try {
                        return i ^= other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                }, return_internal_reference<>())
                .def("__ilshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def("__irshift__", +[](CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def("__mod__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i % other;
                    }
                    catch (const std::exception &e) {
                        throw pyboost::exception{e.what()};
                    }
                })
                .def("__and__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i & other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                })
                .def("__or__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i | other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                })
                .def("__xor__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i ^ other;
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                })
                .def("__lshift__", +[](const CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def("__rshift__", +[](const CppInt &i, const long_ n) {
                    // TODO: This needs conversion from long_ -> self
                })
                .def(+self)
                .def(-self)
                .def("__add__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i + other;
                    }
                    catch (const std::overflow_error &oe) {
                        throw pyboost::overflow_error{oe.what()};
                    }
                })
                .def("__sub__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i - other;
                    }
                    catch (const std::exception &e) {
                        throw pyboost::exception{e.what()};
                    }
                })
                .def("__mul__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i * other;
                    }
                    catch (const std::overflow_error &oe) {
                        throw pyboost::exception{oe.what()};
                    }
                })
                .def("__div__", +[](const CppInt &i, const CppInt &other) {
                    try {
                        return i / other;
                    }
                    catch (const std::overflow_error &oe) {
                        throw pyboost::zero_division_error{oe.what()};
                    }
                })
                ;
        }
    };

    template <class>
    struct is_signed;

    template<unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator>
    struct is_signed<custom_cpp_int<MinBits, MaxBits, SignType, Checked, Allocator>>
            : std::integral_constant<bool, SignType == boost::multiprecision::signed_magnitude> {
    };


    template<class CppInt>
    void register_cpp_int(char const *const name) {
        using namespace boost::python;

        auto cpp_int_class = class_<CppInt>(name, init<>())
                .def("__init__", make_constructor(+[](const boost::python::str value) {
                    try {
                        return boost::make_shared<CppInt>(extract<char const *>(value));
                    }
                    catch (const std::range_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                    catch (const std::runtime_error &re) {
                        throw pyboost::value_error{re.what()};
                    }
                }))
                .def("is_zero", &CppInt::is_zero)
                .def("sign", &CppInt::sign)
                .def("__bool__", &CppInt::operator bool)
                .def("__str__", +[](const CppInt& i) {
                    // TODO: Figure out how to return a pyboost::string
                    return i.str();
                })
                .def(self == self)
                .def(self != self)
                .def(self < self)
                .def(self > self)
                .def(self <= self)
                .def(self >= self)
                ;

        constexpr bool is_checked = CppInt::backend_type::checked_type::value == boost::multiprecision::checked;
        register_custom_cpp_fixed_int_methods<CppInt, is_signed<CppInt>::value, is_checked>{}(cpp_int_class);
        register_custom_cpp_precision_int_methods<CppInt, get_precision<CppInt>::is_fixed_precision()>{}(cpp_int_class);
    }

}


BOOST_PYTHON_MODULE (_pyboost_multiprecision) {
    using namespace boost::multiprecision;

//    register_cpp_int<custom_cpp_int<>>("CppInt");
//    register_cpp_int<>("CppRationalBackend");
//    register_cpp_int<>("CppIntRational");

    // Fixed precision unsigned types:
    register_cpp_int<custom_cpp_int<128, 128, unsigned_magnitude, unchecked, void>>("UInt128");
    register_cpp_int<custom_cpp_int<256, 256, unsigned_magnitude, unchecked, void>>("UInt256");
    register_cpp_int<custom_cpp_int<512, 512, unsigned_magnitude, unchecked, void>>("UInt512");
    register_cpp_int<custom_cpp_int<1024, 1024, unsigned_magnitude, unchecked, void>>("UInt1024");

    // Fixed precision signed types:
    register_cpp_int<custom_cpp_int<128, 128, signed_magnitude, unchecked, void>>("Int128");
    register_cpp_int<custom_cpp_int<256, 256, signed_magnitude, unchecked, void>>("Int256");
    register_cpp_int<custom_cpp_int<512, 512, signed_magnitude, unchecked, void>>("Int512");
    register_cpp_int<custom_cpp_int<1024, 1024, signed_magnitude, unchecked, void>>("Int1024");

    // Over again, but with checking enabled this time:
//    register_cpp_int<custom_cpp_int<0, 0, signed_magnitude, checked>>("CheckedCppInt");
//    register_cpp_int<>("CheckedCppRationalBackend");
//    register_cpp_int<>("CheckedCppRational");

    // Checked fixed precision unsigned types:
    register_cpp_int<custom_cpp_int<128, 128, unsigned_magnitude, checked, void>>("CheckedUInt128");
    register_cpp_int<custom_cpp_int<256, 256, unsigned_magnitude, checked, void>>("CheckedUInt256");
    register_cpp_int<custom_cpp_int<512, 512, unsigned_magnitude, checked, void>>("CheckedUInt512");
    register_cpp_int<custom_cpp_int<1024, 1024, unsigned_magnitude, checked, void>>("CheckedUInt1024");

    // Fixed precision signed types:
    register_cpp_int<custom_cpp_int<128, 128, signed_magnitude, checked, void>>("CheckedInt128");
    register_cpp_int<custom_cpp_int<256, 256, signed_magnitude, checked, void>>("CheckedInt256");
    register_cpp_int<custom_cpp_int<512, 512, signed_magnitude, checked, void>>("CheckedInt512");
    register_cpp_int<custom_cpp_int<1024, 1024, signed_magnitude, checked, void>>("CheckedInt1024");

}
