#include<iostream>
#include<vector>
#include<fstream>
#include <algorithm>
#include <chrono> 

using namespace std;

//Class to calculate time (called in Binary and Linear Search)
class timeClock{
    chrono::high_resolution_clock::time_point start;
    public:
        //starts he timer
        void reset(){
            start = chrono::high_resolution_clock::now(); //starts the timer
        }
        //ends the timer and calculates elapsed time
        double  CurrentTime(){
            auto end = chrono::high_resolution_clock::now(); //ends the timer
            double elapsed_us = chrono::duration<double,micro>(end - start).count();
            return elapsed_us;
        }
};

class Book{
    //Defining three variables - ISBN Number, type, and language
    int ISBNno;
    string type;
    string lang;
    public:
        //Setting ISBN, Language, and type of each element
        void set_ISBNno(int no){
            ISBNno = no;
        }

        void set_type(string type1){
            type = type1;
        }

        void set_lang(string lang1){
            lang = lang1;
        }

        //Getting ISBN, Language, and type of each element
        int get_ISBNno(){
            return ISBNno;
        }

        string get_type(){
            return type;
        }

        string get_lang(){
            return lang;
        };

        // Operator overloaded to sort the contents of the vector
        bool operator<(const Book &b) const{
            if(this->ISBNno!=b.ISBNno){//first order by ISBN no
                return this->ISBNno>b.ISBNno;
            } else if(this->type!=b.type){
                if(this->type=="new"){ //order of type: new>used>digital
                    return true;
                } else if (this->type=="used" and b.type=="digital"){
                    return true;
                } else {
                    return false;
                }
            } else if(this->lang!=b.lang) {//order by language
                return this->lang>b.lang;
            }
            return false;

        }

        //Readine files and adding elements to vectors
        void add_to_vector(string infile, vector<Book> &books){
            ifstream input;
            input.open(infile);
            string str;
            while(input.peek()!=EOF){
                Book book1;
                getline(input, str, ',');//getting ISBN 
                book1.set_ISBNno(stoi(str));
                getline(input,str,',');//getting language 
                book1.set_lang(str);
                getline(input,str);//getting type 
                book1.set_type(str);
                books.push_back(book1);
            }
        }

        //Function to check if each value of element matches with the corresponding target
        bool check_all(vector<Book>new1,vector<Book>req1,int mean,int i){
            if(new1[mean].get_ISBNno()==req1[i].get_ISBNno()){ //matching ISBN numbers
                if(new1[mean].get_lang()==req1[i].get_lang()){ //matching langauges
                    if(new1[mean].get_type()==req1[i].get_type()){ //matching types
                        return true;
                    }
                }
            }
            return false;
        }

        //Function to process linear search
        int linear_search(vector<Book>new1,vector <Book> req1){
            int count=0;
            for(long unsigned int i=0;i<req1.size();i++){
                for(long unsigned int j=0;j<new1.size();j++){
                    if(check_all(new1,req1,i,j)){// checking if both elements are equal
                        count+=1; // incrementing count everytime we find matching elements
                    }
                }
            }
            return count;
        }

        //Function to process Binary search
        int binary_search(vector<Book>new1,vector<Book>req1){
            int count=0;
            for(long unsigned int i =0;i<req1.size();i++){
                int left=0; // first index of vector
                int right=new1.size()-1;// last index of vector
                int mid=0;//we calculate middle of vector index range where the value lies
                while(left<=right){
                    mid=(left+right)/2;
                    if(check_all(new1,req1,mid,i)){// if values match we increment value of count
                        count+=1;
                        break;
                    } else if(new1[mid]<req1[i]){//if target element is larger we shift left to mid + 1
                        left=mid+1;
                    } else{ //if target element is smaller we shift right to mid -1
                        right=mid-1; 
                    }
                }
            }
            return count;
        }
};

//Main function to accept files and write the result to output file
int main(int argc, char **argv){
    Book b;
    timeClock ct;
    vector<Book> newBooks;//declaring vectors
    vector<Book> requestedBooks;
    string file1,file2,file3; //files accepted
    if(argc<4){
        cout<<"Provide 4 files"<<endl; //Validating the number of files (should be 4) sent by the user
        return -1;
    }
    file1=argv[1];
    file2=argv[2];
    file3=argv[3];
    b.add_to_vector(file1,newBooks); //adding contents of file1 to newBooks vector
    b.add_to_vector(file2,requestedBooks); //adding contents of file2 to requestedBooks vector
    char choice;
    int count=0;
    cout<<"Choice of search method ([l]linear, [b]binary)?"<<endl; //letting the user select the type of search strategy they want to employ
    cin>>choice;
    while(choice!='l' && choice!='b'){ //checking for correct value of input
        cout<<"Incorrect choice"<<endl;
        cin>>choice;
    }
    if(choice=='l'){
        ct.reset();
        //running linear search
        count =b.linear_search(newBooks,requestedBooks);
        double total_time=ct.CurrentTime();
        cout << "CPU time: " << total_time << " microseconds"<<endl; //prints the total time taken

    } else if(choice=='b'){
            ct.reset();
            //running binary search
            //sorting vectors based on operator overloading criteria
            sort(newBooks.begin(),newBooks.end()); 
            count =b.binary_search(newBooks,requestedBooks);
            double total_time=ct.CurrentTime();
            cout << "CPU time: " << total_time << " microseconds"<<endl; //prints the total time taken

    }
    //writing final output to outfile
    ofstream outdata;
    outdata.open(file3);
    outdata<<count<<endl;
    
    return 0;
}