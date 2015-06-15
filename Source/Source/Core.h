#ifndef CHALLENGE_CORE_H
#define CHALLENGE_CORE_H

struct GLFWwindow;

namespace Challenge {
namespace Core
{

	void init();
	void run();
	void exit();

	GLFWwindow* getWindow();

} // !namespace Core
} // !namespace Challenge
#endif // !#define CHALLENGE_CORE_H

