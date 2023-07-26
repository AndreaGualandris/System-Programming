#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (one_int) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 0));
    CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
    CHECK_INT_CMP(get_integer(s), ==, 0);
    destroy(s);
    TEST_PASSED;
}

TEST (one_string) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    destroy(s);
    TEST_PASSED;
}

TEST (ints_100_100) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = -100; i <= 100; ++i)
	CHECK (push_integer (s, i));
    for (int i = -100; i <= 100; ++i) {
	CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
	CHECK_INT_CMP(get_integer(s), ==, -i);
	CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

TEST (strings_100_100) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = -100; i <= 100; ++i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", i);
	CHECK (push_string (s, buf));
    }
    for (int i = -100; i <= 100; ++i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", -i);
	CHECK_INT_CMP(get_type(s), ==, STRING_T);
	CHECK_STRING_CMP(get_string(s), ==, buf);
	CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

TEST (mixed_100_100) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = -100; i <= 100; ++i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", i);
	CHECK (push_string (s, buf));
	CHECK (push_integer (s, i));
    }
    for (int i = -100; i <= 100; ++i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", -i);
	CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
	CHECK_INT_CMP(get_integer(s), ==, -i);
	CHECK (pop (s));
	CHECK_INT_CMP(get_type(s), ==, STRING_T);
	CHECK_STRING_CMP(get_string(s), ==, buf);
	CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

TEST (mixed_10000) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 1; i <= 10000; ++i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", i);
	CHECK (push_string (s, buf));
	CHECK (push_integer (s, i));
    }
    for (int i = 10000; i >= 1; --i) {
	char buf [100];
	snprintf (buf, 100, "abcdefghi (%d)", i);
	CHECK_INT_CMP(get_type(s), ==, INTEGER_T);
	CHECK_INT_CMP(get_integer(s), ==, i);
	CHECK (pop (s));
	CHECK_INT_CMP(get_type(s), ==, STRING_T);
	CHECK_STRING_CMP(get_string(s), ==, buf);
	CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_int,
		 one_string,
		 ints_100_100,
		 strings_100_100,
		 mixed_100_100,
		 mixed_10000);
