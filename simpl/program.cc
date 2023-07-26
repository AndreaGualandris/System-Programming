#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <functional>

#include "program.h"

class instruction
{
public:
    ~instruction(){};

    virtual int execute(int index) = 0;
};

class program_impl : public program
{
public:
    std::map<int, int> *my_register;
    std::vector<int> *memory;
    std::vector<instruction *> *instructions;
    std::map<std::string, int> *labels;
    input *myInput;
    output *myOutput;

    program_impl()
    {
        my_register = new std::map<int, int>();

        for (char i = 'a'; i < 'a' + 26; i++)
            my_register->insert(std::pair<int, int>(i, 0));

        memory = new std::vector<int>(10000, 0);
        instructions = new std::vector<instruction *>();
        labels = new std::map<std::string, int>();
        myInput = nullptr;
        myOutput = nullptr;
    };

    void set_input(input *in) override
    {
        myInput = in;
    }

    void set_output(output *out) override
    {
        myOutput = out;
    }

    void run() override
    {
        int i = 0;
        while (i != -1)
        {
            i = instructions->at(i)->execute(i);
        }
    }

    virtual void label_next(const std::string &label);
    virtual void add_assignment(const value &dst, const value &src);
    virtual void add_goto(const std::string &label);
    virtual void add_if_goto(const value &cond, const std::string &label);
    virtual void add_addition(const value &dst, const value &a, const value &b);
    virtual void add_subtraction(const value &dst, const value &a, const value &b);
    virtual void add_multiplication(const value &dst, const value &a, const value &b);
    virtual void add_division(const value &dst, const value &a, const value &b);
    virtual void add_equals(const value &dst, const value &a, const value &b);
    virtual void add_not_equals(const value &dst, const value &a, const value &b);
    virtual void add_less_than(const value &dst, const value &a, const value &b);
    virtual void add_greater_than(const value &dst, const value &a, const value &b);
    virtual void add_greater_or_equal(const value &dst, const value &a, const value &b);
    virtual void add_less_or_equal(const value &dst, const value &a, const value &b);
    virtual void add_input(const value &dst, const value &end_cond);
    virtual void add_output(const value &src);
    virtual void add_halt();
};

class jump : public instruction
{

public:
    jump(const std::string l, program_impl *prog)
        : p(prog),
          label(l) {}

    std::string label;
    program_impl *p;

    ~jump(){};
};

class goTo : public jump
{

public:
    goTo(const std::string l, program_impl *prog) : jump(l, prog) {}

    ~goTo(){};

    int execute(int index) override
    {
        return p->labels->at(label);
    }
};

class ifgoTo : public jump
{
public:
    ifgoTo(value c, std::string l, program_impl *prog)
        : cond(c), jump(l, prog) {}

    ~ifgoTo(){};

    int execute(int index) override
    {
        if (cond.get_type() == value::REGISTER && p->my_register->at(cond.get_reference()))
            return p->labels->at(label);
        else
            return ++index;
    }

private:
    value cond;
};

class halt : public instruction
{
public:
    ~halt(){};

    int execute(int index) override
    {
        return -1;
    }
};

class assign : public instruction
{

public:
    assign(value dst, value src, program_impl *prog)
        : dest(dst),
          src(src),
          p(prog) {}

    ~assign(){};

    int execute(int index) override
    {
        int tmp = 0;

        switch (src.get_type())
        {
        case value::NUMBER:
            tmp = src.get_value();
            break;

        case value ::REGISTER:
            tmp = p->my_register->at(src.get_reference());
            break;

        case value::MEMORY:
            tmp = p->memory->at(p->my_register->at(src.get_reference()));
            break;

        default:
            break;
        }

        switch (dest.get_type())
        {
        case value::REGISTER:
            p->my_register->at(dest.get_reference()) = tmp;
            break;

        case value::MEMORY:
            if (p->my_register->at(dest.get_reference()) > (int)(p->memory->size() - 1))
                p->memory->resize(p->my_register->at(dest.get_reference()) + 1, 0);
            p->memory->at(p->my_register->at(dest.get_reference())) = tmp;
            break;

        default:
            break;
        }
        return ++index;
    }

private:
    value dest;
    value src;
    program_impl *p;
};

class pOutput : public instruction
{
public:
    pOutput(value src, program_impl *prog)
        : src(src),
          p(prog){};

    ~pOutput(){};

    int execute(int index) override
    {
        switch (src.get_type())
        {

        case value::NUMBER:
            p->myOutput->put(src.get_value());
            break;

        case value::REGISTER:
            p->myOutput->put(p->my_register->at(src.get_reference()));
            break;

        case value::MEMORY:
            p->myOutput->put(p->memory->at(p->my_register->at(src.get_reference())));
            break;

        default:
            break;
        }

        return ++index;
    }

private:
    value src;
    program_impl *p;
};

class pInput : public instruction
{

public:
    pInput(value d, value endCond, program_impl *prog)
        : dest(d),
          end_cond(endCond),
          p(prog){};

    ~pInput(){};

