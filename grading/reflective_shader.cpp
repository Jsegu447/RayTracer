#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
//World has cast ray, reflec_shader.h has k
    const double k = this->reflectivity;
    vec3 color = this->shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
    if(recursion_depth < world.recursion_depth_limit){   
    vec3 ref = 2*dot(normal,-ray.direction)*normal + ray.direction; 
    Ray reflec;
    reflec.direction = ref.normalized();
    reflec.endpoint = intersection_point;

    return color = (1-k) * color + k * world.Cast_Ray(reflec,++recursion_depth);
    }
     return color * (1-k);
}
