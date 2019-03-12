#include "Gui.h"

#include "Common/Common.h"
#include "Emulator.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_memory_editor.h>
#include <stdio.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
	throw std::runtime_error("Glfw Error " + std::to_string(error) + " : " + description);
}

Gui::Gui(Emulator& emu_, std::string additional_title, int width, int height) :
	emu(emu_),
	ctrl_window(emu_, scroll_to_pc, track_pc),
	mem_nav_window(emu_),
	reg_window(emu_),
	fun_window(emu_),
	dis_window(emu_, scroll_to_pc, track_pc),
	mem_window()
{
	window_width = width;
	window_height = height;

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw std::runtime_error("Error in glfwInit");

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	window = glfwCreateWindow(window_width, window_height, "Nomu - ", NULL, NULL);
	if (window == NULL)
		throw std::runtime_error("Window created was null");

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	//center windows
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window, (mode->width - window_width) / 2, (mode->height - window_height) / 2);

	if (gl3wInit()) {
		throw std::runtime_error("Error in gl3wInit");
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	//io.IniFilename = nullptr;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

bool Gui::render() {
	if (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//ImGui::ShowDemoWindow(&show_demo_window);
		ctrl_window.render();
		mem_nav_window.render();
		reg_window.render();
		fun_window.render();
		dis_window.render();
		mem_window.DrawWindow("Memory", emu.mem->getDisplayMem().data(), emu.mem->getDisplayMem().size(), emu.mem->getDisplayMemBaseAddress());

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);

		return true;
	}
	else
	{
		return false;
	}
}


Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
