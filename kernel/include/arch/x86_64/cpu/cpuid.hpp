#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_CPUID_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_CPUID_HPP_

#include <assert.h>
#include <stdint.h>
#include <string.h>

namespace cpu_id {
/// \brief Struct representing x86 registers.
struct registers {
    /// \brief Enumeration of x86 register indices.
    enum {
        EAX = 0,  ///< Index for the 32-bit EAX register.
        EBX = 1,  ///< Index for the 32-bit EBX register.
        ECX = 2,  ///< Index for the 32-bit ECX register.
        EDX = 3,  ///< Index for the 32-bit EDX register.
    };

    uint32_t reg[4];  ///< Array to hold 32-bit values of the registers.

    /// \brief Get the 32-bit value of the EAX register.
    /// \return The 32-bit value of the EAX register.
    inline uint32_t eax() const { return reg[EAX]; }

    /// \brief Get the 32-bit value of the EBX register.
    /// \return The 32-bit value of the EBX register.
    inline uint32_t ebx() const { return reg[EBX]; }

    /// \brief Get the 32-bit value of the ECX register.
    /// \return The 32-bit value of the ECX register.
    inline uint32_t ecx() const { return reg[ECX]; }

    /// \brief Get the 32-bit value of the EDX register.
    /// \return The 32-bit value of the EDX register.
    inline uint32_t edx() const { return reg[EDX]; }
};

/// \brief Template structure representing an array of subleaves with registers.
/// \tparam count The number of subleaves.
template <size_t count>
struct subleaves {
    registers subleaf[count];  ///< Array of registers for each subleaf.
    static constexpr size_t size = count;  ///< Number of subleaves.
};

/// \brief Class representing manufacturer information based on CPUID leaves.
class manufacturer_info {
   public:
    /// \brief Enumeration of possible manufacturers.
    enum manufacturer { INTEL, AMD, OTHER };

    static constexpr size_t manufacturer_length =
        12;  ///< Length of the manufacturer information.

    /// \brief Constructor for the manufacturer_info class.
    /// \param leaf0 The registers from CPUID leaf 0.
    /// \param leaf8_0 The registers from CPUID leaf 8, subleaf 0.
    manufacturer_info(registers leaf0, registers leaf8_0);

    /// \brief Get the manufacturer information.
    /// \return The manufacturer information.
    manufacturer get_manufacturer() const;

    /// \brief Get the manufacturer ID as a string.
    /// \param buffer The buffer to store the manufacturer ID.
    void manufacturer_id(char* buffer) const;

    /// \brief Get the highest CPUID leaf supported.
    /// \return The highest CPUID leaf supported.
    size_t highest_cpuid_leaf() const;

    /// \brief Get the highest extended CPUID leaf supported.
    /// \return The highest extended CPUID leaf supported.
    size_t highest_extended_cpuid_leaf() const;

   private:
    const registers leaf0_;    ///< Registers from CPUID leaf 0.
    const registers leaf8_0_;  ///< Registers from CPUID leaf 8, subleaf 0.
};

/// \brief Class representing processor identification based on CPUID registers.
class processor_id {
   public:
    /// \brief Constructor for the processor_id class.
    /// \param regs The registers containing processor identification information.
    processor_id(registers regs);

    /// \brief Get the stepping value of the processor.
    /// \return The stepping value.
    uint8_t stepping() const;

    /// \brief Get the model number of the processor.
    /// \return The model number.
    uint16_t model() const;

    /// \brief Get the family number of the processor.
    /// \return The family number.
    uint16_t family() const;

    /// \brief Get the processor signature.
    /// \return The processor signature.
    uint32_t signature() const;

    /// \brief Get the local Advanced Programmable Interrupt Controller (APIC) ID.
    /// \return The local APIC ID.
    uint8_t local_apic_id() const;

   private:
    const registers
        registers_;  ///< Registers containing processor identification information.
};

/// \brief Class representing processor features based on CPUID leaves.
class features {
   public:
    /// \brief Enumeration of CPUID leaf indices.
    enum leaf_index {
        LEAF1,
        LEAF6,
        LEAF7,
        LEAF8_01,
        LEAF8_07,
        INVALID_SET = 254,
    };

    /// \brief Structure representing a processor feature.
    struct feature {
        uint8_t leaf = INVALID_SET;  ///< CPUID leaf index.
        uint8_t reg;                 ///< Register index in the leaf.
        uint8_t bit;                 ///< Bit index in the register.
    };

