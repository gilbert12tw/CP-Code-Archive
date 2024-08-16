#include <iostream>
#include <stdio.h>
#define MAX_N 1000005
using namespace std;

int n, m;

class ListNode{
public:
    int id;
    ListNode* prev;
    ListNode* next;
    
    ListNode(int val, ListNode* prev, ListNode* next): id(val), prev(prev), next(next){

    }
};

ListNode* lines[MAX_N];
ListNode* tails[MAX_N];
ListNode* person[MAX_N];

void init(){
    for(int i=0;i<MAX_N;i++){
        lines[i] = nullptr;
        tails[i] = nullptr;
        person[i] = nullptr;
    }
}

void print_all(){
    for(int i=0;i<n;i++){
        // cout << "#" << i+1 << ":";
        printf("#%d:", i+1);
        ListNode* curPtr = lines[i];
        while(curPtr != nullptr){
            if(curPtr->id!=-1&&curPtr->id!=-2){//
                // cout << " " << curPtr->id;
                printf(" %d", curPtr->id);
            }
            curPtr = curPtr->next;   
        }
        // cout << endl;
        printf("\n");
    }
}

int main(){
    
    ios_base::sync_with_stdio(false);
    init();
    cin >> n >> m;

    for(int i=0;i<n;i++){
        lines[i] = new ListNode(-1, nullptr, nullptr);
        person[i] = new ListNode(i+1, lines[i], nullptr);
        tails[i] = new ListNode(-2, person[i], nullptr);
        lines[i]->next = person[i];
        person[i]->next = tails[i];
    }
    // -1 -> 1
    // -1 -> 2
    // ...
    // -1 -> n

    int type, a, b;

    for(int i=0;i<m;i++){
        cin >> type >> a >> b;
        if(a > n || b > n) continue;
        if(type==0){
            // if(person[a-1]->next==nullptr){
            //     person[a-1]->prev->next = nullptr;
            //     if(person[b-1]->next==nullptr){
            //         person[a-1]->prev = person[b-1];
            //         person[b-1]->next = person[a-1];
            //         person[a-1]->next = nullptr;
            //     }
            //     else{
            //         person[a-1]->next = person[b-1]->next;
            //         person[b-1]->next->prev = person[a-1];
            //         person[a-1]->prev = person[b-1];
            //         person[b-1]->next = person[a-1];
            //     }
            // }
            //else{
                person[a-1]->prev->next = person[a-1]->next;
                person[a-1]->next->prev = person[a-1]->prev;
                // if(person[b-1]->next==nullptr){
                //     person[a-1]->prev = person[b-1];
                //     person[b-1]->next = person[a-1];
                //     person[a-1]->next = nullptr;
                // }
                // else{
                    person[a-1]->next = person[b-1]->next;
                    person[b-1]->next->prev = person[a-1];
                    person[a-1]->prev = person[b-1];
                    person[b-1]->next = person[a-1];
                // }
            //}
        }
        else if(type==1){
            if(lines[a-1]->next->id!=-2){
                lines[a-1]->next->prev = tails[b-1]->prev;
                tails[b-1]->prev->next = lines[a-1]->next;
                tails[a-1]->prev->next = tails[b-1];
                tails[b-1]->prev = tails[a-1]->prev;

                lines[a-1]->next = tails[a-1];
                tails[a-1]->prev = lines[a-1];
            }
            // -1 -> a, b, c -> -2
            // -1 -> d -> e -> -2
        }
        // print_all();
        // cout << "--------" << endl;
    }

    print_all();

    for(int i=0;i<MAX_N;i++){
        if(lines[i]!=nullptr){
            delete lines[i];
        }
        if(tails[i]!=nullptr){
            delete tails[i];
        }
        if(person[i]!=nullptr){
            delete person[i];
        }
    }
    return 0;
}
