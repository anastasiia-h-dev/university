#include <iostream>

using namespace std;

int c = 0;
int m = 0;
int num;

void random_generator(int arr[]){
    for (int i = 0; i < num; i++){ arr[i] = rand() % num; }}

void bubble(int arr[]){
    for (int i = 0; i < num; ++i){
        for (int j = 0; j < num - i - 1; j++){
        c++;
        if (arr[j] > arr[j + 1]){
            int strg = arr[j]; m++;
            arr[j] = arr[j + 1]; 
            arr[j + 1] = strg; }
        }
    }   
}

int main(){

    cout << "Enter the number of elements : " ; cin >> num;

    int my_array[num];
    srand(time(NULL)); 

    cout << ">>>>>>> My array: ";
    random_generator(my_array);
    for(int i = 0; i < num; i++){ cout << my_array[i] << " "; }

    auto start = chrono::steady_clock::now();
    //for (int i =0; i<1000; i++){}
    bubble(my_array); //sorting an array
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast < chrono::microseconds > (end - start);

    cout << endl << "\n>>>>>>> Sorted array: " << endl;
    for(int n = 0; n < num; ++n){ cout << my_array[n] << " "; }
    cout << endl << "\n>>>> Comparisons were made: " << c;
    cout << endl << ">>>> Moves were made : " << m; 
    cout << endl << ">>>> Execution time: " << duration.count() << " microseconds" << endl;
}