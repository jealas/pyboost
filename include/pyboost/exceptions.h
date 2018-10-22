#ifndef PYBOOST_EXCEPTIONS_H
#define PYBOOST_EXCEPTIONS_H

#include <stdexcept>


namespace pyboost {

struct exception : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct arithmetic_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct assertion_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct attribute_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct blocking_io_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct broken_pipe_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct buffer_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct child_process_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct connection_aborted_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct connection_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct connection_refused_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct connection_reset_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct eof_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct file_exists_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct file_not_found_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct floating_point_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct generator_exit : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct import_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct indentation_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct index_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct interrupted_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct is_a_directory_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct key_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct keyboard_interrupt : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct lookup_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct memory_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct module_not_found_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct name_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct not_a_directory_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct not_implemented_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct os_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct overflow_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct permission_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct process_lookup_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct recursion_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct reference_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct runtime_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct stop_async_iteration : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct stop_iteration : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct syntax_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct system_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct system_exit : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct tab_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct timeout_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct type_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct unbound_local_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct unicode_decode_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct unicode_encode_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct unicode_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct unicode_translate_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct value_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct zero_division_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

}

#endif //PYBOOST_EXCEPTIONS_H
