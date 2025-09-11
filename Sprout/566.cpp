#include <iostream>

struct Student {
    char name[100];
    char gender;
    int score;
};

double girls_average(Student ss[], int size);
double boys_average(Student ss[], int size);
void print(Student s);

double girls_average(Student ss[], int size){
    double ans = 0;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (ss[i].gender == 'F')
        {
            ans += ss[i].score;
            count++;
        }
    }
    if (count == 0)
        return -1;
    return ans / count;
}

double boys_average(Student ss[], int size){
    double ans = 0;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (ss[i].gender == 'M')
        {
            ans += ss[i].score;
            count++;
        }
    }
    if (count == 0)
        return -1;
    return ans / count;
}
void print(Student s){
    std::cout << s.name << " [" << s.gender << "]: " << s.score << "\n";
}

int main() {

    Student ss[1000];
    int n;

    std::cin >> n;
    for(int i = 0; i < n; ++i) {
        std::cin >> ss[i].name;
        std::cin >> ss[i].gender;
        std::cin >> ss[i].score;
    }

    for (int i = 0; i < n; ++i)
        print(ss[i]);
    std::cout << "-----------------------------------------------\n";
    std::cout << "Girl's average = " << girls_average(ss, n) << "\n";
    std::cout << "Boy's average = " << boys_average(ss, n) << "\n";

    return 0;
}