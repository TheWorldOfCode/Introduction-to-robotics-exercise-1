#include "../includes/map2D.hpp" 
#include <stdio.h> 
map2D::map2D(std::string filename, std::string windowName)
{ 
     map = cv::imread(filename); 
     name_window = windowName;    
} 	

void map2D::move(int x, int y, cv::Vec3b color)
{
    map.at<cv::Vec3b>(y,x) = color;
} 	

void map2D::show_map()
{
	if(map.empty())
	       std::cout << "The map is empty" << std::endl; 	

   cv::namedWindow(name_window.c_str() , cv::WINDOW_AUTOSIZE);
   cv::imshow(name_window.c_str() , map); 
   cv::waitKey(0); 
} 	


void map2D::save_map(std::string filename)
{
  cv::imwrite(filename.c_str(),map); 
} 	


cv::Vec3b map2D::check_pixel(int x, int y)
{
   return map.at<cv::Vec3b>(y,x);   
} 	

void map2D::draw_circle(int x, int y, cv::Vec3b color, int size,  int thickness)
{
	std::cout << cv::Point(x,y) << std::endl; 
   cv::circle(map, cv::Point(x,y), size,(color[0], color[1], color[2]) , thickness ); 
} 	


void map2D::draw_line(int startx, int starty, int endx, int endy, cv::Vec3b color, int lineType, int thickness)
{
	cv::line(map, cv::Point(startx,starty), cv::Point(endx, endy), (color[0], color[1], color[2]), thickness, lineType); 
} 	

void  map2D::set_pixel(int x, int y, cv::Vec3b color)
{
   map.at<cv::Vec3b>(x,y) = color; 
} 	

map2D::~map2D() {} 	
