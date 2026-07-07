#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define SEGMENTS 100

typedef struct Robot {
    int idx;
    int count;
    int pos;
} Robot;
    
int wrap(int pos) 
{
    return (pos < 0) ? SEGMENTS - abs(pos) % SEGMENTS 
                     : pos % SEGMENTS;
}

int advance(int pos, char c) 
{
    if (c == '<') {
        return wrap(pos - 1);
    } else {
        return wrap(pos + 1);
    }
}

void part1(FILE* file) 
{
    int wall[SEGMENTS] = {0};    
    int c;
    int pos = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '<') {
            pos--;
            pos = wrap(pos);
        } else if (c == '>') {
            pos++;
            pos = wrap(pos);
        }
        assert(pos >= 0 && pos <= 99);
        wall[pos]++;
    }
    
    int max_loc = 0;
    int max = wall[0];
    for (int i = 1; i < SEGMENTS; ++i) {
        if (wall[i] > max) {
            max = wall[i];
            max_loc = i;
        }
    }
    
    printf("answer = %d\n", (max_loc+1)*max);
    
}

void part2(FILE* file) 
{
    char* buff = NULL;
    int counter = 0;
    
    int c;
    while ((c = fgetc(file)) != EOF) {
        arrput(buff, c);
    }

    int p1, p2;
    p1 = p2 = 0;
    for (int i = 0; i < arrlen(buff); ++i) {
        assert(arrlen(buff) - 1 - i >= 0);
        p1 = advance(p1, buff[i]);
        p2 = advance(p2, buff[arrlen(buff) - 1 - i]);
        
        if (p1 == p2) {
            counter++;
        }
    }
    
    printf("answer = %d\n", counter);
}

void part3(FILE* file) 
{
    char* buff = NULL;
	Robot robots[SEGMENTS] = {0};
    
    int c;
    while ((c = fgetc(file)) != EOF) {
        arrput(buff, c);
    }
    
    for (int i = 0; i < SEGMENTS; ++i) {
        robots[i] = (Robot){ .count = 0, .idx = i + 1, .pos = i };
    }

	int laser_pos = 0;
    for (int i = 0; i < arrlen(buff); ++i) {
			laser_pos = advance(laser_pos, buff[i]);
            int instr = arrlen(buff) - 1 - i;
            assert(instr >= 0);
        for (int j = 0; j < SEGMENTS; ++j) {
			robots[j].pos = advance(robots[j].pos, buff[instr]);
            
            if (laser_pos == robots[j].pos) {
                robots[j].count++;
            }
        }
    }

    int max_loc = 0;
    for (int i = 1; i < SEGMENTS; ++i) {
        if (robots[i].count > robots[max_loc].count) {
            max_loc = i;
        }
    }

    printf("Count: %d, sequence number: %d\n", robots[max_loc].count, robots[max_loc].idx);
    printf("answer = %d\n", robots[max_loc].count * robots[max_loc].idx);
}

int main(int argc, char** argv) 
{
    if (argc < 3) {
        printf("Provide text file and part as arguments\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Invalid file");
        return 1;
    }
    
    switch (atoi(argv[2])) {
        case 1 : part1(file);  break;
        case 2 : part2(file);  break;
        case 3 : part3(file);  break;
        default: break;
    } 
}