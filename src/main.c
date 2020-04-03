#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "data.h"
#include "file_ops.h"

GLuint VAO[2], VBO[2], shader_program;


void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void set_data(void)
{
	glGenVertexArrays(2, VAO);


	glBindVertexArray(VAO[0]);
	glGenBuffers(1, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(first_square), 0, GL_DYNAMIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
			(void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[1]);
	glGenBuffers(1, &VBO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wall_floor), wall_floor, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
			(void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);


	const char *vertex_shader_source = file_to_str("shaders/vertex.glsl");
	const char *fragment_shader_source = file_to_str("shaders/fragment.glsl");

	GLuint vertex_shader, fragment_shader;

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program); 

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(shader_program);
}


int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800,
			"pi-collision-calculator", 0, 0);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	set_data();


	float velocity[] = {-.003, 0}, aux_velocity[2];
	unsigned short col_count = 0;
	char title[31];

	while(!glfwWindowShouldClose(window)) {
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, 1);

		sprintf(title, "pi-collision-calculator: %d", col_count);
		glfwSetWindowTitle(window, title);

		aux_velocity[0] = velocity[0]; aux_velocity[1] = velocity[1];

		if (first_square[10] <= second_square[0]) {
			// First square collision with second square
			// index 10 of first_square is its left point
			// index 0 of second_square is its right point
			velocity[0] =
				(mass_difference-1)/(mass_difference+1)*
				aux_velocity[0]+(2/(mass_difference+1))*
				aux_velocity[1];
			velocity[1] =
				(1-mass_difference)/(mass_difference+1)*
				aux_velocity[1]+((2*mass_difference)/
				(mass_difference+1))*aux_velocity[0];

			++col_count;
		} else if (second_square[10] <= -.9) {
			// Second square collision with wall
			velocity[1] = -(velocity[1]);
			++col_count;
		}


		for (unsigned char i = 0; i < 20; i+=5){
			first_square[i] += velocity[0];
			second_square[i] += velocity[1];
		}

		glClearColor(.2, .3, .3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO[0]);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(first_square),
				first_square);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(second_square),
				second_square);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

