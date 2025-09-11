#include <iostream>
#include <cmath>

/* 
 * 判斷娃娃魚是否能吃到所有增益。 
 * 8個傳入參數依序為：a, b, c, 霸霸位置, 咩咩位置, 喵喵位置, x, y.  
 * 若能吃到所有增益，回傳true；否則回傳false 
 */
bool isValid(int, int, int, int[], int[], int[], int, int);
/*
 * 4個參數分別為：第一個點的x, y座標、第二個點的x, y座標
 * 回傳此二點的平面座標距離 
 */
double distance(int, int, int, int);

/* your code will be placed at here */
double distance(int a, int b, int c, int d) {
    return std::sqrt((a - c) * (a - c) + (d - b) * (d - b));
}

bool isValid(int a, int b, int c, int baba[], int mie[], int miao[], int x, int y) {
    int ok_baba = 0, ok_mie = 0, ok_miao = 0;
    for (int i = 0; i < a; i++) {
        if (distance(baba[i * 2], baba[i * 2 + 1], x, y) < 10 + 1e-6) {
            ok_baba = 1;
        }
    }

    for (int i = 0; i < b; i++) {
        if (distance(mie[i * 2], mie[i * 2 + 1], x, y) < 10 + 1e-6) {
            ok_mie = 1;
        }
    }

    for (int i = 0; i < c; i++) {
        if (distance(miao[i * 2], miao[i * 2 + 1], x, y) < 12 + 1e-6) {
            ok_miao = 1;
        }
    }
    return (ok_baba && ok_mie && ok_miao);
}


int main()
{
    int a, b, c, x, y;
    int baba[20005];    // 霸霸 
    int mie[20005];     // 咩咩
    int miao[20005];    // 喵喵
    
    // input
    std::cin >> a >> b >> c;  // 霸咩喵數量 
    for(int i=0; i<a; ++i)       // 霸霸位置 
        std::cin >> baba[2*i] >> baba[2*i+1];
    for(int i=0; i<b; ++i)       // 咩咩位置 
        std::cin >> mie[2*i] >> mie[2*i+1];
    for(int i=0; i<c; ++i)       // 喵喵位置 
        std::cin >> miao[2*i] >> miao[2*i+1];
    std::cin >> x >> y;     // 娃娃魚當前位置 
    
    // output
    if(isValid(a,b,c,baba,mie,miao,x,y))
        std::cout << "Good Place! =)";
    else
        std::cout << "Not that well... =("; 
    return 0;
}
