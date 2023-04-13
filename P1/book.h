#include<iostream>
#include <string>
#include<iostream>
using std::vector;
using namespace std;

class Book{
    int ISBNno;
    string type;
    string lang;
    public:
        Book();
        void set_ISBNno(int no);
        void set_type(string type1);
        void set_lang(string lang1);
        int get_ISBNno();
        string get_type();
        string get_lang();
        bool operator<(const Book &b) const;
        void add_to_vector(string infile, vector<Book> &books);
        bool check_all(vector<Book>new1,vector<Book>req1,int mean,int i);
        int linear_search(vector<Book>new1,vector <Book> req1);
        int binary_search(vector<Book>new1,vector<Book>req1);
};