#include <iostream>
#include <unistd.h>

using namespace std;

class Node{
    public:
        int data;
        Node *next;
};

class QueueList{

    Node *head;
    Node *tail;

    public:

    //Constructor
        QueueList():  head(nullptr), tail(nullptr){};

        bool is_empty(){
            if(head == nullptr){
                return true;
            }
            else return false;
        }

        void enqueue(int x){
            Node *newNode = new Node{x, nullptr};

            if(head == NULL){
                head = tail = newNode;
            }
            else{
                tail->next = newNode;
                tail = newNode;
            }
        }

        void dequeue(){
            if(is_empty()){
                cout << "\n->[!] Queue underflow" << endl;
                return;
            }
            
            Node *temp = head;
            int removedData = temp->data;
            head = head->next;

            if(head == nullptr){ tail = nullptr;}
            delete temp;
            
        }

        void getState(){
            if(is_empty()){
                cout << "\n-->[!] The queue is empty\n";
            }
            else{
                cout << "\n-->[+] The queue looks like this : ";
                Node *current = head;
                while(current != nullptr){
                    if(current == tail){
                        cout << tail->data;
                        return;
                    }
                    else {
                        cout << current->data << " -> ";
                        current = current->next;
                    }
                }
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


    QueueList my_q;
        
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
                my_q.enqueue(num);
                break;

            case 2:
                my_q.dequeue();
                break;

            case 3:
                my_q.getState();
                break;

            case 4:
                cout << "\n[*] Exiting..." << endl;
                return 0;
                break;
        }
    }

}

