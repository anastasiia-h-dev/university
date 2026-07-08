#include <iostream>

using namespace std;

class CircularQueue{
    private:
        int *queue;
        int capacity, size;
        int head, tail;

    public:
        CircularQueue(int inputCapacity){
            capacity = inputCapacity;
            queue = new int[capacity];
            size = 0;
            head = tail = -1;
        }

        ~CircularQueue(){
            delete[] queue;
        }


        bool is_empty(){
            if(size == 0) return true;
            else return false;
        }

        void enqueue(int data){ // time complexity = O(1), space complexity = O(1)
            if(size == capacity){
                cout << "[!] enqueue() : The queue is full!!!" << endl;
                return;
            }
            else if(size == 0){
                head = tail = 0;
                queue[head] = data;
                size++;
            }
            else{
                tail = (tail+1) % capacity;
                queue[tail] = data;
                size++;
            }
        }

        void dequeue(){ // time complexity = O(1), space complexity = O(1)
            if(is_empty()){
                cout << "\n[!] dequeue() : Nothing to remove..." << endl;
            }
            else if(head == tail){
                queue[head] = 0;
                head = tail = -1;
                size--;
                return;
            }
            else{
                queue[head] = 0;
                head = (head + 1) % capacity;
                size--;
            }
        }

        void getFront(){
            if(is_empty()){
                cout << "\n[*] getFront() : The queue is empty..." << endl;
            }
            else{
                cout << "\n[*] getFront() : The head of the queue is: "  << queue[head];
            }
        }

        void getLast(){
            if(is_empty()){
                cout << "\n[*] getLast() : The queue is empty..." << endl;
                return;
            }
            cout << "\n[*] getLast() : The tail of the queue is : " << queue[tail];
        }

        void getState(){
            if(is_empty()){
                cout << "\n[*] queueState() : The queue is empty..." << endl;
            }
            else{
                for(int i = 0; i < capacity; i++){
                    cout << " |  " << queue[i];
                }
        }
        }
    };

int main(){
    
    cout << "\x1B[35m";
    cout << "\n    //        ///     /----           //   //   ";
    cout << "\n   //       //  //   //   //         //   //    ";
    cout << "\n  //       //==//   //---.          //----/     ";
    cout << "\n //       //  //   //    //             //      ";
    cout << "\n/=====   //  //   //-----              //  .     ";
    cout << "\033[0m";

    cout << "\n========================================================";
    cout << "\n[*] Enter the number - it will be size of the queue : ";
    int num;
    cin >> num;
    CircularQueue my_q(num);
    cout << "========================================================";
    
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
        cout << "\n========================================================\n";

        switch(choice){
            case 1:
                cout << "\n========================================================";
                cout << "\n[*] Insert an element you want to add to the queue : ";
                int num;
                cin >> num;

                my_q.enqueue(num);
                cout << "\n========================================================";
                
                break;

            case 2:
                my_q.dequeue();
                break;

            case 3:
                cout << "\n[+]The queue looks like this : ";
                my_q.getState();
                break;

            case 4:
                cout << "\n[*] Exiting..." << endl;
                return 0;
                break;
        }

    }

}