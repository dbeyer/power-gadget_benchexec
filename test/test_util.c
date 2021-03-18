// This file is part of CPU Energy Meter,
// a tool for measuring energy consumption of Intel CPUs:
// https://github.com/sosy-lab/cpu-energy-meter
//
// SPDX-FileCopyrightText: 2018-2021 Dirk Beyer <https://www.sosy-lab.org>
//
// SPDX-License-Identifier: BSD-3-Clause

#include <sys/capability.h>
#include <unistd.h>

#include "unity.h"
#include "util.h"

void test_DropCapabilities_DoesNotFail(void) {
  drop_capabilities(); // terminates process if it fails
}

void test_DropCapabilities_should_ClearCaps(void) {
  char *cur_caps;
  cap_value_t cap_values[1] = {CAP_SYS_RAWIO};

  // Create and test the pointer to the capability state
  pid_t pid = getpid();
  cap_t capabilities = cap_get_pid(pid);
  TEST_ASSERT(capabilities != NULL);
  TEST_ASSERT_TRUE(CAP_IS_SUPPORTED(cap_values[0]));

  // Remove any capabilities in case some exist already and test that afterwards
  cap_clear(capabilities);
  cur_caps = cap_to_text(capabilities, NULL);
  TEST_ASSERT_EQUAL_STRING("=", cur_caps);

  // Manually add the CAP_SYS_RAWIO flag to the capabilities
  cap_set_flag(capabilities, CAP_EFFECTIVE, 1, cap_values, CAP_SET);
  cap_set_flag(capabilities, CAP_PERMITTED, 1, cap_values, CAP_SET);
  cap_set_proc(capabilities);

  // Test that the previously added capability does in fact exist.
  cur_caps = cap_to_text(capabilities, NULL);
  TEST_ASSERT_EQUAL_STRING("= cap_sys_rawio+ep", cur_caps);

  // Clear all capabilities and test that afterwards
  cap_clear(capabilities);
  cur_caps = cap_to_text(capabilities, NULL);
  TEST_ASSERT_EQUAL_STRING("=", cur_caps);

  cap_free(capabilities);
}
