#include "minirt.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}
