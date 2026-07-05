#include <stdio.h>
#include <stdbool.h>

void part2(FILE* file) 
{
    int c = 0;
    int max = 0;
    int counter = 0;
    int currMove = 0;
    bool dirChange = false;
    char dir = -1;
    
    while (c != EOF) {
        c = fgetc(file);
        if (dir == -1)
            dir = c;
        else if (dir != c) {
            currMove = 0;
            dir = c;
        }
        currMove++;
        if (c == '^') {
            counter += currMove;
        } else if (c == 'v') {
            counter -= currMove;
        }

        if (counter > max) {
            max = counter;
        }
    }

    printf("%d\n", max);
}

int fibo(int n) {
    if (n < 0)
        return 0;
    else if (n == 1) {
        return 1;
    } else {
        return fibo(n-2) + fibo(n-1); 
    }
}

void part3(FILE* file) 
{
    int c;
    int counter = 0;
    char dir = -1;
    int max = 0;
    int currPoint = 0;

    while ((c = fgetc(file)) != EOF) {
        if (dir == -1) {
            dir = c;
        } else if (dir != c) {
            int point = fibo(abs(counter));
            currPoint = counter > 0 ? currPoint + point 
                                    : currPoint - point;
            if (currPoint > max) {
                max = currPoint;
            }
            // printf("%d Consecutive\n", counter);
            // printf("currPoint = %d\n", currPoint);
            counter = 0; 
            dir = c;
        }
        if (dir == '^')
            ++counter;
        else 
            --counter;
    }
    max = max == 0 ? fibo(counter) : max;
    
    printf("%d\n", counter);
    printf("%d\n", max);
}

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");
    if (!file) return;

    part2(file);
    part3(file);    
}