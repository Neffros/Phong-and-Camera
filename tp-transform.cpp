#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm.hpp>
#include "DragonData.h"
#include "myShader.h"
#include "myMesh.h"
#include "Camera.h"


struct Application
{

	// INTIALIZE DRAGON MESH
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	Mesh mesh;
	myShader shader;
	Camera cam;

	bool Initialize()
	{
		shader = myShader("transform.vs.glsl", "transform.fs.glsl");
		glEnable(GL_DEPTH_TEST);
		cam.setPosition(myVector3(0, 0, 0));

		for (int i = 0; i < sizeof(DragonVertices) / sizeof(float) - 7; i += 8)
		{
			glm::vec3 pos(DragonVertices[i], DragonVertices[i + 1], DragonVertices[i + 2]);
			glm::vec3 norm(DragonVertices[i + 3], DragonVertices[i + 4], DragonVertices[i + 5]);
			glm::vec2 text(DragonVertices[i + 6], DragonVertices[i + 7]);
			vertices.push_back(Vertex{ pos, norm, text });
		}

		for (int i = 0; i < sizeof(DragonIndices) / sizeof(uint16_t); i++) {
			indices.push_back(DragonIndices[i]);
		}


		mesh = Mesh(vertices, indices);


		return true;
	}

	void Terminate()
	{

		mesh.terminate();
		shader.terminate();
	}

	void Display(GLFWwindow* window)
	{

		shader.use();

		/* Render here */
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.15f, 0.1f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLint timeLoc = glGetUniformLocation(shader.getProgramId(), "u_Time");
		float time = static_cast<float>(glfwGetTime());
		glUniform1f(timeLoc, time);



		GLint tmatLoc = glGetUniformLocation(shader.getProgramId(), "u_TranslationMatrix");
		float translationMatrix[] = {
			1.f, 0.f, 0.f, 0.f, // 1ere colonne
			0.f, 1.f, 0.f, 0, // 2eme colonne
			0.f, 0.f, 1.f, 0, // 3eme colonne
			0, 0, 20.f, 1.f // 4eme colonne
		};
		glUniformMatrix4fv(tmatLoc, 1, false, translationMatrix);

		GLint rmatLoc = glGetUniformLocation(shader.getProgramId(), "u_RotationMatrix");
		float rotationMatrix[] = {
			cos(time), 0.f, -sin(time), 0.f, // 1ere colonne
			0.f, 1.f, 0.f, 0.f, // 2eme colonne
			sin(time), 0.f, cos(time), 0.f, // 3eme colonne
			0.f, 0.f, 0.f, 1.f // 4eme colonne
		};
		glUniformMatrix4fv(rmatLoc, 1, false, rotationMatrix);

		GLint projLoc = glGetUniformLocation(shader.getProgramId(), "u_ProjectionMatrix");
		float fov = 60.f * 3.14159f / 180.f;
		float f = 1.f / tan(fov / 2.f);
		float a = (float)width / (float)height;
		float far = 1000.f;
		float near = 0.1f;
		float projectionMatrix[] = {
			f / a, 0.f, 0.f, 0.f, // 1ere colonne
			0.f, f, 0.f, 0.f, // 2eme colonne
			0.f, 0.f, (far + near) / (near - far), -1.f, // 3eme colonne
			0.f, 0.f, (2.f * far * near) / (near - far), 0.f // 4eme colonne
		};

		glUniformMatrix4fv(projLoc, 1, false, projectionMatrix);

		GLint colorLocation = glGetUniformLocation(shader.getProgramId(), "u_Color");
		glm::vec3 color(1.0f, 0.0f, 0.0f);
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));

		GLint camPosLocation = glGetUniformLocation(shader.getProgramId(), "u_viewPos");
		GLfloat camPos[] = { cam.getPosition().getX(),cam.getPosition().getY(),cam.getPosition().getZ() };
		glUniform3fv(camPosLocation, 1, camPos);

		GLint viewLoc = glGetUniformLocation(shader.getProgramId(), "u_ViewMatrix");
		//myVector3 targetPos(-cos(time), -sin(time), -10.f);et un 
		//myVector3 targetPos(0, -sin(time), -10.f);
		myVector3 targetPos(0, 5, 20); // x and y have to be opposite values 
		float* viewMat = cam.lookAt(targetPos); //check if size of float is right if not working 
		glUniformMatrix4fv(viewLoc, 1, false, viewMat);
		mesh.draw(shader);
		/*	glBindVertexArray(g_Mesh.VAO);
			glDrawElements(GL_TRIANGLES, g_Mesh.indicesCount /* nb indices*/
			//	, GL_UNSIGNED_SHORT, (void*)0);

			// color	



	}
};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 720, "TP transformations et projection 15/12", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewInit();

	Application app;

	app.Initialize();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		app.Display(window);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	app.Terminate();

	glfwTerminate();
	return 0;
}