#ifndef KERNEL_INCLUDE_ARCH_X86_64_REGISTERS_H_
#define KERNEL_INCLUDE_ARCH_X86_64_REGISTERS_H_

// clang-format off

///
/// \defgroup X86_CR0 Control Register 0 (CR0) Bits
/// \{
///
#define X86_CR0_PE   0x00000001 ///< Protection Enable
#define X86_CR0_MP   0x00000002 ///< Monitor Coprocessor
#define X86_CR0_EM   0x00000004 ///< Emulation
#define X86_CR0_TS   0x00000008 ///< Task Switched
#define X86_CR0_ET   0x00000010 ///< Extension Type
#define X86_CR0_NE   0x00000020 ///< Numeric Error
#define X86_CR0_WP   0x00010000 ///< Write Protect
#define X86_CR0_NW   0x20000000 ///< Not Write-Through
#define X86_CR0_CD   0x40000000 ///< Cache Disable
#define X86_CR0_PG   0x80000000 ///< Paging
/// \}

///
/// \defgroup X86_CR4 Control Register 4 (CR4) Bits
/// \{
///
#define X86_CR4_PAE        0x00000020 ///< Page Address Extension
#define X86_CR4_PGE        0x00000080 ///< Page Global Enable
#define X86_CR4_OSFXSR     0x00000200 ///< OS supports FXSAVE and FXRSTOR instructions
#define X86_CR4_OSXMMEXPT  0x00000400 ///< OS supports unmasked SIMD floating-point exceptions
#define X86_CR4_UMIP       0x00000800 ///< User-Mode Instruction Prevention
#define X86_CR4_VMXE       0x00002000 ///< Virtual Machine Extensions Enable
#define X86_CR4_FSGSBASE   0x00010000 ///< FS/GS BASE access instructions
#define X86_CR4_PCIDE      0x00020000 ///< PCID Enable
#define X86_CR4_OSXSAVE    0x00040000 ///< XSAVE and Processor Extended States Enable
#define X86_CR4_SMEP       0x00100000 ///< Supervisor Mode Execution Protection
#define X86_CR4_SMAP       0x00200000 ///< Supervisor Mode Access Prevention
#define X86_CR4_PKE        0x00400000 ///< Protection Key Enable
/// \}

///
/// \defgroup X86_EFER Extended Feature Enable Register (EFER) Bits
/// \{
///
#define X86_EFER_SCE  0x00000001 ///< System Call Extensions
#define X86_EFER_LME  0x00000100 ///< Long Mode Enable
#define X86_EFER_LMA  0x00000400 ///< Long Mode Active
#define X86_EFER_NXE  0x00000800 ///< No-Execute Enable
/// \}

///
/// \defgroup X86_MSR Model-Specific Registers (MSR)
/// \{
///
#define X86_MSR_IA32_PLATFORM_ID 0x00000017 ///< IA32 Platform ID MSR
#define X86_MSR_IA32_APIC_BASE 0x0000001b ///< IA32 APIC Base MSR
#define X86_MSR_IA32_TSC_ADJUST 0x0000003b ///< IA32 TSC Adjust MSR
#define X86_MSR_IA32_SPEC_CTRL 0x00000048 ///< IA32 Speculation Control MSR
#define X86_SPEC_CTRL_IBRS (1ull << 0) ///< Speculation Control MSR Bits
/// \}

///
/// \defgroup X86_SPEC_CTRL Speculation Control MSR Bits
/// \{
///
#define X86_SPEC_CTRL_STIBP (1ull << 1)
#define X86_SPEC_CTRL_SSBD (1ull << 2)
/// \}

///
/// \defgroup X86_MSR Model-Specific Registers (MSR) - Continued
/// \{
///

/// MSR for SMI Count
#define X86_MSR_SMI_COUNT 0x00000034

/// IA32 Prediction Command MSR
#define X86_MSR_IA32_PRED_CMD 0x00000049

/// IA32 BIOS Update Trigger MSR
#define X86_MSR_IA32_BIOS_UPDT_TRIG 0x00000079u

/// IA32 BIOS Signature ID MSR
#define X86_MSR_IA32_BIOS_SIGN_ID 0x0000008b

/// IA32 MTRR Capability MSR
#define X86_MSR_IA32_MTRRCAP 0x000000fe

/// IA32 Architecture Capabilities MSR
#define X86_MSR_IA32_ARCH_CAPABILITIES 0x0000010a

