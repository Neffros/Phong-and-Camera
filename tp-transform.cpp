#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DragonData.h"
#include "myShader.h"
#include "myMesh.h"
#include <math.h>
#include <Camera.h>
#include <glm.hpp>
Camera cam;
myShader shader("transform.vs.glsl", "transform.fs.glsl");

struct Application
{
	
	bool Initialize() 
	{
		vector<Vertex> res;
		// format X,Y,Z, NX, NY, NZ, U, V = 8 floats par vertex
		for (int i = 0; i < sizeof(DragonVertices) / sizeof(float); i += 8)
		{
			glm::vec3 pos(DragonVertices[i], DragonVertices[i + 1], DragonVertices[i + 2]);
			glm::vec3 norm(DragonVertices[i+4],DragonVertices[i+5], DragonVertices[i+6]);
			glm::vec2 text(DragonVertices[i + 7], DragonVertices[i + 8]);
			res.push_back(Vertex{pos, norm, text});
		}
		Mesh mesh(res, DragonIndices);


		// Exercice 2 : VAO

		glGenVertexArrays(1, &g_Mesh.VAO);
		
		// ATTENTION: le VAO va maintenant enregister tous les parametres
		// des fonctions glEnableVertexAttribArray, glVertexAttribPointer, mais aussi
		// glBindBuffer quand le 1er param est GL_(ELEMENT)_ARRAY_BUFFER
		glBindVertexArray(g_Mesh.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, g_Mesh.VBO);

		GLuint program = shader.GetProgram();

		// on indique a OpenGL la structuration des sommets
		// stride = ecart en octets entre deux sommets
		GLint posLocation = glGetAttribLocation(program, "a_Position");
		glVertexAttribPointer(posLocation, 2/*(x,y)*/, GL_FLOAT, false,
			sizeof(Vertex)/*stride*/, (void*)0);
		glEnableVertexAttribArray(posLocation);

		GLint colorLocation = glGetAttribLocation(program, "a_Color");
		glVertexAttribPointer(colorLocation, 3/*(r,g,b)*/, GL_FLOAT, false,
			sizeof(Vertex)/*stride*/
			, (void*)(sizeof(float) * 2)); // facon C
			//, offsetof(Vertex, r));	// en C99/C11/C++11

		glEnableVertexAttribArray(colorLocation);

		// dessine moi un triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3 /* nb sommets*/);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Mesh.IBO);

		// Penser a reinit le VAO actuellement utilise a zero si on souhaite manipuler les BO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	void Terminate() 
	{
		glGenVertexArrays(1, &g_Mesh.VAO);
		glDeleteBuffers(1, &g_Mesh.VBO);
		glDeleteBuffers(1, &g_Mesh.IBO);


		shader.Destroy();
	}

	void Display(GLFWwindow* window)
	{
		/* Render here */
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.5f, 0.5f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);


		GLuint program = shader.GetProgram();
		glUseProgram(program);


		// Exercice 1 ----
#if 0
		// A partir de cette ligne, glVertexAttribPointer va considerer
		// que le dernier parametre est une adresse relative (offset) et plus absolue
		glBindBuffer(GL_ARRAY_BUFFER, g_Mesh.VBO);

		// on indique a OpenGL la structuration des sommets
		// stride = ecart en octets entre deux sommets
		GLint posLocation = glGetAttribLocation(program, "a_Position");
		glVertexAttribPointer(posLocation, 2/*(x,y)*/, GL_FLOAT, false,
			sizeof(Vertex)/*stride*/, (void*)0);
		glEnableVertexAttribArray(posLocation);

		GLint colorLocation = glGetAttribLocation(program, "a_Color");
		glVertexAttribPointer(colorLocation, 3/*(r,g,b)*/, GL_FLOAT, false,
			sizeof(Vertex)/*stride*/
			, (void*)(sizeof(float) * 2)); // facon C
			//, offsetof(Vertex, r));	// en C99/C11/C++11

		glEnableVertexAttribArray(colorLocation);

		// dessine moi un triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3 /* nb sommets*/);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Mesh.IBO);


		glDrawElements(GL_TRIANGLES, 3 /* nb indices*/
			, GL_UNSIGNED_SHORT, (void*)0);
#endif
		// Exercice 2 ---

		// cas general matriciel lorsque matrice "lineaire"
		/*v' = M * v

		// translation, classe de transformation "affine"
		v' = v(x,y) + t(x,y)
		v'(vx + tx, vy + ty)

		| a b | * (x
		| c d |	   y)

			v'x = a*vx + b*vy
			v'y = c*vx + d*vy

		// coordonnées homogenes
		// on passe a la dimension superieur

		| a b tx | *(x
		| c d ty | y
		| 0 0 1 | 1 )

			v'x = a*vx + b*vy + tx
			v'y = c*vx + d*vy + ty
			v'z = 1
			*/

		GLint timeLoc = glGetUniformLocation(program, "u_Time");
		float time = static_cast<float>(glfwGetTime());
		glUniform1f(timeLoc, time);

		GLint baseColorLoc = glGetUniformLocation(program, "u_BaseColor");
		glUniform3f(baseColorLoc, 0.2f, 0.5f, 0.1f);
		float baseColor[] = { 0.7f, 0.5f, 0.3f };
		glUniform3fv(baseColorLoc, 1, baseColor);

		GLint tmatLoc = glGetUniformLocation(program, "u_TranslationMatrix");
		float translationMatrix[] = {
			1.f, 0.f, 0.f, 0.f, // 1ere colonne
			0.f, 1.f, 0.f, 0.f, // 2eme colonne
			0.f, 0.f, 1.f, 0.f, // 3eme colonne
			0, 0, -10.f, 1.f // 4eme colonne
		};
		glUniformMatrix4fv(tmatLoc, 1, false, translationMatrix);

		GLint rmatLoc = glGetUniformLocation(program, "u_RotationMatrix");
		float rotationMatrix[] = {
			cos(time), 0.f, -sin(time), 0.f, // 1ere colonne
			0.f, 1.f, 0.f, 0.f, // 2eme colonne
			sin(time), 0.f, cos(time), 0.f, // 3eme colonne
			0.f, 0.f, 0.f, 1.f // 4eme colonne
		};
		glUniformMatrix4fv(rmatLoc, 1, false, rotationMatrix);

		GLint projLoc = glGetUniformLocation(program, "u_ProjectionMatrix");
		float fov = 45.f * 3.14159f / 180.f;
		float f = 1.f / tan(fov / 2.f);
		float a = (float)width / (float)height;
		float far = 1000.f;
		float near = 0.1f;
		float projectionMatrix[] = {
			f/a, 0.f, 0.f, 0.f, // 1ere colonne
			0.f, f, 0.f, 0.f, // 2eme colonne
			0.f, 0.f, (far+near)/(near-far), -1.f, // 3eme colonne
			0.f, 0.f, (2.f * far * near) / (near - far), 0.f // 4eme colonne
		};

		glUniformMatrix4fv(projLoc, 1, false, projectionMatrix);

		GLint viewLoc = glGetUniformLocation(program, "u_ViewMatrix");
		//myVector3 targetPos(-cos(time), -sin(time), -10.f);et un 
		//myVector3 targetPos(0, -sin(time), -10.f);
		myVector3 targetPos(-2,0,-10); // x and y have to be opposite values 
		float* viewMat = cam.lookAt(targetPos); //check if size of float is right if not working 
		glUniformMatrix4fv(viewLoc, 1, false, viewMat);

		glBindVertexArray(g_Mesh.VAO);
		glDrawElements(GL_TRIANGLES, g_Mesh.indicesCount /* nb indices*/
			, GL_UNSIGNED_SHORT, (void*)0);

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