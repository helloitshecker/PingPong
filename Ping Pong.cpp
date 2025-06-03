#include "Framebuffer.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Text.hpp"

#include <stdexcept>

Paddle lp{ .coord = {0, 0} };
Paddle rp{ .coord = {0, 0} };
Ball ball{ .coord = {10, 10}, .dir = BallDir::SE };
uint32_t leftscore = 0;
uint32_t rightscore = 0;


static void lpout() {
	rightscore++;
}

static void rpout() {
	leftscore++;
}

static void drawpaddle(Framebuffer& framebuffer, Paddle& paddle) {
	framebuffer.set(paddle.coord.r  , paddle.coord.c, char(219));
	framebuffer.set(paddle.coord.r+1, paddle.coord.c, char(219));
	framebuffer.set(paddle.coord.r+2, paddle.coord.c, char(219));
	framebuffer.set(paddle.coord.r+3, paddle.coord.c, char(219));
	framebuffer.set(paddle.coord.r+4, paddle.coord.c, char(219));
	framebuffer.set(paddle.coord.r+5, paddle.coord.c, char(219));
}

static void inputResponse(Vec2& fbsize) {
	if (Keyboard::isKeyDown('W')) {
		if (lp.coord.r > 0)
			lp.coord.r--;
	}
	else if (Keyboard::isKeyDown('S')) {
		if (lp.coord.r+6 < fbsize.r)
			lp.coord.r++;
	}

	if (Keyboard::isKeyDown(KEY_UP)) {
		if (rp.coord.r > 0)
			rp.coord.r--;
	}
	else if (Keyboard::isKeyDown(KEY_DOWN)) {
		if (rp.coord.r+6 < fbsize.r)
			rp.coord.r++;
	}

	if (Keyboard::isKeyDown(KEY_ESCAPE)) {
		exit(0);
	}
}

static bool willballcollide(Ball& ball, Vec2& fbsize) {
	if (ball.dir == BallDir::NW) {
		return ball.coord.r == 0 || ball.coord.c == 1;
	}
	else if (ball.dir == BallDir::NE) {
		return ball.coord.r == 0 || ball.coord.c == fbsize.c - 2;
	}
	else if (ball.dir == BallDir::SW) {
		return ball.coord.r == fbsize.r - 1 || ball.coord.c == 1;
	}
	else if (ball.dir == BallDir::SE) {
		return ball.coord.r == fbsize.r - 1 || ball.coord.c == fbsize.c - 2;
	}
	return false;
}

static void drawball(Framebuffer& framebuffer, Ball& ball, Vec2& fbsize) {
	// Collision detection and hit direction offset
	if (willballcollide(ball, fbsize)) {
		// Ball Collides on top
		if (ball.dir == BallDir::NW && ball.coord.r == 0) {
			ball.dir = BallDir::SW;
		}
		// Ball collides to left
		else if (ball.dir == BallDir::NW) {
			ball.dir = BallDir::NE;
			// Stick hit check
			if (ball.coord.r >= lp.coord.r && ball.coord.r <= lp.coord.r + 6);
			else lpout();
		}
		// Ball Collides on top
		else if (ball.dir == BallDir::NE && ball.coord.r == 0) {
			ball.dir = BallDir::SE;
		}
		// Ball collides to right
		else if (ball.dir == BallDir::NE) {
			ball.dir = BallDir::NW;
			// Stick hit check
			if (ball.coord.r >= rp.coord.r && ball.coord.r <= rp.coord.r + 6);
			else rpout();
		}
		// Ball Collides on bottom
		else if (ball.dir == BallDir::SW && ball.coord.r == fbsize.r-1) {
			ball.dir = BallDir::NW;
		}
		// Ball collides to left
		else if (ball.dir == BallDir::SW) {
			ball.dir = BallDir::SE;
			// Stick hit check
			if (ball.coord.r >= lp.coord.r && ball.coord.r <= lp.coord.r + 6);
			else lpout();
		}
		// Ball Collides on bottom
		else if (ball.dir == BallDir::SE && ball.coord.r == fbsize.r-1) {
			ball.dir = BallDir::NE;
		}
		// Ball collides to right
		else if (ball.dir == BallDir::SE) {
			ball.dir = BallDir::SW;
			// Stick hit check
			if (ball.coord.r >= rp.coord.r && ball.coord.r <= rp.coord.r + 6);
			else rpout();
		}
	}

	// Move ball
	if (ball.dir == BallDir::NW) {
		ball.coord.r--;
		ball.coord.c--;
	}
	else if (ball.dir == BallDir::NE) {
		ball.coord.r--;
		ball.coord.c++;
	}
	else if (ball.dir == BallDir::SW) {
		ball.coord.r++;
		ball.coord.c--;
	}
	else if (ball.dir == BallDir::SE) {
		ball.coord.r++;
		ball.coord.c++;
	}

	framebuffer.set(ball.coord.r, ball.coord.c, 'O');
}

int main() {

	Renderer::setcursorvisibility(true); // Hidden

	Vec2 fbsize = Renderer::getframesize();

	rp.coord.c = fbsize.c - 1;

	Framebuffer fb(fbsize.r, fbsize.c);
	


	while (true) {
		Vec2 fbnew = Renderer::getframesize();
		if (fbnew.c != fbsize.c || fbnew.r != fbsize.r) {
			fbsize = fbnew;
			fb.resize(fbsize.r, fbsize.c);
			rp.coord.c = fbsize.c - 1;
		}
		
		fb.clear();

		//if (llos) {
		//	Vec2 pos1 = { fbsize.r / 2 - 3, 20 };
		//	Text::print(fb, pos1, "LEFT");
		//	Vec2 pos2 = { fbsize.r / 2 + 6, 28 };
		//	Text::print(fb, pos2, "LOST");
		//	Renderer::draw(fb.get());
		//	Renderer::setcursorvisibility(false);
		//	exit(0);
		//}
		//else if (rlos) {
		//	Vec2 pos1 = { fbsize.r / 2 - 3, 20 };
		//	Text::print(fb, pos1, "RIGHT");
		//	Vec2 pos2 = { fbsize.r / 2 + 6, 28 };
		//	Text::print(fb, pos2, "LOST");
		//	Renderer::draw(fb.get());
		//	Renderer::setcursorvisibility(false);
		//	exit(0);
		//}

		inputResponse(fbsize);
		
		Vec2 leftscorepos  = { 2, fbsize.c / 2 - 5 };
		Vec2 rightscorepos = { 2, fbsize.c / 2 + 5 };
		Vec2 scorescorepos = { 5, fbsize.c / 2 - 6 };
		

		Text::printsingle(fb, leftscorepos, std::to_string(leftscore));
		Text::printsingle(fb, rightscorepos, std::to_string(rightscore));
		Text::printsingle(fb, scorescorepos, "S  C  O  R  E");

		drawpaddle(fb, lp);
		drawpaddle(fb, rp);
		drawball(fb, ball, fbsize);

		Renderer::draw(fb.get());

		Renderer::sleep(16);
	}

	Renderer::setcursorvisibility(false); // Visible

	return 0;
}