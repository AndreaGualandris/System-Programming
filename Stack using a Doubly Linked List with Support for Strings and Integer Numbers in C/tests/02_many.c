#include "basic_testing.h"

#include "../sl.h"

TEST (push_100_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 100; ++i)
	push_integer (s, i);
    destroy(s);
    TEST_PASSED;
}

TEST (push_10000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 10000; ++i)
	push_integer (s, i);
    destroy(s);
    TEST_PASSED;
}

TEST (push_1000000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 1000000; ++i)
	push_integer (s, i);
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_100_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 100; ++i)
	push_integer (s, i);
    int i = 0;
    while (! empty (s)) {
	pop (s);
	++i;
    }
    CHECK_INT_CMP (i,==,100);
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_10000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 10000; ++i)
	push_integer (s, i);
    int i = 0;
    while (! empty (s)) {
	pop (s);
	++i;
    }
    CHECK_INT_CMP (i,==,10000);
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_1000000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int i = 0; i < 1000000; ++i)
	push_integer (s, i);
    int i = 0;
    while (! empty (s)) {
	pop (s);
	++i;
    }
    CHECK_INT_CMP (i,==,1000000);
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_10_100_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int j = 0; j < 10; ++j) {
	for (int i = 0; i < 100; ++i)
	    CHECK (push_integer (s, i));
	for (int i = 0; i < 100; ++i)
	    CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_10_10000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int j = 0; j < 10; ++j) {
	for (int i = 0; i < 10000; ++i)
	    CHECK (push_integer (s, i));
	for (int i = 0; i < 10000; ++i)
	    CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_10_1000000_i) {
    struct sl * s = create();
    CHECK (s != 0);
    for (int j = 0; j < 10; ++j) {
	for (int i = 0; i < 1000000; ++i)
	    CHECK (push_integer (s, i));
	for (int i = 0; i < 1000000; ++i)
	    CHECK (pop (s));
    }
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(push_100_i,
		 push_10000_i,
		 push_1000000_i,
		 push_pop_100_i,
		 push_pop_10000_i,
		 push_pop_1000000_i,
		 push_pop_10_100_i,
		 push_pop_10_10000_i,
		 push_pop_10_1000000_i);
		 
