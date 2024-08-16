#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")

using namespace std;

struct Patient {
    string name;
    int age;
    int money;
    bool is_member;
    vector<int> join_date; // Handling date as string
    int input_order;
    
    vector<int> parse_date(string &s) {
        vector<int> res;
        if (s == "NaN") {
            res.emplace_back(1000000000);
            return res;
        }
        string tmp; s += "-";
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] != '-') {
                tmp.push_back(s[i]);
            } else {
                res.emplace_back(stoi(tmp));
                tmp.clear();
            }
        }
        return res;
    }

    // Default constructor
    Patient(string n, int a, int m, bool im, string jd, int i)
        : name(n), age(a), money(m), is_member(im), join_date(parse_date(jd)), input_order(i) {
    }
};


bool pandaComparator(const Patient& a, const Patient& b) {
    if (a.is_member != b.is_member) return a.is_member > b.is_member; // Members first
    if (a.join_date != b.join_date) {
        return a.join_date < b.join_date; // Older membership date first
    }
    if (a.name != b.name) return a.name < b.name; // Alphabetical order
    return a.input_order < b.input_order; 
}

bool bearComparator(const Patient& a, const Patient& b) {
    if (a.money != b.money) return a.money > b.money; // Richest first
    return a.input_order < b.input_order; 
}

bool cp(const Patient &a, const Patient &b, int tp) {
    if (tp == 0) return pandaComparator(a, b);
    return bearComparator(a, b);
}

template<typename MyIt>
inline void my_swap(MyIt a, MyIt b) {
    auto temp = *a;
    *a = *b;
    *b = temp;
}

template<typename MyIt>
inline MyIt partition(MyIt first, MyIt last, int type) {
    auto pivot = *(last - 1);  // Using the last element as pivot
    MyIt i = first;
    for (MyIt j = first; j < last - 1; ++j) {
        if (cp(*j, pivot, type)) {
            my_swap(i, j);
            i++;
        }
    }
    my_swap(i, last - 1);  // Put the pivot element in the correct position
    return i;
}

template<typename MyIt>
void my_sort(MyIt first, MyIt last, int type) {
    if (first < last - 1) {  // More than one element
        MyIt p = partition(first, last, type);
        my_sort(first, p, type);  // Recursively sort elements before partition
        my_sort(p + 1, last, type);  // Recursively sort elements after partition
    }
}

template<typename T, typename Compare = std::less<T>>
class MinHeap {
private:
    vector<T> heap;
    Compare comp;

    void bubbleUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (comp(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void bubbleDown(int index) {
        int leftChildIndex, rightChildIndex, minIndex, size = heap.size();

        while (true) {
            leftChildIndex = 2 * index + 1;
            rightChildIndex = 2 * index + 2;
            minIndex = index;

            if (leftChildIndex < size && comp(heap[leftChildIndex], heap[minIndex])) {
                minIndex = leftChildIndex;
            }
            if (rightChildIndex < size && comp(heap[rightChildIndex], heap[minIndex])) {
                minIndex = rightChildIndex;
            }

            if (minIndex != index) {
                swap(heap[index], heap[minIndex]);
                index = minIndex;
            } else {
                break;
            }
        }
    }

public:
    MinHeap(Compare c = Compare()) : comp(c) {}

    void push(const T& value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    T pop() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        T min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            bubbleDown(0);
        }
        return min;
    }

    const T& top() const {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    bool isEmpty() const {
        return heap.empty();
    }
};

int main() {
    int N, M;
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cin.ignore(); // To handle the newline character after reading numbers

    string name, join_date;
    int age, money;
    bool is_member;
    vector<int> is_del(1);

    MinHeap<Patient, function<bool(const Patient&, const Patient&)>> pandaHeap(pandaComparator);
    MinHeap<Patient, function<bool(const Patient&, const Patient&)>> bearHeap(bearComparator);

    // Read initial patient list
    int tot_cnt = 0;
    for (int i = 0; i < N; i++) {
        getline(cin, name);
        cin >> age >> money >> is_member >> join_date;
        cin.ignore(); // Consume the newline after the input
        auto tmp = Patient(name, age, money, is_member, join_date, tot_cnt++);
        pandaHeap.push(tmp);
        bearHeap.push(tmp);
        is_del.emplace_back(0);
    }

    for (int day = 1; day <= M; ++day) {
        int P, X, K;
        cin >> P >> X >> K;
        cin.ignore(); // Consume the newline after reading P X K

        // Read new patients for the day
        for (int i = 0; i < P; i++) {
            getline(cin, name);
            cin >> age >> money >> is_member >> join_date;
            cin.ignore(); // Consume the newline after the input
            auto tmp = Patient(name, age, money, is_member, join_date, tot_cnt++);
            pandaHeap.push(tmp);
            bearHeap.push(tmp);
            is_del.emplace_back(0);
        }

        // Compute income and print treated patients
        cout << "DAY #" << day << '\n';
        int totalIncome = 0, count = 0;
        while (!pandaHeap.isEmpty() && count < X) {
            Patient p = pandaHeap.pop();
            if (is_del[p.input_order]) continue;
            is_del[p.input_order] = 1;
            cout << p.name << " " << p.age << '\n';
            totalIncome += (p.money * 9 / 10);
            count++;
        }

        cout << "INCOME TODAY: " << totalIncome << '\n';

        // Compute income and print treated patients (bear)
        count = 0;
        while (!bearHeap.isEmpty() && count < K) {
            Patient p = bearHeap.pop();
            if (is_del[p.input_order]) continue;
            is_del[p.input_order] = 1;
            count++;
        }
    }

    return 0;
}

