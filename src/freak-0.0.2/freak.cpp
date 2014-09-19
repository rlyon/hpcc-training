/**
 * Borrowed from: 
 * http://stackoverflow.com/questions/4888879/elegant-ways-to-count-the-frequency-of-words-in-a-file
 */
#include <string>
#include <fstream>
#include <map>
#include <locale>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<string, int> keyvalue;

struct int_cmp {
    bool operator()(const keyvalue &lhs, const keyvalue &rhs) {
        return lhs.second > rhs.second;
    }
};

struct letter_only: ctype<char> 
{
    letter_only(): ctype<char>(get_table()) {}

    static ctype_base::mask const* get_table()
    {
        static vector<ctype_base::mask> 
            rc(ctype<char>::table_size,ctype_base::space);

        fill(&rc['A'], &rc['z'+1], ctype_base::alpha);
        return &rc[0];
    }
};

int main(int argc, char **argv)
{
    map<string, int> wordCount;
    ifstream input;
    input.imbue( locale(locale(), new letter_only()) ); //enable reading only letters!
    input.open(argv[1]);
    string word;
    while(input >> word)
    {
        ++wordCount[word];
    }

    vector<keyvalue> sortable(wordCount.begin(), wordCount.end());
    sort(sortable.begin(), sortable.end(), int_cmp());

    for (vector<keyvalue>::iterator it = sortable.begin(); it != sortable.end(); ++it)
    {
        cout << it->first <<":"<< it->second << endl;
    }
}