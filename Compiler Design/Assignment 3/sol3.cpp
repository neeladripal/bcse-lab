#include <iostream>
#include <string>
#include <vector>
#include <ios>    //used to get stream size
#include <limits> //used to get numeric limits
#include <unistd.h>
using namespace std;

vector<string> parse(const string &prod)
{
    vector<string> productions;
    string s = prod.substr(5);
    string p = "";
    for (char ch : s)
    {
        if (ch == '|')
        {
            productions.push_back(p);
            p = "";
        }
        else
            p += ch;
    }
    if (s[s.length() - 1] == '|' || s == "")
        productions.push_back("#");
    else
        productions.push_back(p);
    return productions;
}

vector<string> concat_prod(const vector<string> &prods, const string &prod)
{
    vector<string> productions;
    for (string pr : prods)
    {
        productions.push_back(pr + prod);
    }
    return productions;
}

void remLR_dir(const string &prod, const vector<string> &productions, vector<string> &res)
{
    char c = prod[0];
    vector<string> recur, non_recur;
    for (int i = 0; i < productions.size(); i++)
    {
        if (productions[i][0] != c)
            non_recur.push_back(productions[i]);
        else
            recur.push_back(productions[i].substr(1));
    }
    if (recur.empty())
    {
        res.push_back(prod);
        return;
    }
    string p = "";
    string y = string(1, c);
    p += y + " -> ";
    for (string x : non_recur)
        p += ((x == "#") ? "" : x) + y + "\'|";
    res.push_back(p.substr(0, p.size() - 1));
    p = "";
    p += y + "\' -> ";
    for (string x : recur)
        p += x + y + "\'|";
    // p += "#";
    res.push_back(p);
    return;
}

vector<string> remLR_indir(const vector<string> &inp, vector<vector<string> > &parsed_prod)
{
    vector<string> res;
    for (int i = 0; i < inp.size(); i++)
    {
        char ci = inp[i][0];
        for (int j = 0; j < i; j++)
        {
            char cj = inp[j][0];
            for (vector<string>::iterator it = parsed_prod[i].begin(); it != parsed_prod[i].end();)
            {
                if ((*it)[0] == cj)
                {
                    vector<string> new_prod = concat_prod(parsed_prod[j], it->substr(1));
                    it = parsed_prod[i].erase(it);
                    it = parsed_prod[i].insert(it, new_prod.begin(), new_prod.end());
                    it += new_prod.size();
                }
                else
                    it++;
            }
        }
        // cout << "#" << i << " " << inp[i] << "        ";
        // for (string s: parsed_prod[i])
        //     cout << s << " ";
        // cout << "\n"; 
        remLR_dir(inp[i], parsed_prod[i], res);
    }
    return res;
}

int main()
{
    int n;
    string s;
    vector<string> inp, res;
    vector<vector<string> > parsed_prod;
    // if (isatty(fileno(stdin)))
    //     cout << "Enter number of productions:\n";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // if (isatty(fileno(stdin)))
    //     cout << "Enter productions:\n";
    while (n--)
    {
        getline(cin, s);
        inp.push_back(s);
        parsed_prod.push_back(parse(s));
    }
    res = remLR_indir(inp, parsed_prod);
    // for (int i = 0; i < inp.size(); ++i)
    //     remLR_dir(inp[i], parsed_prod[i], res);
    for (string x : res)
        cout << x << "\n";
    return 0;
}