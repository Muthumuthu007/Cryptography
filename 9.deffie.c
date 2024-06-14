#include <stdio.h>

int compute(int a, int m, int n)
{
    int r;
    int y = 1;
 
    while (m > 0)
    {
        r = m % 2;
        if (r == 1) {
            y = (y*a) % n;
        }
        a = a*a % n;
        m = m / 2;
    }
 
    return y;
}
 
int main()
{
    int p = 7;        
    int g = 5;        
 
    int a, b;    
    int A, B;    
    a = 2;       
    A = compute(g, a, p);
 
    b = 3;        
 
    B = compute(g, b, p);
 
    int keyA = compute(B, a, p);
    int keyB = compute(A, b, p);
 
    printf("Alice's secret key is %d\nBob's secret key is %d", keyA, keyB);
 
    return 0;
}
