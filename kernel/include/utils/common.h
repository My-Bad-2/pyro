#ifndef KERNEL_INCLUDE_UTILS_COMMON_H_
#define KERNEL_INCLUDE_UTILS_COMMON_H_

#include <system/compiler.h>

#ifdef __cplusplus
#define UTILS_NAMESPACE_BEGIN namespace utils {
#define UTILS_NAMESPACE_END }
#else
#error Only include utils in C++ files
#endif

#endif  // KERNEL_INCLUDE_UTILS_COMMON_H_