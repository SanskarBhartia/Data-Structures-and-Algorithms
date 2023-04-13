#include "book.h"
#include <iostream>
#include<vector>
#include<fstream>
#include <algorithm>
using namespace std;

Book::Book(){
//Defining three variables - ISBN Number, type, and language
    ISBNno =0;
    type="";
    lang="";
}

//Setting ISBN, Language, and type of each element
void Book::set_ISBNno(int no){
    ISBNno = no;
}

void Book::set_lang(string lang1){
    lang = lang1;
}
void Book::set_type(string type1){
    type = type1;
}

//Getting ISBN, Language, and type of each element
int Book::get_ISBNno(){
    return ISBNno;
}

string Book::get_lang(){
    return lang;
}

string Book::get_type(){
    return type;
}

// Operator overloaded to sort the contents of the vector
bool Book::operator<(const Book &b) const{
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
void Book::add_to_vector(string infile, vector<Book> &books){
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
bool Book::check_all(vector<Book>new1,vector<Book>req1,int mean,int i){
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
int Book::linear_search(vector<Book>new1,vector <Book> req1){
    int count=0;
    for(int i=0;i<req1.size();i++){
        for(int j=0;j<new1.size();j++){
            if(check_all(new1,req1,i,j)){// checking if both elements are equal
                count+=1; // incrementing count everytime we find matching elements
            }
        }
    }
    return count;
}

//Function to process Binary search
int Book::binary_search(vector<Book>new1,vector<Book>req1){
    int count=0;
    for(int i =0;i<req1.size();i++){
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