    /// \brief Static constexpr instances of commonly used processor features
    static constexpr feature FPU = {
        LEAF1,
        registers::EDX,
        0,
    };

    static constexpr feature VME = {
        LEAF1,
        registers::EDX,
        1,
    };

    static constexpr feature DE = {
        LEAF1,
        registers::EDX,
        2,
    };

    static constexpr feature PSE = {
        LEAF1,
        registers::EDX,
        3,
    };

    static constexpr feature TSC = {
        LEAF1,
        registers::EDX,
        4,
    };

    static constexpr feature MSR = {
        LEAF1,
        registers::EDX,
        5,
    };

    static constexpr feature PAE = {
        LEAF1,
        registers::EDX,
        6,
    };

    static constexpr feature MCE = {
        LEAF1,
        registers::EDX,
        7,
    };

    static constexpr feature CX8 = {
        LEAF1,
        registers::EDX,
        8,
    };

    static constexpr feature APIC = {
        LEAF1,
        registers::EDX,
        9,
    };

    static constexpr feature SEP = {
        LEAF1,
        registers::EDX,
        11,
    };

    static constexpr feature MTRR = {
        LEAF1,
        registers::EDX,
        12,
    };

    static constexpr feature PGE = {
        LEAF1,
        registers::EDX,
        13,
    };

    static constexpr feature MCA = {
        LEAF1,
        registers::EDX,
        14,
    };

    static constexpr feature CMOV = {
        LEAF1,
        registers::EDX,
        15,
    };

    static constexpr feature PAT = {
        LEAF1,
        registers::EDX,
        16,
    };

    static constexpr feature PSE36 = {
        LEAF1,
        registers::EDX,
        17,
    };

    static constexpr feature PSN = {
        LEAF1,
        registers::EDX,
        18,
    };

    static constexpr feature CLFSH = {
        LEAF1,
        registers::EDX,
        19,
    };

    static constexpr feature DS = {
        LEAF1,
        registers::EDX,
        21,
    };

    static constexpr feature ACPI = {
        LEAF1,
        registers::EDX,
        22,
    };

    static constexpr feature MMX = {
        LEAF1,
        registers::EDX,
        23,
    };

    static constexpr feature FXSR = {
        LEAF1,
        registers::EDX,
        24,
    };

    static constexpr feature SSE = {
        LEAF1,
        registers::EDX,
        25,
    };

    static constexpr feature SSE2 = {
        LEAF1,
        registers::EDX,
        26,
    };

    static constexpr feature SS = {
        LEAF1,
        registers::EDX,
        27,
    };

    static constexpr feature HTT = {
        LEAF1,
        registers::EDX,
        28,
    };

    static constexpr feature TM = {
        LEAF1,
        registers::EDX,
        29,
    };

    static constexpr feature PBE = {
        LEAF1,
        registers::EDX,
        31,
    };

    static constexpr feature SSE3 = {
        LEAF1,
        registers::ECX,
        0,
    };

    static constexpr feature PCLMULQDQ = {
        LEAF1,
        registers::ECX,
        1,
    };

    static constexpr feature DTES64 = {
        LEAF1,
        registers::ECX,
        2,
    };

    static constexpr feature MONITOR = {
        LEAF1,
        registers::ECX,
        3,
    };

    static constexpr feature DS_CPL = {
        LEAF1,
        registers::ECX,
        4,
    };

    static constexpr feature VMX = {
        LEAF1,
        registers::ECX,
        5,
    };

    static constexpr feature SMX = {
        LEAF1,
        registers::ECX,
        6,
    };

    static constexpr feature EST = {
        LEAF1,
        registers::ECX,
        7,
    };

    static constexpr feature TM2 = {
        LEAF1,
        registers::ECX,
        8,
    };

    static constexpr feature SSSE3 = {
        LEAF1,
        registers::ECX,
        9,
    };

    static constexpr feature CNXT_ID = {
        LEAF1,
        registers::ECX,
        10,
    };

    static constexpr feature SDBG = {
        LEAF1,
        registers::ECX,
        11,
    };

    static constexpr feature FMA = {
        LEAF1,
        registers::ECX,
        12,
    };

    static constexpr feature CX16 = {
        LEAF1,
        registers::ECX,
        13,
    };

    static constexpr feature XTPR = {
        LEAF1,
        registers::ECX,
        14,
    };

    static constexpr feature PDCM = {
        LEAF1,
        registers::ECX,
        15,
    };

    static constexpr feature PCID = {
        LEAF1,
        registers::ECX,
        17,
    };

