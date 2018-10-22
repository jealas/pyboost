#include <Python.h>

#include <boost/python.hpp>
#include <boost/crc.hpp>

#include "pyboost/exceptions.h"


namespace
{
template <class CrcType, bool IsBasic>
struct register_custom_crc_methods;

template <class CrcType>
struct register_custom_crc_methods<CrcType, true> {
    void operator()(boost::python::class_<CrcType> &crc_class) {
        using value_type = typename CrcType::value_type;

        crc_class
            .def(boost::python::init<value_type, value_type, value_type, bool, bool>((
                boost::python::arg("truncated_polynominal"),
                boost::python::arg("initial_remainder") = 0,
                boost::python::arg("final_xor_value") = 0,
                boost::python::arg("reflect_input") = false,
                boost::python::arg("reflect_remainder") = false)))
            .def("process_bit", &CrcType::process_bit)
            .def("process_bits", &CrcType::process_bits);
    }
};

template <class CrcType>
struct register_custom_crc_methods<CrcType, false> {
    void operator()(boost::python::class_<CrcType> &crc_class) {
        crc_class
            .def(boost::python::init<typename CrcType::value_type>((boost::python::arg("init_rem") = CrcType::initial_remainder)));
    }
};

template <class CrcType, bool IsBasic>
void register_crc(char const * const name)
{
    using namespace boost::python;

    using crc_type = CrcType;

    auto crc_class = class_<crc_type>(name, no_init);

    register_custom_crc_methods<CrcType, IsBasic>{}(crc_class);

    crc_class
        .def("get_truncated_polynominal", &crc_type::get_truncated_polynominal)
        .def("get_initial_remainder", &crc_type::get_initial_remainder)
        .def("get_final_xor_value", &crc_type::get_final_xor_value)
        .def("get_reflect_input", &crc_type::get_reflect_input)
        .def("get_reflect_remainder", &crc_type::get_reflect_remainder)
        .def("get_interim_remainder", &crc_type::get_interim_remainder)
        .def("reset", static_cast<void (crc_type::*)(typename crc_type::value_type)>(&crc_type::reset))
        .def("reset", +[](crc_type &crc) {
         crc.reset();
        })
        .def("process_byte", &crc_type::process_byte)
        .def("process_bytes", +[](crc_type &crc, object obj, const std::size_t byte_count) {
         if (!PyMemoryView_Check(obj.ptr())) {
             throw pyboost::type_error{"Cannot process_bytes, expected memoryview-like object."};

         }

         const auto memory_view = object{handle<>{PyMemoryView_FromObject(obj.ptr())}};
         const auto buffer = PyMemoryView_GET_BUFFER(memory_view.ptr());

         if (!PyBuffer_IsContiguous(buffer, 'C')) {
             throw pyboost::type_error{"Expected contiguous memoryview-like object."};
         }

         crc.process_bytes(buffer->buf, buffer->len);
        })
        .def("checksum", &crc_type::checksum);
}
}



BOOST_PYTHON_MODULE(_pyboost_crc) {
    using namespace boost::python;

    register_crc<boost::crc_16_type, false>("OptimalCrc16");
    register_crc<boost::crc_ccitt_type, false>("OptimalCrcCcitt");
    register_crc<boost::crc_xmodem_type, false>("OptimalCrcXmodem");
    register_crc<boost::crc_32_type, false>("OptimalCrc32");

    register_crc<boost::crc_basic<16>, true>("BasicCrc16");
    register_crc<boost::crc_basic<32>, true>("BasicCrc32");
}
