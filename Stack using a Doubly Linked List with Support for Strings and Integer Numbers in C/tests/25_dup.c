#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_dup) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK_INT_CMP (duplicate (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 1);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 1);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (number123_dup) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (duplicate (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (ciao_dup) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciao"));
    CHECK_INT_CMP (duplicate (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciao");
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciao");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_dup,
		 number123_dup,
		 ciao_dup);
