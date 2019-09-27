#include "../includes/robot2D.hpp"
#include "../includes/map2D.hpp"
#include "../includes/position.hpp"

#include <stdio.h>

int main()
{
	map2D map = map2D("../images/map.png", "Map");

	robot2D robot1(6,6,1, cv::Vec3b(0,255,0), cv::Vec3b(255,0,255), & map ); 
	robot2D robot2(6,6,1, cv::Vec3b(0,255,0), cv::Vec3b(100,255,100), & map ); 

	position g = position(502,502, cv::Vec3b(100 ,100, 100));
	position s = position(6,6,cv::Vec3b(0,0,255)); 

	g.draw_position_on_map(map);
	s.draw_position_on_map(map); 
	//  s.draw_line_between_position_on_map(g,map,cv::Vec3b(100,0,100) );

	std::cout << "Bug 1 started" << std::endl; 
	robot1.bug1(g); 
	std::cout << "bug 1 done" << std::endl;
	std::cout << "Bug 2 started" << std::endl; 
	robot2.bug2(g); 
	std::cout << "bug 2 done" << std::endl; 
	map.show_map(); 

	map.save_map("../images/map_with_path.png"); 
	return 0; 
} 	

