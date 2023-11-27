#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

void distinctNumber(void);
void distinctString(void);
void distinctList(void);
void distinctMap(void);
void distinctSet(void);
void distinctQueue(void);
void distinctStack(void);

int main()
{
    string invl;

    cout << "Input[number|string|list|map|set|queue|stack]: ";
    cin >> invl;

    if (invl == "number")
    {distinctNumber();}
    else if (invl == "string")
    {distinctString();}
    else if (invl == "list")
    {distinctList();}
    else if (invl == "map")
    {distinctMap();}
    else if (invl == "set")
    {distinctSet();}
    else if (invl == "queue")
    {distinctQueue();}
    else if (invl == "stack")
    {distinctStack();}
    else
    {
        cout << "Error: " << invl << endl;
        cout << "Usage: number|string|list" << endl;
    }
    return 0;
}

void distinctNumber(void)
{
    int invl = 0;

    vector<int> vvctr;
    vector<int> vodd;
    vector<int> vevn;
    vector<int> v_dec[10];
    
    int maxv = 0;
    int minv = 999999999;

    while (true)
    {
        cout << "1<=99: ";
        cin >> invl;
        if (invl <= 0)
        {
            break;
        }
        if (maxv < invl)
        {maxv = invl;}
        if (invl < minv)
        {minv = invl;}

        vvctr.push_back(invl);

        v_dec[invl % 10].push_back(invl);
    }
    if (invl == -1)
    {
        for (int i = 0; i < vvctr.size(); i++)
        {
            if (vvctr[i] & 1)
            {vodd.push_back(vvctr[i]);}
            else
            {vevn.push_back(vvctr[i]);}
            cout << vvctr[i] << endl;
        }
        cout << "All:";
        for (int i = 0; i < vvctr.size(); i++)
        {cout << " " << vvctr[i];}
        cout << endl;

        cout << "Odd:";
        for (int i = 0; i < vodd.size(); i++)
        {cout << " " << vodd[i];}
        cout << endl;

        cout << "Evn:";
        for (int i = 0; i < vevn.size(); i++)
        {cout << " " << vevn[i];}
        cout << endl;

        cout << "Max: " << maxv << " Min: " << minv << endl;

        for (int i = 0; i < 10; i++)
        {
            cout << "Dec " << i << ":";
            for (int j = 0; j < v_dec[i].size(); j++)
            {cout << " " << v_dec[i][j];}
            cout << endl;
        }
    }
}

void distinctString(void)
{
    vector <string> vstr;
    int maxl = 0;
    int minl = 999999999;
    string invl;

    cin.ignore();
    while (true)
    {
        cout << "["+invl+"]" << "Input: ";
        //cin >> invl;
        getline(std::cin, invl);
        if (invl == "")
        {break;}

        vstr.push_back(invl);
        if (maxl < invl.length())
        {maxl = invl.length();}
        if (invl.length() < minl)
        {minl = invl.length();}
    }
    cout << "MaxLength:";
    for (int i = 0; i < vstr.size(); i++)
    {
        int vlen = vstr[i].length();
        if (maxl <= vlen)
        {cout << " " << vstr[i];}

        if (5 <= vlen)
        {vstr.erase(vstr.begin() + i);}
    }
    cout << endl;
    cout << "MinLength:";
    for (int i = 0; i < vstr.size(); i++)
    {
        if (vstr[i].length() <= minl)
        {cout << " " << vstr[i];}
    }
    cout << endl;
}

void distinctList(void)
{
    list <int> lnum;
    int invl;


    for (int i = 0; i < 30; i++)
    {
        invl = rand() % 100;
        lnum.push_back(invl);
    }
    cout << "All:   ";
    for (list<int>::iterator it = lnum.begin(); it != lnum.end(); )
    {
        int vtmp = *it;
        cout << " " << vtmp;
        string stmp = to_string(vtmp);
        if (stmp.find("2") != string::npos)
        {it = lnum.erase(it);}
        else
        {it++;}
    }
    cout << endl;
    cout << "NoInc2:";
    for (list<int>::iterator it = lnum.begin(); it != lnum.end(); it++)
    {
        int vtmp = *it;
        cout << " " << vtmp;
    }
    cout << endl;

    lnum.sort();
    cout << "Sort:  ";
    for (list<int>::iterator it = lnum.begin(); it != lnum.end(); it++)
    {
        int vtmp = *it;
        cout << " " << vtmp;
    }
    cout << endl;
}