    static constexpr feature DCA = {
        LEAF1,
        registers::ECX,
        18,
    };

    static constexpr feature SSE4_1 = {
        LEAF1,
        registers::ECX,
        19,
    };

    static constexpr feature SSE4_2 = {
        LEAF1,
        registers::ECX,
        20,
    };

    static constexpr feature X2APIC = {
        LEAF1,
        registers::ECX,
        21,
    };

    static constexpr feature MOVBE = {
        LEAF1,
        registers::ECX,
        22,
    };

    static constexpr feature POPCNT = {
        LEAF1,
        registers::ECX,
        23,
    };

    static constexpr feature TSC_DEADLINE = {
        LEAF1,
        registers::ECX,
        24,
    };

    static constexpr feature AES = {
        LEAF1,
        registers::ECX,
        25,
    };

    static constexpr feature XSAVE = {
        LEAF1,
        registers::ECX,
        26,
    };

    static constexpr feature OSXSAVE = {
        LEAF1,
        registers::ECX,
        27,
    };

    static constexpr feature AVX = {
        LEAF1,
        registers::ECX,
        28,
    };

    static constexpr feature F16C = {
        LEAF1,
        registers::ECX,
        29,
    };

    static constexpr feature RDRAND = {
        LEAF1,
        registers::ECX,
        30,
    };

    static constexpr feature TURBO = {
        LEAF6,
        registers::EAX,
        1,
    };

    static constexpr feature HWP = {
        LEAF6,
        registers::EAX,
        7,
    };

    static constexpr feature HWP_PREF = {
        LEAF6,
        registers::EAX,
        10,
    };

    static constexpr feature HWP_PKG = {
        LEAF6,
        registers::EAX,
        11,
    };

    static constexpr feature HWP_REQ_FAST = {
        LEAF6,
        registers::EAX,
        18,
    };

    static constexpr feature MPERFAPERF = {
        LEAF6,
        registers::ECX,
        0,
    };

    static constexpr feature EPB = {
        LEAF6,
        registers::ECX,
        3,
    };

    static constexpr feature FSGSBASE = {
        LEAF7,
        registers::EBX,
        0,
    };

    static constexpr feature SGX = {
        LEAF7,
        registers::EBX,
        2,
    };

    static constexpr feature BMI1 = {
        LEAF7,
        registers::EBX,
        3,
    };

    static constexpr feature HLE = {
        LEAF7,
        registers::EBX,
        4,
    };

    static constexpr feature AVX2 = {
        LEAF7,
        registers::EBX,
        5,
    };

    static constexpr feature SMEP = {
        LEAF7,
        registers::EBX,
        7,
    };

    static constexpr feature BMI2 = {
        LEAF7,
        registers::EBX,
        8,
    };

    static constexpr feature ERMS = {
        LEAF7,
        registers::EBX,
        9,
    };

    static constexpr feature INVPCID = {
        LEAF7,
        registers::EBX,
        10,
    };

    static constexpr feature RTM = {
        LEAF7,
        registers::EBX,
        11,
    };

    static constexpr feature PQM = {
        LEAF7,
        registers::EBX,
        12,
    };

    static constexpr feature PQE = {
        LEAF7,
        registers::EBX,
        15,
    };

    static constexpr feature AVX512F = {
        LEAF7,
        registers::EBX,
        16,
    };

    static constexpr feature AVX512DQ = {
        LEAF7,
        registers::EBX,
        17,
    };

    static constexpr feature RDSEED = {
        LEAF7,
        registers::EBX,
        18,
    };

    static constexpr feature ADX = {
        LEAF7,
        registers::EBX,
        19,
    };

    static constexpr feature SMAP = {
        LEAF7,
        registers::EBX,
        20,
    };

    static constexpr feature AVX512IFMA = {
        LEAF7,
        registers::EBX,
        21,
    };

    static constexpr feature CLWB = {
        LEAF7,
        registers::EBX,
        24,
    };

    static constexpr feature INTEL_PT = {
        LEAF7,
        registers::EBX,
        25,
    };

    static constexpr feature AVX512PF = {
        LEAF7,
        registers::EBX,
        26,
    };

    static constexpr feature AVX512ER = {
        LEAF7,
        registers::EBX,
        27,
    };

    static constexpr feature AVX512CD = {
        LEAF7,
        registers::EBX,
        28,
    };

    static constexpr feature SHA = {
        LEAF7,
        registers::EBX,
        29,
    };

