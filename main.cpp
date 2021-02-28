#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class student {
public:
    string name;
    float mark[5];
    bool is_cont;
    float rating;

    void output () {
        cout << name << ";"<< mark[0] << ";"<< mark[1] << ";"<< mark[2] << 
            ";"<< mark[3] << ";"<< mark[4] << ";"<< rating << endl;
    }
};

void get_students(ifstream &file, vector<student>& st) {

    string cell, line;
    student new_st;

    getline(file, line);

    while (!file.eof())
    {
        cell = "";
        if (file.is_open()) {
            getline(file, line);

            for (int i = 0, k = 0; i < line.size(); i++) {
                if (line[i] == ',') {

                    if (k == 0) {
                        new_st.name = cell;
                    } else if (k < 5) {
                        new_st.mark[k-1] = stoi(cell);
                    } else {
                        new_st.mark[k-1] = stoi(cell);
                            if (line[i+1] == 'T') {
                                new_st.is_cont = 1;
                            }
                            else {
                                new_st.is_cont = 0;
                            }
                    }
                    k++;
                    cell = "";
                } else {
                    cell += line[i];
                }
            }

            if (!new_st.is_cont) {
                new_st.rating = (new_st.mark[0] + new_st.mark[1] + new_st.mark[2] + new_st.mark[3] + new_st.mark[4]) / 5;
            } else {
                new_st.rating = 0;
            }
        }

        st.push_back(new_st);
    }
}

void input_st2 (vector<student>& st, vector<student>& st2) {
    for (int i = 0; i < st.size(); i++) {
        if (st[i].rating != 0) {
            st2.push_back(st[i]);
        }
    }
}

void sort_st (vector<student>& st) {
    student d;
    int was_changed = true;

    while (was_changed) {
        was_changed = false;
        for (int i = 1; i < st.size(); i++) {
            if (st[i - 1].rating < st[i].rating) {
                d = st[i - 1];
                st[i - 1] = st[i];
                st[i] = d;
                was_changed = true;
            }
        }
    }
}

int scholarship(vector<student>& st, ofstream & res) {

    int n = 0.4 * st.size(), min;

    for (int i = 0; i < n; i++) {
        res << st[i].name << "," << st[i].rating << endl;
        min = st[i].rating;
    }

    return min;
}

int main () {
    string dir;
    ifstream file1, file2;
    ofstream res;
    vector<student> st, st2;

    cout<< "input direction name:\n";
    getline(cin, dir);

    file1.open(dir + "/students1.csv");
    file2.open(dir + "/students2.csv");
    res.open(dir + "/result.csv");

    get_students(file1, st);
    get_students(file2, st);

    input_st2 (st, st2);

    sort_st (st2);

    cout << "minimum mark is " << scholarship(st2, res) << endl;

    file1.close();
    file2.close();
    res.close();
}