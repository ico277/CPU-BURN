#include <iostream>
#include <stdexcept>
#include <thread>
#include <climits>
#include <ctime>
#include <vector>
#include <string>

#define VERSION "1.0.0"

using std::cout;
using std::cerr;
using std::string;
using std::thread;
using std::time;
using std::time_t;
using std::vector;

vector<string> split_once(string str, string delimiter) {
    string s = str;
    if (s.find(delimiter) != string::npos) {
        string a = s.substr(0, s.find(delimiter));
        s.erase(0, s.find(delimiter) + delimiter.length());
        return {a, s};
    }
    else
        return {};
}

void cpu_burn(time_t end_time) {
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
        ++amount;
    }
}

int main(int argc, char **argv) {
    int threads = thread::hardware_concurrency();
    int duration = 60;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        vector<string> split = split_once(arg, "=");
        if (split.size() == 2) {
            if (split.at(0) == "--threads") {
                try {
                    int num = stoi(split.at(1));
                    if (num != 0) {
                        threads = num;
                    } else {
                        cerr << "Invalid argument\n";
                        return 1;
                    }
                } catch (std::invalid_argument) {
                    cerr << "Invalid argument\n";
                    return 1;
                }
            } else if (split.at(0) == "--duration") {
                try {
                    int num = stoi(split.at(1));
                    if (num != 0) {
                        duration = num;
                    } else {
                        cerr << "Invalid argument\n";
                        return 1;
                    }
                } catch (std::invalid_argument) {
                    cerr << "Invalid argument\n";
                    return 1;
                }
            } else {
                cerr << "Invalid argument\n";
                return 1;
            }
        } else {
            if (arg == "--version") {
                cout << "CPU BURN v" << VERSION << "\n";
                return 0;
            }
        }
    }
    if (threads < 1) {
        threads = 2;
        cout << "Could not detect amount of logical processors\n"
             << "Using 2 threads\n";
    }
    cout << "\n"
         << "Threads:   " << threads << "\n"
         << "Duration:  " << duration << "s\n";
    time_t end_time = time(nullptr) + duration;
    thread thread1(cpu_burn, end_time);
    if (threads > 1)
        for (int i = 1; i < threads; i++) {
            thread(cpu_burn, end_time).detach();
        }
    thread1.join();
}