#include "minirt.h"
void printf_split(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		printf("%i.%s\n", i, str[i]);
		i++;
	}
}

#include "minirt.h"

// Function to print a t_color
void printf_color(t_color color)
{
    printf("Color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b);
}

// Function to print a t_point3 or t_vec3
void printf_point3(t_point3 point)
{
    printf("Point3: X=%.3f, Y=%.3f, Z=%.3f\n", point.x, point.y, point.z);
}

void printf_vec3(t_vec3 vec)
{
    printf("Vec3: X=%.3f, Y=%.3f, Z=%.3f\n", vec.x, vec.y, vec.z);
}

// Print details of a sphere
void printf_sphere(t_sphere *sphere)
{
    if (!sphere)
    {
        printf("Sphere: NULL\n");
        return;
    }
    printf("=== Sphere ===\n");
    printf("Center: ");
    printf_point3(sphere->center);
    printf("Radius: %.3f\n", sphere->radius);
    printf("Color: ");
    printf_color(sphere->color);
    printf("================\n");
}

// Print details of a plane
void printf_plane(t_plane *plane)
{
    if (!plane)
    {
        printf("Plane: NULL\n");
        return;
    }
    printf("=== Plane ===\n");
    printf("Center: ");
    printf_point3(plane->center);
    printf("Normal Vector: ");
    printf_vec3(plane->N);
    printf("Color: ");
    printf_color(plane->color);
    printf("================\n");
}

// Print details of a cone
void printf_cone(t_cone *cone)
{
    if (!cone)
    {
        printf("Cone: NULL\n");
        return;
    }
    printf("=== Cone ===\n");
    printf("Vertex: ");
    printf_point3(cone->vertex);
    printf("Axis Vector: ");
    printf_vec3(cone->axis);
    printf("Angle (Radians): %.3f\n", cone->angle);
    printf("Height: %.3f\n", cone->height);
    printf("Color: ");
    printf_color(cone->color);
    printf("Intersection Type: %d\n", cone->inter_type);
    printf("================\n");
}

// Print details of a cylinder
void printf_cylinder(t_cylinder *cylinder)
{
    if (!cylinder)
    {
        printf("Cylinder: NULL\n");
        return;
    }
    printf("=== Cylinder ===\n");
    printf("Center: ");
    printf_point3(cylinder->center);
    printf("Axis Vector: ");
    printf_vec3(cylinder->N_axis_vec);
    printf("Diameter: %.3f\n", cylinder->diameter);
    printf("Height: %.3f\n", cylinder->height);
    printf("Color: ");
    printf_color(cylinder->color);
    printf("================\n");
}

#include "minirt.h"

// Print details of t_view
void printf_view(t_view *view)
{
    if (!view)
    {
        printf("View: NULL\n");
        return;
    }
    printf("=== View ===\n");
    printf("Camera Center: ");
    printf_point3(view->camera_center);
    printf("Focal Length: ");
    printf_point3(view->focal_length);
    printf("Field of View (degrees): %f\n", view->fov_degrees);
    printf("================\n");
}

// Print all lights
void printf_lights(t_light *amb_light, t_light *diff_lights, size_t diff_lights_cnt)
{
    if (amb_light)
    {
        printf("=== Ambient Light (Type 1) ===\n");
        printf("Origin: ");
        printf_point3(amb_light->origin);
        printf("Brightness: %.3f\n", amb_light->brightness);
        printf("Color: ");
        printf_color(amb_light->color);
        printf("================\n");
    }
    else
    {
        printf("Ambient Light: None\n");
    }

    if (diff_lights_cnt > 0)
    {
        printf("=== Diffuse Lights (Type 3) ===\n");
        for (size_t i = 0; i < diff_lights_cnt; i++)
        {
            printf("Diffuse Light %zu (Type 3):\n", i + 1);
            printf("Origin: ");
            printf_point3(diff_lights[i].origin);
            printf("Brightness: %.3f\n", diff_lights[i].brightness);
            printf("Color: ");
            printf_color(diff_lights[i].color);
        }
        printf("================\n");
    }
    else
    {
        printf("Diffuse Lights: None\n");
    }
}

// Print all objects
// Print all objects with updated type codes
void printf_objects(t_object *objects, size_t objects_cnt)
{
    printf("=== Objects ===\n");
    for (size_t i = 0; i < objects_cnt; i++)
    {
        printf("Object %zu (Type %d):\n", i + 1, objects[i].type);
        switch (objects[i].type)
        {
            case SPHERE: // Sphere
                printf_sphere((t_sphere *)objects[i].object);
                break;
            case PLANE: // Plane
                printf_plane((t_plane *)objects[i].object);
                break;
            case CYLINDER: // Cylinder
                printf_cylinder((t_cylinder *)objects[i].object);
                break;
            case CONE: // Cone
                printf_cone((t_cone *)objects[i].object);
                break;
            default:
                printf("Unknown object type.\n");
                break;
        }
    }
    printf("================\n");
}

// Print everything
void printf_all(t_data *data)
{
    if (!data)
    {
        printf("Data: NULL\n");
        return;
    }
    printf_view(data->view);
    printf_lights(data->amb_light, data->diff_lights, data->diff_lights_cnt);
    printf_objects(data->objects, data->objects_cnt);
	printf("%ldHEREEEE\n",data->objects_cnt);
}
