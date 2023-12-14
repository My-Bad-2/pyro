#include <system/compiler.h>

#define ATEXIT_MAX_FUNCS 128

__BEGIN_CDECLS

/// \brief Type definition for the architecture-specific unsigned integer.
typedef unsigned int uarch_t;

/// \brief Structure representing an entry in the atexit function table.
struct atexit_func_entry_t {
    void (*destructor_func)(void*);  ///< Pointer to the destructor function.
    void* obj_ptr;                   ///< Pointer to the object.
    void* dso_handle;  ///< Handle to the dynamic shared object (DSO).
};

/// \brief Array to store atexit function entries.
struct atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];

/// \brief Count of atexit function entries.
uarch_t __atexit_func_count = 0;

/// \brief Pointer to the dynamic shared object (DSO).
void* __dso_handle = 0;

/// \brief Register a function to be called at program termination.
///
/// \param f Pointer to the function to be called.
/// \param objptr Pointer to the object.
/// \param dso Pointer to the dynamic shared object (DSO).
/// \return 0 on success, -1 if the maximum number of functions is reached.
int __cxa_atexit(void (*f)(void*), void* objptr, void* dso) {
    if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {
        return -1;
    }

    __atexit_funcs[__atexit_func_count].destructor_func = f;
    __atexit_funcs[__atexit_func_count].obj_ptr = objptr;
    __atexit_funcs[__atexit_func_count].dso_handle = dso;
    __atexit_func_count++;
    return 0;
}

/// \brief Perform cleanup for functions registered with __cxa_atexit.
///
/// \param f If NULL, perform cleanup for all functions; otherwise, perform
///          cleanup for the function specified by f.
void __cxa_finalize(void* f) {
    uarch_t i = __atexit_func_count;

    if (!f) {
        while (i--) {
            if (__atexit_funcs[i].destructor_func) {
                (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
            }
        }

        return;
    }

    while (i--) {
        if (__atexit_funcs[i].destructor_func == f) {
            (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
            __atexit_funcs[i].destructor_func = 0;
        }
    }
}

/// \brief Array of pointers to functions to be called before main().
extern void (*__init_array_start[])();  ///< Start of the initialization array.

/// \brief Array of pointers to functions to be called after main().
extern void (*__init_array_end[])();  ///< End of the initialization array.

/// \brief Initialize the Application Binary Interface (ABI).
///
/// This function is responsible for initializing the ABI, including any
/// necessary setup for the interaction between different binary components.
///
/// \note This function is typically called during the initialization
///       phase of a kernel or similar low-level system software.
void abi_initialize() {
    for (auto ctor = __init_array_start; ctor < __init_array_end; ctor++) {
        (*ctor)();
    }
}

__END_CDECLS