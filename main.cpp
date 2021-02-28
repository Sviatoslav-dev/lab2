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

int main () {
    string s;
    ifstream a;
    string b;
    student st;

    getline(a, b);

    a.open("students1.csv");

    if (a.is_open()) {
        getline(a, b);

        cout << b << endl;

        for (int i = 0, k = 0; i < b.size(); i++) {
            if (b[i] == ',') {
                switch (k)
                {
                    case 0:
                        st.name = s;
                    break;

                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                        st.mark[k-1] = stoi(s);
                        if (b[i+1] == 'T') {
                            st.is_cont = 1;
                        }
                        else {
                            st.is_cont = 0;
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
        if (!st.is_cont) {
            st.rating = (st.mark[0] + st.mark[1] + st.mark[2] + st.mark[3] + st.mark[4]);
        } else {
            st.rating = 0;
        }
    }

    st.output();

    a.close();
}