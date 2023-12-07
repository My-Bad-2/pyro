#ifndef KERNEL_INCLUDE_UTILS_TO_STRING_HPP_
#define KERNEL_INCLUDE_UTILS_TO_STRING_HPP_

#include <utils/common.h>

UTILS_NAMESPACE_BEGIN

char* to_string(int value);
char* to_string(long value);
char* to_string(long long value);
char* to_string(unsigned int value);
char* to_string(unsigned long value);
char* to_string(unsigned long long value);
char* to_string(void* value);

UTILS_NAMESPACE_END

#endif  // KERNEL_INCLUDE_UTILS_TO_STRING_HPP_