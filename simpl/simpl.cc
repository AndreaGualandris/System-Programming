#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "program.h"

bool parse_value (value & v, const std::string & s) {
    if (s.length() == 1 && islower(s[0])) {
	v.set_register_reference (s[0]);
	return true;
    }
    if (s.length() == 2 && s[0] == '@' && islower(s[1])) {
	v.set_memory_reference (s[1]);
	return true;
    }
    try {
	v.set_number_value(std::stoi(s));
	return true;
    } catch (std::invalid_argument & e) {
	return false;
    } catch (std::out_of_range & e) {
	return false;
    }
}

static bool read_d_a_b (std::istream & input, value & d, value & a, value & b) {
    std::string dst, opa, opb;
    if ((input >> dst >> opa >> opb)
	&& parse_value(d, dst) && d.get_type() != value::NUMBER
	&& parse_value(a, opa) && parse_value(b, opb))
	return true;
    return false;
}

bool read_program (program * p, const char * fname) {
    std::ifstream input (fname);
    std::string s;
    for (;;) {
	if (! (input >> s))
	    return true;

	std::string label;
	if (s.length() > 1 && s[s.length() - 1] == ':') {
	    p->label_next (s.substr(0, s.length() - 1));
	    if (! (input >> s))
		return false;
	}
	if (s == "assign") {
	    std::string dst, src;
	    value d, s;
	    if (! (input >> dst >> src) || !parse_value(s, src) || !parse_value(d, dst))
		return false;
	    p->add_assignment(d,s);
	    continue;
	}
	if (s == "add") {
	    value d, a, b;
	    if (!read_d_a_b(input, d, a, b))
		return false;
	    p->add_addition (d, a, b);
	    continue;
	}
	if (s == "sub") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_subtraction (d, a, b);
	    continue;
	}
	if (s == "mul") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_multiplication (d, a, b);
	    continue;
	}
	if (s == "div") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_division (d, a, b);
	    continue;
	}
	if (s == "eq") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_equals (d, a, b);
	    continue;
	}
	if (s == "neq") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_not_equals (d, a, b);
	    continue;
	}
	if (s == "lt") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_less_than (d, a, b);
	    continue;
	}
	if (s == "gt") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_greater_than (d, a, b);
	    continue;
	}
	if (s == "gte") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_greater_or_equal (d, a, b);
	    continue;
	}
	if (s == "lte") {
	    value d, a, b;
	    if (!read_d_a_b (input, d, a, b))
		return false;
	    p->add_less_or_equal (d, a, b);
	    continue;
	}
	if (s == "goto") {
	    std::string dst;
	    if (! (input >> dst))
		return false;
	    p->add_goto (dst);
	    continue;
	}
	if (s == "if") {
	    std::string dst, cond;
	    value c;
	    if (! (input >> cond >> dst) || !parse_value(c, cond))
		return false;
	    p->add_if_goto (c, dst);
	    continue;
	}
	if (s == "input") {
	    std::string dst, end;
	    value d, e;
	    if (! (input >> dst >> end) || !parse_value(d, dst) || !parse_value(e, end))
		return false;
	    p->add_input (d, e);
	    continue;
	}
	if (s == "output") {
	    std::string src;
	    value s;
	    if (! (input >> src) || !parse_value(s, src))
		return false;
	    p->add_output (s);
	    continue;
	}
	if (s == "halt") {
	    p->add_halt ();
	    continue;
	}
	return false;
    }
}

class istream_input : public input {
public:
    istream_input (std::istream & i)
	: in (i) {};
    virtual bool get (int & v) {
	if (!in)
	    return false;
	in >> v;
	return ! in.fail();
    };
private:
    std::istream & in;
};

class ostream_output : public output {
public:
    ostream_output (std::ostream & o)
	: out (o) {};
    virtual void put (int v) {
	out << v << std::endl;;
    };
private:
    std::ostream & out;
};

int main (int argc, char * argv[]) {
    const char * progname = "PROGRAM";
    if (argc > 1)
	progname = argv[1];

    program * p = program::create();

    if (!read_program (p, progname)) {
	std::cerr << "bad program" << std::endl;
	return EXIT_FAILURE;
    }

    istream_input in (std::cin);
    ostream_output out (std::cout);

    p->set_input(&in);
    p->set_output(&out);

    p->run();

    delete (p);

    return EXIT_SUCCESS;
};