    static constexpr feature AVX512BW = {
        LEAF7,
        registers::EBX,
        30,
    };

    static constexpr feature AVX512VL = {
        LEAF7,
        registers::EBX,
        31,
    };

    static constexpr feature PREFETCHWT1 = {
        LEAF7,
        registers::ECX,
        0,
    };

    static constexpr feature AVX512VBMI = {
        LEAF7,
        registers::ECX,
        1,
    };

    static constexpr feature UMIP = {
        LEAF7,
        registers::ECX,
        2,
    };

    static constexpr feature PKU = {
        LEAF7,
        registers::ECX,
        3,
    };

    static constexpr feature AVX512VBMI2 = {
        LEAF7,
        registers::ECX,
        6,
    };

    static constexpr feature GFNI = {
        LEAF7,
        registers::ECX,
        8,
    };

    static constexpr feature VAES = {
        LEAF7,
        registers::ECX,
        9,
    };

    static constexpr feature VPCLMULQDQ = {
        LEAF7,
        registers::ECX,
        10,
    };

    static constexpr feature AVX512VNNI = {
        LEAF7,
        registers::ECX,
        11,
    };

    static constexpr feature AVX512BITALG = {
        LEAF7,
        registers::ECX,
        12,
    };

    static constexpr feature AVX512VPOPCNTDQ = {
        LEAF7,
        registers::ECX,
        14,
    };

    static constexpr feature RDPID = {
        LEAF7,
        registers::ECX,
        22,
    };

    static constexpr feature AVX512_4VNNIW = {
        LEAF7,
        registers::EDX,
        2,
    };

    static constexpr feature AVX512_4FMAPS = {
        LEAF7,
        registers::EDX,
        3,
    };

    static constexpr feature MD_CLEAR = {
        LEAF7,
        registers::EDX,
        10,
    };

    static constexpr feature CLFLUSH = {
        LEAF7,
        registers::EDX,
        19,
    };

    static constexpr feature ARCH_CAPABILITIES = {
        LEAF7,
        registers::EDX,
        29,
    };

    static constexpr feature LAHF = {
        LEAF8_01,
        registers::ECX,
        0,
    };

    static constexpr feature RDTSCP = {
        LEAF8_01,
        registers::EDX,
        27,
    };

    static constexpr feature PDPE1GB = {
        LEAF8_01,
        registers::EDX,
        26,
    };

    static constexpr feature XD = {
        LEAF8_01,
        registers::EDX,
        20,
    };

    static constexpr feature SYSCALL = {
        LEAF8_01,
        registers::EDX,
        11,
    };

    static constexpr feature CPB = {
        LEAF8_07,
        registers::EDX,
        9,
    };

    /// \brief Constructor for the features class.
    /// \param leaf1 The registers from CPUID leaf 1.
    /// \param leaf6 The registers from CPUID leaf 6.
    /// \param leaf7 The registers from CPUID leaf 7.
    /// \param leaf8_01 The registers from CPUID leaf 8, subleaf 1.
    /// \param leaf8_07 The registers from CPUID leaf 8, subleaf 7.
    features(registers leaf1, registers leaf6, registers leaf7,
             registers leaf8_01, registers leaf8_07);

    /// \brief Check if the processor has a specific feature.
    /// \param feature The feature to check.
    /// \return True if the feature is present, false otherwise.
    inline bool had_feature(feature feature) const {
        assert(feature.leaf < leaf_count && feature.reg <= registers::EDX &&
               feature.bit <= 32);

        return leaves_[feature.leaf].reg[feature.reg] & (1 << feature.bit);
    }

    /// \brief Get the maximum number of logical processors in a package.
    /// \return The maximum number of logical processors in a package.
    uint8_t max_logical_processors_in_package() const;

   private:
    static constexpr size_t leaf_count = 6;  ///< Number of CPUID leaves.

    // clang-format off
    const registers leaves_[leaf_count];  ///< Array of registers from different CPUID leaves.
    // clang-format on
};

/// \brief Interface representing CPUID functionality.
class cpuid {
   public:
    /// \brief Destructor for the cpuid interface.
    ~cpuid() = default;

    /// \brief Function to read manufacturer information.
    /// \return The manufacturer information.
    manufacturer_info read_manufacturer_info() const;

    /// \brief Function to read processor identification.
    /// \return The processor identification.
    processor_id read_processor_id() const;

    /// \brief Function to read processor features.
    /// \return The processor features.
    features read_features() const;
};
}  // namespace cpu_id

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_CPUID_HPP_