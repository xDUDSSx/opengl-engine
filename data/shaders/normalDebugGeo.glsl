#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 18) out;

in VS_OUT {
	vec3 normal;
	vec3 tangent;
	vec3 binormal;
} gs_in[];

out vec3 fColor;

uniform float magnitude;

uniform mat4 projectionMatrix;

void generate(int index, int type)
{
	gl_Position = projectionMatrix * gl_in[index].gl_Position;
	fColor = vec3(1, 1, 1);
	EmitVertex();
	if (type == 0) {
		fColor = vec3(0, 1, 0);
		gl_Position = projectionMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * magnitude);
	} else
	if (type == 1) {
		fColor = vec3(1, 0, 0);
		gl_Position = projectionMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].tangent, 0.0) * magnitude);
	} else
	if (type == 2) {
		fColor = vec3(0, 0, 1);
		gl_Position = projectionMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].binormal, 0.0) * magnitude);
	}
	EmitVertex();
	EndPrimitive();
}

void main()
{
	generate(0, 0);
	generate(1, 0);
	generate(2, 0);

	generate(0, 1);
	generate(1, 1);
	generate(2, 1);

	generate(0, 2);
	generate(1, 2);
	generate(2, 2);
}