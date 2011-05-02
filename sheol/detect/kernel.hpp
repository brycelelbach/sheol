////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Most information based on the data collected by predef.sourceforge.net
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_671423C3_49F7_42CB_8284_F09B701A6B85)
#define SHEOL_671423C3_49F7_42CB_8284_F09B701A6B85

// AIX UNIX (aix)
#if defined(_AIX)         \
 || defined(__TOS_AIX__)
  #define SHEOL_KERNEL "aix"
  #define SHEOL_AIX_KERNEL

// AmigaOS (amiga)
#elif defined(AMIGA)         \
   || defined(__amigaos__)
  #define SHEOL_KERNEL "amiga"
  #define SHEOL_AMIGA_KERNEL

// BeOS (beos)
#elif defined(__BEOS__)
  #define SHEOL_KERNEL "beos"
  #define SHEOL_BEOS_KERNEL

// Cray UniCOS (unicos)
#elif defined(_UNICOS)
  #define SHEOL_KERNEL "unicos"
  #define SHEOL_UNICOS_KERNEL

// DG/UX (dgux)
#elif defined(DGUX)     \
   || defined(__DGUX__) \
   || defined(__dgux__)
  #define SHEOL_KERNEL "dgux"
  #define SHEOL_DGUX_KERNEL

// BSD/OS (bsdi)
#elif defined(__bsdi__)
  #define SHEOL_KERNEL "bsdi"
  #define SHEOL_BSDI_KERNEL

// DragonFly BSD (dragonflybsd)
#elif defined(__DragonFly__)
  #define SHEOL_KERNEL "dragonflybsd"
  #define SHEOL_DRAGONFLYBSD_KERNEL

// FreeBSD (freebsd)
#elif defined(__FreeBSD__)
  #define SHEOL_KERNEL "freebsd"
  #define SHEOL_FREEBSD_KERNEL

// NetBSD (netbsd)
#elif defined(__NetBSD__)
  #define SHEOL_KERNEL "netbsd"
  #define SHEOL_NETBSD_KERNEL

// OpenBSD (openbsd)
#elif defined(__OpenBSD__)
  #define SHEOL_KERNEL "openbsd"
  #define SHEOL_OPENBSD_KERNEL

// DYNIX/ptx (dynix)
#elif defined(_SEQUENT_)
  #define SHEOL_KERNEL "dynix"
  #define SHEOL_DYNIX_KERNEL

// eCos (ecos)
#elif defined(__ECOS)
  #define SHEOL_KERNEL "ecos"
  #define SHEOL_ECOS_KERNEL

// HI-UX/MPP (hiuxmpp)
#elif defined(__hiuxmpp)
  #define SHEOL_KERNEL "hpiuxmpp"
  #define SHEOL_HPIUXMPP_KERNEL

// HP-UX (hpux)
#elif defined(_hpux)  \
   || defined(hpux)   \
   || defined(__hpux)
  #define SHEOL_KERNEL "hpux"
  #define SHEOL_HPUX_KERNEL

// INTEGRITY (integrity)
#elif defined(__INTEGRITY)
  #define SHEOL_KERNEL "integrity"
  #define SHEOL_INTEGRITY_KERNEL

// IRIX (irix)
#elif defined(sgi)    \
   || defined(__sgi)
  #define SHEOL_KERNEL "irix"
  #define SHEOL_IRIX_KERNEL

// Linux (linux) :)
#elif defined(linux)    \
   || defined(__linux)
  #define SHEOL_KERNEL "linux"
  #define SHEOL_LINUX_KERNEL

// LynxOS (lynxos)
#elif defined(__Lynx__)
  #define SHEOL_KERNEL "lynxos"
  #define SHEOL_LYNXOS_KERNEL

// MacOS (macos)
#elif defined(macintosh)    \
   || defined(Macintosh)
  #define SHEOL_KERNEL "macos"
  #define SHEOL_MACOS_KERNEL

// Apple Darwin (darwin)
#elif defined(__APPLE__)  \
   && defined(__MACH__)
  #define SHEOL_KERNEL "darwin"
  #define SHEOL_DARWIN_KERNEL

