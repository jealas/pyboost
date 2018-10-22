#ifndef PYBOOST_ALLOCATOR_H
#define PYBOOST_ALLOCATOR_H

#include <cstdint>
#include <limits>
#include <new>

#include <Python.h>


namespace pyboost {

    template <class T>
    struct allocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = T const *;
        using reference = T&;
        using const_reference = T const &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        template <class U>
        struct rebind {
            using other = allocator<U>;
        };

        pointer address (reference value) const noexcept {
            return &value;
        }

        const_pointer address (const_reference value) const noexcept {
            return &value;
        }

        allocator() noexcept {
        }

        allocator(const allocator&) noexcept {
        }

        template <class U>
        allocator (const allocator<U>&) noexcept {
        }

        ~allocator() noexcept {
        }

        size_type max_size() const noexcept {
            return std::numeric_limits<std::size_t>::max() / sizeof(T);
        }

        pointer allocate (size_type num, const void* = 0) {
            if (pointer ret = reinterpret_cast<pointer>(PyMem_Malloc(num * sizeof(T)))) {
                return ret;
            }

            throw std::bad_alloc();
        }

        void destroy (pointer p) {
            p->~T();
        }

        void deallocate (pointer p, size_type num) noexcept {
            PyMem_Free(p);
        }
    };

} // namespace pyboost

#endif //PYBOOST_ALLOCATOR_H
