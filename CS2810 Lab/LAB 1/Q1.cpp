#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

class Book{

    public:
    string title;
    string author;

    private:
    string isbn;
    int copiesAvailable;
    int totalCopies ;

    public:
    Book (string title1,string author1,string isbn1,
            int copiesAvailable1,int totalCopies1){
            title = title1;
            author = author1;
            isbn = isbn1;
            copiesAvailable = copiesAvailable1;
            totalCopies = totalCopies1;
    }
    Book (){
            title = "UnknownTitle";
            author = "UnknownAuthor";
            isbn = "ISBN";
            copiesAvailable = 0;
            totalCopies = 5;
    }
    Book (Book &oldBook,string newISBN){
            title = oldBook.title;
            author = oldBook.author;
            isbn = newISBN;
            copiesAvailable = oldBook.copiesAvailable;
            totalCopies = oldBook.totalCopies;
    }
    
    string getISBN (){
        return title;
    }
    int getCopiesAvailable (){
        return copiesAvailable;
    }
    int getTotalCopies (){
        return totalCopies;
    }
    void updateCopies(int count){
        if(count+copiesAvailable<0 or count+totalCopies<0){
            cout<<"Invalid request! Count becomes negative\n";
            return;
        }
        copiesAvailable += count;
        totalCopies += count;
    }

    bool borrowBook (){
        if(copiesAvailable){
            copiesAvailable--;
            return true;
        }
        cout<<"Invalid request! Copy of book not available\n";
        return false;
    }
    bool returnBook (){
        if(copiesAvailable<totalCopies){
            copiesAvailable++;
            return true;
        }
        cout<<"Invalid request! Copy of book exceeds total copies\n";
        return false;
    }
    void printDetails (){
        cout<<title<<" "<<author<<"\n";
    }
    friend class Library;

};

class Member {
    public:
    string name;

    private:
    string memberID;
    map < string , int > borrowedBooks;
    int borrowLimit;
    int size;

    public:
    Member (string name1,string memberID1,int borrowLimit1){
        name = name1;
        memberID = memberID1;
        borrowLimit = borrowLimit1;
        size = 0;
    }
    Member (string name1,string memberID1){
        name = name1;
        memberID = memberID1;
        borrowLimit = 3;
        size = 0;
    }

    bool borrowBook (string isbn1){
        if(size<borrowLimit){
            borrowedBooks[isbn1]++;
            size++;
            return true;
        }
        cout<<"Invalid request! Borrow limit exceeded\n";
        return false;
    }
    bool returnBook (string isbn1){
        if(borrowedBooks.find(isbn1)!=borrowedBooks.end()){
            borrowedBooks[isbn1]--;
            size--;
            if(borrowedBooks[isbn1]==0)borrowedBooks.erase(isbn1);
            return true;
        }
        cout<<"Invalid request! Book not borrowed\n";
        return false;
    }

    void printDetails (){
        for(auto x:borrowedBooks){
            cout<<memberID<<" "<<name<<" "<<x.F<<" "<<x.S<<"\n";
        }
    }
    friend class Library;

};

class Library {
    private:
    vector < Book > books;
    vector < Member > members;

    public:
    Book& findBook(string isbn){
        for(int i=0;i<(int)books.size();i++){
            if(isbn==books[i].isbn){
                return books[i];
            }
        }
        return books[0];
    }
    Member& findMember(string memberID){
        for(int i=0;i<(int)members.size();i++){
            if(memberID==members[i].memberID){
                return members[i];
            }
        }
        return members[0];
    }
    bool addBook(Book &newBook){
        for(int i=0;i<(int)books.size();i++){
            if(newBook.isbn==books[i].isbn){
                cout<<"Invalid request! Book with same isbn already exists\n";
                return false;
            }
        }
        books.push_back(newBook);
        return true;
    }

    bool registerMember(Member &newMember){
        for(int i=0;i<(int)members.size();i++){
            if(newMember.memberID==members[i].memberID){
                cout<<"Invalid request! Member with same id already exists\n";
                return false;
            }
        }
        members.push_back(newMember);
        return true;
    }

    bool borrowBook (string memberID, string isbn){
        int bookIndex = -1;
        for(int i=0;i<(int)books.size();i++){
            if(isbn==books[i].isbn){
                bookIndex = i;
            }
        }
        int memberIndex = -1;
        for(int i=0;i<(int)members.size();i++){
            if(memberID==members[i].memberID){
                memberIndex = i;
            }
        }
        if(bookIndex != -1 and memberIndex != -1){
            if(books[bookIndex].borrowBook()){
                if(!members[memberIndex].borrowBook(isbn)){
                    books[bookIndex].returnBook();
                    return false;
                }
                else return true;
            }
        }
        return false;
    }
    bool returnBook (string memberID, string isbn){
        int bookIndex = -1;
        for(int i=0;i<(int)books.size();i++){
            if(isbn==books[i].isbn){
                bookIndex = i;
            }
        }
        int memberIndex = -1;
        for(int i=0;i<(int)members.size();i++){
            if(memberID==members[i].memberID){
                memberIndex = i;
            }
        }
        if(bookIndex != -1 and memberIndex != -1){
            if(books[bookIndex].returnBook()){
                if(!members[memberIndex].returnBook(isbn)){
                    books[bookIndex].borrowBook();
                    return false;
                }
                else return true;
            }
        }
        return false;
    }
    void printLibraryDetails (){
        for(int i=0;i<(int)books.size();i++){
            cout<<books[i].title<<" "<<books[i].author<<" "<<books[i].copiesAvailable<<"\n";
        }
        for(int i=0;i<(int)members.size();i++){
            cout<<members[i].memberID<<" "<<members[i].name<<"\n";
        }
    }
};

int main(){
    Library lib;
    string s; cin>>s;
    while(s!="Done"){
        if(s=="Book"){
            string t; cin>>t;
            if(t=="None"){
                Book* bookObj = new Book();
                lib.addBook(*bookObj);
            }
            else if(t=="ExistingBook"){
                string t1,t2; cin>>t1>>t2;
                Book* bookObj = new Book(lib.findBook(t1),t2);
                lib.addBook(*bookObj);
            }
            else{
                string t1,t2; cin>>t1>>t2;
                int i1,i2; cin>>i1>>i2;
                Book* bookObj = new Book(t,t1,t2,i1,i2);
                lib.addBook(*bookObj);
            }
        }
        else if(s=="UpdateCopiesCount"){
            string t; cin>>t;
            int i; cin>>i;
            lib.findBook(t).updateCopies(i);
        }
        else if(s=="Member"){
            string t; cin>>t;
            if(t=="NoBorrowLimit"){
                string t1,t2; cin>>t1>>t2;
                Member* memberObj = new Member(t2,t1);
                lib.registerMember(*memberObj);
            }
            else{
                string t1; cin>>t1;
                int i; cin>>i;
                Member* memberObj = new Member(t1,t,i);
                lib.registerMember(*memberObj);
            }
        }
        else if(s=="Borrow"){
            string t1,t2; cin>>t1>>t2;
            lib.borrowBook(t1,t2);
        }
        else if(s=="Return"){
            string t1,t2; cin>>t1>>t2;
            lib.returnBook(t1,t2);
        }
        else if(s=="PrintBook"){
            string t; cin>>t;
            lib.findBook(t).printDetails();
        }
        else if(s=="PrintMember"){
            string t; cin>>t;
            lib.findMember(t).printDetails();
        }
        else if(s=="PrintLibrary"){
            lib.printLibraryDetails();
        }
        cin>>s;
    }
}
