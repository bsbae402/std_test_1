#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "endian_swap.h"

/*
Test(hw1_tests_suite, validargs_help_test) {
    int argc = 2;
    char *argv[] = {"bin/hw1", "-h", NULL};
    int ret = validargs(argc, argv);
    int exp_ret = 1;
    unsigned int opt = global_options;
    unsigned int flag = 0x1;
    cr_assert_eq(ret, exp_ret, "Invalid return for valid args.  Got: %d | Expected: %d",
		 ret, exp_ret);
    cr_assert_eq(opt & flag, flag, "Least significant bit not set for -h. Got: %d",
		 opt);
}
*/