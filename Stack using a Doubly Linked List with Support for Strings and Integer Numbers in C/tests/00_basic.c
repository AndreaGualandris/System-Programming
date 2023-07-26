#include "basic_testing.h"

#include "../sl.h"

TEST (create_destroy) {
    struct sl * s = create();
    CHECK (s != 0);
    destroy(s);
    TEST_PASSED;
}

TEST (is_empty) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_one_i) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_integer (s, 0));
    CHECK (! empty (s));
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

TEST (push_pop_one_s) {
    struct sl * s = create();
    CHECK (s != 0);
    CHECK (push_string (s, ""));
    CHECK (! empty (s));
    CHECK (pop (s));
    CHECK (empty (s));
    destroy(s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_destroy, is_empty);
