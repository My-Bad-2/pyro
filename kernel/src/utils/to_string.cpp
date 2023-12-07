/**
 * @brief Convert different integer types to a c-style string
 */

#include <stdint.h>
#include <stdio.h>

#include <utils/common.h>
#include <utils/to_string.hpp>

UTILS_NAMESPACE_BEGIN

char* to_string(int value) {
    char* buffer = nullptr;
    sprintf(buffer, "%d", value);
    return buffer;
}

char* to_string(long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%ld", value);
    return buffer;
}

char* to_string(long long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%lld", value);
    return buffer;
}

char* to_string(unsigned int value) {
    char* buffer = nullptr;
    sprintf(buffer, "%u", value);
    return buffer;
}

char* to_string(unsigned long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%lu", value);
    return buffer;
}

char* to_string(unsigned long long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%llu", value);
    return buffer;
}

char* to_string(void* value) {
    return to_string(reinterpret_cast<uintptr_t>(value));
}

UTILS_NAMESPACE_END