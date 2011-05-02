////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2001 - 2003 John Maddock
//  Copyright (c) 2003        Martin Wille
//  Copyright (c) 2003        Guillaume Melquiond
//  Copyright (c) 2011        Bryce Lelbach
//
//  Most information based on the data collected by predef.sourceforge.net
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_2AE15EB8_A1DE_42B7_BA5E_14222A1CEF2F)
#define SHEOL_2AE15EB8_A1DE_42B7_BA5E_14222A1CEF2F

#include <sheol/detect/kernel.hpp>

// NVIDIA CUDA C++ (nvidia)
#if defined(__CUDACC__)
  #define SHEOL_COMPILER "nvidia"
  #define SHEOL_NVIDIA_COMPILER

// Comeau C++ (comeau)
#elif defined(__COMO__)
  #define SHEOL_COMPILER "comeau"
  #define SHEOL_COMEAU_COMPILER

// IAR C/C++ (iar)
#elif defined(__IAR_SYSTEMS_ICC__)
  #define SHEOL_COMPILER "iar"
  #define SHEOL_IAR_COMPILER

// PathScale EKOPath (pathscale) 
#elif defined(__PATHSCALE__)  \
   || defined(__PATHCC__)
  #define SHEOL_COMPILER "pathscale"
  #define SHEOL_PATHSCALE_COMPILER

// Clang/LLVM (clang) 
#elif defined(__clang__)
  #define SHEOL_COMPILER "clang"
  #define SHEOL_CLANG_COMPILER

// Digital Mars C++ (digitalmars)
#elif defined(__DMC__)  \
   || defined(__SC__)   \
   || defined(__ZTC__)  \
   || defined(__DMC__)
  #define SHEOL_COMPILER "digitalmars"
  #define SHEOL_DIGITALMARS_COMPILER

// Dignus System/C and System/C++ (dignus)
#elif defined(__SYSC__)
  #define SHEOL_COMPILER "dignus"
  #define SHEOL_DIGNUS_COMPILER

// Intel C++ (intel)
#elif defined(__INTEL_COMPILER) \
   || defined(__ICL)            \
   || defined(__ICC)            \
   || defined(__ECC)
  #define SHEOL_COMPILER "intel"
  #define SHEOL_INTEL_COMPILER

// Wind River C++ (windriver)
#elif defined(__DCC__)
  #define SHEOL_COMPILER "windriver"
  #define SHEOL_WINDRIVER_COMPILER

// Local C Compiler (lcc) 
#elif defined(__LCC__)
  #define SHEOL_COMPILER "lcc"
  #define SHEOL_LCC_COMPILER

// Keil CARM, C166 and C51 (keil) 
#elif defined(__CA__)   \
   || defined(__KEIL__) \
   || defined(__C166__) \
   || defined(__C51__)  \
   || defined(__CX51__)
  #define SHEOL_COMPILER "keil"
  #define SHEOL_KEIL_COMPILER

// MetaWare High C/C++ (metaware) 
#elif defined(__metaware__)
  #define SHEOL_COMPILER "metaware"
  #define SHEOL_METAWARE_COMPILER

// LLVM/GCC (llvm) 
#elif defined(__llvm__)
  #define SHEOL_COMPILER "llvm"
  #define SHEOL_LLVM_COMPILER

// mingw-w64 (mingw-w64) 
#elif defined(__MING64__)
  #define SHEOL_COMPILER "mingw-w64"
  #define SHEOL_MINGW64_COMPILER

// MinGW (mingw) 
#elif defined(__MINGW32__)
  #define SHEOL_COMPILER "mingw"
  #define SHEOL_MINGW_COMPILER

// DOS port of GNU GCC (djgpp) 
#elif defined(__DJGPP__)  \
   || defined(__GO32__)
  #define SHEOL_COMPILER "djgpp"
  #define SHEOL_DJGPP_COMPILER

// Cygwin (cygwin)
#elif defined(__CYGWIN__)
  #define SHEOL_COMPILER "cygwin"
  #define SHEOL_CYGWIN_COMPILER

// Kai C++ (kai)
#elif defined(__KCC)
  #define SHEOL_COMPILER "kai"
  #define SHEOL_KAI_COMPILER

// Cray C (cray)
#elif defined(_CRAYC)
  #define SHEOL_COMPILER "cray"
  #define SHEOL_CRAY_COMPILER

// Small Device C Compiler (sdcc)
#elif defined(SDCC)
  #define SHEOL_COMPILER "sdcc"
  #define SHEOL_SDCC_COMPILER

// SAS/C (sas)
#elif defined(SASC)     \
   || defined(__SASC)   \
   || defined(__SASC__)
  #define SHEOL_COMPILER "sas"
  #define SHEOL_SAS_COMPILER

// Compaq C++ (compaq)
#elif defined(__DECC)   \
   || defined(__DECXX)  \
   || defined(__VAXC)   \
   || defined(VAXC)
  #define SHEOL_COMPILER "compaq"
  #define SHEOL_COMPAQ_COMPILER

// Greenhills C++ (greenhills)
#elif defined(__ghs)
  #define SHEOL_COMPILER "greenhills"
  #define SHEOL_GREENHILLS_COMPILER

// CodeGear C++Builder (codegear)
#elif defined(__CODEGEARC__)
  #define SHEOL_COMPILER "codegear"
  #define SHEOL_CODEGEAR_COMPILER

