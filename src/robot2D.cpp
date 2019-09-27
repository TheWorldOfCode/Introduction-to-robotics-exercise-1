#include "../includes/robot2D.hpp"
#include <stdio.h> 

robot2D::robot2D(int start_position_x, int start_position_y, int si, cv::Vec3b rColor, cv::Vec3b pColor, map2D * new_map)
{
	x = start_position_x;
	y = start_position_y;
	robot_color = rColor;
	path_color = pColor;
	size = si;
	map = new_map;
} 	

template<typename T> int sign(T val)
{
   return (T(0) < val) - (val < T(0));  

} 	

cv::Point normalize(cv::Point p)
{

	if(p.x != 0 && p.x < p.y){
		p.x /= std::abs( p.x);
		p.y /= std::abs( p.x);

	} else if (p.x == 0) 
		p.y /= std::abs( p.y);
	else if(p.y == 0) 
		p.x /= std::abs(p.x);
	else{  
		p.x /= std::abs(p.y);
		p.y /= std::abs(p.y);
	} 

	if(p.x > 1)
	{
		p.x = 1 * sign(p.x) ;
		p.y = 0;
	} else if (p.x == 1 && p.y > 1) {
		p.x = 1 * sign(p.x) ;
		p.y = 1* sign(p.y) ;
	} else{
		p.y = 1 * sign(p.y);
	} 

	return p;
}

cv::Point moving_direction(cv::Point path){

	path = normalize(path); 

	cv::Point dir;

	if(path.x > 0 )
		dir.x = 1;
	else if(path.x < 0)
		dir.x = -1;
	else 
		dir.x = 0;

	if(path.y > 0)
		dir.y = 1;
	else if(path.y < 0)
		dir.y = -1;
	else 
		dir.y = 0;

	return dir;	

}  


std::vector<bool> collision_detect(int x, int y, map2D * map)
{

	std::vector<bool> k;
	k.push_back(map->check_pixel(x +1, y) == cv::Vec3b(0,0,0) ); //0
	k.push_back(map->check_pixel(x -1, y) == cv::Vec3b(0,0,0) ); // 1
	k.push_back(map->check_pixel(x, y + 1) == cv::Vec3b(0,0,0) ); // 2
	k.push_back(map->check_pixel(x, y - 1) == cv::Vec3b(0,0,0) ); // 3
	k.push_back(map->check_pixel(x+1,y+1) == cv::Vec3b(0,0,0));  // 4
	k.push_back(map->check_pixel(x-1,y+1) == cv::Vec3b(0,0,0));  // 5 
	k.push_back(map->check_pixel(x-1,y-1) == cv::Vec3b(0,0,0));  // 6
	k.push_back(map->check_pixel(x+1,y-1) == cv::Vec3b(0,0,0));  // 7
	return k;	
} 	


void robot2D::moving_around_border()
{
	std::vector<bool> k = collision_detect(x,y, map); 

	if(k[0] && k[3])
	{ 
		if(k[7])
			map->move(--x,y,path_color); 
		else 
			map->move(--x,--y, path_color); 	

	} else if(k[0])
		map->move(x, --y, path_color); 
	else if(k[1] && k[2])
		map->move(++x,++y, path_color);	
	else if(k[1])
		map->move(x,++y, path_color);
	else if(k[2] && k[0])
		map->move(++x, --y, path_color);
	else if(k[2])
		map->move(++x,y, path_color);
	else if(k[3] && k[1])
		map->move(--x,++y, path_color);
	else if(k[3])
		map->move(--x, y, path_color); 
	else if(k[4])
		map->move(++x,y,path_color);
	else if(k[5])
		map->move(x, ++y, path_color);
	else if(k[6])
		map->move(--x,y, path_color);
	else if(k[7])
		map->move(x,--y,path_color); 	


} 

void robot2D::bug1(position p)
{
	cv::Point start(x,y);
	cv::Point goal(p.get_x(), p.get_y());
	int behaviour = 0;
	int behaviour2 = 0;
	cv::Point mini_distance_point;
	int mini_distance = 0;

	std::cout << "Enter 1" << std::endl;  
	cv::Point hit_point;

	while(!p.at_position(x,y))
	{
		cv::Point current_path = goal - cv::Point(x,y);
		int distance_to_goal = std::sqrt(current_path.x * current_path.x + current_path.y*current_path.y);
		cv::Point path = moving_direction(current_path); 
bfswitch:       	
		

		if(behaviour == 1) {  

			if(distance_to_goal < mini_distance && behaviour2 == 0){
				mini_distance_point = cv::Point(x,y);
				mini_distance = distance_to_goal;	
			} else if(mini_distance_point == cv::Point(x,y) ) 	{
				behaviour = 0;
				behaviour2 = 0;
				goto  bfswitch;
			} 

			moving_around_border();


			if(hit_point == cv::Point(x,y))
				behaviour2 = 1;	

		} else { 
			if(map->check_pixel(x+path.x, y + path.y) == cv::Vec3b(0,0,0)){ 
				behaviour = 1;
				hit_point = cv::Point(x,y);
				mini_distance = distance_to_goal; 
			} else { 
				x += path.x;
				y += path.y;
				map->move(x,y ,path_color); 	   
			}
		} 	
	}
}  


bool check_if_point_is_on_line(cv::Point point, cv::Point start, cv::Point end )
{

	cv::Point path = start;
	while(path != end) 
	{
		if(path == point)
			return true;

		cv::Point line = end - path;

		line = normalize(line);  
		path += line; 

		if(line == cv::Point(0,0)) 
			break;
	} 

	return false;
} 	


void robot2D::bug2(position p)
{
	cv::Point start(x,y);
	cv::Point goal(p.get_x(), p.get_y());
	cv::Point mLine = goal - start;

	int behaviour = 0;

	cv::Point mini_distance_point;
	int mini_distance = 0;

	cv::Point hit_point;

	int b = 0;
	while(!p.at_position(x,y))
	{
		cv::Point current_path = goal - cv::Point(x,y); 
		cv::Point next_move = moving_direction(current_path);
		int distance_to_goal = std::sqrt(current_path.x * current_path.x + current_path.y+current_path.y);

		if(behaviour == 1)
		{


			moving_around_border();

			if(check_if_point_is_on_line(cv::Point(x,y), hit_point,goal))
			{
				b = 0;
				behaviour = 0;
				mini_distance = distance_to_goal;
			} 


		}
		else
		{

			if(map->check_pixel(x+next_move.x, y+next_move.y) == cv::Vec3b(0,0,0) ) {

				behaviour = 1;
				hit_point = cv::Point(x,y);
				mini_distance = distance_to_goal; 

			} else {  
				x += next_move.x;
				y += next_move.y;
				map->move(x, y, path_color); 
			}

		} 	

	} 

} 	
robot2D::~robot2D() {}  

