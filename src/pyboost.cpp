#include <boost/python.hpp>

#include "pyboost/exception_translators.h"
#include "pyboost/string.h"

namespace
{

template <class Exception>
void register_translator() {
    boost::python::register_exception_translator<Exception>(static_cast<void (*)(Exception const& e)>(&pyboost::translate));
}

}


BOOST_PYTHON_MODULE(_pyboost)
{
    using namespace boost::python;

    register_translator<pyboost::exception>();
    register_translator<pyboost::arithmetic_error>();
    register_translator<pyboost::assertion_error>();
    register_translator<pyboost::attribute_error>();
    register_translator<pyboost::blocking_io_error>();
    register_translator<pyboost::broken_pipe_error>();
    register_translator<pyboost::buffer_error>();
    register_translator<pyboost::child_process_error>();
    register_translator<pyboost::connection_aborted_error>();
    register_translator<pyboost::connection_error>();
    register_translator<pyboost::connection_refused_error>();
    register_translator<pyboost::connection_reset_error>();
    register_translator<pyboost::eof_error>();
    register_translator<pyboost::file_exists_error>();
    register_translator<pyboost::file_not_found_error>();
    register_translator<pyboost::floating_point_error>();
    register_translator<pyboost::generator_exit>();
    register_translator<pyboost::import_error>();
    register_translator<pyboost::indentation_error>();
    register_translator<pyboost::index_error>();
    register_translator<pyboost::interrupted_error>();
    register_translator<pyboost::is_a_directory_error>();
    register_translator<pyboost::key_error>();
    register_translator<pyboost::keyboard_interrupt>();
    register_translator<pyboost::lookup_error>();
    register_translator<pyboost::memory_error>();
    register_translator<pyboost::module_not_found_error>();
    register_translator<pyboost::name_error>();
    register_translator<pyboost::not_a_directory_error>();
    register_translator<pyboost::not_implemented_error>();
    register_translator<pyboost::os_error>();
    register_translator<pyboost::overflow_error>();
    register_translator<pyboost::permission_error>();
    register_translator<pyboost::process_lookup_error>();
    register_translator<pyboost::recursion_error>();
    register_translator<pyboost::reference_error>();
    register_translator<pyboost::runtime_error>();
    register_translator<pyboost::stop_async_iteration>();
    register_translator<pyboost::stop_iteration>();
    register_translator<pyboost::syntax_error>();
    register_translator<pyboost::system_error>();
    register_translator<pyboost::system_exit>();
    register_translator<pyboost::tab_error>();
    register_translator<pyboost::timeout_error>();
    register_translator<pyboost::type_error>();
    register_translator<pyboost::unbound_local_error>();
    register_translator<pyboost::unicode_decode_error>();
    register_translator<pyboost::unicode_encode_error>();
    register_translator<pyboost::unicode_error>();
    register_translator<pyboost::unicode_translate_error>();
    register_translator<pyboost::value_error>();
    register_translator<pyboost::zero_division_error>();

    to_python_converter<pyboost::string, pyboost::string_to_str>();
}