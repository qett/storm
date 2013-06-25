#include <GL/glfw.h>
#include <stdlib.h>
#include <stdio.h>

/* Window dimensions. */
const int window_h = 600, window_w = 1000;

/* Application and window name. */
const char *app_name = "glfw_template";

/*
 * Window resize callback.
 */
static void GLFWCALL
resize(int width, int height)
{
	double aspect = (double)width / (double)height;

	puts("resize");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * OpenGL initialization.
 */
int
gl_init(void)
{
	resize(window_w, window_h);

	if (glGetError() != GL_NO_ERROR)
		return GL_FALSE;
	return GL_TRUE;
}

/*
 * GLFW initialization.
 */
int
glfw_init(void)
{
	if (GL_TRUE != glfwInit()) {
		exit(EXIT_FAILURE);
	}

	if (GL_TRUE != glfwOpenWindow(window_w, window_h, 8, 8, 
				      8, 8, 16, 0, GLFW_WINDOW)) {
		return GL_FALSE;
	}

	glfwSetWindowTitle(app_name);
	glfwSetWindowSizeCallback(resize);

	return GL_TRUE;
}

/*
 * Application initialization.
 */
int
app_init(void)
{
	if (GL_TRUE != glfw_init()) {
		glfwTerminate();
		return GL_FALSE;
	}
	
	if (GL_TRUE != gl_init()) {
		return GL_FALSE;
	}

	return GL_TRUE;
}

/*
 * OpenGL cleanup.
 */
void
gl_exit(void)
{
}

/*
 * GLFW cleanup.
 */
void
glfw_exit(void)
{
	glfwCloseWindow();
	glfwTerminate();
}

/*
 * Application cleanup.
 */
void
app_exit(void)
{
	gl_exit();
	glfw_exit();
}

void
draw_square(GLfloat size)
{
	glBegin(GL_QUADS);
		glVertex3f(-size, size, 0.0f);
		glVertex3f(size, size, 0.0f);
		glVertex3f(size, -size, 0.0f);
		glVertex3f(-size, -size, 0.0f);
	glEnd();
}

/*
 * OpenGL display function.
 */
void
display(void)
{
	static GLfloat z_rot = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();


	glRotatef(z_rot, 0, 0, 1);
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	draw_square(1.0f);
	glPopMatrix();

	z_rot += 0.02;
}

/*
 * Application main loop (keyboard events, display, ..., etc.).
 */
void
app_loop(void)
{
	while (!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)) {
		display();
		glfwSwapBuffers();
	}
}

/*
 * Application entry point.
 */
int
main(int argc, char *argv[])
{
	if (GL_TRUE != app_init())
		exit(EXIT_FAILURE);

	app_loop();
	app_exit();
	return 0;
}
