#version 330 core
out vec4 FragColor;
uniform vec2 mousePos;
uniform vec2 wndSize;
uniform float theta; // -pi to pi
in vec4 pos;
in vec4 color;

#define PI 3.1415926535897932384626433832795f
#define TWOPI 6.28318530718f
#define SIXTH 0.16666666666f
#define THIRD 0.33333333333f
#define TWO_THIRDS 0.66666666667f

vec4 hsv2rgb(float hue, float sat, float val)
{
    float slope = 6.f*sat;
	// hue from 0 to 1
	float red = 0.f;
	float green = 0.f;
	float blue = 0.f;
	float huemod = mod(hue, SIXTH);
    float y = huemod * slope;
	if (hue < SIXTH)
	{
		red = 1.f;
		green = 1.f - sat + y;
		blue = 1.f - sat;
	} else if (hue < 2.f * SIXTH)
	{
		red = 1.f - y;
		green = 1.f;
		blue = 1.f - sat;
	} else if (hue < 3.f * SIXTH)
	{
		red = 1.f - sat;
		green = 1.f;
		blue = 1.f - sat + y;
	} else if (hue < 4.f * SIXTH)
	{
		red = 1.f - sat;
		green = 1.f - y;
		blue = 1.f;
	} else if (hue < 5.f * SIXTH)
	{
		red = 1.f - sat + y;
		green = 1.f - sat;
		blue = 1.f;
	} else
	{
		red = 1.f;
		green = 1.f - sat;
		blue = 1.f - y;
	}
	return vec4(val * red, val * green, val * blue, 1.0f);
}


void main()
{
	float angle = atan(pos.y, pos.x); // -pi to pi
    angle += theta;
    angle = mod(angle, TWOPI);
	if (angle > PI)
	{
		angle -= TWOPI;
	}
	float angle_n = angle / PI; // -1 to 1
	float a = (angle_n + 1.f) * 0.5f; // 0 to 1

    float dist = sqrt((pos.x * pos.x) + (pos.y * pos.y));

    vec2 mPos = vec2(mousePos.x / wndSize.x, 1.f - (mousePos.y / wndSize.y)); // 0 to 1, origin BL

	float theta_n = mod(theta, TWOPI) / TWOPI;

	FragColor = hsv2rgb(theta_n, dist, mPos.y);
}