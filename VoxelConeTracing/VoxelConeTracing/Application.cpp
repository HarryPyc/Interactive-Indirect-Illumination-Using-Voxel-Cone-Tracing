#include "Application.h"
void display();
void idle();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void special_up(int key, int x, int y);
void passive(int x, int y);
void special(int key, int x, int y);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);

void Application::init(int argc, char** argv) {
#if _DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitContextVersion(4, 3);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	window = glutCreateWindow(title);

	graphics = new Graphics();
	controller = new FPSController(graphics->scene->cam, WINDOW_WIDTH, WINDOW_HEIGHT);

	//init OpenGL
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialUpFunc(special_up);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
}

void Application::run() {
	glutMainLoop();
	glutDestroyWindow(window);
}

Application& Application::getInstance() {
	static Application app;
	return app;
}

void display() {
	auto& app = Application::getInstance();
	app.controller->update();
	app.graphics->render();
}

void idle() {
	glutPostRedisplay();
	const int time_ms = glutGet(GLUT_ELAPSED_TIME);
	Timer::time = 0.001f * time_ms;
}
void keyboard(unsigned char key, int x, int y) {
	auto& app = Application::getInstance();
	app.controller->keyboard(key, x, y);
}
void keyboard_up(unsigned char key, int x, int y) {
	auto& app = Application::getInstance();
	app.controller->keyboard_up(key, x, y);
}
void special_up(int key, int x, int y) {
	auto& app = Application::getInstance();
	app.controller->special_up(key, x, y);
}
void passive(int x, int y) {
	auto& app = Application::getInstance();
	app.controller->passive(x, y);
}
void special(int key, int x, int y) {
	auto& app = Application::getInstance();
	app.controller->special(key, x, y);
}
void motion(int x, int y) {
	auto& app = Application::getInstance();
	app.controller->motion(x, y);
}
void mouse(int button, int state, int x, int y) {
	auto& app = Application::getInstance();
	app.controller->mouse(button, state, x, y);
}
void reshape(int w, int h) {
	auto& app = Application::getInstance();
	app.graphics->w = w;
	app.graphics->h = h;
}