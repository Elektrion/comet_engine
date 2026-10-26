module;

#include "comet_std_include.hpp"

#include "GLFW/glfw3.h"


export module comet.window;


import comet.application;


namespace comet::window
{
	
	export class WindowAPIManagerComponent
	{
	public:
		constexpr void onAttach(comet::application::Application&) noexcept
		{
			glfwInit();
			glfwSetErrorCallback([](int error_code, char const* description) {
				std::println("GLFW error {}: {}", error_code, description);
			});
		}
		
		constexpr void onDetach(comet::application::Application&) noexcept
		{
			glfwTerminate();
		}
		
		constexpr void onUpdate(comet::application::Application&) noexcept
		{
			glfwPollEvents();
		}
	};
	
	
	export class WindowComponent
	{
	private:
		GLFWwindow* window = nullptr;
		
	public:
		constexpr void onAttach(comet::application::Application&) noexcept
		{
			window = glfwCreateWindow(800, 600, "Comet Engine", NULL, NULL);
			glfwMakeContextCurrent(window);
		}
		
		constexpr void onDetach(comet::application::Application&) noexcept
		{
			glfwDestroyWindow(window);
			window = nullptr;
		}
		
		constexpr void onUpdate(comet::application::Application& app) noexcept
		{
			// glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			
			if(glfwWindowShouldClose(window))
				app.stop();
		}
	};
	
}
