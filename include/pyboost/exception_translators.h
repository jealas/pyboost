#ifndef PYBOOST_EXCEPTION_TRANSLATOR_H
#define PYBOOST_EXCEPTION_TRANSLATOR_H

#include <Python.h>

#include <boost/python/exception_translator.hpp>

#include "exceptions.h"


namespace pyboost {

inline void translate(runtime_error const& e)
{
    PyErr_SetString(PyExc_RuntimeError, e.what());
}

inline void translate(exception const& e)
{
  PyErr_SetString(PyExc_Exception, e.what());
}

inline void translate(arithmetic_error const& e)
{
  PyErr_SetString(PyExc_ArithmeticError, e.what());
}

inline void translate(assertion_error const& e)
{
  PyErr_SetString(PyExc_AssertionError, e.what());
}

inline void translate(attribute_error const& e)
{
  PyErr_SetString(PyExc_AttributeError, e.what());
}

inline void translate(blocking_io_error const& e)
{
  PyErr_SetString(PyExc_BlockingIOError, e.what());
}

inline void translate(broken_pipe_error const& e)
{
  PyErr_SetString(PyExc_BrokenPipeError, e.what());
}

inline void translate(buffer_error const& e)
{
  PyErr_SetString(PyExc_BufferError, e.what());
}

inline void translate(child_process_error const& e)
{
  PyErr_SetString(PyExc_ChildProcessError, e.what());
}

inline void translate(connection_aborted_error const& e)
{
  PyErr_SetString(PyExc_ConnectionAbortedError, e.what());
}

inline void translate(connection_error const& e)
{
  PyErr_SetString(PyExc_ConnectionError, e.what());
}

inline void translate(connection_refused_error const& e)
{
  PyErr_SetString(PyExc_ConnectionRefusedError, e.what());
}

inline void translate(connection_reset_error const& e)
{
  PyErr_SetString(PyExc_ConnectionResetError, e.what());
}

inline void translate(eof_error const& e)
{
  PyErr_SetString(PyExc_EOFError, e.what());
}

inline void translate(file_exists_error const& e)
{
  PyErr_SetString(PyExc_FileExistsError, e.what());
}

inline void translate(file_not_found_error const& e)
{
  PyErr_SetString(PyExc_FileNotFoundError, e.what());
}

inline void translate(floating_point_error const& e)
{
  PyErr_SetString(PyExc_FloatingPointError, e.what());
}

inline void translate(generator_exit const& e)
{
  PyErr_SetString(PyExc_GeneratorExit, e.what());
}

inline void translate(import_error const& e)
{
  PyErr_SetString(PyExc_ImportError, e.what());
}

inline void translate(indentation_error const& e)
{
  PyErr_SetString(PyExc_IndentationError, e.what());
}

inline void translate(index_error const& e)
{
  PyErr_SetString(PyExc_IndexError, e.what());
}

inline void translate(interrupted_error const& e)
{
  PyErr_SetString(PyExc_InterruptedError, e.what());
}

inline void translate(is_a_directory_error const& e)
{
  PyErr_SetString(PyExc_IsADirectoryError, e.what());
}

inline void translate(key_error const& e)
{
  PyErr_SetString(PyExc_KeyError, e.what());
}

inline void translate(keyboard_interrupt const& e)
{
  PyErr_SetString(PyExc_KeyboardInterrupt, e.what());
}

inline void translate(lookup_error const& e)
{
  PyErr_SetString(PyExc_LookupError, e.what());
}

inline void translate(memory_error const& e)
{
  PyErr_SetString(PyExc_MemoryError, e.what());
}

inline void translate(module_not_found_error const& e)
{
  PyErr_SetString(PyExc_ModuleNotFoundError, e.what());
}

inline void translate(name_error const& e)
{
  PyErr_SetString(PyExc_NameError, e.what());
}

inline void translate(not_a_directory_error const& e)
{
  PyErr_SetString(PyExc_NotADirectoryError, e.what());
}

inline void translate(not_implemented_error const& e)
{
  PyErr_SetString(PyExc_NotImplementedError, e.what());
}

inline void translate(os_error const& e)
{
  PyErr_SetString(PyExc_OSError, e.what());
}

inline void translate(overflow_error const& e)
{
  PyErr_SetString(PyExc_OverflowError, e.what());
}

inline void translate(permission_error const& e)
{
  PyErr_SetString(PyExc_PermissionError, e.what());
}

inline void translate(process_lookup_error const& e)
{
  PyErr_SetString(PyExc_ProcessLookupError, e.what());
}

inline void translate(recursion_error const& e)
{
  PyErr_SetString(PyExc_RecursionError, e.what());
}

inline void translate(reference_error const& e)
{
  PyErr_SetString(PyExc_ReferenceError, e.what());
}

inline void translate(stop_async_iteration const& e)
{
  PyErr_SetString(PyExc_StopAsyncIteration, e.what());
}

inline void translate(stop_iteration const& e)
{
  PyErr_SetString(PyExc_StopIteration, e.what());
}

inline void translate(syntax_error const& e)
{
  PyErr_SetString(PyExc_SyntaxError, e.what());
}

inline void translate(system_error const& e)
{
  PyErr_SetString(PyExc_SystemError, e.what());
}

inline void translate(system_exit const& e)
{
  PyErr_SetString(PyExc_SystemExit, e.what());
}

inline void translate(tab_error const& e)
{
  PyErr_SetString(PyExc_TabError, e.what());
}

inline void translate(timeout_error const& e)
{
  PyErr_SetString(PyExc_TimeoutError, e.what());
}

inline void translate(type_error const& e)
{
  PyErr_SetString(PyExc_TypeError, e.what());
}

inline void translate(unbound_local_error const& e)
{
  PyErr_SetString(PyExc_UnboundLocalError, e.what());
}

inline void translate(unicode_decode_error const& e)
{
  PyErr_SetString(PyExc_UnicodeDecodeError, e.what());
}

inline void translate(unicode_encode_error const& e)
{
  PyErr_SetString(PyExc_UnicodeEncodeError, e.what());
}

inline void translate(unicode_error const& e)
{
  PyErr_SetString(PyExc_UnicodeError, e.what());
}

inline void translate(unicode_translate_error const& e)
{
  PyErr_SetString(PyExc_UnicodeTranslateError, e.what());
}

inline void translate(value_error const& e)
{
  PyErr_SetString(PyExc_ValueError, e.what());
}

inline void translate(zero_division_error const& e)
{
  PyErr_SetString(PyExc_ZeroDivisionError, e.what());
}

}

#endif //PYBOOST_EXCEPTION_TRANSLATOR_H
