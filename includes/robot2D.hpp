#pragma once
#include<opencv2/opencv.hpp>
#include "position.hpp" 
#include "map2D.hpp" 

#define BUG 1

class robot2D
{
   public:
         robot2D(int start_position_x, int start_position_y, int si , cv::Vec3b rColor, cv::Vec3b pColor, map2D * new_map);

         void bug1(position p); 
	 void bug2(position p); 
	 ~robot2D(); 
   private:
	 int x;
	 int y;
	 int size;

	 cv::Vec3b robot_color; 
	 cv::Vec3b path_color;

	 map2D * map;


	 void moving_around_border(); 
}; 
