#include <iostream>
#include <cmath>

#include "include/raylib.h"
#include "mandelbrot.h"

/*
 * You may change the width and height of the window, but ensure
 * it complies to a 4:3 resolution or the entire mandelbrot will
 * not show on the edges (or show skewed).
 */

/*
 * Mandelbrot:
 * x-axis = Real
 * y-axis = Imaginary
 *
 * Values normalized on x: [-1, 1], y: [-2, 1] for viewing on all Real coordinates
 */

void gen_colors(Color *color){
    color->r = static_cast<unsigned char>(rand()%255);
    color->g = static_cast<unsigned char>(rand()%255);
    color->b = static_cast<unsigned char>(rand()%255);
    color->a = 255;
}

int main(){

	// Initialization
	//-----------------------------------------------------------------
	const int WIDTH = 1080;
	const int HEIGHT = 1080;
	const int FPS = 60;
	const int PRECISION = 500;
   
	enum { STATE_LOADING, STATE_FINISHED } state = STATE_LOADING;
    std::pair<float, float> norm_points;
    float norm_x, norm_y;
    Color d_color;
    gen_colors(&d_color);

	srand(time(NULL));
	
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
                        norm_points = std::pair<float, float>(0, 0);
						norm_x = 3*(static_cast<float>(i)/static_cast<float>(WIDTH))-2;
						norm_y = 2*(static_cast<float>(j)/static_cast<float>(HEIGHT))-1;
						for(int k = 0; k < PRECISION; ++k){
							norm_points = get_mandelbrot_points(norm_points, norm_x, norm_y);
							if(std::isnan(norm_points.first) || std::isnan(norm_points.second)){
                                DrawPixel(i, j, Color{
                                    static_cast<unsigned char>( (k*d_color.r) * (d_color.r%5)),
                                    static_cast<unsigned char>( (k*d_color.g) * (d_color.g%5)),
                                    static_cast<unsigned char>( (k*d_color.b) * (d_color.b%5)),
                                    255
                                });
                                
								// Some other nice color presets
								//DrawPixel(i, j, Color{255, (k % 255), (2*k % 255), (3*k % 255)});	
								//DrawPixel(i, j, Color{(k % 255), (2*k % 255), (3*k % 255), 255});
								//DrawPixel(i, j, Color{(k % 255), (2*k % 255), (3*k % 255), (4*k % 255)});
								
								break;
							}
						}
					}
				}
                
                std::cout << "Colors drawn (R/G/B/A): \n" << 
                    (int)d_color.r << "/" << 
                    (int)d_color.g << "/" << 
                    (int)d_color.b << "/" << 
                    (int)d_color.a << "\n\n" <<
                    "Press Key(R) for new color!\n" <<
                    "Press Key (Q) to quit.\n"
                    << std::endl;

				state = STATE_FINISHED;
				break;	
			// End Case -------------------------------------------------------
			

			// Start Case -----------------------------------------------------
			case STATE_FINISHED:
				if(IsKeyDown(KEY_R)){
                    gen_colors(&d_color);
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
