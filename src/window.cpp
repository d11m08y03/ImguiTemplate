#include "window.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>

Window::Window() {
    initSDL();
}

void Window::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error: " << SDL_GetError() << '\n';
        exit(1);
    }

    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    this->window = SDL_CreateWindow(
        "Dear ImGui SDL2+SDL_Renderer example", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        1280, 720, 
        window_flags
    );
    if (this->window == nullptr) {
        SDL_Log("Error creating SDL_Window!");
    }

    this->renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
    if (this->renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
    }
}

void Window::initImgui(ImGuiIO& io) {
    (void) io;

    // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);
    ImGui_ImplSDLRenderer2_Init(this->renderer);
}

void Window::run(ImGuiIO& io) {
    bool done = false;
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;

            if (
                event.type == SDL_WINDOWEVENT 
                && event.window.event == SDL_WINDOWEVENT_CLOSE
                && event.window.windowID == SDL_GetWindowID(window)
            ) done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); 

            ImGui::Text("This is some useful text."); 

            ImGui::Checkbox("Demo Window", &show_demo_window); 

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); 
            ImGui::ColorEdit3("clear color", (float*) &clear_color); 

            if (ImGui::Button("Button")) counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text(
                "Application average %.3f ms/frame (%.1f FPS)",
                1000.0f /io.Framerate,io.Framerate
            );
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        SDL_RenderSetScale(
            renderer, 
            io.DisplayFramebufferScale.x,
            io.DisplayFramebufferScale.y
        );

        SDL_RenderClear(this->renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(this->renderer);
    }
}

Window::~Window() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
