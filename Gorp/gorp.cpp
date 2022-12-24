#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

map<string, string> variables;
stack<string> s;

void read_input(string line);
void cond_ifelse();

string popStack()
{
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

void while_fun(){
    string a = popStack();
    string c = popStack();
    while(c != ""){
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


void read_input(string line) // passare la stringa da cui leggere per i blocchi di codice nello stack
{
    int open = 0;

    istringstream iss(line);
    string word;

    while (iss >> word)
    {
        // call function for check the symbols and the variables
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
            // cout << word << endl;
            s.push(word);
        }
    }
}



int main()
{

    // read a line from the stdin and push it onto the stack word by word, if there is a { it will push only the block of code into the parenthesis} into the stack

    // solve_stack(s, variables);

    string line;

    while (getline(cin, line))
    {
        read_input(line);
    }

    // while (!s.empty())
    // {
    //     cout << s.top() << endl;
    //     s.pop();
    // }
}
