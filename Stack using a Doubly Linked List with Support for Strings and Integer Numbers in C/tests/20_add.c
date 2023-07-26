#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_plus_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 3);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_plus_minus_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, -2));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, -1);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_plus_two_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "1"));
    CHECK (push_string (s, "2"));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "12");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_plus_empty_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "1"));
    CHECK (push_string (s, ""));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "1");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (empty_plus_one_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (push_string (s, "1"));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "1");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (empty_plus_empty_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (push_string (s, ""));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_plus_two,
		 one_plus_minus_two,
		 one_plus_two_s,
		 one_plus_empty_s,
		 empty_plus_one_s,
		 empty_plus_empty_s);
