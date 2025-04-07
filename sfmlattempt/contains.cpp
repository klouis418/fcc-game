#include <cmath>

bool pointIsInside(int circle_x, int circle_y, int circle_radius, int x, int y)
        {
            if(sqrt(pow((circle_x - x),2) + pow((circle_y-y),2)) <= circle_radius){
                return true;
            }
            else 
            return false;
        }

