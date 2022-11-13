//
// Created by Benjamin Gosling on 08/11/2022.
//

#ifndef KRYSTAL_WINDOW_H
#define KRYSTAL_WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>

// Represents a Window on the user screen. Backend is platform dependant.
class Window
{
public:
	// Type of event
	enum EventType
	{
		None,
		CloseCall,
		Resized,
		CursorPosition,
		KeyPress,
		KeyRelease
	};

	enum KeyType
	{
		Unknown = GLFW_KEY_UNKNOWN,
		Space = GLFW_KEY_SPACE,
	    Apostrophe = GLFW_KEY_APOSTROPHE,
		Comma = GLFW_KEY_COMMA,
		Minus = GLFW_KEY_MINUS,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,
		Zero = GLFW_KEY_0,
		One = GLFW_KEY_1,
		Two = GLFW_KEY_2,
		Three = GLFW_KEY_3,
		Four = GLFW_KEY_4,
		Five = GLFW_KEY_5,
		Six = GLFW_KEY_6,
		Seven = GLFW_KEY_7,
		Eight = GLFW_KEY_8,
		Nine = GLFW_KEY_9,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		Semicolon = GLFW_KEY_SEMICOLON,
		Equals = GLFW_KEY_EQUAL,
		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		RightBracket = GLFW_KEY_RIGHT_BRACKET,
		Escape = GLFW_KEY_ESCAPE,
		Enter = GLFW_KEY_ENTER,
	    Tab = GLFW_KEY_TAB,
	    Backspace = GLFW_KEY_BACKSPACE,
		Insert = GLFW_KEY_INSERT,
	    Delete = GLFW_KEY_DELETE,
		Right = GLFW_KEY_RIGHT,
	    Left = GLFW_KEY_LEFT,
	    Down = GLFW_KEY_DOWN,
		Up = GLFW_KEY_UP,
		PageUp = GLFW_KEY_PAGE_UP,
	    PageDown = GLFW_KEY_PAGE_DOWN,
	    Home = GLFW_KEY_HOME,
	    End = GLFW_KEY_END,
	    CapsLock = GLFW_KEY_CAPS_LOCK,
		ScrollLock = GLFW_KEY_SCROLL_LOCK,
	    NumLock = GLFW_KEY_NUM_LOCK,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		Pause = GLFW_KEY_PAUSE,
		F1 = GLFW_KEY_F1,
	    F2 = GLFW_KEY_F2,
		F3 =  GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
	    KeypadZero = GLFW_KEY_KP_0,
		KeypadOne = GLFW_KEY_KP_1,
		KeypadTwo = GLFW_KEY_KP_2,
		KeypadThree = GLFW_KEY_KP_3,
		KeypadFour = GLFW_KEY_KP_4,
		KeypadFive = GLFW_KEY_KP_5,
		KeypadSix = GLFW_KEY_KP_6,
		KeypadSeven = GLFW_KEY_KP_7,
		KeypadEight = GLFW_KEY_KP_8,
		KeypadNine = GLFW_KEY_KP_9,
	    KeypadDecimal = GLFW_KEY_KP_DECIMAL,
	    KeypadDivide = GLFW_KEY_KP_DIVIDE,
	    KeypadMultiply = GLFW_KEY_KP_MULTIPLY,
	    KeypadSubtract = GLFW_KEY_KP_SUBTRACT,
	    KeypadAdd = GLFW_KEY_KP_ADD,
	    KeypadEnter = GLFW_KEY_KP_ENTER,
	    KeypadEqual = GLFW_KEY_KP_EQUAL,
	    LeftShift = GLFW_KEY_LEFT_SHIFT,
	    LeftControl = GLFW_KEY_LEFT_CONTROL,
	    LeftAlt = GLFW_KEY_LEFT_ALT,
	    LeftSuper = GLFW_KEY_LEFT_SUPER,
	    RightShift = GLFW_KEY_RIGHT_SHIFT,
	    RightControl = GLFW_KEY_RIGHT_CONTROL,
	    RightAlt = GLFW_KEY_RIGHT_ALT,
	    RightSuper = GLFW_KEY_RIGHT_SUPER,
	    Menu = GLFW_KEY_MENU,
	    Last = GLFW_KEY_LAST,
	};

	// An event and any data relevant to it.
	class Event
	{
	public:
		Event();
		EventType type;
		KeyType key;
	};

public:
	Window(int width, int height, const char *title);
	~Window();
	Window(Window &) = delete;
	Window &operator=(const Window &) = delete;
	// Returns whether this window is open or not.
	bool isOpen() const;
	// Shows the window.
	void Show();
	// Closes this window.
	void Close();
	// Opens this window.
	void Open();
	// Pops the event at the end of the event queue into the event buffer (first in, last out). Returns if there is an event to process.
	bool ProcessEvents(Window::Event &event_buffer);
	// Make this window the current OpenGL context.
	void SetCurrentContext();
	// Swaps the back and front buffers.
	void Display();
	// Get X size of window
	int GetSizeX() const;
	// Get Y size of window
	int GetSizeY() const;
	// Gets if the key is down
	bool IsKeyDown(KeyType key) const;
	// Get Time
	static float GetTime();

private:
	GLFWwindow *_nativeWindow;
	int _width;
	int _height;
	const char *_title;
	bool _open;
	std::vector<Window::Event> _eventQueue;

	void _queueEvent(Window::Event event);

// Static
public:
	static void Poll();
	static bool IsActive();

private:
	static int _windowCount;
	static bool _isGlfwLoaded;
	static void _loadGlfw();
	static void _unloadGlfw();
	
	static void _closeCallback(GLFWwindow *window);
	static void _resizeCallback(GLFWwindow* window, int width, int height);
	static void _cursorPositionCallback(GLFWwindow* window, double x, double y);
	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	float _previousTime;
};


#endif //KRYSTAL_WINDOW_H
