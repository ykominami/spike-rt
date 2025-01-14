// SPDX-License-Identifier: MIT
/*
 * Tests for the internal status light.
 *
 * Copyright (c) 2022 Embedded and Real-Time Systems Laboratory,
 *                    Graduate School of Information Science, Nagoya Univ., JAPAN
 */

#include <kernel.h>

#include <unity.h>
#include <unity_fixture.h>

#include <cbricks/hub/light.h>

TEST_GROUP(Light);

TEST_GROUP_RUNNER(Light) {
  RUN_TEST_CASE(Light, on_hsv);
  RUN_TEST_CASE(Light, on_color);
  RUN_TEST_CASE(Light, off);
}

TEST_SETUP(Light)
{
  // Prepare the pybricks runtime for running a user program.
  // TODO: integrate pbsys_user_program_prepare() and wup_pybricks into one function. 
  pbsys_user_program_prepare(NULL);
  wup_pybricks();
}

TEST_TEAR_DOWN(Light)
{
  // Perform cleanup/reset after running a user program.
  // TODO: integrate pbsys_user_program_unprepare() and wup_pybricks into one function. 
  pbsys_user_program_unprepare();
  wup_pybricks();
}

TEST(Light, on_hsv)
{
  pbio_error_t err;

  err = hub_light_on_hsv(&((pbio_color_hsv_t){120, 100, 100}));
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);
  
  // Wait 1 sec for visual confirmation the light glows green.
  dly_tsk(1000000);

  err = hub_light_on_hsv(&((pbio_color_hsv_t ){0, 0, 0}));
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);

  // Wait 1 sec.
  dly_tsk(1000000);
}

TEST(Light, on_color)
{
  pbio_error_t err;

  err = hub_light_on_color(PBIO_COLOR_GREEN);
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);

  // Wait 1 sec for visual confirmation the light glows green.
  dly_tsk(1000000);

  err = hub_light_on_color(PBIO_COLOR_NONE);
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);

  // Wait 1 sec.
  dly_tsk(1000000);
}

TEST(Light, off)
{
  pbio_error_t err;

  err = hub_light_on_color(PBIO_COLOR_GREEN);
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);

  dly_tsk(1000000);

  err = hub_light_off();
  TEST_ASSERT_EQUAL(err, PBIO_SUCCESS);

  // Wait 1 sec for visual confirmation the light is off.
  dly_tsk(1000000);
}
