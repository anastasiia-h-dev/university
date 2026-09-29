#include <iostream>

using namespace std;

#include <iostream>
#include <unistd.h>

using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(int x){
        data = x;
        next = nullptr;
    }
};

class StackList {
    private:        
        Node *top;

    public:
    StackList(){top = NULL;};

    bool Stack_Empty(){
        if (top == nullptr){
            return true;
        }
        else return false;
    }

    int Push(int x){
        Node *temp = new Node(x);
        temp->next = top;
        top = temp;
        return top->data;
    }

    int Pop(){
        if(Stack_Empty()){
            cout << "Error: underflow" << endl;
            return 0;
        }

        Node *temp = top;
        top = top->next;
        return temp->data;

        delete temp;
        
    }

    int Peek(){
        if(Stack_Empty()){
            cout << "Error: underflow" << endl;
            return 0;
        }

        return top->data;
    }

};

int main(){
    string word, reversed;
    StackList stack;

    while(true){
        word = {0};
        reversed = {0};

        cout << "\n[*] Please, insert a word you want to reverse : ";
        cin >> word;

        for(int i = 0; i < word.length(); i++){
            stack.Push(word[i]);
        }

        for(int i = 0; i < word.length(); i++){
            reversed += stack.Pop();
        }

        cout << "\n[+]The reversed word is :  " << reversed << endl;
    }

}