#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

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
    productions.push_back(p);
    return productions;
}

int main()
{
    // cout << "\nEnter number of productions: ";
    int p;
    cin >> p;
    vector<string> prodleft(p), prodright(p);
    // cout << "\nEnter productions one by one: ";
    int i;

    for (i = 0; i < p; ++i)
    {
        // cout << "\nLeft of production " << i + 1 << ": ";
        cin >> prodleft[i];
        // cout << "\nRight of production " << i + 1 << ": ";
        cin >> prodright[i];
    }
    int j;
    int e = 1;
    for (i = 0; i < p; ++i)
    {
        for (j = i + 1; j < p; ++j)
        {
            if (prodleft[j] == prodleft[i])
            {
                int k = 0;
                string com = "";
                while (k < prodright[i].length() && k < prodright[j].length() && prodright[i][k] == prodright[j][k])
                {
                    com += prodright[i][k];
                    ++k;
                }
                if (k == 0)
                    continue;
                char *buffer;
                string comleft = prodleft[i];
                if (k == prodright[i].length())
                {
                    prodleft[i] += to_string(e);
                    prodleft[j] += to_string(e);
                    prodright[i] = "^";
                    prodright[j] = prodright[j].substr(k, prodright[j].length() - k);
                }
                else if (k == prodright[j].length())
                {
                    prodleft[i] += to_string(e);
                    prodleft[j] += to_string(e);
                    prodright[j] = "^";
                    prodright[i] = prodright[i].substr(k, prodright[i].length() - k);
                }
                else
                {
                    prodleft[i] += to_string(e);
                    prodleft[j] += to_string(e);
                    prodright[j] = prodright[j].substr(k, prodright[j].length() - k);
                    prodright[i] = prodright[i].substr(k, prodright[i].length() - k);
                }
                int l;
                for (l = j + 1; l < p; ++l)
                {
                    if (comleft == prodleft[l] && com == prodright[l].substr(0, fmin(k, prodright[l].length())))
                    {
                        prodleft[l] += to_string(e);
                        prodright[l] = prodright[l].substr(k, prodright[l].length() - k);
                    }
                }
                prodleft.push_back(comleft);
                prodright.push_back(com + prodleft[i]);
                ++p;
                ++e;
            }
        }
    }
    cout << "\nLeft Factoring removed -> \n";
    for (i = 0; i < p; ++i)
    {
        cout << prodleft[i] << "->" << prodright[i] << "\n";
    }
    return 0;
}