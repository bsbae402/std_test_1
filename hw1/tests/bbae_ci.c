#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <string.h>
#include "hw1.h"

#define MAX_PATH_LEN 256

char *bbae_test1_path = "rsrc/bbae_test1/";
char *bbae_run_path = "rsrc/bbae_run_test/";

Test(hw1_tests_suite, test11_out) {
    char *infile_name = "test11_in.txt";
    char infile_path[MAX_PATH_LEN];
    strcpy(infile_path, bbae_test1_path);
    strcat(infile_path, infile_name);

    char *run_out_name = "test11_run.out";
    char run_out_path[MAX_PATH_LEN];
    strcpy(run_out_path, bbae_run_path);
    strcat(run_out_path, run_out_name);

    char cmd[MAX_PATH_LEN];
    strcpy(cmd, "bin/hw1 -a < ");
    strcat(cmd, infile_path);
    strcat(cmd, " > ");
    strcat(cmd, run_out_path);
    int return_code = WEXITSTATUS(system(cmd));

    cr_assert_eq(return_code, EXIT_SUCCESS, "Program exited with %d instead of EXIT_SUCCESS", return_code);

    char *exp_res_name = "test11_out.bin";
    char exp_res_path[MAX_PATH_LEN];
    strcpy(exp_res_path, bbae_test1_path);
    strcat(exp_res_path, exp_res_name);

    FILE *fp_exp, *fp_run;
    int ch1, ch2;
    int same_file = 0;

    fp_exp = fopen(exp_res_path, "r");
    fp_run = fopen(run_out_path, "r");

    if (fp_exp == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", exp_res_path);
    } else if (fp_run == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", run_out_path);
    } else {
        ch1 = getc(fp_exp);
        ch2 = getc(fp_run);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
            ch1 = getc(fp_exp);
            ch2 = getc(fp_run);
        }

        if (ch1 == ch2)
            same_file = 1;

        cr_assert_eq(same_file, 1, "%s doesn't match to %s", run_out_path, exp_res_path);
    }
    fclose(fp_exp);
    fclose(fp_run);
}

Test(hw1_tests_suite, test11_out_be) {
    char *infile_name = "test11_in.txt";
    char infile_path[MAX_PATH_LEN];
    strcpy(infile_path, bbae_test1_path);
    strcat(infile_path, infile_name);

    char *run_out_name = "test11_be_run.out";
    char run_out_path[MAX_PATH_LEN];
    strcpy(run_out_path, bbae_run_path);
    strcat(run_out_path, run_out_name);

    char cmd[MAX_PATH_LEN];
    strcpy(cmd, "bin/hw1 -a -e b < ");
    strcat(cmd, infile_path);
    strcat(cmd, " > ");
    strcat(cmd, run_out_path);
    int return_code = WEXITSTATUS(system(cmd));

    cr_assert_eq(return_code, EXIT_SUCCESS, "Program exited with %d instead of EXIT_SUCCESS", return_code);

    char *exp_res_name = "test11_out_be.bin";
    char exp_res_path[MAX_PATH_LEN];
    strcpy(exp_res_path, bbae_test1_path);
    strcat(exp_res_path, exp_res_name);

    FILE *fp_exp, *fp_run;
    int ch1, ch2;
    int same_file = 0;

    fp_exp = fopen(exp_res_path, "r");
    fp_run = fopen(run_out_path, "r");

    if (fp_exp == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", exp_res_path);
    } else if (fp_run == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", run_out_path);
    } else {
        ch1 = getc(fp_exp);
        ch2 = getc(fp_run);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
            ch1 = getc(fp_exp);
            ch2 = getc(fp_run);
        }

        if (ch1 == ch2)
            same_file = 1;

        cr_assert_eq(same_file, 1, "%s doesn't match %s", run_out_path, exp_res_path);
    }
    fclose(fp_exp);
    fclose(fp_run);
}

Test(hw1_tests_suite, test12_out) {
    char *infile_name = "test12_in.bin";
    char infile_path[MAX_PATH_LEN];
    strcpy(infile_path, bbae_test1_path);
    strcat(infile_path, infile_name);

    char *run_out_name = "test12_run.txt";
    char run_out_path[MAX_PATH_LEN];
    strcpy(run_out_path, bbae_run_path);
    strcat(run_out_path, run_out_name);

    char cmd[MAX_PATH_LEN];
    strcpy(cmd, "bin/hw1 -d < ");
    strcat(cmd, infile_path);
    strcat(cmd, " > ");
    strcat(cmd, run_out_path);
    int return_code = WEXITSTATUS(system(cmd));

    cr_assert_eq(return_code, EXIT_SUCCESS, "Program exited with %d instead of EXIT_SUCCESS", return_code);

    char *exp_res_name = "test12_out.txt";
    char exp_res_path[MAX_PATH_LEN];
    strcpy(exp_res_path, bbae_test1_path);
    strcat(exp_res_path, exp_res_name);

    FILE *fp_exp, *fp_run;
    int ch1, ch2;
    int same_file = 0;

    fp_exp = fopen(exp_res_path, "r");
    fp_run = fopen(run_out_path, "r");

    if (fp_exp == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", exp_res_path);
    } else if (fp_run == NULL) {
        cr_assert_eq(0, 1, "%s cannot be opened", run_out_path);
    } else {
        ch1 = getc(fp_exp);
        ch2 = getc(fp_run);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
            ch1 = getc(fp_exp);
            ch2 = getc(fp_run);
        }

        if (ch1 == ch2)
            same_file = 1;

        cr_assert_eq(same_file, 1, "%s doesn't match %s", run_out_path, exp_res_path);
    }
    fclose(fp_exp);
    fclose(fp_run);
}
