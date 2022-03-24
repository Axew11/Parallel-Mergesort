#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>

using namespace std;

bool is_power_of_two(int num);
void mergesort(vector<int> &vec, int low, int high);
void merge(vector<int> &a, int low, int mid, int high);


int main(int argc, char** argv) {

    short int number_of_threads = stoi(argv[1]);
    const int SIZE = stoi(argv[2]);
    
    if (!is_power_of_two(number_of_threads) && number_of_threads != 1) {
        cout << "Error: Must provide a number of threads to use that's a power of two\n";
        exit(1);
    }

    if (SIZE % number_of_threads) {
        cout << "Warning: Parallel Mergesort works best if the number of threads evenly divides the number of integers to generate and sort\n\n";
    }

    if (number_of_threads > thread::hardware_concurrency()) {
        cout << "Error: You provided more threads than your CPU currently has, this will have no added effect\n";
        cout << "to the benchmark. It will benchmark as if you were running it with the max amount of threads\n";
        cout << "your hardware has (which is " << thread::hardware_concurrency() << ")\n";
        exit(1);
    }

    vector<int> vec(SIZE);

    srand(1);

    for (int i = 0; i < SIZE; i++) vec[i] = rand() % 1'000'000 + 1;

    cout << "Generating vector of " << SIZE << " random ints from 1 - 1,000,000" << endl;
   
    if (number_of_threads == 1) {
        cout << "mergesort(vec, " << 0 << ", " << SIZE-1 << ");\n";
        mergesort(vec, 0, SIZE-1);
    }
    else {
        vector<thread> threads(number_of_threads);
        for (int i = 0; i < number_of_threads; i++) { 
            int low = i * SIZE/number_of_threads;
            int high = (i+1) * SIZE/number_of_threads - 1;
            cout << "Thread " << i << ": mergesort(vec, " << low << ", " << high << ");\n";
            threads.emplace_back(mergesort, ref(vec), i * SIZE/number_of_threads, (i+1) * SIZE/number_of_threads-1);
        }
        
        for (thread &thr : threads) {
            if (thr.joinable())
                thr.join();
        }

        for (int i = 0; i < number_of_threads-1; i++) {
            if (number_of_threads == 1) {
                cout << "merge(vec, " << 0 << ", " << (SIZE-1)/2 << ", " << SIZE-1 << ");\n";
                merge(vec, 0, (SIZE-1)/2, SIZE-1);
                break;
            }
            int low = i * SIZE/number_of_threads*2;
            int high = (i+1) * SIZE/number_of_threads*2 - 1;
            int mid = (low + high)/2;
            cout << "merge(vec, " << low << ", " << mid << ", " << high << ");\n";
            merge(vec, low, mid, high);
            if (is_power_of_two(number_of_threads - 1 - i)) {
                i = -1;
                number_of_threads /= 2;
            }
        }
    }
    
    cout << endl << "Mergesorted vector\n";

}

bool is_power_of_two(int num) {
    return (num & (num - 1)) == 0;
}

void mergesort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        
        mergesort(vec, low, mid);
        mergesort(vec, mid+1, high);
        
        merge(vec, low, mid, high);
    }

    return;
}

void merge(vector<int> &a, int low, int mid, int high) {
    int pointer_a = low;
    int pointer_b = mid + 1;
    int pointer_c = 0;
    vector<int> c(high-low+1);

    while (pointer_a <= mid && pointer_b <= high) {
        if (a[pointer_a] < a[pointer_b]) c[pointer_c++] = a[pointer_a++];
        else c[pointer_c++] = a[pointer_b++];
    }

    for (; pointer_a <= mid; pointer_a++)
        c[pointer_c++] = a[pointer_a];

    for (; pointer_b <= high; pointer_b++)
        c[pointer_c++] = a[pointer_b];

    for (int i = low; i < pointer_c+low; i++)
        a[i] = c[i-low];
}
