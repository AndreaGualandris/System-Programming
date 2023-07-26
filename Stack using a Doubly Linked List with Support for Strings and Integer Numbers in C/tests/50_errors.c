#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (pop_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (pop (s) == 0);
    destroy(s);
    TEST_PASSED;
}

TEST (add_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK_INT_CMP (add (s),==,0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (add_single) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (add (s),==,0);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (multiply_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK_INT_CMP (multiply (s),==,0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (multiply_single) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (multiply (s),==,0);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (divide_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK_INT_CMP (divide (s),==,0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (divide_single) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (divide (s),==,0);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (divide_by_zero) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK (push_integer (s, 0));
    CHECK_INT_CMP (divide (s),==,0);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 0);
    CHECK (pop (s));
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (swap_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK_INT_CMP (swap (s),==,0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (swap_single) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (swap (s),==,0);
    CHECK_INT_CMP (get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP (get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (duplicate_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK_INT_CMP (duplicate (s),==,0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}


MAIN_TEST_DRIVER(pop_empty,
		 add_empty,
		 add_single,
		 multiply_empty,
		 multiply_single,
		 divide_empty,
		 divide_single,
		 divide_by_zero,
		 swap_empty,
		 swap_single,
		 duplicate_empty)
