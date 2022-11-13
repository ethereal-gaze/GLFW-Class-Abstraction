//
// Created by Benjamin Gosling on 08/11/2022.
//

#include <ApplicationSettings.h>
#include <Window.h>
#include <iostream>

// Static member initialisation
int Window::_windowCount = 0;
bool Window::_isGlfwLoaded = false;

Window::Window(int width, int height, const char *title) : _nativeWindow(nullptr), _width(width), _height(height),
                                                           _title(title), _open(false), _eventQueue()
{
	Open();
	SetCurrentContext();
}

Window::Event::Event() : type(None)
{}

void Window::Open()
{
	if (_open)
		return;

	_loadGlfw();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_nativeWindow = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);

	// Give GLFW the pointer to this class. Now callbacks can access it
	glfwSetWindowUserPointer(_nativeWindow, this);

	// Set callbacks
	glfwSetFramebufferSizeCallback(_nativeWindow, _resizeCallback);
	glfwSetWindowCloseCallback(_nativeWindow, _closeCallback);
	glfwSetCursorPosCallback(_nativeWindow, _cursorPositionCallback);
	glfwSetKeyCallback(_nativeWindow, _keyCallback);

	if (_nativeWindow == nullptr)
		throw std::runtime_error("Failed to create GLFW window");

	Show();

	_windowCount++;
	_open = true;
}

Window::~Window()
{
	glfwDestroyWindow(_nativeWindow);
	_windowCount--;

	if (_windowCount <= 0)
		_unloadGlfw();
}

bool Window::isOpen() const
{ return _open; }

bool Window::IsActive()
{ return _isGlfwLoaded; }

void Window::Close()
{
	if (!_open) return;
	glfwDestroyWindow(_nativeWindow);
	_open = false;
}

void Window::Show()
{ glfwShowWindow(_nativeWindow); }

void Window::SetCurrentContext()
{ glfwMakeContextCurrent(_nativeWindow); }

void Window::Poll()
{ glfwPollEvents(); }

void Window::Display()
{ glfwSwapBuffers(_nativeWindow); }

bool Window::ProcessEvents(Window::Event &event_buffer)
{
	if (!_eventQueue.empty()) {
		event_buffer = _eventQueue[_eventQueue.size() - 1];
		_eventQueue.pop_back();
		return true;
	} else
		return false;
}

void Window::_unloadGlfw()
{
	std::cout << "Unloading GLFW" << std::endl;
	if (!_isGlfwLoaded)
		return;

	glfwTerminate();
	_isGlfwLoaded = false;
}

void Window::_loadGlfw()
{
	std::cout << "Loading GLFW" << std::endl;
	if (_isGlfwLoaded)
		return;

	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialise GLFW");
	}
	_isGlfwLoaded = true;
}

void Window::_closeCallback(GLFWwindow *window)
{
	auto *window_instance = static_cast<Window *>(glfwGetWindowUserPointer(window));

	Event event;
	event.type = EventType::CloseCall;
	window_instance->_queueEvent(event);
}

void Window::_resizeCallback(GLFWwindow *window, int width, int height)
{
	auto *window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	Event event;
	event.type = EventType::Resized;
	window_instance->_width = width;
	window_instance->_height = height;
	window_instance->_queueEvent(event);
}

void Window::_queueEvent(Window::Event event) { _eventQueue.push_back(event); }
int Window::GetSizeY() const  { return _width; }
int Window::GetSizeX() const  { return _height; }

void Window::_cursorPositionCallback(GLFWwindow *window, double x, double y)
{
	auto *window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	Event event;
	event.type = EventType::CursorPosition;

	window_instance->_queueEvent(event);
}

void Window::_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	auto *window_instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	Event event;

	switch (action)
	{
		case GLFW_PRESS:
			event.type = EventType::KeyPress;
			break;
		case GLFW_RELEASE:
			event.type = EventType::KeyRelease;
		default:
			GLFW_PRESS;
	}

	event.key = (KeyType) key;
	window_instance->_queueEvent(event);
}

bool Window::IsKeyDown(KeyType key) const
{
	return glfwGetKey(_nativeWindow, (int) key) == GLFW_PRESS;
}

float Window::GetTime()
{
	return glfwGetTime();
}
