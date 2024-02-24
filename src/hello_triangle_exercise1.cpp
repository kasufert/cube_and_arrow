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
#include <fstream>
#include <sstream>

#ifdef GLAD_BUILD
#include "glad.c"
#endif

#define PI 3.1415926535897932384626433832795


bool Initialize(sf::Window& window)
{
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Attribute::Core;
	window.create(sf::VideoMode(800, 600), "LearnOpenGL", sf::Style::Default, settings);
	window.setFramerateLimit(144);
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




void Input(sf::Window& window, bool& wireframe, sf::Vector2f& mPos)
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
			fmt::print("Resized to {}, {}\n", e.size.width, e.size.height);
			glViewport(0, 0, e.size.width, e.size.height);
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::W)
		{
			wireframe = !wireframe;
		}
		if (e.type == sf::Event::MouseMoved)
		{
			mPos = { (float)e.mouseMove.x, (float)e.mouseMove.y };
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			fmt::print("Click at {}, {}\n", e.mouseButton.x, e.mouseButton.y);
		}
	}
}

std::string ReadFile(const char* path)
{
	std::ifstream f(path);
	std::stringstream s;
	s << f.rdbuf();
	return s.str();
}

GLuint CreateShaderProgram(bool right)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderSrcStr = ReadFile("../resources/shaders/alt/vert.glsl");
	const char* vertShaderSrc = vertShaderSrcStr.c_str();
	glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
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
	std::string fragSrc = ReadFile("../resources/shaders/alt/frag.glsl");
	const char* fragSrcStr = fragSrc.c_str();
	glShaderSource(fragShader, 1, &fragSrcStr, NULL);
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


	float vertices[] = {
	// 	  x		y		z	 r	  g	   b	a
		-1.0f, -1.0f, 0.0f, 1.f, 0.f, 0.f, 1.f, // Bottom left
		-1.0f,  1.0f, 0.0f, 0.f, 1.f, 0.f, 1.f, // Top left
		 1.0f, -1.0f, 0.0f, 0.f, 0.f, 1.f, 1.f, // Bottom right
		 1.0f,  1.0f, 0.0f, 0.f, 0.f, 1.f, 1.f  // Top right
	};

	u_int indices[] = {
		// BL, TL, BR
		0, 1, 2,
		// TL, BR, TR
		1, 2, 3
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint shaderProgram = CreateShaderProgram(true);
	glUseProgram(shaderProgram);



	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // VAOs store EBO bindings. So whenever you bind an EBO, the currently bound VBO stores a pointer to it.

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // If this was called while our VAO was bound, it would unbind our EBO from its EBO pointer.

	bool wireframe = false;
	sf::Vector2f mPos = { 0.f,0.f };
	float hue = 0.f;
	float sat = 0.f;
	float val = 1.f;
	float theta = -PI;
	while (window.isOpen())
	{
		theta += 0.004f;
		if (theta > PI)
		{
			theta -= 2 * PI;
		}

		glClearColor(.062f, .092f, 0.13f, .180f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);


		glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

		GLint mousePosLoc = glGetUniformLocation(shaderProgram, "mousePos");
		glUniform2f(mousePosLoc, mPos.x, mPos.y);
		GLint windowSizeLoc = glGetUniformLocation(shaderProgram, "wndSize");
		glUniform2f(windowSizeLoc, (float)window.getSize().x, (float)window.getSize().y);
		GLint thetaLoc = glGetUniformLocation(shaderProgram, "theta");
		glUniform1f(thetaLoc, theta);

		//GLenum mode, GLsizei count, GLenum type, const void *indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		window.display();
		Input(window, wireframe, mPos);
	}


	return 0;
}