/// Architecture Capabilities Bits
#define X86_ARCH_CAPABILITIES_RDCL_NO (1ull << 0)
#define X86_ARCH_CAPABILITIES_IBRS_ALL (1ull << 1)
#define X86_ARCH_CAPABILITIES_RSBA (1ull << 2)
#define X86_ARCH_CAPABILITIES_SSB_NO (1ull << 4)
#define X86_ARCH_CAPABILITIES_MDS_NO (1ull << 5)
#define X86_ARCH_CAPABILITIES_TSX_CTRL (1ull << 7)
#define X86_ARCH_CAPABILITIES_TAA_NO (1ull << 8)

/// IA32 Flush Command MSR
#define X86_MSR_IA32_FLUSH_CMD 0x0000010b

/// IA32 TSX Control MSR
#define X86_MSR_IA32_TSX_CTRL 0x00000122

/// TSX Control Bits
#define X86_TSX_CTRL_RTM_DISABLE (1ull << 0)
#define X86_TSX_CTRL_CPUID_DISABLE (1ull << 1)

/// IA32 SYSENTER CS, ESP, EIP MSRs
#define X86_MSR_IA32_SYSENTER_CS 0x00000174
#define X86_MSR_IA32_SYSENTER_ESP 0x00000175
#define X86_MSR_IA32_SYSENTER_EIP 0x00000176

/// IA32 MCG (Machine Check Global) MSRs
#define X86_MSR_IA32_MCG_CAP 0x00000179
#define X86_MSR_IA32_MCG_STATUS 0x0000017a

/// IA32 Miscellaneous Enable MSR
#define X86_MSR_IA32_MISC_ENABLE 0x000001a0

/// Miscellaneous Enable Bits
#define X86_MSR_IA32_MISC_ENABLE_TURBO_DISABLE (1ull << 38)

/// IA32 Temperature Target MSR
#define X86_MSR_IA32_TEMPERATURE_TARGET 0x000001a2

/// IA32 Energy Performance Bias MSR
#define X86_MSR_IA32_ENERGY_PERF_BIAS 0x000001b0

/// IA32 MTRR (Memory Type Range Registers) MSRs
#define X86_MSR_IA32_MTRR_PHYSBASE0 0x00000200
#define X86_MSR_IA32_MTRR_PHYSMASK0 0x00000201
#define X86_MSR_IA32_MTRR_PHYSMASK9 0x00000213
#define X86_MSR_IA32_MTRR_DEF_TYPE 0x000002ff
#define X86_MSR_IA32_MTRR_FIX64K_00000 0x00000250
#define X86_MSR_IA32_MTRR_FIX16K_80000 0x00000258
#define X86_MSR_IA32_MTRR_FIX16K_A0000 0x00000259
#define X86_MSR_IA32_MTRR_FIX4K_C0000 0x00000268
#define X86_MSR_IA32_MTRR_FIX4K_F8000 0x0000026f

/// IA32 PAT (Page Attribute Table) MSR
#define X86_MSR_IA32_PAT 0x00000277

/// IA32 TSC Deadline MSR
#define X86_MSR_IA32_TSC_DEADLINE 0x000006e0
/// \}

///
/// \defgroup X86_MSR_IA32_X2APIC x2APIC MSRs
/// \{
///

/// x2APIC Local APIC ID MSR
#define X86_MSR_IA32_X2APIC_APICID 0x00000802

/// x2APIC Version MSR
#define X86_MSR_IA32_X2APIC_VERSION 0x00000803

/// x2APIC Task Priority Register MSR
#define X86_MSR_IA32_X2APIC_TPR 0x00000808

/// x2APIC Processor Priority Register MSR
#define X86_MSR_IA32_X2APIC_PPR 0x0000080A

/// x2APIC End of Interrupt MSR
#define X86_MSR_IA32_X2APIC_EOI 0x0000080B

/// x2APIC Logical Destination Register MSR
#define X86_MSR_IA32_X2APIC_LDR 0x0000080D

/// x2APIC Spurious Interrupt Vector Register MSR
#define X86_MSR_IA32_X2APIC_SIVR 0x0000080F

/// x2APIC Interrupt Status Registers
#define X86_MSR_IA32_X2APIC_ISR0 0x00000810
#define X86_MSR_IA32_X2APIC_ISR1 0x00000811
#define X86_MSR_IA32_X2APIC_ISR2 0x00000812
#define X86_MSR_IA32_X2APIC_ISR3 0x00000813
#define X86_MSR_IA32_X2APIC_ISR4 0x00000814
#define X86_MSR_IA32_X2APIC_ISR5 0x00000815
#define X86_MSR_IA32_X2APIC_ISR6 0x00000816
#define X86_MSR_IA32_X2APIC_ISR7 0x00000817

