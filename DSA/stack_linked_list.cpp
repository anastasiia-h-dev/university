#include <iostream>

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

    void getState(){
        if (Stack_Empty()) {
            cout << "\n->[!] Stack is empty!" << endl;
            return;
        }
        Node *current = top;
        cout << "\n            top";
        cout << "\n             ⬇";
        cout << "\n[+] Stack : ";

        while (current != nullptr){
            if(current->next == nullptr){
                cout << current->data;
                return;
            }
            else {
                cout << current->data << " -> ";
                current = current->next;
            }
        }
        cout << endl;
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


    StackList my_stack;
        
    while(true){
        
        cout << "\n========================================================";
        cout << "\x1B[34m";
        cout << "\n[*] Choose what to do with the queue : ";
        cout << "\n.--------------------------------------.";
        cout << "\n| 1) Add an element.                   |";
        cout << "\n| 2) Remove an element from the queue. |";
        cout << "\n| 3) Check the state of the queue.     |";
        cout << "\n| 4) Exit.                             |";
        cout << "\n.--------------------------------------.";
        cout << "\n\n[*] Your choice : ";
        cout << "\033[0m";
        int choice;
        cin >> choice;
        cout << "========================================================\n";


        switch(choice){
            case 1:
                cout << "\n\n[*] Insert an element you want to add to the queue : ";
                int num;
                cin >> num;
                my_stack.Push(num);
                break;

            case 2:
                my_stack.Pop();
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