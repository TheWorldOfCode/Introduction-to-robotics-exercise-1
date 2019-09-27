#pragma once
#include<opencv2/opencv.hpp>
#include "map2D.hpp" 
class position
{
  public:
      position(int position_x, int position_y, cv::Vec3b Color);
      bool at_position(int x, int y); 
      void draw_position_on_map(map2D & map); 
      void draw_line_between_position_on_map(position p, map2D & map, cv::Vec3b color);
      int get_x();
      int get_y();   
      ~position();  
  private:
	  int x;
	  int y;
	  cv::Vec3b color;

}; 
