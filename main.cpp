#include <iostream>
#include <cmath>
#include <unistd.h>
#include "raylib.h"
#include "mandelbrot.h"

/*
 * You may change the width and height of the window, but ensure
 * it complies to a 4:3 resolution or the entire mandelbrot will
 * not show on the edges.
 */

int WIDTH 	= 800;
int HEIGHT 	= 600;
int PRECISION 	= 150;
int FPS 	= 60;
bool CONTINUE	= true;

/*
 * Mandelbrot:
 * x-axis = Real
 * y-axis = Imaginary
 *
 * Values normalized on x: [-1, 1], y: [-2, 1] for viewing on all Real coordinates
 */

int main(){
	InitWindow(WIDTH, HEIGHT, "raylib [core]");
	SetTargetFPS(FPS);
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		// DrawText("Image Loading...", WIDTH/2, HEIGHT/2, 20, WHITE);
		if(!CONTINUE) continue;
		for(float i = 0.; i <= WIDTH; i+=1){
			for(float j = 0.; j <= HEIGHT; j+=1){
				std::pair<float, float> p(0, 0);
				float norm_x = 3*(i/800)-2;
				float norm_y = 2*(j/600)-1;
				for(int k = 0; k < PRECISION; k++){
					p = get_mandelbrot_points(p, norm_x, norm_y);
					std::cout << p.first << " " << p.second << std::endl; //Debugging if precision was changed
					if(abs(p.first) > 1e4 || std::isnan(p.first) || abs(p.second) > 1e4 || std::isnan(p.second)){
						DrawPixel(i, j, Color{255 - k, 255 - 2*k, 255 - 3*k, 255});
						break;
					}
				}
			}
		}
		CONTINUE = false;
		EndDrawing();
	}
	CloseWindow();
	return 0;
}


/*
   DrawLine(400, 0, 400, 800, WHITE);
   DrawLine(0, 400, 800, 400, WHITE);


   for(float i = -400.0; i <= 400.0; i+=0.1){
// y = x^2
DrawCircle(i + 400, std::pow(i, 2) + 400, 2, RED);

// y = sqrt(x)
DrawCircle(i + 400, std::sqrt(i) + 400, 2, GREEN);

// y = 1/x
DrawCircle(i + 400, 1/i + 400, 2, BLUE);

// y = e^x
DrawCircle(i + 400, std::exp(i) + 400, 2, BROWN);
}
*/

/*
	 * FIGURE OUT HOW TO PRERENDER BEFORE WINDOW OPENS
	 * LOAD PIXEL VALUES INTO VECTOR
	 * ... wA = pixel vector
	float norm_x = 0;
	float norm_y = 0;
	int precision = 100;
	std::pair<float, float> mand_p(0, 0);
	std::vector<std::vector<Color>> wA;
	for(float i = 0; i <= WIDTH; i+=1){
		for(float j = 0; j <= HEIGHT; j+=1){
			wA.push_back(std::vector<Color>{BLACK});
			mand_p.first = 0;
			mand_p.second = 0;
			norm_x = 3 * (i/WIDTH) - 2;
			norm_y = 2 * (j/HEIGHT) - 1;
			for(int k = 0; k < precision; k++){
				mand_p = mandel(mand_p, norm_x, norm_y);
				if(mand_p.first > 10000 || std::isnan(mand_p.first) || mand_p.second > 10000 || std::isnan(mand_p.second)){
					wA[i][j] = WHITE;
					break;
				}
			}
		}
	}

	
	InitWindow(WIDTH, HEIGHT, "raylib [core]");
	SetTargetFPS(60);
	while(!WindowShouldClose()){
		BeginDrawing();
		
		FETCH AND DRAW VALUES FROM PIXEL VECTOR
		for(float i = 0; i <= WIDTH; i++){
			for(float j = 0; j <= HEIGHT; j++){
				DrawPixelV(Vector2{i, j}, wA[i][j]);
			}
		}

		EndDrawing();
	}
	*/

