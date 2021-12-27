#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <thread>
#include <ctime>
#include <climits>
#include <chrono>

using std::cout;
using std::time;
using std::time_t;
using std::thread;
//using std::this_thread::sleep_for;

unsigned long long int cpu_burn(time_t end_time) {
    unsigned long int amount = 0;
    unsigned long long int last_fib = 0;
    unsigned long long int current_fib = 1;
    while (time(nullptr) <= end_time) {
        if (amount == ULONG_MAX) {
            cout << "Maximum number of fibonacci numbers generated\n" 
                 << "Generated " << amount << " fibonacci numbers\n";
            break;
        }
        unsigned long fib = last_fib + current_fib;
        last_fib = current_fib;
        current_fib = fib;
        //cout << fib << "\n";
        ++amount;
    }
    return amount;
}

int main() {
    time_t result = time(nullptr);
    cout << result << " seconds since the Epoch\n";
    cout << thread::hardware_concurrency() << " threads\n";
    /*unsigned long long int fibs = cpu_burn(time(nullptr) + 4);
    cout << "Time is up\n"
         << "Generated " << fibs << " fibonacci numbers\n";*/
    time_t end_time = time(nullptr) + 60;
    thread thread1(cpu_burn, end_time);
    for (int i = 1; i < 12; i++) {
        thread(cpu_burn, end_time).detach();
    }
    //sleep_for(std::chrono::seconds(6));
    thread1.join();
}