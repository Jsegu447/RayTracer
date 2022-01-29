#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; //determine the color
    color = world.ambient_color * world.ambient_intensity * color_ambient; //ALWAYS AMBIENT LIGHT
    for(unsigned i = 0; i < world.lights.size(); i++){
	vec3 l = world.lights[i]->position - intersection_point; // light vector
	Ray Light;
	Light.direction = l.normalized();
	Light.endpoint = intersection_point; //Light ray created

	if(world.enable_shadows == false || world.Closest_Intersection(Light).object == nullptr){

	color += color_diffuse * std::max(dot(Light.direction,normal),0.0) * world.lights[i]->Emitted_Light(l); // L_d*R_d*max(n dot l,0) or Diffuse portion
//EMIITED LIGHT NEEDS DISTANCE ********
	

	vec3 r = 2 * dot(Light.direction,normal)*normal - Light.direction; //Formula for r
	r = r.normalized();
	vec3 c = world.camera.position - intersection_point;
	c = c.normalized();
	color += color_specular * std::pow(std::max(dot(r,c),0.0),specular_power) * world.lights[i]->Emitted_Light(l); // Specular portion		
	}
	}
    
    return color;
}
