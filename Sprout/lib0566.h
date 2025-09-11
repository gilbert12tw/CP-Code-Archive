struct Student {
    char name[100];
    char gender;
    int score;
};

double girls_average(Student ss[], int size);
double boys_average(Student ss[], int size);
void print(Student s);