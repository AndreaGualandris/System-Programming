#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_and_two) {
    struct sl * s1 = create();
    struct sl * s2 = create();
    CHECK (s1 != 0);
    CHECK (s2 != 0);
    CHECK (push_integer (s1, 1));
    CHECK (empty (s2));
    CHECK (push_integer (s2, 2));
    CHECK (!empty (s2));
    CHECK_INT_CMP(get_type(s1), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s1), ==, 1);
    CHECK_INT_CMP(get_type(s2), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s2), ==, 2);
    CHECK (pop (s2));
    CHECK (empty (s2));
    CHECK (!empty (s1));
    destroy(s1);
    destroy(s2);
    TEST_PASSED;
}

TEST (one_and_two_many) {
    struct sl * s1 = create();
    struct sl * s2 = create();
    CHECK (s1 != 0);
    CHECK (s2 != 0);
    for (int i = 0; i <= 100; ++i)
	CHECK (push_integer (s1, i));
    CHECK (empty (s2));
    for (int i = 200; i <= 300; ++i)
	CHECK (push_integer (s2, i));
    CHECK (!empty (s2));
    for (int i = 100; i >= 0; --i) {
	CHECK_INT_CMP(get_type(s1), ==, INTEGER_T);
	CHECK_INT_CMP(get_integer(s1), ==, i);
	CHECK (pop (s1));
    }
    CHECK (empty (s1));
    CHECK (!empty (s2));
    for (int i = 300; i >= 200; --i) {
	CHECK_INT_CMP(get_type(s2), ==, INTEGER_T);
	CHECK_INT_CMP(get_integer(s2), ==, i);
	CHECK (pop (s2));
    }
    CHECK (empty (s2));
    destroy(s1);
    destroy(s2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_and_two,
		 one_and_two_many);
