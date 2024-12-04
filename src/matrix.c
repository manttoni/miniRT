#include "../inc/minirt.h"

t_matrix	transformation(double a, double b, double g)
{
	t_matrix	m;
	
	m.val[0][0] = cos(b) * cos(g);
	m.val[0][1] = sin(a) * sin(b) * cos(g) - cos(a) * sin(g);
	m.val[0][2] = cos(a) * sin(b) * cos(g) + sin(a) * sin(g);
	m.val[1][0] = cos(b) * sin(g);
	m.val[1][1] = sin(a) * sin(b) * sin(g) + cos(a) * cos(g);
	m.val[1][2] = cos(a) * sin(b) * sin(g) - sin(a) * cos(g);
	m.val[2][0] = -sin(b);
	m.val[2][1] = sin(a) * cos(b);
	m.val[2][2] = cos(a) * cos(b);
	return (m);
}

/* Multiplies a vector with a matrix */
t_vector	multi_matrix(t_vector v, t_matrix m)
{
	t_vector	r;

	r.x = dot_product(v, vector(m.val[0][0], m.val[1][0], m.val[2][0]));
	r.y = dot_product(v, vector(m.val[0][1], m.val[1][1], m.val[2][1]));
	r.z = dot_product(v, vector(m.val[0][2], m.val[1][2], m.val[2][2]));
	return (r);
}

/*
int main(void)
{
	t_matrix m = transformation(1, 2, 3);
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			printf("%f", m.val[i][j]);
			if (j == 2)
				printf("\n");
			else
				printf(" ");
		}
	}
}*/
