#include "Utils.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Hittable.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"

int main() {
	camera camera;

	//World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

	camera.render(world);
}