/// x2APIC Timer Registers
#define X86_MSR_IA32_X2APIC_TMR0 0x00000818
#define X86_MSR_IA32_X2APIC_TMR1 0x00000819
#define X86_MSR_IA32_X2APIC_TMR2 0x0000081A
#define X86_MSR_IA32_X2APIC_TMR3 0x0000081B
#define X86_MSR_IA32_X2APIC_TMR4 0x0000081C
#define X86_MSR_IA32_X2APIC_TMR5 0x0000081D
#define X86_MSR_IA32_X2APIC_TMR6 0x0000081E
#define X86_MSR_IA32_X2APIC_TMR7 0x0000081F

/// x2APIC Interrupt Request Registers
#define X86_MSR_IA32_X2APIC_IRR0 0x00000820
#define X86_MSR_IA32_X2APIC_IRR1 0x00000821
#define X86_MSR_IA32_X2APIC_IRR2 0x00000822
#define X86_MSR_IA32_X2APIC_IRR3 0x00000823
#define X86_MSR_IA32_X2APIC_IRR4 0x00000824
#define X86_MSR_IA32_X2APIC_IRR5 0x00000825
#define X86_MSR_IA32_X2APIC_IRR6 0x00000826
#define X86_MSR_IA32_X2APIC_IRR7 0x00000827

/// x2APIC Error Status Register
#define X86_MSR_IA32_X2APIC_ESR 0x00000828

/// x2APIC LVT (Local Vector Table) Configuration Registers
#define X86_MSR_IA32_X2APIC_LVT_CMCI 0x0000082F
#define X86_MSR_IA32_X2APIC_ICR 0x00000830
#define X86_MSR_IA32_X2APIC_LVT_TIMER 0x00000832
#define X86_MSR_IA32_X2APIC_LVT_THERMAL 0x00000833
#define X86_MSR_IA32_X2APIC_LVT_PMI 0x00000834
#define X86_MSR_IA32_X2APIC_LVT_LINT0 0x00000835
#define X86_MSR_IA32_X2APIC_LVT_LINT1 0x00000836
#define X86_MSR_IA32_X2APIC_LVT_ERROR 0x00000837

/// x2APIC Initial and Current Count Registers
#define X86_MSR_IA32_X2APIC_INIT_COUNT 0x00000838
#define X86_MSR_IA32_X2APIC_CUR_COUNT 0x00000839

/// x2APIC Divisor Configuration Register
#define X86_MSR_IA32_X2APIC_DIV_CONF 0x0000083E

/// x2APIC Self-IPI Register
#define X86_MSR_IA32_X2APIC_SELF_IPI 0x0000083F
/// \}

///
/// \defgroup X86_MSR_RAPL Power Management MSRs
/// \{
///

/// Power Unit MSR
#define X86_MSR_RAPL_POWER_UNIT 0x00000606

/// Package Power Limit MSR
#define X86_MSR_PKG_POWER_LIMIT 0x00000610

/// Package Energy Status MSR
#define X86_MSR_PKG_ENERGY_STATUS 0x00000611

/// Package Power Info MSR
#define X86_MSR_PKG_POWER_INFO 0x00000614

/// DRAM Power Limit MSR
#define X86_MSR_DRAM_POWER_LIMIT 0x00000618

/// DRAM Energy Status MSR
#define X86_MSR_DRAM_ENERGY_STATUS 0x00000619

/// Power Plane 0 (PP0) Power Limit MSR
#define X86_MSR_PP0_POWER_LIMIT 0x00000638

/// Power Plane 0 (PP0) Energy Status MSR
#define X86_MSR_PP0_ENERGY_STATUS 0x00000639

/// Power Plane 1 (PP1) Power Limit MSR
#define X86_MSR_PP1_POWER_LIMIT 0x00000640

/// Power Plane 1 (PP1) Energy Status MSR
#define X86_MSR_PP1_ENERGY_STATUS 0x00000641

/// Platform Energy Counter MSR
#define X86_MSR_PLATFORM_ENERGY_COUNTER 0x0000064d

/// Processor Performance (P-STATE) MSR
#define X86_MSR_PPERF 0x0000064e

/// Performance Limit Reasons MSR
#define X86_MSR_PERF_LIMIT_REASONS 0x0000064f

/// Graphics Performance Limit Reasons MSR
#define X86_MSR_GFX_PERF_LIMIT_REASONS 0x000006b0

/// Platform Power Limit MSR
#define X86_MSR_PLATFORM_POWER_LIMIT 0x0000065c
/// \}

