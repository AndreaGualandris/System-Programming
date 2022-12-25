// //function that extracts a block of code from a string, and returns it as a string
// //the block is contained between two delimiters { and }
// // the function returns the block of code, and the position of the end of the block
// // use istringstream to extract the block of code

// #include <iostream>
// #include <string>
// #include <sstream>
// using namespace std;

// // string getBlock(string s, int &pos)
// // {
// //     string block;
// //     int count = 0;
// //     int i = pos;
// //     while (i < s.length())
// //     {
// //         if (s[i] == '{')
// //         {
// //             count++;
// //         }
// //         else if (s[i] == '}')
// //         {
// //             count--;
// //         }
// //         if (count == 0)
// //         {
// //             block = s.substr(pos, i - pos + 1);
// //             pos = i + 1;
// //             return block;
// //         }
// //         i++;
// //     }
// //     return block;
// // }

// // void read_input(string line)
// // {
// //     int open = 0;
// //     int pos = 0;
// //     string block;
// //     while (pos < line.length())
// //     {
// //         if (line[pos] == '{')
// //         {
// //             block = getBlock(line, pos);
// //             s.push(block);
// //         }
// //         else if (line[pos] == '}')
// //         {
// //             // cout << "Error: Invalid Sintax \"}\" " << endl;       //invalid sintax
// //             break;
// //         }
// //         else
// //         {
// //             string word;
// //             while (pos < line.length() && line[pos] != ' ')
// //             {
// //                 word += line[pos];
// //                 pos++;
// //             }
// //             if (check_operation(word))
// //                 continue;
// //             else
// //             {
// //                 s.push(word);
// //             }
// //         }
// //         pos++;
// //     }
// // }

// int check_parentesis(ifstream &myfile, istringstream &iss, string word, int count)
// {
//     string block;

//     do
//     {
//         if (word == "{")
//         {
//             count++;
//         }
//         else if (word == "}" && count == 0)
//         {
//             cout << "Error: Invalid Sintax \"}\" " << endl; // invalid sintax
//             return 0;
//         }
//         else if (word == "}" && count > 0)
//         {
//             count--;
//         }
//         block += word + " ";

//         // if count != 0 and iss.fail() then get a new line from myfile

//     } while (iss >> word);

//     if (count != 0 && iss.fail())
//     {
//         string line;
//         getline(myfile, line);
//         iss.clear();
//         iss.str(line);
//         check_parentesis(myfile, iss, word, count);
//     }
// }



// istringstream &words(ifstream &myfile, istringstream &iss)
// {
//     string word;
//     string line;
//     int open = 0;

//     while (iss >> word)
//     {
//         // call function for check the keys and the variables
//         if (check_operation(word))
//             continue;

//         else if (word == "{")
//         {
//             open++;
//             string block;

//             while (exit)
//             {
//                 iss >> word;

//                 if (iss.fail() && open != 0)
//                 {
//                     getline(myfile, line);
//                     istringstream iss(line);
//                     iss >> word;
//                 }
//                 else if (iss.fail() && open == 0)
//                 {
//                     break;
//                 }

//                 if (word == "{")
//                 {
//                     open++;
//                 }
//                 else if (open > 0 && word == "}")
//                 {
//                     open--;
//                 }

//                 if (word == "}" && open == 0)
//                 {
//                     // cout << "Error: Invalid Sintax \"}\" " << endl;       //invalid sintax
//                     break;
//                 }
//                 block += word + " ";

//                 // non finisce di leggere la riga quando finisce il count delle parentesi
//             }
//             s.push(block);
//         }
//         else
//         {
//             s.push(word);
//         }
//     }
// }

// void read_input_file(ifstream &myfile, istringstream &iss)
// {
//     // se iss != fail allora leggi da iss
//     // se iss == fail allora getline da myfile su line e leggi da iss
//     // call read_input_file(myfile, iss)

//     int open = 0;
//     int exit = 1;
//     string line;
//     string word;

//     if (iss.fail())
//     {
//         while (iss >> word)
//         {
//         }
//     }
//     while (getline(myfile, line))
//     {
//         istringstream iss(line);

//         while (iss >> word)
//         {
//             // call function for check the keys and the variables
//             if (check_operation(word))
//                 continue;

//             else if (word == "{")
//             {
//                 open++;
//                 string block;

//                 while (exit)
//                 {
//                     iss >> word;

//                     if (iss.fail() && open != 0)
//                     {
//                         getline(myfile, line);
//                         istringstream iss(line);
//                         iss >> word;
//                     }
//                     else if (iss.fail() && open == 0)
//                     {
//                         break;
//                     }

//                     if (word == "{")
//                     {
//                         open++;
//                     }
//                     else if (open > 0 && word == "}")
//                     {
//                         open--;
//                     }

//                     if (word == "}" && open == 0)
//                     {
//                         // cout << "Error: Invalid Sintax \"}\" " << endl;       //invalid sintax
//                         break;
//                     }
//                     block += word + " ";

//                     // non finisce di leggere la riga quando finisce il count delle parentesi
//                 }
//                 s.push(block);
//             }
//             else
//             {
//                 s.push(word);
//             }
//         }
//     }
// }

// void read_input2(string file) // passare la stringa da cui leggere per i blocchi di codice nello stack
// {
//     int open = 0;
//     int exit = 1;

//     ifstream myfile(file);
//     string line;

//     while (getline(myfile, line))
//     {
//         istringstream iss(line);
//         string word;

//         while (iss >> word)
//         {
//             // call function for check the keys and the variables
//             if (check_operation(word))
//                 continue;

//             else if (word == "{")
//             {
//                 open++;
//                 string block;

//                 while (exit)
//                 {
//                     iss >> word;

//                     if (iss.fail() && open != 0)
//                     {
//                         getline(myfile, line);
//                         istringstream iss(line);
//                         iss >> word;
//                     }
//                     else if (iss.fail() && open == 0)
//                     {
//                         break;
//                     }

//                     if (word == "{")
//                     {
//                         open++;
//                     }
//                     else if (open > 0 && word == "}")
//                     {
//                         open--;
//                     }

//                     if (word == "}" && open == 0 && iss.fail())
//                     {
//                         // cout << "Error: Invalid Sintax \"}\" " << endl;       //invalid sintax
//                         break;
//                     }
//                     block += word + " ";

//                     // non finisce di leggere la riga quando finisce il count delle parentesi
//                 }
//                 s.push(block);
//             }
//             else
//             {
//                 s.push(word);
//             }
//         }
//     }
// }

// void read(istringstream &stream)
// {
//     string line;
//     istringstream iss(line);
//     string word;
//     while (getline(stream, line))
//     {
//         try
//         {
//             read_input(line);
//         }
//         catch (const std::exception &e)
//         {
//             cerr << "Error: " << e.what() << '\n';
//         }
//     }
// }


