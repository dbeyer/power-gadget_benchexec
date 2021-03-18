// This file is part of CPU Energy Meter,
// a tool for measuring energy consumption of Intel CPUs:
// https://github.com/sosy-lab/cpu-energy-meter
//
// SPDX-FileCopyrightText: 2015-2021 Dirk Beyer <https://www.sosy-lab.org>
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef _ASM_X86_INTEL_FAMILY_H
#define _ASM_X86_INTEL_FAMILY_H

/*
 * Mapping from Intel's CPU generation names to their respective family- and model number.
 *
 * For reference, see Intel Architectures Software Developer's Manual Volume 4, Model-Specific
 * Registers, Chapter 2, Table 2-1
 * (https://software.intel.com/sites/default/files/managed/22/0d/335592-sdm-vol-4.pdf)
 */

/*
 * "Big Core" Processors (Branded as Core, Xeon, etc...). The "_X" parts are generally the EP and EX
 * Xeons.
 */
// clang-format off
#define CPU_INTEL_SANDYBRIDGE           0x206A0     // Family 6 Model 42 (0x2a)
#define CPU_INTEL_SANDYBRIDGE_X         0x206D0     // Family 6 Model 45 (0x2d)

#define CPU_INTEL_IVYBRIDGE             0x306A0     // Family 6 Model 58 (0x3a)
#define CPU_INTEL_IVYBRIDGE_X           0x306E0     // Family 6 Model 62 (0x3e)

#define CPU_INTEL_HASWELL_CORE          0x306C0     // Family 6 Model 60 (0x3c)
#define CPU_INTEL_HASWELL_ULT           0x40650     // Family 6 Model 69 (0x45)
#define CPU_INTEL_HASWELL_GT3E          0x40660     // Family 6 Model 70 (0x46)
#define CPU_INTEL_HASWELL_X             0x306F0     // Family 6 Model 63 (0x3f)

#define CPU_INTEL_BROADWELL_CORE        0x306D0     // Family 6 Model 61 (0x3d)
#define CPU_INTEL_BROADWELL_GT3E        0x40670     // Family 6 Model 71 (0x47)
#define CPU_INTEL_BROADWELL_X           0x406F0     // Family 6 Model 79 (0x4f)
#define CPU_INTEL_BROADWELL_XEON_D      0x50660     // Family 6 Model 64 (0x56)

#define CPU_INTEL_SKYLAKE_MOBILE        0x406E0     // Family 6 Model 78 (0x4e)
#define CPU_INTEL_SKYLAKE_DESKTOP       0x506E0     // Family 6 Model 94 (0x5e)
#define CPU_INTEL_SKYLAKE_X             0x50650     // Family 6 Model 85 (0x55)

#define CPU_INTEL_KABYLAKE_MOBILE       0x806E0     // Family 6 Model 142 (0x8e)
#define CPU_INTEL_KABYLAKE_DESKTOP      0x906E0     // Family 6 Model 158 (0x9e)

#define CPU_INTEL_CANNONLAKE            0x60660     // Family 6 Model 102 (0x66)

/* "Small Core" Processors (Atom) */
#define CPU_INTEL_ATOM_SILVERMONT1      0x30670     // Family 6 Model 55 (0x37) /* E3000 series, Z3600 series, Z3700 series */
#define CPU_INTEL_ATOM_MERRIFIELD       0x406A0     // Family 6 Model 74 (0x4a)
#define CPU_INTEL_ATOM_AIRMONT          0x406C0     // Family 6 Model 76 (0x4c)
#define CPU_INTEL_ATOM_SILVERMONT2      0x406D0     // Family 6 Model 77 (0x4d) /* C2000 series */
#define CPU_INTEL_ATOM_MOOREFIELD       0x506A0     // Family 6 Model 90 (0x5a)
#define CPU_INTEL_ATOM_SILVERMONT3      0x506D0     // Family 6 Model 93 (0x5d) /* X3-C3000 series */
#define CPU_INTEL_ATOM_GOLDMONT         0x506C0     // Family 6 Model 92 (0x5c)
#define CPU_INTEL_ATOM_DENVERTON        0x506F0     // Family 6 Model 95 (0x5f)
#define CPU_INTEL_ATOM_GEMINI_LAKE      0x706A0     // Family 6 Model 122 (0x7a)

/* Xeon Phi */
#define CPU_INTEL_XEON_PHI_KNL          0x50670     // Family 6 Model 87 (0x57) /* Knights Landing */
#define CPU_INTEL_XEON_PHI_KNM          0x80650     // Family 6 Model 133 (0x85) /* Knights Mill */
// clang-format on

#endif /* _ASM_X86_INTEL_FAMILY_H */
