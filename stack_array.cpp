#include <iostream>
#include <unistd.h>

using namespace std;

class ArrayStack{
    private :
        int *stack;
        int top;
        int capacity;

    public:

        ArrayStack(int inputCapacity){
            capacity = inputCapacity;
            stack = new int[capacity];
            top = -1;
        }

        ~ArrayStack(){
            delete[] stack;
        }

        bool empty(){
            if(top == -1){
                return true;
            }else {
                return false;
            }
        }

        void push(int x){
            if(top == capacity - 1) {
                cout << "Stack overflow!";
                return;
            }
            top++;
            stack[top] = x;
            
        }

        void pop(){
            if(empty()){
                cout << "Stack underflow!";
                return;
            } else {
                top--;
            }
        }

        int show_top(){
            if(empty()){
                cout << "Stack underflow!";
                return 0;
            } else {
                return stack[top];
            }
        }

        void getState(){
            if(empty()){
                cout << "\n->[!] Stack underflow!";
                return;
            }
                for(int i = top; i >= 0; i--){
                    if(i == top){cout << stack[i] << " <- top\n---\n"; continue;}
                    else cout << stack[i] << "\n---\n";
                }
        }

};

int main(){
    cout << "\x1B[35m";
    cout << "\n    //        ///     /----           //   //    ";
    cout << "\n   //       //  //   //   //         //   //     ";
    cout << "\n  //       //==//   //---.          //----/      ";
    cout << "\n //       //  //   //    //             //       ";
    cout << "\n/=====   //  //   /------              //  .     ";
    cout << "\033[0m";

    cout << "\n========================================================";
    cout << "\n[*] Enter the number - it will be size of the stack : ";
    int num;
    cin >> num;
    ArrayStack my_stack(num);
    cout << "========================================================";
    
    while(true){

        cout << "\n========================================================";
        cout << "\x1B[34m";
        cout << "\n[*] Choose what to do with the stack : ";
        cout << "\n.--------------------------------------.";
        cout << "\n| 1) Add an element.                   |";
        cout << "\n| 2) Remove an element from the stack. |";
        cout << "\n| 3) Check the state of the stack.     |";
        cout << "\n| 4) Exit.                             |";
        cout << "\n.--------------------------------------.";
        cout << "\n\n[*] Your choice : ";
        cout << "\033[0m";
        int choice;
        cin >> choice;
        cout << "========================================================\n";


        switch(choice){
            case 1:
                cout << "\n\n[*] Insert an element you want to add to the stack : ";
                int num;
                cin >> num;
                my_stack.push(num);
                break;

            case 2:
                my_stack.pop();
                cout << "\n->[+] The top element was removed.";
                break;

            case 3:
                my_stack.getState();
                break;

            case 4:
                cout << "\n[*] Exiting..." << endl;
                return 0;
                break;
        }
    }

}

