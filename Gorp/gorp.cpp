#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

map<string, string> variables;
stack<string> s;

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
    s.push(to_string(a > b)); // attenzione a cosa sto pushando (note: devi pushare true o stringa vuota)
}

void less_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a < b)); // attenzione a cosa sto pushando
}

void equal()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a == b)); // attenzione a cosa sto pushando
}

void not_equal()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a != b)); // attenzione a cosa sto pushando
}

void greater_equal_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a >= b)); // attenzione a cosa sto pushando
}

void less_equal_fun()
{
    int b = stoi(popStack());
    int a = stoi(popStack());
    s.push(to_string(a <= b)); // attenzione a cosa sto pushando
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
    // pop 3 timesa b, a , c. if (c != emptyString) -> cout a else -> cout b
    string b = popStack();
    string a = popStack();
    string c = popStack();

    if (c == "")
        cout << b; //eseguire il; codice contenuto in b, se possibile scriverlo su cin e poi chiamare la funzione read_input 
    else
        cout << a;
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
    }
    else if (word == "*")
    {
        mul();
    }
    else if (word == "/")
    {
        div();
    }
    else if (word == ">")
    {
        greater_fun();
    }
    else if (word == "<")
    {
        less_fun();
    }
    else if (word == "==")
    {
        equal();
    }
    else if (word == "!=")
    {
        not_equal();
    }
    else if (word == ">=")
    {
        greater_equal_fun();
    }
    else if (word == "<=")
    {
        less_equal_fun();
    }
    else if (word == "load")
    {
        load();
    }
    else if (word == "store")
    {
        store();
    }
    else if (word == "if")
    {
        cond_if();
    }
    else if (word.find("input"))
    {
        string input;
        cin >> input;
        s.push(input); // controllare se e' apposto
    }
    else
    {
        return 0;
    }
}

int addition()
{
}

void read_input()
{
    int open = 0;
    string line;

    while (getline(cin, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            // call function for check the symbols and the variables
            if (check_operation(word))
                continue;

            if (word == "{")
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
}

int main()
{

    // read a line from the stdin and push it onto the stack word by word, if there is a { it will push only the block of code into the parenthesis} into the stack

    // solve_stack(s, variables);

    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}

