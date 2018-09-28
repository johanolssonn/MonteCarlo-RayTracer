#include "Camera.h"

 Camera::Camera(Vertex eyePoint1, Vertex eyePoint2, bool useEyePoint1 = true)
        :_eyePoint1{eyePoint1}, _eyePoint2{eyePoint2}, _useEyePoint1{useEyePoint1}
    {
    
	}

void Camera::render() {

    //launches a ray through each pixel one at a time
    
}