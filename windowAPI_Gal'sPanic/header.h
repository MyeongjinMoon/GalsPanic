#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <cstring>

#define WINDOW_WIDTH 1424
#define WINDOW_HEIGHT 790

#define MAP_WIDTH 600
#define MAP_HEIGHT 700

#define PLAYER_RADIUS 5

#define MAP_OFFSET_X 100
#define MAP_OFFSET_Y 150

#define MAX 200000
#define PIXEL 3

#define ITEM_SIZE 8

#define MAX_VELOCITY 5
#define INITDIR 90

#define UI_FONT_NAME "Bauhaus 93"

using namespace std;

struct item {
	POINT p;
	int value;
	int length = ITEM_SIZE;

	item* next = nullptr;
	item* pre = nullptr;
};