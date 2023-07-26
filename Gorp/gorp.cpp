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
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    s.push(to_string(stoi(a) + stoi(b)));
}

void sub()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    s.push(to_string(stoi(a) - stoi(b)));
}

void mul()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    s.push(to_string(stoi(a) * stoi(b)));
}

void div()
{
  
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(b) == 0)
    {
        cout << "Error: division by zero" << endl;
        exit(1);
    }
    s.push(to_string(stoi(a) / stoi(b)));
}

void greater_fun()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) > stoi(b))
        s.push("true");
    else
        s.push("");
}

void less_fun()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) < stoi(b))
        s.push("true");
    else
        s.push("");
}

void equal()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) == stoi(b))
        s.push("true");
    else
        s.push("");
}

void not_equal()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) != stoi(b))
        s.push("true");
    else
        s.push("");
}

void greater_equal_fun()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) >= stoi(b))
        s.push("true");
    else
        s.push("");
}

void less_equal_fun()
{
    string b = popStack();
    string a = popStack();
    if (a == "" || b == "")
    {
        cout << "Error: not enough arguments" << endl;
        exit(1);
    }
    if (stoi(a) <= stoi(b))
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
    if (variables.find(var) == variables.end())
    {
        cout << "Error: variable not found" << endl;
        exit(1);
    }
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
        try
        {
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
        catch (const std::exception &e)
        {
            cerr << "Error: " << e.what() << '\n';
        }
    }
}

int check_parentesis(string line)
{
    int open = 0;
    int close = 0;

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '{')
            open++;
        else if (line[i] == '}')
            close++;
    }

    if (open == close)
        return 1;
    else
        return 0;
}

void cin_program()
{
    string line;

    while (getline(cin, line))
    {
        try
        {
            if (!check_parentesis(line))
            {
                throw std::runtime_error("Parenthesis not balanced inline, if you want write in multiple line:\n\nWrite the code in a file and run the program with the file as argument\n");
            }
            else
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
    if (!check_parentesis(input))
        throw std::runtime_error("Error: Parenthesis not balanced");

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