///
/// \defgroup X86_MSR_AMD AMD-specific MSRs
/// \{
///

/// AMD F10h Decode Configuration MSR
#define X86_MSR_AMD_F10_DE_CFG 0xc0011029

/// AMD F10h Decode Configuration MSR - LFENCE_SERIALIZE Bit
#define X86_MSR_AMD_F10_DE_CFG_LFENCE_SERIALIZE (1 << 1)
/// \}

///
/// \defgroup X86_MSR_AMD AMD-specific MSRs (Continued)
/// \{
///

/// AMD LS_CFG MSR
#define X86_MSR_AMD_LS_CFG 0xc0011020

/// AMD LS_CFG MSR - F15H Speculative Store Bypass Disable (SSBD)
#define X86_AMD_LS_CFG_F15H_SSBD (1ull << 54)

/// AMD LS_CFG MSR - F16H Speculative Store Bypass Disable (SSBD)
#define X86_AMD_LS_CFG_F16H_SSBD (1ull << 33)

/// AMD LS_CFG MSR - F17H Speculative Store Bypass Disable (SSBD)
#define X86_AMD_LS_CFG_F17H_SSBD (1ull << 10)

/// AMD K7 HWCR MSR
#define X86_MSR_K7_HWCR 0xc0010015

/// AMD K7 HWCR MSR - CPB Disable Bit
#define X86_MSR_K7_HWCR_CPB_DISABLE (1ull << 25)

/// KVM PV EOI Enable MSR
#define X86_MSR_KVM_PV_EOI_EN 0x4b564d04

/// KVM PV EOI Enable MSR - Enable Bit
#define X86_MSR_KVM_PV_EOI_EN_ENABLE (1ull << 0)
/// \}

///
/// \defgroup X86_FLAGS x86 CPU Flags
/// \{
///

/// x86 Flags - Carry Flag
#define X86_FLAGS_CF (1 << 0)

/// x86 Flags - Parity Flag
#define X86_FLAGS_PF (1 << 2)

/// x86 Flags - Adjust Flag
#define X86_FLAGS_AF (1 << 4)

/// x86 Flags - Zero Flag
#define X86_FLAGS_ZF (1 << 6)

/// x86 Flags - Sign Flag
#define X86_FLAGS_SF (1 << 7)

/// x86 Flags - Trap Flag
#define X86_FLAGS_TF (1 << 8)

/// x86 Flags - Interrupt Enable Flag
#define X86_FLAGS_IF (1 << 9)

/// x86 Flags - Direction Flag
#define X86_FLAGS_DF (1 << 10)

/// x86 Flags - Overflow Flag
#define X86_FLAGS_OF (1 << 11)

/// x86 Flags - Status Mask
#define X86_FLAGS_STATUS_MASK (0xfff)

/// x86 Flags - I/O Privilege Level Mask
#define X86_FLAGS_IOPL_MASK (3 << 12)

/// x86 Flags - I/O Privilege Level Shift
#define X86_FLAGS_IOPL_SHIFT (12)

/// x86 Flags - Nested Task Flag
#define X86_FLAGS_NT (1 << 14)

/// x86 Flags - Resume Flag
#define X86_FLAGS_RF (1 << 16)

/// x86 Flags - Virtual 8086 Mode Flag
#define X86_FLAGS_VM (1 << 17)

/// x86 Flags - Alignment Check/Access Control Flag
#define X86_FLAGS_AC (1 << 18)

/// x86 Flags - Virtual Interrupt Flag
#define X86_FLAGS_VIF (1 << 19)

/// x86 Flags - Virtual Interrupt Pending Flag
#define X86_FLAGS_VIP (1 << 20)

/// x86 Flags - ID Flag
#define X86_FLAGS_ID (1 << 21)

/// x86 Flags - Reserved Ones (fixed bits)
#define X86_FLAGS_RESERVED_ONES 0x2

/// x86 Flags - Reserved Bits
#define X86_FLAGS_RESERVED 0xffc0802a

/// x86 Flags - User Flags Mask
#define X86_FLAGS_USER                                           \
    (X86_FLAGS_CF | X86_FLAGS_PF | X86_FLAGS_AF | X86_FLAGS_ZF | \
     X86_FLAGS_SF | X86_FLAGS_TF | X86_FLAGS_DF | X86_FLAGS_OF | \
     X86_FLAGS_NT | X86_FLAGS_AC | X86_FLAGS_ID)
/// \}

///
/// \defgroup X86_DR6 x86 Debug Register 6 (DR6)
/// \{
///

