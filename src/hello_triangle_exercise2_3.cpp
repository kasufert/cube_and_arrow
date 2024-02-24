#ifdef GLAD_BUILD
#include <glad/glad.h>
#endif
#ifdef GLEW_BUILD
#include <gl/glew.h>
#endif
#include <SFML/OpenGL.hpp>
#include <fmt/format.h>
#include <fmt/color.h>
#include <SFML/Graphics.hpp>

#ifdef GLAD_BUILD
#include "glad.c"
#endif

const char* vertexShaderSrc =
R"(#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 pos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = gl_Position;
})";

const char* fragShaderSrc =
R"(#version 330 core
out vec4 FragColor;
in vec4 pos;

void main()
{
	FragColor = vec4((pos.x + 1.f) * 0.5f, 0.0f, 0.0f, 1.0f);
})";

const char* fragShaderSrc2 =
R"(#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
})";



bool Initialize(sf::Window& window)
{
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Attribute::Core;
	window.create(sf::VideoMode(800, 600), "LearnOpenGL", sf::Style::Default, settings);
	window.setFramerateLimit(60);
#ifdef GLAD_BUILD
	if (!gladLoadGLLoader((GLADloadproc)sf::Context::getFunction))
	{
		fmt::print("Failed to init GLAD\n");
		return false;
	}
#endif
#ifdef GLEW_BUILD
	if (glewInit() != GLEW_OK)
	{
		fmt::print("Failed to init GLEW\n");
		return false;
	}
#endif
	glViewport(0, 0, 800, 600);
	return true;
}




void Input(sf::Window& window, bool& wireframeleft, bool& wireframeright)
{
	for (sf::Event e; window.pollEvent(e);)
	{
		if (e.type == sf::Event::Closed)
		{
			fmt::print("Goodbye\n");
			window.close();
		}
		if (e.type == sf::Event::Resized)
		{
			fmt::print("Resized\n");
			glViewport(0, 0, e.size.width, e.size.height);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) wireframeleft = false;
	else wireframeleft = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) wireframeright = false;
	else wireframeright = true;
}


GLuint CreateShaderProgram(bool right)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);
	// Check for shader compilation errors
	GLint success = -1;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fmt::print("Error::Shader::Vertex::Compilation_Failed: Message:\n{}\n", infoLog);
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, right ? &fragShaderSrc2 : &fragShaderSrc, NULL);
	glCompileShader(fragShader);
	// Check for shader compilation errors
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		fmt::print("Error::Shader::Fragment::Compilation_Failed: Message:\n{}\n", infoLog);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	// Error check
	glGetProgramiv(shaderProgram, shaderProgram, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fmt::print("Shader Program failed to link: Message: \n{}\n", infoLog);
	}

	// Delete old and no longer needed shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return shaderProgram;
}

int main()
{
	sf::Window window;
	if (!Initialize(window))
	{
		return -1;
	}

	GLuint progLeft = CreateShaderProgram(false);
	GLuint progRight = CreateShaderProgram(true);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // Bottom left
		-0.5f,  0.5f, 0.0f, // Top left
		 0.4f, -0.5f, 0.0f, // Bottom right
	};

	float vertices2[] = {
		-0.4f,  0.5f, 0.0f, // TL
		 0.5f,  0.5f, 0.0f,// TR
		 0.5f, -0.5f, 0.0f	// BR 
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	GLuint VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	bool wireframeleft = true;
	bool wireframeright = true;
	while (window.isOpen())
	{
		glClearColor(.062f, .092f, 0.13f, .180f);
		glClear(GL_COLOR_BUFFER_BIT);




		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, wireframeleft ? GL_LINE : GL_FILL);
		glUseProgram(progLeft);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glBindVertexArray(VAO2);
		glPolygonMode(GL_FRONT_AND_BACK, wireframeright ? GL_LINE : GL_FILL);
		glUseProgram(progRight);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);





		window.display();
		Input(window, wireframeleft, wireframeright);
	}


	return 0;
}

