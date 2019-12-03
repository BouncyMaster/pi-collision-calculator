#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "data.h"

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(first_square), 0, GL_STREAM_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[1]);
	glGenBuffers(1, &VBO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wall_floor), wall_floor, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);


	const char * const vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main(){\n"
		"	gl_Position = vec4(aPos.xy, 0, 1);\n"
		"	ourColor = aColor;\n"
		"}\0";

	const char * const fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main(){\n"
		"	FragColor = vec4(ourColor, 1);\n"
		"}\0";

	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertexShader);
	glAttachShader(shader_program, fragmentShader);
	glLinkProgram(shader_program); 

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shader_program);

}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "pi-collision-calculator", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	set_data();


	float x_velocity[] = {-.003, 0}, aux_x_velocity[2];
	unsigned short col_count = 0;
	while(!glfwWindowShouldClose(window)){
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, 1);

		aux_x_velocity[0] = x_velocity[0]; aux_x_velocity[1] = x_velocity[1];
		if (first_square[10] <= second_square[0]){ // First square collision with second square
			x_velocity[0] = (mass_difference-1)/(mass_difference+1)*aux_x_velocity[0]+
					(2/(mass_difference+1))*aux_x_velocity[1];
			x_velocity[1] = (1-mass_difference)/(mass_difference+1)*aux_x_velocity[1]+
					((2*mass_difference)/(mass_difference+1))*aux_x_velocity[0];

			++col_count;
		} else if (second_square[10] <= -.9){ // Second square collision with wall
			x_velocity[1] = -(x_velocity[1]);
			++col_count;
		}


		for (unsigned char i = 0; i < 20; i+=5){
			first_square[i] += x_velocity[0]; 
			second_square[i] += x_velocity[1];
		}

		glClearColor(.2, .3, .3, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(VAO[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(first_square), first_square);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(second_square), second_square);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

