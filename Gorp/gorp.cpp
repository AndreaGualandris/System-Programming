#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

using namespace std;

map<string, string> variables;
stack<string> s;

void read_input(string line);

string popStack()
{
    if (s.empty())
        return "";

    string word = s.top();
    s.pop();
    return word;
}

void add()
{
    string b = popStack();
    string a = popStack();
    s.push(to_string(stoi(a) + stoi(b)));
}

void sub()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a - b));
}

void mul()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a * b));
}

void div()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a / b));
}

void greater_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a > b)
        s.push("true");
    else
        s.push("");
}

void less_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a < b)
        s.push("true");
    else
        s.push("");
}

void equal()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a == b)
        s.push("true");
    else
        s.push("");
}

void not_equal()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a != b)
        s.push("true");
    else
        s.push("");
}

void greater_equal_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a >= b)
        s.push("true");
    else
        s.push("");
}

void less_equal_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    if (a <= b)
        s.push("true");
    else
        s.push("");
}

void concat_fun()
{
    string b = popStack();
    string a = popStack();
    s.push(a + b);
}

void load()
{
    string var = popStack();
    s.push(variables[var]);
}

void store()
{
    string var = popStack();
    string value = popStack();
    variables[var] = value;
}

void cond_if()
{
    string a = popStack();
    string c = popStack();

    if (c != "")
        read_input(a);
}

void cond_ifelse()
{
    string b = popStack();
    string a = popStack();
    string c = popStack();

    if (c == "")
        read_input(b);
    else
        read_input(a);
}

void duplicate()
{
    string a = popStack();
    s.push(a);
    s.push(a);
}

void while_fun()
{
    string a = popStack();
    string c = popStack();
    while (c != "")
    {
        read_input(a);
        c = popStack();
    }
}

int check_operation(string word)
{
    if (word == "+")
    {
        add();
        return 1;
    }
    else if (word == "-")
    {
        sub();
        return 1;
    }
    else if (word == "*")
    {
        mul();
        return 1;
    }
    else if (word == "/")
    {
        div();
        return 1;
    }
    else if (word == ">")
    {
        greater_fun();
        return 1;
    }
    else if (word == "<")
    {
        less_fun();
        return 1;
    }
    else if (word == "==")
    {
        equal();
        return 1;
    }
    else if (word == "!=")
    {
        not_equal();
        return 1;
    }
    else if (word == ">=")
    {
        greater_equal_fun();
        return 1;
    }
    else if (word == "<=")
    {
        less_equal_fun();
        return 1;
    }
    else if (word == ".")
    {
        concat_fun();
        return 1;
    }
    else if (word == "load")
    {
        load();
        return 1;
    }
    else if (word == "store")
    {
        store();
        return 1;
    }
    else if (word == "if")
    {
        cond_if();
        return 1;
    }
    else if (word == "ifelse")
    {
        cond_ifelse();
        return 1;
    }
    else if (word == "dup")
    {
        duplicate();
        return 1;
    }
    else if (word == "while")
    {
        while_fun();
        return 1;
    }
    else if (word.find("input") != string::npos)
    {
        string input;
        cin >> input;
        s.push(input); // controllare se e' apposto
        return 1;
    }
    else if (word.find("output") != string::npos)
    {
        cout << popStack() << endl;
        return 1;
    }
    else
    {
        return 0;
    }
}


void read_input(string line) 
{
    int open = 0;

    istringstream iss(line);
    string word;

    while (iss >> word)
    {
        // call function for check the keys and the variables
        if (check_operation(word))
            continue;

        else if (word == "{")
        {
            string block;
            while (iss >> word)
            {
                if (word == "{")
                {
                    open++;
                }
                else if (open > 0 && word == "}")
                {
                    open--;
                }
                else if (word == "}" && open == 0)
                {
                    break;
                }
                block += word + " ";
            }
            s.push(block);
        }
        else
        {
            s.push(word);
        }
    }
}


void cin_program()
{
    string line;

    while (getline(cin, line))
    {
        try
        {
            read_input(line);
        }
        catch (const std::exception &e)
        {
            cerr << "Error: " << e.what() << '\n';
        }
    }
}

void format_input(string file)
{
    ifstream myfile(file);

    if (!myfile.is_open())
        throw std::runtime_error("Error: File not found");

    string line;
    string input;
    while (getline(myfile, line))
    {
        input += line + " ";
    }
    read_input(input);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cin_program();
    }
    else
    {
        string file = argv[1];
        try
        {
            format_input(file);
        }
        catch (const std::exception &e)
        {
            cerr << "Error: " << e.what() << '\n';
        }
    }
}

// 1 2 + 3 4 + * 5 6 + * output
// result: 77
// 0 n store n load 1 + output
// result: 1
// 0 n store n load 1 + n load output output
// result: 0 1
// 1 do { 1 + } while output
// result: 1
