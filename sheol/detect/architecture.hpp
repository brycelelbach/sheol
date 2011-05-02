////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Most information based on the data collected by predef.sourceforge.net
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_A454A7E1_8A13_4B47_A7E9_69606F1F2B93)
#define SHEOL_A454A7E1_8A13_4B47_A7E9_69606F1F2B93

// Alpha (alpha)
#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
  #define SHEOL_ARCHITECTURE "alpha"
  #define SHEOL_ALPHA_ARCHITECTURE

// x86_64 (x86-64)
#elif defined(__amd64__) || defined(__amd64)    \
   || defined(__x86_64__) || defined(__x86_64)  \
   || defined(_M_X64)
  #define SHEOL_ARCHITECTURE "x86-64"
  #define SHEOL_X86_64_ARCHITECTURE

// ARM (arm)
#elif defined(__arm__) || defined(__thumb__) || defined(_ARM) \
   || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB)
  #define SHEOL_ARCHITECTURE "arm"
  #define SHEOL_ARM_ARCHITECTURE

// ARM v6+ (arm-v6)
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__)   \
   || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) \
   || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_7A__)
  #define SHEOL_ARCHITECTURE "arm-v6"
  #define SHEOL_ARM_V6_ARCHITECTURE

// HP/PA RISC (hppa)
#elif defined(__hppa__) || defined(__hppa)
  #define SHEOL_ARCHITECTURE "hppa"
  #define SHEOL_HPPA_ARCHITECTURE

// x86 (x86-32)
#elif defined(i386) || defined(__i386__) || defined(__i486__) \
   || defined(__i586__) || defined(__i686__) || defined(__i386) \
   || defined(_M_IX86) || defined(__X86__) || defined(_X86_) \
   || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__)
  #define SHEOL_ARCHITECTURE "x86-32"
  #define SHEOL_X86_32_ARCHITECTURE

// Intel 64 (ia64)
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) \
   || defined(__ia64) || defined(_M_IA64)
  #define SHEOL_ARCHITECTURE "ia64"
  #define SHEOL_IA64_ARCHITECTURE

// Motorola 68k (m68k)
#elif defined(__m68k__) || defined(M68000)
  #define SHEOL_ARCHITECTURE "m68k"
  #define SHEOL_M68K_ARCHITECTURE

// MIPS (mips)
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__)
  #define SHEOL_ARCHITECTURE "mips"
  #define SHEOL_MIPS_ARCHITECTURE

// PowerPC (ppc)
#elif defined(__powerpc) || defined(__powerpc__) || defined(__ppc__) \
   || defined(__POWERPC__) || defined(_M_PPC) || defined(_ARCH_PPC)
  #define SHEOL_ARCHITECTURE "ppc"
  #define SHEOL_PPC_ARCHITECTURE

// RS/6000 (power)
#elif defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) \
   || defined(_ARCH_PWR) || defined(_ARCH_PWR2)
  #define SHEOL_ARCHITECTURE "power"
  #define SHEOL_POWER_ARCHITECTURE

// SPARC (sparc)
#elif defined(__sparc__) || defined(__sparc)
  #define SHEOL_ARCHITECTURE "sparc"
  #define SHEOL_SPARC_ARCHITECTURE

// SuperH (superh)
#elif defined(__sh__)
  #define SHEOL_ARCHITECTURE "superh"
  #define SHEOL_SUPERH_ARCHITECTURE

// System/370 (s370)
#elif defined(__370__) || defined(__THW_370__) 
  #define SHEOL_ARCHITECTURE "s370"
  #define SHEOL_S370_ARCHITECTURE

// System/390 (s390)
#elif defined(__s390__) || defined(__s390x__) 
  #define SHEOL_ARCHITECTURE "s390"
  #define SHEOL_S390_ARCHITECTURE

// z/Architecture (zarch)
#elif defined(__SYSC_ZARCH__)
  #define SHEOL_ARCHITECTURE "zarch"
  #define SHEOL_ZARCH_ARCHITECTURE

#else
  #define SHEOL_ARCHITECTURE "unknown"
  #define SHEOL_UNKNOWN_ARCHITECTURE

#endif

#endif // SHEOL_A454A7E1_8A13_4B47_A7E9_69606F1F2B93

