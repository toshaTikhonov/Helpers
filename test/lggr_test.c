/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "h_lggr.h"

char message[1024];
//char app_name[128];
//int level;

START_TEST(test_h_lggr_printf_line)
{
  message[0] = '\0';
  h_lggr_printf_line("first test");
  ck_assert_str_eq(message, "");
  
  message[0] = '\0';
  h_lggr_printf_line("second test %d",2);
  ck_assert_str_eq(message, "");
  
  message[0] = '\0';
  h_lggr_printf_line("%s","third test");
  ck_assert_str_eq(message, "");
  
  message[0] = '\0';
  h_lggr_printf_line("%s","fourth test");
  ck_assert_str_eq(message, "");

}
END_TEST

static Suite *helpers_lggr_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("lggr tests functions");
  tc_core = tcase_create("test_helpers");
  tcase_add_test(tc_core, test_h_lggr_printf_line);
  tcase_set_timeout(tc_core, 30);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  
  s = helpers_lggr_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
