/* Public domain, no copyright. Use at your own risk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <check.h>
#include "h_lggr.h"
#include "h_str.h"
#include "h_memory.h"

char message[1024];

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

  message[0] = '\0';
  h_StrCpy(message,"aaab");
  h_lggr_print_memory("data",message,5);

}
END_TEST

START_TEST(test_h_StrStr)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result=h_StrStr("this is a test", "test"),NULL);
    ck_assert_str_eq(result,test);
}
END_TEST

START_TEST(test_h_StrDup)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result=h_StrDup("test"),NULL);
    ck_assert_str_eq(result,test);
    h_free(result);
}
END_TEST
START_TEST(test_h_StrnDup)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result= h_StrNDup("test12345", 4), NULL);
    ck_assert_str_eq(result,test);
    h_free(result);
}
END_TEST
START_TEST(test_h_StrCpy)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result = h_StrCpy(message, test), NULL);
    ck_assert_str_eq(result,test);
}
END_TEST
START_TEST(test_h_StrNCpy)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result = h_StrNCpy(message, test,4), NULL);
    ck_assert_str_eq(result,test);
}
END_TEST
START_TEST(test_h_StrCat)
{
    char* result, *test = "test";
    message[0]='\0';
    ck_assert_ptr_ne(result = h_StrCat(message, test), NULL);
    ck_assert_str_eq(result,test);
}
END_TEST
START_TEST(test_h_StrCmp)
{
    char* test = "test";
    h_StrCpy(message,"test");
    ck_assert_int_eq(h_StrCmp(message, test), 0);
}
END_TEST
START_TEST(test_h_StrLwr_h_StrUpr)
{
    char* result,*test = "test";
    h_StrCpy(message,test);
    ck_assert_ptr_ne(result = h_StrUpr(message), NULL);
    ck_assert_ptr_ne(result = h_StrLwr(message), NULL);
    ck_assert_str_eq(message,test);
}
END_TEST
START_TEST(test_h_StrChr)
{
    char* result, *test = "test";
    ck_assert_ptr_ne(result=h_StrChr("is a test", 't'),NULL);
    ck_assert_str_eq(result,test);
}
END_TEST
START_TEST(test_h_AtoI)
{
    ck_assert_int_eq(h_AtoI("123"), 123);
}
END_TEST
START_TEST(test_h_AtoL)
{
    ck_assert_int_eq(h_AtoL("12345678"), 12345678);
}
END_TEST
START_TEST(test_h_LtoA)
{
    h_LtoA (1423, message, 16);
    ck_assert_str_eq(message, "58F");
}
END_TEST
START_TEST(test_h_StrReplase)
{
    char *ptr;
    h_StrCpy(message,"aaa;bbb;ccc");
    ck_assert_ptr_ne(ptr = h_StrReplace(";","",message),NULL);
    ck_assert_str_eq(ptr, "aaabbbccc");
    h_free(ptr);
}
END_TEST
START_TEST(test_h_StrCatNewBuf)
{
    char *ptr;
    h_StrCpy(message,"aaa");
    ck_assert_ptr_ne(ptr = h_StrCatNewBuf(message,"bbb"),NULL);
    ck_assert_str_eq(ptr, "aaabbb");
    h_free(ptr);
}
END_TEST
START_TEST(test_h_GetUntil)
{
    char *ptr;
    ck_assert_ptr_ne(ptr = h_GetUntil("aaa;bbb",";"),NULL);
    ck_assert_str_eq(ptr, "aaa");
    h_free(ptr);
}
END_TEST


static Suite *helpers_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("helpers tests functions");
  tc_core = tcase_create("test_helpers");
  tcase_add_test(tc_core, test_h_lggr_printf_line);
  tcase_add_test(tc_core, test_h_StrStr);
  tcase_add_test(tc_core, test_h_StrDup);
  tcase_add_test(tc_core, test_h_StrnDup);
  tcase_add_test(tc_core, test_h_StrCpy);
  tcase_add_test(tc_core, test_h_StrNCpy);
  tcase_add_test(tc_core, test_h_StrCat);
  tcase_add_test(tc_core, test_h_StrCmp);
  tcase_add_test(tc_core, test_h_StrLwr_h_StrUpr);
  tcase_add_test(tc_core, test_h_StrChr);
  tcase_add_test(tc_core, test_h_AtoI);
  tcase_add_test(tc_core, test_h_AtoL);
  tcase_add_test(tc_core, test_h_LtoA);
  tcase_add_test(tc_core, test_h_StrReplase);
  tcase_add_test(tc_core, test_h_StrCatNewBuf);
  tcase_add_test(tc_core, test_h_GetUntil);
  tcase_set_timeout(tc_core, 30);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(int argc, char *argv[])
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = helpers_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
