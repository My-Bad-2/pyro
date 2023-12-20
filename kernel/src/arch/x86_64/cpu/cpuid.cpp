#include <cpu/cpuid.hpp>
#include <cstdint>
#include "utils/misc.hpp"

namespace cpu_id {
namespace {
/// \brief Template function to calculate the extended leaf for CPUID.
/// \tparam base The base value used to calculate the extended leaf.
/// \return The extended leaf value.
template <uint32_t base>
constexpr uint32_t extended_leaf() {
    return 0x80000000 + base;
};

/// \brief Function to extract the base family from the EAX register.
/// \param eax The EAX register value.
/// \return The base family extracted from the EAX register.
inline uint8_t base_family_from_eax(uint32_t eax) {
    return utils::extract_bits<11, 8, uint8_t>(eax);
}

/// \brief Function to call the CPUID instruction and retrieve the result in registers.
/// \param leaf The CPUID leaf to query.
/// \param subleaf The subleaf for the CPUID instruction (default is 0).
/// \return The registers containing the CPUID result.
registers call_cpu_id(uint32_t leaf, uint32_t subleaf = 0) {
    registers result;

    asm volatile(
        "cpuid"
        : "=a"(result.reg[registers::EAX]), "=b"(result.reg[registers::EBX]),
          "=c"(result.reg[registers::ECX]), "=d"(result.reg[registers::EDX])
        : "a"(leaf), "c"(subleaf));

    return result;
}
}  // namespace

/// \brief Reads the manufacturer information using CPUID instructions.
///
/// This function calls the CPUID instruction twice, once with the input value 0
/// and once with the extended leaf value 0. The results are used to construct
/// a manufacturer_info object, which is then returned.
///
/// \return A manufacturer_info object containing information about the CPU manufacturer.
manufacturer_info cpuid::read_manufacturer_info() const {
    return manufacturer_info(call_cpu_id(0), call_cpu_id(extended_leaf<0>()));
}

/// \brief Reads various CPU features using CPUID instructions.
///
/// This function calls the CPUID instruction multiple times with different input values
/// and extended leaf values to retrieve information about CPU features. The results
/// are used to construct a features object, which is then returned.
///
/// \return A features object containing information about various CPU features.
features cpuid::read_features() const {
    return features(
        call_cpu_id(1),                   // CPUID with input value 1
        call_cpu_id(6),                   // CPUID with input value 6
        call_cpu_id(7),                   // CPUID with input value 7
        call_cpu_id(extended_leaf<1>()),  // CPUID with extended leaf value 1
        call_cpu_id(extended_leaf<7>())   // CPUID with extended leaf value 7
    );
}

/// \brief Reads the processor ID using CPUID instruction.
///
/// This function calls the CPUID instruction with the input value 1 to retrieve
/// information about the processor ID. The result is used to construct a
/// processor_id object, which is then returned.
///
/// \return A processor_id object containing information about the processor.
processor_id cpuid::read_processor_id() const {
    return processor_id(call_cpu_id(1));  // CPUID with input value 1
}

/// \brief Constructor for the manufacturer_info class.
///
/// \param leaf0 The registers containing information from CPUID with input value 0.
/// \param leaf8_0 The registers containing information from CPUID with extended leaf value 0 of input value 8.
manufacturer_info::manufacturer_info(registers leaf0, registers leaf8_0)
    : leaf0_(leaf0), leaf8_0_(leaf8_0) {
    // Constructor implementation
}

/// \brief Gets the CPU manufacturer based on the stored information.
///
/// This function retrieves the manufacturer information stored in the object
/// and returns the corresponding manufacturer enumerator.
///
/// \return The CPU manufacturer enumerator (INTEL, AMD, or OTHER).
manufacturer_info::manufacturer manufacturer_info::get_manufacturer() const {
    char buffer[manufacturer_length + 1] = {0};
    manufacturer_id(buffer);

    if (strcmp("GenuineIntel", buffer) == 0) {
        return INTEL;
    } else if (strcmp("AuthenticAMD", buffer) == 0) {
        return AMD;
    }

    return OTHER;
}

/// \brief Retrieves the CPU manufacturer identifier as a string.
///
/// This function constructs a string representation of the CPU manufacturer identifier
/// based on the information stored in the object and copies it to the provided buffer.
///
/// \param buffer A pointer to the buffer where the manufacturer identifier string will be stored.
void manufacturer_info::manufacturer_id(char* buffer) const {
    union {
        uint32_t regs[3];  ///< Array to hold CPUID register values.
        char string
            [13];  ///< String representation of the manufacturer identifier.
    } translator = {
        {
            leaf0_.ebx(),
            leaf0_.edx(),
            leaf0_.ecx(),
        },
    };

    // Copy the manufacturer identifier string to the provided buffer.
    memcpy(buffer, translator.string, manufacturer_length);
}

/// \brief Retrieves the highest CPUID leaf value supported by the processor.
///
/// This function returns the value of the highest CPUID leaf supported by the processor,
/// which is obtained from the stored information in the object.
///
/// \return The highest CPUID leaf value.
size_t manufacturer_info::highest_cpuid_leaf() const {
    return leaf0_.eax();
}

/// \brief Retrieves the highest extended CPUID leaf value supported by the processor.
///
/// This function returns the value of the highest extended CPUID leaf supported by the processor,
/// which is obtained from the stored information in the object.
///
/// \return The highest extended CPUID leaf value.
size_t manufacturer_info::highest_extended_cpuid_leaf() const {
    return leaf8_0_.eax();
}

/// \brief Constructor for the processor_id class.
///
/// \param regs The registers containing information about the processor.
processor_id::processor_id(registers regs) : registers_(regs) {
    // Constructor implementation
}

/// \brief Retrieves the stepping value of the processor.
///
/// This function returns the low-order 4 bits of the EAX register, which
/// represent the stepping value of the processor.
///
/// \return The processor stepping value.
uint8_t processor_id::stepping() const {
    return registers_.eax() & 0xF;
}

/// \brief Retrieves the model value of the processor.
///
/// This function calculates and returns the model value of the processor
/// based on the information stored in the object.
///
/// \return The processor model value.
uint16_t processor_id::model() const {
    const uint8_t base = utils::extract_bits<7, 4, uint8_t>(registers_.eax());
    const uint8_t extended =
        utils::extract_bits<19, 16, uint8_t>(registers_.eax());

    const uint8_t family = base_family_from_eax(registers_.eax());

    if (family == 0xF || family == 0x6) {
        return static_cast<uint16_t>((extended << 4) + base);
    }

    return base;
}

/// \brief Retrieves the family value of the processor.
///
/// This function calculates and returns the family value of the processor
/// based on the information stored in the object.
///
/// \return The processor family value.
uint16_t processor_id::family() const {
    const uint8_t base = base_family_from_eax(registers_.eax());
    const uint8_t extended =
        utils::extract_bits<27, 20, uint8_t>(registers_.eax());

    if (base == 0xF) {
        return static_cast<uint16_t>(base + extended);
    }

    return base;
}

/// \brief Retrieves the processor signature.
///
/// This function returns the value of the EBX register, which represents
/// the processor signature.
///
/// \return The processor signature.
uint32_t processor_id::signature() const {
    return registers_.ebx();
}

/// \brief Retrieves the local Advanced Programmable Interrupt Controller (APIC) ID of the processor.
///
/// This function extracts and returns the bits 31 to 24 from the EBX register,
/// which represent the local APIC ID of the processor.
///
/// \return The local APIC ID of the processor.
uint8_t processor_id::local_apic_id() const {
    return utils::extract_bits<31, 24, uint8_t>(registers_.ebx());
}

/// \brief Constructor for the features class.
///
/// \param leaf1 Information from CPUID with input value 1.
/// \param leaf6 Information from CPUID with input value 6.
/// \param leaf7 Information from CPUID with input value 7.
/// \param leaf8_01 Information from CPUID with extended leaf value 0 of input value 8.
/// \param leaf8_07 Information from CPUID with extended leaf value 7 of input value 8.
features::features(registers leaf1, registers leaf6, registers leaf7,
                   registers leaf8_01, registers leaf8_07)
    : leaves_{leaf1, leaf6, leaf7, leaf8_01, leaf8_07} {
    // Constructor implementation
}

/// \brief Retrieves the maximum number of logical processors in a package.
///
/// This function extracts and returns the bits 23 to 16 from the EBX register
/// of CPUID with input value 1, representing the maximum number of logical processors
/// in a single processor package.
///
/// \return The maximum number of logical processors in a package.
uint8_t features::max_logical_processors_in_package() const {
    return utils::extract_bits<23, 16, uint8_t>(leaves_[LEAF1].ebx());
}
}  // namespace cpu_id