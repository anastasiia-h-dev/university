#include <iostream> 
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

int c = 0;
int m = 0;
int num;

// ------ Hoare --------- 

int partition(int arr[], int left, int right){
    int i = left - 1;
    int j = right + 1;
    int pivot = arr[(left + right)/2];

    while (true){
        do { i++; c++;} while (arr[i] < pivot); 
        
        do {j--; c++;} while (arr[j] > pivot);

        if (i >= j){ return j; }

        swap(arr[i], arr[j]); m++; //int temp = 0; temp = arr[j]; arr[j] = arr[i]; arr[i] = temp

    }
}

void quick_sort(int arr[], int left, int right){
    
    if (left < right){
        int pivot = partition(arr, left, right);
        quick_sort(arr, left, pivot);
        quick_sort(arr, pivot+1, right);
    }
}


void random_generator(int arr[]){
    for (int i = 0; i < num; i++){ arr[i] = rand() % num; }
}

int main(){
    cout << "Enter the number of elements : " ; cin >> num;

    int arr[num];
    srand(time(NULL));

    // cout << ">>>>>>> My array: ";
     
    // for(int i = 0; i < num; i++){
    //     cout << arr[i] << " ";
    // }
    
    auto start = chrono::steady_clock::now();
    
    // for (int i = 0; i<100; i++){
    random_generator(arr);  
    quick_sort(arr, 0, num-1);
    auto end = chrono::steady_clock::now();

    // cout << endl << "\n>>>>>>> Sorted array: ";
    // for (int n = 0; n <= num-1; n++){ cout << arr[n] << " "; }

    cout << endl << "\n>>>> Comparisons were made: " << c;
    cout << endl << ">>>> Moves were made : " << m; 

    auto duration = chrono::duration_cast < chrono::microseconds > (end - start);
    cout << endl << ">>>> Execution time: " << duration.count()  << " microseconds" << endl;
}
