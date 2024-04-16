#pragma once

typedef struct {
    int X, Y;
} Point;

#define min(x, y) x > y ? y : x
#define max(x, y) x > y ? x : y