const int QSIZE = 2000000;
struct Queue {
  int hd = 0, ed = 0;
  int q[QSIZE];
  bool empty() { return hd == ed; }
  void push(int x) {
    q[ed++] = x;
    if (ed >= QSIZE) ed = 0;
  }
  void clear() { hd = ed = 0; }
  void pop() {
    ed--;
    if (ed < 0) ed += QSIZE;
  }
  int front() {
    assert(!empty());
    return q[hd];
  }
};
