#ifndef KERNEL_INCLUDE_UTILS_COMMON_H_
#define KERNEL_INCLUDE_UTILS_COMMON_H_

#include <system/compiler.h>

#if defined(__cplusplus)
#define UTILS_NAMESPACE_BEGIN namespace utils {
#define UTILS_NAMESPACE_END }
#else  // defined(__cplusplus)
#define UTILS_NAMESPACE_BEGIN
#define UTILS_NAMESPACE_END
#endif  // defined(__cplusplus)

#endif  // KERNEL_INCLUDE_UTILS_COMMON_H_
