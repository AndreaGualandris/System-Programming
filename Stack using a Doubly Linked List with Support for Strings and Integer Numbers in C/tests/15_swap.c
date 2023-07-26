#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_swap_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (swap (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 1);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 2);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_swap_two_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "1"));
    CHECK (push_string (s, "2"));
    CHECK_INT_CMP (swap (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "1");
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "2");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (ciao_swap_number123) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciao"));
    CHECK (push_integer (s, 123));
    CHECK_INT_CMP (swap (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciao");
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (number123_swap_ciao) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 123));
    CHECK (push_string (s, "ciao"));
    CHECK_INT_CMP (swap (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 123);
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciao");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_swap_empty_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "1"));
    CHECK (push_string (s, ""));
    CHECK_INT_CMP (swap (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "1");
    CHECK (pop (s));
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_swap_two,
		 one_swap_two_s,
		 ciao_swap_number123,
		 number123_swap_ciao,
		 one_swap_empty_s);
