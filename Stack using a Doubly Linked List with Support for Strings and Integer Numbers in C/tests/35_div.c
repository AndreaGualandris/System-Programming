#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_div_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (divide (s),==,1);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 1);
    CHECK (pop (s));
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 0);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (two_div_one) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 2));
    CHECK (push_integer (s, 1));
    CHECK_INT_CMP (divide (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 0);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 2);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_div_minus_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, -2));
    CHECK_INT_CMP (divide (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 1);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 0);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (minus_six_div_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, -6));
    CHECK (push_integer (s, 3));
    CHECK_INT_CMP (divide (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 0);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, -2);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_div_two,
		 two_div_one,
		 one_div_minus_two,
		 minus_six_div_two);
		 
