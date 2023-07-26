#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_times_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 2);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_times_minus_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_integer (s, -2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, -2);
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_s_times_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "1"));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "11");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (two_times_one_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 2));
    CHECK (push_string (s, "1"));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "11");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (ciao_times_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciao"));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciaociao");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (four_spaces_times_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "    "));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "        ");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (two_times_ciao) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 2));
    CHECK (push_string (s, "ciao"));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciaociao");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (four_spaces_times_one) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "    "));
    CHECK (push_integer (s, 1));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "    ");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_times_ciao) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_string (s, "ciao"));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "ciao");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (two_times_four_spaces) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 2));
    CHECK (push_string (s, "    "));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "        ");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (empty_times_one) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (push_integer (s, 1));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (empty_times_two) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (push_integer (s, 2));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (two_times_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 2));
    CHECK (push_string (s, ""));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (one_times_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 1));
    CHECK (push_string (s, ""));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_times_two,
		 one_times_minus_two,
		 one_s_times_two,
		 two_times_one_s,
		 ciao_times_two,
		 four_spaces_times_two,
		 two_times_ciao,
		 four_spaces_times_one,
		 one_times_ciao,
		 two_times_four_spaces,
		 empty_times_one,
		 empty_times_two,
		 two_times_empty,
		 one_times_empty);
		 