    int execute(int index) override
    {
        int tmp = 0;

        switch (dest.get_type())
        {
        case value::REGISTER:
            tmp = !p->myInput->get(p->my_register->at(dest.get_reference()));
            break;

        case value::MEMORY:
            tmp = !p->myInput->get(p->memory->at(p->my_register->at(dest.get_reference())));
            break;

        default:
            break;
        }

        switch (end_cond.get_type())
        {
        case value ::REGISTER:
            p->my_register->at(end_cond.get_reference()) = tmp;
            break;

        case value::MEMORY:
            p->memory->at(p->my_register->at(end_cond.get_reference())) = tmp;
            break;

        default:
            break;
        }

        return ++index;
    }

private:
    program_impl *p;
    value dest;
    value end_cond;
};

class calculator : public instruction
{

public:
    calculator(
        const value &d,
        const value &a,
        const value &b,
        program_impl *prog,
        int (*function)(int, int))
        : p(prog),
          dest(d),
          first_value(a),
          second_value(b),
          function(function){};

    ~calculator(){};

    int execute(int index) override
    {
        int tmp1 = 0, tmp2 = 0;

        //first value
        switch (first_value.get_type())
        {
        case value::NUMBER:
            tmp1 = first_value.get_value();
            break;

        case value::REGISTER:
            tmp1 = p->my_register->at(first_value.get_reference());
            break;

        case value::MEMORY:
            tmp1 = p->memory->at(p->my_register->at(first_value.get_reference()));
            break;

        default:
            break;
        }

        //second value
        switch (second_value.get_type())
        {
        case value::NUMBER:
            tmp2 = second_value.get_value();
            break;

        case value::REGISTER:
            tmp2 = p->my_register->at(second_value.get_reference());
            break;

        case value::MEMORY:
            tmp2 = p->memory->at(p->my_register->at(second_value.get_reference()));
            break;

        default:
            break;
        }

        switch (dest.get_type())
        {
        case value::REGISTER:
            p->my_register->at(dest.get_reference()) = function(tmp1, tmp2);
            break;

        case value::MEMORY:
            p->memory->at(p->my_register->at(dest.get_reference()) = function(tmp1, tmp2));
            break;

        default:
            break;
        }

        return ++index;
    }

private:
    value dest;
    value first_value;
    value second_value;
    program_impl *p;
    int (*function)(int, int);
};
/* 
#pragma region lambda functions

auto addition = [](int first, int second)
{ return first + second; };

auto subtraction = [](int first, int second)
{ return first - second; };

auto multiplication = [](int first, int second)
{ return first * second; };

auto division = [](int first, int second)
{ return first / second; };

auto equals = [](int first, int second) -> int
{ return first == second; };

auto not_equals = [](int first, int second) -> int
{ return first == second; };

auto less_than = [](int first, int second) -> int
{ return first < second; };

auto greater_than = [](int first, int second) -> int
{ return first > second; };

auto greater_or_equal = [](int first, int second) -> int
{ return first >= second; };

auto less_than_equal = [](int first, int second) -> int
{ return first <= second; };

#pragma endregion

void program_impl::add_assignment(const value &dst, const value &src)
{
    instructions->push_back(new assign(dst, src, this));
};
void program_impl::label_next(const std::string &label)
{
    labels->insert(std::pair<std::string, int>(label, (int)instructions->size()));
};
void program_impl::add_goto(const std::string &label)
{
    instructions->push_back(new goTo(label, this));
};
void program_impl::add_if_goto(const value &cond, const std::string &label)
{
    instructions->push_back(new ifgoTo(cond, label, this));
};
void program_impl::add_addition(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, addition));
};
void program_impl::add_subtraction(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, subtraction));
};
void program_impl::add_multiplication(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, multiplication));
};
void program_impl::add_division(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, division));
};
void program_impl::add_equals(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, equals));
};
void program_impl::add_not_equals(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, not_equals));
};
void program_impl::add_less_than(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, less_than));
};
void program_impl::add_greater_than(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, greater_than));
};
void program_impl::add_greater_or_equal(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, greater_or_equal));
};
void program_impl::add_less_or_equal(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, less_than_equal));
};
 */

void program_impl::add_assignment(const value &dst, const value &src)
{
    instructions->push_back(new assign(dst, src, this));
};

void program_impl::label_next(const std::string &label)
{
    labels->insert(std::pair<std::string, int>(label, (int)instructions->size()));
};

void program_impl::add_goto(const std::string &label)
{
    instructions->push_back(new goTo(label, this));
};
void program_impl::add_if_goto(const value &cond, const std::string &label)
{
    instructions->push_back(new ifgoTo(cond, label, this));
};

void program_impl::add_addition(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first + second; }));
};
void program_impl::add_subtraction(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first - second; }));
};
void program_impl::add_multiplication(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first * second; }));
};
void program_impl::add_division(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first / second; }));
};
void program_impl::add_equals(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first == second; }));
};
void program_impl::add_not_equals(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first != second; }));
};
void program_impl::add_less_than(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first < second; }));
};
void program_impl::add_greater_than(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first > second; }));
};
void program_impl::add_greater_or_equal(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first >= second; }));
};
void program_impl::add_less_or_equal(const value &dst, const value &a, const value &b)
{
    instructions->push_back(new calculator(dst, a, b, this, [](int first, int second) -> int
                                           { return first <= second; }));
};

//input e output
void program_impl::add_input(const value &dst, const value &end_cond)
{
    instructions->push_back(new pInput(dst, end_cond, this));
};
void program_impl::add_output(const value &src)
{
    instructions->push_back(new pOutput(src, this));
};

//halt
void program_impl::add_halt()
{
    instructions->push_back(new halt());
};

program *program ::create()
{
    return new program_impl();
};
