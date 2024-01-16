#include "minirt.h"

// delete diam param?
bool	find_closer_disk_hit(t_cylinder *cylinder, t_ray *ray, double ray_tmin, double *t1, t_hit_record* rec)
{
    // Calculate the center of the disk
    t_vector diskCenter;
	t_vector temp_p = multiply(&cylinder->axis, cylinder->height / 2.0);
	t_vector temp_n = multiply(&cylinder->axis, -cylinder->height / 2.0);
    if (ray->direction.y > 0) {
        diskCenter = vector_add(&cylinder->center, &temp_p);
    } else {
        diskCenter = vector_add(&cylinder->center, &temp_n);
    }

    // Calculate the coefficients for the quadratic equation
    double a = dot(&ray->direction, &cylinder->axis);
	t_vector temp = vector_subtract(&diskCenter, &ray->origin);
    double b = dot(&temp, &cylinder->axis);
    double c = dot(&temp, &temp) - pow(cylinder->radius, 2);

    // Solve the quadratic equation
    double discriminant = b * b - a * c;
    if (discriminant < 0) {
        // No intersection with the disk
        return false;
    }

    // Find the closest intersection point
    double sqrtDiscriminant = sqrt(discriminant);
    double root1 = (-b + sqrtDiscriminant) / a;
    double root2 = (-b - sqrtDiscriminant) / a;

    // Check if the roots are within the valid range
    if (root1 < ray_tmin || root1 > *t1) {
        if (root2 < ray_tmin || root2 > *t1) {
            // Both roots are outside the valid range
            return false;
        } else 
		{
            *t1 = root2;
        }
    } else {
        *t1 = root1;
    }
	record_cylinder_cap_hit(t1, cylinder, ray, rec);
    return true;
}

void	find_abc_and_discriminant(t_cylinder *cylinder, t_ray *ray, double *abcd)
{
	double		a;
	t_vector	origin_minus_center;
	double		b;
	double		c;
	double		discriminant;

	a = dot(&ray->direction, &ray->direction) - powf(dot(&ray->direction, &cylinder->axis), 2);
	origin_minus_center = vector_subtract(&ray->origin, &cylinder->center);
	b = 2 * (dot(&ray->direction, &origin_minus_center) - dot(&ray->direction, &cylinder->axis) * dot(&origin_minus_center, &cylinder->axis));
	c = dot(&origin_minus_center, &origin_minus_center) - powf(dot(&origin_minus_center, &cylinder->axis), 2) - powf(cylinder->radius, 2);
	discriminant = b * b - 4 * a * c;
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = discriminant;
}

bool	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record* rec) 
{
	double	abcd[4];
	double	t1;
	double	t2;

	find_abc_and_discriminant(cylinder, ray, abcd);
	if (abcd[DISCRIMINANT] < 0) 
	    return (false);
	else if (abcd[DISCRIMINANT] == 0) 
	    t1 = -abcd[B] / (2 * abcd[A]);
	else 
	{
	    double sqrtDiscriminant = sqrt(abcd[DISCRIMINANT]);
	    t1 = (-abcd[B] + sqrtDiscriminant) / (2 * abcd[A]);
	    t2 = (-abcd[B] - sqrtDiscriminant) / (2 * abcd[A]);
	    if (t2 >= ray_tmin && t2 <= ray_tmax) 
	    {
	        t1 = t2;
	    }
	}
	if (t1 < ray_tmin || t1 > ray_tmax) 
		return (false);

	t_point point = trace_ray(ray, t1);
	double y = point.y;  // Assuming 'y' is the vertical coordinate of the intersection point
    
	bool hit_side = true;
	bool hitCap1 = false;
	bool hitCap2 = false;
	if (y < cylinder->center.y - cylinder->height / 2.0 || y > cylinder->center.y + cylinder->height / 2.0) {
        // The intersection point is outside the height range, so ignore it
        hit_side = false;
    }
	else
	{
		hitCap1 = find_closer_disk_hit(cylinder, ray, ray_tmin, &t1, rec);
		hitCap2 = find_closer_disk_hit(cylinder, ray, ray_tmin, &t1, rec);
		if (hitCap1 || hitCap2) 
			printf("Hit a cap\n");
	}
	
	if (!hit_side && !hitCap1 && !hitCap2) 
		return (false);
	
	if (!hitCap1 && !hitCap2)
	{
		record_cylinder_tube_hit(t1, cylinder, ray, rec);
	}
	return (true);
}