// Microware OS-9 (microware)
#elif defined(__OS9000)  \
   || defined(__OSK)
  #define SHEOL_KERNEL "microware"
  #define SHEOL_MICROWARE_KERNEL

// MINIX (minix)
#elif defined(__minix)
  #define SHEOL_KERNEL "minix"
  #define SHEOL_MINIX_KERNEL

// MPE/iX (mpeix)
#elif defined(mpeix)   \
   || defined(__mpexl)
  #define SHEOL_KERNEL "mpeix"
  #define SHEOL_MPEIX_KERNEL

/// MSDOS (msdos)
#elif defined(MSDOS)      \
   || defined(__MSDOS__)  \
   || defined(_MSDOS)     \
   || defined(__DOS__)
  #define SHEOL_KERNEL "msdos"
  #define SHEOL_MSDOS_KERNEL

// MS Windows (windows)
#elif defined(_WIN32)       \
   || defined(_WIN64)       \
   || defined(__WIN32__)    \
   || defined(__TOS_WIN__)  \
   || defined(__WINDOWS__)
  #define SHEOL_KERNEL "windows"
  #define SHEOL_WINDOWS_KERNEL

// NonStop (nonstop)
#elif defined(__TANDEM)
  #define SHEOL_KERNEL "nonstop"
  #define SHEOL_NONSTOP_KERNEL

// Nucleus OS (nucleusos)
#elif defined(__nucleus__)
  #define SHEOL_KERNEL "nucleusos"
  #define SHEOL_NUCLEUSOS_KERNEL

// OS/2 (os2)
#elif defined(OS2)          \
   || defined(_OS2)         \
   || defined(__OS2__)      \
   || defined(__TOS_OS2__)
  #define SHEOL_KERNEL "os2"
  #define SHEOL_OS2_KERNEL

// QNX (qnx)
#elif defined(__QNX__)    \
   || defined(__QNXNTO__)
  #define SHEOL_KERNEL "qnx"
  #define SHEOL_QNX_KERNEL

// Solaris (solaris)
#elif defined(sun)   \
   || defined(__sun) 
  #define SHEOL_KERNEL "solaris"
  #define SHEOL_SOLARIS_KERNEL

// Symbian OS (symbianos)
#elif defined(__SYMBIAN32__)
  #define SHEOL_KERNEL "symbianos"
  #define SHEOL_SYMBIANOS_KERNEL

// Tru64 OSF/1 (osf)
#elif defined(__osf__)  \
   || defined(__osf)
  #define SHEOL_KERNEL "osf"
  #define SHEOL_OSF_KERNEL

// Ultrix (ultrix)
#elif defined(ultrix)     \
   || defined(__ultrix)   \
   || defined(__ultrix__) \
   || (defined(unix) && defined(vax))
  #define SHEOL_KERNEL "ultrix"
  #define SHEOL_ULTRIX_KERNEL

// UnixWare (unixware)
#elif defined(sco)        \
   || defined(_UNIXWARE7)
  #define SHEOL_KERNEL "unixware"
  #define SHEOL_UNIXWARE_KERNEL

// UnixWare (unixware)
#elif defined(VMS)    \
   || defined(__VMS)
  #define SHEOL_KERNEL "vms"
  #define SHEOL_VMS_KERNEL

// XBox (xbox)
#elif defined(_XBOX)
  #define SHEOL_KERNEL "xbox"
  #define SHEOL_XBOX_KERNEL

// z/OS aka OS/390 (zos)
#elif defined(__MVS__)      \
   || defined(__HOS_MVS__)  \
   || defined(__TOS_MVS__)
  #define SHEOL_KERNEL "zos"
  #define SHEOL_ZOS_KERNEL

// GNU Hurd (hurd)
#elif defined(__GNU__)
  #define SHEOL_KERNEL "hurd"
  #define SHEOL_HURD_KERNEL

#else
  #define SHEOL_KERNEL "unknown"
  #define SHEOL_UNKNOWN_KERNEL

#endif

#if defined(BSD)
  #define SHEOL_BSD
#endif

#if defined(__unix__) || defined(__unix)
  #define SHEOL_UNIX
#endif

#endif // SHEOL_671423C3_49F7_42CB_8284_F09B701A6B85