/// x86 DR6 - Breakpoint 0 Trigger
#define X86_DR6_B0 (1ul << 0)

/// x86 DR6 - Breakpoint 1 Trigger
#define X86_DR6_B1 (1ul << 1)

/// x86 DR6 - Breakpoint 2 Trigger
#define X86_DR6_B2 (1ul << 2)

/// x86 DR6 - Breakpoint 3 Trigger
#define X86_DR6_B3 (1ul << 3)

/// x86 DR6 - Debug Register Reserved Bit
#define X86_DR6_BD (1ul << 13)

/// x86 DR6 - Single-Step Flag
#define X86_DR6_BS (1ul << 14)

/// x86 DR6 - Task Switch Flag
#define X86_DR6_BT (1ul << 15)

/// x86 DR6 - User-Accessible Bits Mask
#define X86_DR6_USER_MASK                                             \
    (X86_DR6_B0 | X86_DR6_B1 | X86_DR6_B2 | X86_DR6_B3 | X86_DR6_BD | \
     X86_DR6_BS | X86_DR6_BT)

/// x86 DR6 - Reserved Bits Mask
#define X86_DR6_MASK (0xffff0ff0ul)
/// \}

///
/// \defgroup X86_DR7 x86 Debug Register 7 (DR7)
/// \{
///

/// x86 DR7 - Local Breakpoint 0 (L0)
#define X86_DR7_L0 (1ul << 0)

/// x86 DR7 - Global Breakpoint 0 (G0)
#define X86_DR7_G0 (1ul << 1)

/// x86 DR7 - Local Breakpoint 1 (L1)
#define X86_DR7_L1 (1ul << 2)

/// x86 DR7 - Global Breakpoint 1 (G1)
#define X86_DR7_G1 (1ul << 3)

/// x86 DR7 - Local Breakpoint 2 (L2)
#define X86_DR7_L2 (1ul << 4)

/// x86 DR7 - Global Breakpoint 2 (G2)
#define X86_DR7_G2 (1ul << 5)

/// x86 DR7 - Local Breakpoint 3 (L3)
#define X86_DR7_L3 (1ul << 6)

/// x86 DR7 - Global Breakpoint 3 (G3)
#define X86_DR7_G3 (1ul << 7)

/// x86 DR7 - Local Exact Breakpoint Enable (LE)
#define X86_DR7_LE (1ul << 8)

/// x86 DR7 - Global Exact Breakpoint Enable (GE)
#define X86_DR7_GE (1ul << 9)

/// x86 DR7 - General Detect Enable (GD)
#define X86_DR7_GD (1ul << 13)

/// x86 DR7 - Read/Write for Breakpoint 0 (Bits 16-17)
#define X86_DR7_RW0 (3ul << 16)

/// x86 DR7 - Length for Breakpoint 0 (Bits 18-19)
#define X86_DR7_LEN0 (3ul << 18)

/// x86 DR7 - Read/Write for Breakpoint 1 (Bits 20-21)
#define X86_DR7_RW1 (3ul << 20)

/// x86 DR7 - Length for Breakpoint 1 (Bits 22-23)
#define X86_DR7_LEN1 (3ul << 22)

/// x86 DR7 - Read/Write for Breakpoint 2 (Bits 24-25)
#define X86_DR7_RW2 (3ul << 24)

/// x86 DR7 - Length for Breakpoint 2 (Bits 26-27)
#define X86_DR7_LEN2 (3ul << 26)

/// x86 DR7 - Read/Write for Breakpoint 3 (Bits 28-29)
#define X86_DR7_RW3 (3ul << 28)

/// x86 DR7 - Length for Breakpoint 3 (Bits 30-31)
#define X86_DR7_LEN3 (3ul << 30)

/// x86 DR7 - User-Accessible Bits Mask
#define X86_DR7_USER_MASK                                                    \
    (X86_DR7_L0 | X86_DR7_G0 | X86_DR7_L1 | X86_DR7_G1 | X86_DR7_L2 |        \
     X86_DR7_G2 | X86_DR7_L3 | X86_DR7_G3 | X86_DR7_RW0 | X86_DR7_LEN0 |     \
     X86_DR7_RW1 | X86_DR7_LEN1 | X86_DR7_RW2 | X86_DR7_LEN2 | X86_DR7_RW3 | \
     X86_DR7_LEN3)

/// x86 DR7 - Mask for Reserved Bits
#define X86_DR7_MASK ((1ul << 10) | X86_DR7_LE | X86_DR7_GE)
/// \}

// clang-format off

#endif