// Borland C++ (borland)
#elif defined(__BORLANDC__) \
   || defined(__TURBOC__) 
  #define SHEOL_COMPILER "borland"
  #define SHEOL_BORLAND_COMPILER

// Metrowerks CodeWarrior (metrowerks)
#elif defined(__MWERKS__)
  #define SHEOL_COMPILER "metrowerks"
  #define SHEOL_METROWERKS_COMPILER

// Pacific C (pacific) 
#elif defined(__PACIFIC__)
  #define SHEOL_COMPILER "pacific"
  #define SHEOL_PACIFIC_COMPILER

// Pelles C (pelles) 
#elif defined(__POCC__)
  #define SHEOL_COMPILER "pelles"
  #define SHEOL_PELLES_COMPILER

// Palm C/C++ (palm) 
#elif defined(_PACC_VER)
  #define SHEOL_COMPILER "palm"
  #define SHEOL_PALM_COMPILER

// Norcroft C (norcroft) 
#elif defined(__CC_NORCROFT)
  #define SHEOL_COMPILER "norcroft"
  #define SHEOL_NORCROFT_COMPILER

// Renesas and Hitachi C/C++ (renesas) 
#elif defined(__RENESAS__)  \
   || defined(__HITACHI__)
  #define SHEOL_COMPILER "renesas"
  #define SHEOL_RENESAS_COMPILER

// Microtec C/C++ (microtec) 
#elif defined(_MRI)
  #define SHEOL_COMPILER "microtec"
  #define SHEOL_MICROTEC_COMPILER

// ImageCraft C (imagecraft) 
#elif defined(__IMAGECRAFT__)
  #define SHEOL_COMPILER "imagecraft"
  #define SHEOL_IMAGECRAFT_COMPILER

// Tiny C (tinyc)
#elif defined(__TINYC__)
  #define SHEOL_COMPILER "tinyc"
  #define SHEOL_TINYC_COMPILER

// Watcom C++ and Open Watcom C++ (watcom)
#elif defined(__WATCOMC__)
  #define SHEOL_COMPILER "watcom"
  #define SHEOL_WATCOM_COMPILER

// Ultimate C/C++ (ultimate)
#elif defined(_UCC)
  #define SHEOL_COMPILER "ultimate"
  #define SHEOL_ULTIMATE_COMPILER

// TenDRA C/C++ (dera)
#elif defined(__TenDRA__)
  #define SHEOL_COMPILER "dera"
  #define SHEOL_DERA_COMPILER

// Sun Workshop Compiler C++ or Solaris Studio (sun)
#elif defined(__SUNPRO_C)   \
   || defined(__SUNPRO_CC)
  #define SHEOL_COMPILER "sun"
  #define SHEOL_SUN_COMPILER

// HP aCC and HP ANSI C (hp)
#elif defined(__HP_aCC) \
   || defined(__HP_cc)
  #define SHEOL_COMPILER "hp"
  #define SHEOL_HP_COMPILER

// MPW MrCpp or SCpp (mpw)
#elif defined(__MRC__)    \
   || defined(__SC__)     \
   || defined(MPW_C)      \
   || defined(MPW_CPLUS)
  #define SHEOL_COMPILER "mpw"
  #define SHEOL_MPW_COMPILER

// IBM Visual Age, XL C/C++ and z/OS C/C++ (ibm)
#elif defined(__IBMCPP__) \
   || defined(__IBMC__)   \
   || defined(__xlc__)    \
   || defined(__xlC__) 
  #define SHEOL_COMPILER "ibm"
  #define SHEOL_IBM_COMPILER

// RealView C (realview)
#elif defined(__CC_ARM)
  #define SHEOL_COMPILER "realview"
  #define SHEOL_REALVIEW_COMPILER

// Portland Group Inc. (pgi)
#elif defined(__PGI)
  #define SHEOL_COMPILER "pgi"
  #define SHEOL_PGI_COMPILER

// SGI MIPSpro C++ (sgi)
#elif defined(__sgi)  \
   || defined(sgi)
  #define SHEOL_COMPILER "sgi"
  #define SHEOL_SGI_COMPILER

// EDG C++ Frontend (edg)
#elif defined(__EDG__)
  #define SHEOL_COMPILER "edg"
  #define SHEOL_EDG_COMPILER

// GNU GCC (gnu)
#elif defined(__GNUC__)
  #define SHEOL_COMPILER "gnu"
  #define SHEOL_GNU_COMPILER

// Microsoft Visual C++ (microsoft)
#elif defined(_MSC_VER)
  #define SHEOL_COMPILER "microsoft"
  #define SHEOL_MICROSOFT_COMPILER

#else
  #define SHEOL_COMPILER "unknown"
  #define SHEOL_UNKNOWN_COMPILER

#endif

#if defined(__GNUC__)                 \
 || defined(SHEOL_PATHSCALE_COMPILER) \
 || defined(SHEOL_CLANG_COMPILER)     \
 || (  defined(SHEOL_INTEL_COMPILER)  \
    && !defined(SHEOL_WINDOWS_KERNEL))
  #define SHEOL_GNULIKE_COMPILER
#endif

#endif // SHEOL_2AE15EB8_A1DE_42B7_BA5E_14222A1CEF2F

