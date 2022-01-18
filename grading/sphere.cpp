#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO; IN PROGRESS
    Hit inter;

    vec3 ec =  ray.endpoint - this->center;
    double b = 2 * dot(ec,ray.direction);
    double c = dot(ec,ec) - (this->radius*this->radius);
    double t;
    if( (b * b) - (4 * c) > 0 ){
	double temp = -1*b - sqrt(((b*b) - (4*c)));
	t = temp / 2;
	if(t > 0){
		inter.object = this;
		inter.dist = t;
		inter.part = part;
	}
	else{
		temp = -1*b + sqrt(((b*b) - (4*c)));
		t = temp/2;
		inter.object = this;
		inter.dist = t;
		inter.part = part;
	}
}

    else{
	inter.object = nullptr;
	inter.part = 0;
	inter.dist = part;

	}

    return inter;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
