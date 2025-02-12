#include "Input.h"

#include "Walnut/Application.h"

#include <GLFW/glfw3.h>

namespace Walnut {

	std::unordered_map<int, std::function<void()>> Input::s_KeyCallbackMap;

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			auto funcIter = Input::s_KeyCallbackMap.find(key);
			if (funcIter != Input::s_KeyCallbackMap.end())
			{
				funcIter->second();
			}
		}
	}

	void Input::InitKeysCallBack()
	{
		GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
		glfwSetKeyCallback(windowHandle, KeyCallback);
	}

	void Input::SetKeyCallback(KeyCode keycode, std::function<void()> func)
	{
		s_KeyCallbackMap[(int)keycode] = func;
	}

	bool Input::IsKeyDown(KeyCode keycode)
	{
		GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
		int state = glfwGetKey(windowHandle, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(MouseButton button)
	{
		GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
		int state = glfwGetMouseButton(windowHandle, (int)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* windowHandle = Application::Get().GetWindowHandle();

		double x, y;
		glfwGetCursorPos(windowHandle, &x, &y);
		return { (float)x, (float)y };
	}

	void Input::SetCursorMode(CursorMode mode)
	{
		GLFWwindow* windowHandle = Application::Get().GetWindowHandle();
		glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
	}

}