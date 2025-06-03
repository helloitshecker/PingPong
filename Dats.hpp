#pragma once

union Vec2 {
	struct { int x, y; };
	struct { int r, c; };
	int arr[2];
};

enum class BallDir {
	NW, NE, SW, SE
};

struct Paddle {
	Vec2 coord;
};

struct Ball {
	Vec2 coord;
	BallDir dir;
};