#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <string.h>
#include <signal.h>
#include <ctime>

#include "Container.h"
#include "SkipList.h"

using namespace std;

#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define WHITE       "\033[m"
#define TEMP_FILE   "temp"
#define TEST_NUM    6
SkipList skiplist;
fstream temp;
streambuf *backup;
int grade;
int test_number;

void build_container(Container *container, string input_file_path)
{
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return;
    }

    string line;
    while (inputData >> line)
    {
        int bracketPos = line.find('(');
        string op = line.substr(0, bracketPos);
        string param = line.substr(bracketPos + 1, line.size() - bracketPos - 2);
        if (op == "Insert")
        {
            int commaPos = param.find(',');
            int key = atoi(param.substr(0, commaPos).c_str());
            int val = atoi(param.substr(commaPos + 1).c_str());
            container->Insert(key, val);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
            container->Search(key);
        }
        else if (op == "Delete")
        {
            int key = atoi(param.c_str());
            container->Delete(key);
        }
    }
    container->Display();
    inputData.close();
}



int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        cout << "[usage]: ./main options [input_file_path]" << endl;
        return 0;
    }
    if ((*argv[1] == 'h' || *argv[1] == 's') && argc != 3) {
        cout << "[usage]: ./main h(or s) input_file_path" << endl;
        return 0;
    }

    switch(*argv[1]) {
        case 's':
            build_container(&skiplist, argv[2]);
            int length = 0;
            srand(time(NULL));
            for(int i = 0; i < 10000; ++i){
                int key = rand()%500 + 1;
                length += skiplist.Search(key);
            }
            double avg_length = length/10000.0;
            cout<<"length : "<<avg_length<<endl;
            break;

    }

    return 0;
}

