#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <stdint.h>

#include "include/raylib.h"
#include "mandelbrot.h"

#define WIDTH		800
#define HEIGHT 		600
#define FPS		60
#define PRECISION	500

/*
 * You may change the width and height of the window, but ensure
 * it complies to a 4:3 resolution or the entire mandelbrot will
 * not show on the edges.
 */

/*
 * Mandelbrot:
 * x-axis = Real
 * y-axis = Imaginary
 *
 * Values normalized on x: [-1, 1], y: [-2, 1] for viewing on all Real coordinates
 */

int main(){

	// Initialization
	//-----------------------------------------------------------------
	std::pair<uint16_t, bool> fc[3];
	std::pair<uint16_t, bool> tc[3];
	srand(time(NULL));

	for(auto i = 0; i < sizeof(fc)/sizeof(*fc); i++) fc[i] = std::pair<uint16_t, bool>(rand(), rand() % 2);	
	
	enum { STATE_LOADING, STATE_FINISHED } state = STATE_LOADING;
	
	InitWindow(WIDTH, HEIGHT, "raylib [core] - Mandelbrot Set");
	SetTargetFPS(FPS);
	//-----------------------------------------------------------------
	
	// Main game loop
	while(!WindowShouldClose()){
		// Draw
		//-----------------------------------------------------------------
		BeginDrawing();	
		switch(state){

			// Start Case -----------------------------------------------------
			case STATE_LOADING:
				ClearBackground(BLACK);
				for(auto i = 0; i <= WIDTH; ++i){
					for(auto j = 0; j <= HEIGHT; ++j){
						std::pair<float, float> norm_points(0., 0.);
						float norm_x = 3*(static_cast<float>(i)/800)-2;
						float norm_y = 2*(static_cast<float>(j)/600)-1;
						for(int k = 0; k < PRECISION; ++k){
							norm_points = get_mandelbrot_points(norm_points, norm_x, norm_y);
							if(std::isnan(norm_points.first) || std::isnan(norm_points.second)){
								DrawPixel(i, j, Color{
									static_cast<unsigned char>( (k * fc[0].first) % 255 * fc[0].second ),	//Red
									static_cast<unsigned char>( (k * fc[1].first) % 255 * fc[1].second ),	//Green
									static_cast<unsigned char>( (k * fc[2].first) % 255 * fc[2].second ),	//Blue
									255		//Alpha
								});

								for(auto v = 0; v < sizeof(fc)/sizeof(*fc); v++) tc[v] = std::pair<uint16_t, bool>(fc[v].first, fc[v].second);

								// Some other nice color presets
								//DrawPixel(i, j, Color{255, (k % 255), (2*k % 255), (3*k % 255)});	
								//DrawPixel(i, j, Color{(k % 255), (2*k % 255), (3*k % 255), 255});
								//DrawPixel(i, j, Color{(k % 255), (2*k % 255), (3*k % 255), (4*k % 255)});
								
								break;
							}
						}
					}
				}
				state = STATE_FINISHED;
				break;	
			// End Case -------------------------------------------------------
			

			// Start Case -----------------------------------------------------
			case STATE_FINISHED:
				if(IsKeyDown(KEY_R)){
					std::cout << "Key Down for new color!" << std::endl;
					for(auto i = 0; i < sizeof(fc)/sizeof(*fc); i++) fc[i] = std::pair<uint16_t, bool>(rand(), rand() % 2);
					
					std::cout << "New Colors (RGBA and On/Off):" << std::endl;
					for(auto i = 0; i < sizeof(tc)/sizeof(*tc); i++) std::cout << tc[i].first << " : " << tc[i].second << std::endl;
					
					state = STATE_LOADING;
				}
				break;
			// End Case -------------------------------------------------------
		}
		EndDrawing();
		//-----------------------------------------------------------------
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
