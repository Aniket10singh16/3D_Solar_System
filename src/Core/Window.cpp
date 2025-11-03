#include <Core/Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int w, int h, const std::string& title)

	: width_(w), height_(h), title_(title) {}

Window::~Window()
{
	// Ensure GLFW window and context are properly released
	//glfwDestroyWindow(handle_);
	//glfwTerminate();
}

bool Window::Initialize()
{
	// Initialize GLFW library
	if (!glfwInit())
	{
		std::cerr << "[Window] failed to initialize GLFW\n";
		return false;
	}

	// Request Open GL 4.6 Core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	handle_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
	if (!handle_)
	{
		std::cerr << "[Window] failed to create GLFW window\n";
		glfwTerminate();
		return false;
	}

	// Make the OpenGL context for this window the current context on this thread
	// All subsequent OpenGL calls (and gladLoadGLLoader) will apply to this context.
	// Without this line, GLAD cannot load function pointers → OpenGL calls will crash.
	glfwMakeContextCurrent(handle_);

	// GLAD must be loaded HERE
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}

	std::cout << "[Window] Initialized successfullly ("
		<< width_ << "x" << height_ << ')\n';

	return true;
}

void Window::PollEvents() const
{
	// Polls for keyboard, mouse, and window events
	glfwPollEvents();
}

void Window::SwapBuffers() const
{
	// Swaps front and back buffer to present rendered frame
	glfwSwapBuffers(handle_);
}

bool Window::ShouldClose() const
{
	// Query if user has requested to close the window
	return glfwWindowShouldClose(handle_);
}

glm::ivec2 Window::GetSize() const
{
	return { width_, height_ };
}

void Window::SetTitle(const std::string& newTitle)
{
	title_ = newTitle;
	glfwSetWindowTitle(handle_, title_.c_str());
}