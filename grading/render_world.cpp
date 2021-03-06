#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include "limits.h"
extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //TODO; IN PROGRESS
    double min_t = std::numeric_limits<double>::max();
    Hit bestHit;
	bestHit.object = nullptr;
	bestHit.dist = 0;
	bestHit.part = -1;

    for(unsigned i = 0; i < objects.size(); i++){
	Hit temp = objects[i]->Intersection(ray,-1);
	if(temp.dist < min_t && temp.dist >= small_t){
	  bestHit = temp;
	  min_t = temp.dist;	
	}
	}  
    return bestHit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
   // TODO; // set up the initial view ray here in PROGRESS
    Ray ray;
    ray.endpoint = camera.position;
    vec3 direc = camera.World_Position(pixel_index) - camera.position;
    ray.direction = direc.normalized();
     
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
  //  TODO; // determine the color here IN PROGRESS
     Hit cInter =  Closest_Intersection(ray);
      if(cInter.object != nullptr){
	vec3 interPoint = ray.Point(cInter.dist);
	vec3 objNorm = cInter.object->Normal(interPoint,cInter.part);
	color = cInter.object->material_shader->Shade_Surface(ray,interPoint,objNorm,recursion_depth);
}
else{
vec3 temp(0,0,0);
color = this->background_shader->Shade_Surface(ray,temp,temp,recursion_depth);
}
	
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
