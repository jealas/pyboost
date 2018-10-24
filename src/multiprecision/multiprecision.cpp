#include <boost/python.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/mpl/int.hpp>

#include "pyboost/exceptions.h"
#include "pyboost/allocator.h"
#include "pyboost/string.h"


namespace {

    template<class CppInt, bool IsChecked>
    struct register_custom_cpp_int_methods;

    template<class CppInt>
    struct register_custom_cpp_int_methods<CppInt, true> {
        void operator()(boost::python::class_<CppInt> &crc_class) {
        }
    };

    template<class CppInt>
    struct register_custom_cpp_int_methods<CppInt, false> {
        void operator()(boost::python::class_<CppInt> &crc_class) {
        }
    };


    template<class CppInt>
    void register_cpp_int(char const *const name) {
        using namespace boost::python;

        auto cpp_int_class = class_<CppInt>(name, init<>());

        constexpr bool is_checked = CppInt::backend_type::checked_type::value == boost::multiprecision::checked;
        register_custom_cpp_int_methods<CppInt, is_checked>{}(cpp_int_class);
    }

    template<unsigned MinBits = 0,
            unsigned MaxBits = 0,
            boost::multiprecision::cpp_integer_type SignType = boost::multiprecision::signed_magnitude,
            boost::multiprecision::cpp_int_check_type Checked = boost::multiprecision::unchecked,
            class Allocator = pyboost::allocator<boost::multiprecision::limb_type>>
    using custom_cpp_int = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>>;

}


BOOST_PYTHON_MODULE (_pyboost_multiprecision) {
    using namespace boost::multiprecision;

    register_cpp_int<custom_cpp_int<>>("CppInt");
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
    register_cpp_int<custom_cpp_int<0, 0, signed_magnitude, checked>>("CheckedCppInt");
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
