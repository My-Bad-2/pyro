#include <utils/misc.hpp>

namespace utils {
/// \brief Global variable to store the hhdm offset.
///
/// This variable holds the hhdm offset information and is initialized during the
/// initialization process.
uintptr_t hhdm_offset = 0;

/// \brief Initializes the library with the provided boot information.
///
/// This function initializes the library by extracting the hhdm offset from the
/// provided boot information.
///
/// \param bootinfo Pointer to the boot information structure.
void initialize(bootinfo_t* bootinfo) {
    /// Store the hhdm offset from the boot information.
    hhdm_offset = bootinfo->hhdm_offset;
}
}  // namespace utils