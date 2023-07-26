#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

class value {
public:
    enum type_id { NUMBER, REGISTER, MEMORY };

    void set_number_value (int n) { type = NUMBER; val = n; }
    void set_register_reference (char r) { type = REGISTER; reg = r; }
    void set_memory_reference (char r) { type = MEMORY; reg = r; }
    
    type_id get_type () const { return type; }
    int get_reference () const { return reg; };
    int get_value () const { return val; };

private:
    type_id type;
    int val;
    char reg;
};

class input {
public:
    virtual bool get (int & v) = 0;
};

class output {
public:
    virtual void put (int v) = 0;
};

class program {
public:
    static program * create ();
    virtual ~program () {};

    virtual void label_next (const std::string & label) = 0;

    virtual void add_assignment (const value & dst, const value & src) = 0;   //dts[src] src is the register

    virtual void add_goto (const std::string & label) = 0;
    virtual void add_if_goto (const value & cond, const std::string & label) = 0;

    virtual void add_addition (const value & dst, const value & a, const value & b) = 0;
    virtual void add_subtraction (const value & dst, const value & a, const value & b) = 0;
    virtual void add_multiplication (const value & dst, const value & a, const value & b) = 0;
    virtual void add_division (const value & dst, const value & a, const value & b) = 0;
    virtual void add_equals (const value & dst, const value & a, const value & b) = 0;
    virtual void add_not_equals (const value & dst, const value & a, const value & b) = 0;
    virtual void add_less_than (const value & dst, const value & a, const value & b) = 0;
    virtual void add_greater_than (const value & dst, const value & a, const value & b) = 0;
    virtual void add_greater_or_equal (const value & dst, const value & a, const value & b) = 0;
    virtual void add_less_or_equal (const value & dst, const value & a, const value & b) = 0;

    virtual void add_input (const value & dst, const value & end_cond) = 0;
    virtual void add_output (const value & src) = 0;

    virtual void add_halt () = 0;

    virtual void set_input (input * in) = 0;
    virtual void set_output (output * out) = 0;

    virtual void run () = 0;
};

#endif
