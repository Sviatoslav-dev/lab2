#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class student {
public:
    string name;
    int mark[5];
    bool is_cont;
    int rating;

    void output () {
        cout << name << ";"<< mark[0] << ";"<< mark[1] << ";"<< mark[2] << ";"<< mark[3] << ";"<< mark[4] << ";"<< rating << endl;
    }
};

void get_students(ifstream &a, vector<student>& st) {

    string s;
    string b;
    student p;

    getline(a, b);

    int n = 0;

    while (!a.eof())
    {
        s = "";
        if (a.is_open()) {
            getline(a, b);

            //cout << b << endl;

            for (int i = 0, k = 0; i < b.size(); i++) {
                if (b[i] == ',') {
                    switch (k)
                    {
                        case 0:
                            p.name = s;
                        break;

                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            p.mark[k-1] = stoi(s);
                            if (b[i+1] == 'T') {
                                p.is_cont = 1;
                            }
                            else {
                                p.is_cont = 0;
                            }
                        break;
                    
                    default:
                        break;
                    }
                    k++;
                    s = "";
                } else {
                    s += b[i];
                }
            }
            if (!p.is_cont) {
                p.rating = (p.mark[0] + p.mark[1] + p.mark[2] + p.mark[3] + p.mark[4]) / 5;
            } else {
                p.rating = 0;
            }
        }

        //p.output();

        st.push_back(p);
        n++;
    }
}

void input_st2 (vector<student>& a1, vector<student>& a2) {
    for (int i = 0; i < a1.size(); i++) {
        if (a1[i].rating != 0) {
            a2.push_back(a1[i]);
            //a1[i].output();
        }
    }
}

void sort_st (vector<student>& a) {
    student d;
    int was_changed = true;

    while (was_changed) {
        was_changed = false;
        for (int i = 1; i < a.size(); i++) {
            if (a[i - 1].rating < a[i].rating) {
                d = a[i - 1];
                a[i - 1] = a[i];
                a[i] = d;
                was_changed = true;
            }
        }
    }
}

int out_vec(vector<student>& a) {

    int n = 0.4 * a.size();

    for (int i = 0; i < n; i++) {
        a[i].output();
    }

    return n;
}

int main () {
    ifstream a, b;
    vector<student> st;
    vector<student> st2;

    a.open("students1.csv");
    b.open("students2.csv");

    get_students(a, st);
    get_students(b, st);

    input_st2 (st, st2);

    sort_st (st2);

    cout << out_vec(st2) << endl;

    a.close();
    b.close();
}