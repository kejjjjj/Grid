#include "pch.h"


float VectorAngle(const PVector<float>& s, const PVector<float> e)
{

	//const auto vec =  s - e;
	//return atan((float)vec.y / (float)vec.x) * 180.f / PI;

	auto sub = s - e;
	float angle = atan2(-sub.y, -sub.x) * 180.f / PI;


	return angle;
}
float VectorAngle(const PVector<int>& e)  //where s = 0,0 
{	
	//			opposite	  adjacent
	return atan((float)e.y / (float)e.x) * 180.f / PI;
}
float AngleFromAxis(const PVector<int>& pos, float angle)
{
	//angle = fmodf(angle, 90);

	if (pos.x > 0 && pos.y > 0) {
		//top right - +x +y
		//0-90
		return angle < 0 ? -angle : angle;
	}
	else if (pos.x < 0 && pos.y > 0) {
		//top left - -x +y
		//90 - 180
		return angle < 0 ? -angle + 90 : angle + 90;

	}
	else if (pos.x < 0 && pos.y < 0) {
		//bottom left - -x -y
		//-180 - -90
		angle = angle > 0 ? -angle - 90 : angle - 90;
		angle += 180;
		angle = (angle + 180 % 360);
	}
	else if (pos.x > 0 && pos.y < 0) {
		//bottom right - +x -y
		//-90 - 0
		angle = angle > 0 ? -angle : angle;
		angle += 180;
		angle = (angle + 180 % 360);
	}

	return angle;
}