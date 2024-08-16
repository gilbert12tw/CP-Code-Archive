class Stack {
private:
    int tp = 0;
    int *stk;
public:
    Stack(int n) { tp = 0; stk = new int[n+1]{}; }
    ~Stack() { delete [] stk; }

    void push(int x) { stk[tp++] = x; }
    bool empty() { return tp == 0; }
    void clear() { tp = 0; }
    int pop() { 
        assert(!empty());
        return stk[--tp];
    }
    int top() { 
        assert(!empty());
        return stk[tp-1]; 
    }
};
