//============================================================================
// Name        : hello_opengl.cpp
// Author      : avorobyev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {

	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL.
	//Мажорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	    std::cout << "Failed to initialize GLEW" << std::endl;
	    return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	GLfloat vertices[] = {
	    -0.5f,  0.5f, 0.0f,  // Верхний угол
	     0.0f, -0.5f, 0.0f,  // Нижний правый угол
	    -1.0f, -0.5f, 0.0f,  // Нижний левый угол
	};

	GLfloat vertices_2[] = {
	     0.5f,  0.5f, 0.0f,  // Верхний угол 2
	     1.0f, -0.5f, 0.0f,  // Нижний правый угол 2
	     0.0f, -0.5f, 0.0f   // Нижний левый угол 2
	};
	GLuint indices[] = {  // Помните, что мы начинаем с 0!
	    0, 1, 2
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VBO_2;
	glGenBuffers(1, &VBO_2);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	const char *vertexShaderSource = "#version 330 core\n"
	    "layout (location = 0) in vec3 position;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	    "}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
	    "out vec4 color;\n"
	    "void main()\n"
	    "{\n"
	    "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	const char *fragmentShaderSource_yellow = "#version 330 core\n"
	    "out vec4 color;\n"
	    "void main()\n"
	    "{\n"
	    "   color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader_yellow;
	fragmentShader_yellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_yellow, 1, &fragmentShaderSource_yellow, NULL);
	glCompileShader(fragmentShader_yellow);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram_yellow;
	shaderProgram_yellow = glCreateProgram();
	glAttachShader(shaderProgram_yellow, vertexShader);
	glAttachShader(shaderProgram_yellow, fragmentShader_yellow);
	glLinkProgram(shaderProgram_yellow);

	glGetProgramiv(shaderProgram_yellow, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram_yellow, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader_yellow);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VAO_2;
	glGenVertexArrays(1, &VAO_2);

	// 1. Привязываем VAO
	glBindVertexArray(VAO);
	// 2. Копируем наш массив вершин в буфер для OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. Устанавливаем указатели на вершинные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//4. Отвязываем VAO
	glBindVertexArray(0);

	// 1. Привязываем VAO_2
	glBindVertexArray(VAO_2);
	// 2. Копируем наш массив вершин в буфер для OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. Устанавливаем указатели на вершинные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//4. Отвязываем VAO_2
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window))
	{
	    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    	glfwSetWindowShouldClose(window, true);

	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);

	    glUseProgram(shaderProgram);
	    glBindVertexArray(VAO);
	    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	    glBindVertexArray(0);
	    glUseProgram(shaderProgram_yellow);
	    glBindVertexArray(VAO_2);
	    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	    glBindVertexArray(0);
	    glfwSwapBuffers(window); //appeared black screen
	    glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
