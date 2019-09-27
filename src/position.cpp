#include "../includes/position.hpp"

position::position(int position_x, int position_y, cv::Vec3b Color)
{
  x = position_x;
  y = position_y;
  color = Color;
} 	


bool position::at_position(int x_r, int y_r)
{
  return x == x_r && y == y_r;
} 	

void position::draw_position_on_map(map2D & map)
{
    map.draw_circle(x,y,color); 
} 	


void position::draw_line_between_position_on_map(position p, map2D & map, cv::Vec3b color)
{
  map.draw_line(x,y,p.get_x() , p.get_y(), color); 
} 	


int position::get_x()
{
   return x;
} 	


int position::get_y()
{
   return y;
} 	

position::~position(){}  

