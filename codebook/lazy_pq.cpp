struct lazy_pq {
  priority_queue<int> pq, del;
  inline void lazy_delete() {
    while (!pq.empty() && !del.empty() && pq.top() == del.top()) {
      del.pop();
      pq.pop();
    }
  }
  inline int getmax() {
    lazy_delete();
    return pq.top();
  }
  inline void remove(int num) {
    if (num == pq.top()) pq.pop();
    else del.push(num);
  }
  inline void insert(int num) {
    pq.push(num);
  }
};