void distinctMap(void)
{
    map <string, string> mstr;
    mstr["cat"] = "猫";
    mstr["dog"] = "犬";
    mstr["bird"] = "鳥";
    mstr["fish"] = "魚";
    mstr["tiger"] = "虎";
    mstr["lion"] = "獅子";
    mstr["elephant"] = "象";
    mstr["giraffe"] = "キリン";
    mstr["penguin"] = "ペンギン";
    mstr["panda"] = "パンダ";


    string invl;

    while (true)
    {
        cout << "Please Eng. word: ";
        cin >> invl;
        if (invl == "")
        {break;}

        if (mstr.find(invl) != mstr.end())
        {cout << mstr[invl] << endl;}
        else
        {
            cout << "Not Found" << endl;
            break;
        }
    }

    map <string, string> knum;
    knum["0"] = "零";
    knum["1"] = "一";
    knum["2"] = "二";
    knum["3"] = "三";
    knum["4"] = "四";
    knum["5"] = "五";
    knum["6"] = "六";
    knum["7"] = "七";
    knum["8"] = "八";
    knum["9"] = "九";
    knum["10"] = "十";
    knum["100"] = "百";
    knum["1000"] = "千";
    knum["10000"] = "万";
    knum["100000000"] = "億";
    knum["1000000000000"] = "兆";

    stack <string> innum;

    while (true)
    {
        cout << "Please Number: ";
        cin >> invl;
        if (invl == "\\")
        {break;}

        int lstx = invl.length();
        cout << invl << " : " << lstx << endl;

        while (!innum.empty()) {
            innum.pop();
        }
        int clm = 0;
        for (; 0 < lstx; lstx--)
        {
            string vtmp = invl.substr(lstx-1, 1);
            cout << vtmp << " : " << lstx << " : " << clm << endl;
            if (clm && (clm % 3 == 0))
            {innum.push("、");}
            if (knum[vtmp] != "")
            {innum.push(knum[vtmp]);}
            else
            {
                cout << "数値を入力してください" << endl;
                break;
            }
            clm++;
        }
        if (lstx == 0)
        {
            cout << "Number: ";
            while (!innum.empty())
            {
                cout << innum.top();
                innum.pop();
            }
            cout << endl;
        }
    }

    map <string, string> mstr2;
    mstr2["r"] = "room     ";
    mstr2["w"] = "wonderful";
    mstr2["p"] = "pork     ";
    mstr2["t"] = "trap     ";
    mstr2["k"] = "kind     ";
    mstr2["m"] = "money    ";
    mstr2["d"] = "dog      ";
    mstr2["g"] = "given    ";
    mstr2["y"] = "yellow   ";
    mstr2["e"] = "eat      ";
    mstr2["a"] = "apple    ";
    mstr2["n"] = "neighbor ";

    string firstwd = "apple";
    string lastchar;

    cin.ignore();
    cout << "First Word: ";
    getline(cin, firstwd);

    lastchar = firstwd.substr(firstwd.length()-1, 1);
    while (mstr2[lastchar].length() != 0)
    {
        cout << mstr2[lastchar] << endl;
        firstwd = mstr2[lastchar];
        int lstx = firstwd.length();
        lastchar = firstwd.substr(lstx-1, 1);
        while (lastchar == " ")
        {
            lstx--;
            lastchar = firstwd.substr(lstx-1, 1);
        }
    }
}

void distinctSet(void)
{
    set <int> snum;
    int invl;

    srand((unsigned int)time(NULL));
    cout << "Obtained Number:";
    for (int ix=0; ix<10; ix++)
    {
        invl = rand() % 10;
        cout << " " << invl;
        snum.insert(invl);
    }
    cout << endl;
    set <int> ::iterator it;
    cout << "Distinct Number:";
    for (it = snum.begin(); it != snum.end(); it++)
    {
        int vtmp = *it;
        cout << " " << vtmp;
    }
    cout << endl;

    set <string> sstr;
    string sval;

    cout << "Please input sentence:";
    bool escape = false;
    cin >> sval;
    while (sval != "")
    {
        for (int ix=0; ix<sval.length(); ix++)
        {
            string vtmp = sval.substr(ix, 1);
            if (vtmp != "\\")
            {
                //cout << " " << vtmp;
                sstr.insert(vtmp);
            }
            else
            {
                cout << "Distinct Character:";
                set <string> ::iterator it2;
                for (it2 = sstr.begin(); it2 != sstr.end(); it2++)
                {
                    string vtmp = *it2;
                    cout << " " << vtmp;
                }
                cout << endl;
                escape = true;
                break;
            }
        }
        if (escape)
        {break;}

        cin >> sval;
    }
}

void distinctQueue(void)
{
    string sval;
    queue <string> qstr;

    cin.ignore();

    cout << "1:Please input words:";
    getline(cin,sval);
    while (sval != "")
    {
        //cout << sval;
        //cout << endl;
        qstr.push(sval);
        cout << "1:Please input words:";
        getline(cin,sval);
    }
    cout << "Output words:";
    while (!qstr.empty())
    {
        cout << " " << qstr.front();
        qstr.pop();
    }
    cout << endl;

}

void distinctStack(void)
{
    string sval;
    stack <string> qstr;

    cin.ignore();

    cout << "1:Please input words:";
    getline(cin,sval);
    while (sval != "")
    {
        cout << sval;
        cout << endl;
        qstr.push(sval);
        cout << "1:Please input words:";
        getline(cin,sval);
    }
    cout << "Output words:";
    while (!qstr.empty())
    {
        cout << " " << qstr.top();
        qstr.pop();
    }
    cout << endl;

    cout << "2:Please input words:";
    getline(cin,sval);
    for (int ix=0; ix<sval.length(); ix++)
    {
        string vtmp = sval.substr(ix, 1);
        qstr.push(vtmp);
    }
    cout << "Output words reverse:";
    while (!qstr.empty())
    {
        cout << qstr.top();
        qstr.pop();
    }
    cout << endl;
}