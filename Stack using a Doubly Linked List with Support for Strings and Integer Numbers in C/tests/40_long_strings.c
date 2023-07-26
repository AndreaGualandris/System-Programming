#include <stdio.h>

#include "basic_testing.h"

#include "../sl.h"

TEST (add_str_100) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    CHECK (push_string (s, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"));
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (a_times_100) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "a"));
    CHECK (push_integer (s, 100));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

static int s1_equals_s2_times_n (const char * s1, const char * s2, int n) {
    int j = 0;
    int i = 0;
    while (s1[i] != 0) {
	if (s2[j] == 0)
	    j = 0;
	if (s1[i] != s2[j])
	    return 0;
	++i;
	++j;
    }
    return (s1[i] == s2[j]);
}

TEST (ciao_times_100) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciao"));
    CHECK (push_integer (s, 100));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK (s1_equals_s2_times_n (get_string(s), "ciao", 100));
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (ciao_times_10000) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciaociao"));
    CHECK (push_integer (s, 50000));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK (s1_equals_s2_times_n (get_string(s), "ciao", 10000));
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (empty_times_100) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (push_integer (s, 100));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK_STRING_CMP(get_string(s), ==, "");
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (ciao_times_20000) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, "ciaociao"));
    CHECK (push_integer (s, 50000));
    CHECK_INT_CMP (multiply (s),==,1);
    CHECK_INT_CMP (duplicate (s),==,1);
    CHECK_INT_CMP (add (s),==,1);
    CHECK_INT_CMP(get_type(s), ==, STRING_T);
    CHECK (s1_equals_s2_times_n (get_string(s), "ciao", 20000));
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(add_str_100,
		 a_times_100,
		 ciao_times_100,
		 empty_times_100,
		 ciao_times_10000,
		 ciao_times_20000);
		 
		 
