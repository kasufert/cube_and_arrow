#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 uCompleteMatrix;
out vec4 pos;
out vec4 color;
out vec2 texCoord;

#define PI 3.1415926535897932384626433832795f
#define SIXTH 0.16666666666f


vec3 rect2pol(vec3 v)
{
	float theta = atan(v.y, v.z);
	float phi = atan(v.x, v.z);
	float r = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return vec3(phi, theta, r);
}

vec2 pol2rect(vec2 v)
{
	return vec2(v.x * cos(v.y), v.x * sin(v.y));
}

vec4 hsv2rgb(float hue, float sat, float val)
{
    hue = abs(hue);
    hue = mod(hue, 1.0);
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
	gl_Position = uCompleteMatrix * vec4(aPos, 1.0);
    pos = gl_Position;
	color = mix(hsv2rgb(aPos.x, 1.0, 1.0), aColor, 0.6);
    texCoord = aTexCoord;
}