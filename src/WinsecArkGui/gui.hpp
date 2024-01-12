#pragma once

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include <string>

#pragma comment(lib,"d3d9.lib")

#include "app.h"

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


namespace Gui
{
    extern inline LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static LPDIRECT3D9              g_pD3D = nullptr;
    static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
    static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
    static D3DPRESENT_PARAMETERS    g_d3dpp = {};

    inline WNDCLASSEXW g_Wc = {
    sizeof(g_Wc),
    CS_CLASSDC,
    WndProc,
    0L,
    0L,
    GetModuleHandle(nullptr),
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    L"Winsec Anti-Rookit GUI",
    nullptr
    };

    int g_ScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int g_ScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

    HWND g_hWnd = nullptr;

    inline LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
            g_ResizeHeight = (UINT)HIWORD(lParam);
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_DPICHANGED:
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
            {
                const RECT* suggested_rect = (RECT*)lParam;
                ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
            break;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }

    inline bool CreateDeviceD3D(HWND hWnd)
    {
        if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
            return false;

        // Create the D3DDevice
        ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
        g_d3dpp.Windowed = TRUE;
        g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
        g_d3dpp.EnableAutoDepthStencil = TRUE;
        g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
        //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
        if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
            return false;

        return true;
    }

    inline void CleanupDeviceD3D()
    {
        if (g_pd3dDevice)
        {
            g_pd3dDevice->Release();
            g_pd3dDevice = nullptr;
        }
        if (g_pD3D)
        {
            g_pD3D->Release();
            g_pD3D = nullptr;
        }
    }

    inline void ResetDevice()
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
        if (hr == D3DERR_INVALIDCALL)
            IM_ASSERT(0);
        ImGui_ImplDX9_CreateDeviceObjects();
    }

    inline void CreatehWindow()
    {
        ::RegisterClassExW(&g_Wc);

        g_hWnd = ::CreateWindowW(
            g_Wc.lpszClassName,
            L"Winsec Anti-Rookit",
            WS_OVERLAPPEDWINDOW,
            g_ScreenWidth * 0.15, g_ScreenHeight * 0.15, g_ScreenWidth * 0.7, g_ScreenHeight * 0.7,
            nullptr,
            nullptr,
            g_Wc.hInstance,
            nullptr);

        // Initialize Direct3D
        if (!CreateDeviceD3D(g_hWnd))
        {
            CleanupDeviceD3D();
            ::UnregisterClassW(g_Wc.lpszClassName, g_Wc.hInstance);
            return;
        }

        // Show the window
        ::ShowWindow(g_hWnd, SW_SHOWDEFAULT);
        ::UpdateWindow(g_hWnd);
    }

    inline void InitIMGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsLight();

        ImGuiStyle& style = ImGui::GetStyle();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX9_Init(g_pd3dDevice);


        ImFont* font = io.Fonts->AddFontFromFileTTF(
            "C:/Windows/Fonts/msyh.ttc",
            18,
            nullptr,
            io.Fonts->GetGlyphRangesChineseFull()
        );
    }

    inline void Run()
    {
        CreatehWindow();
        InitIMGui();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        // Main loop
        bool done = false;
        while (!done)
        {
            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }
            if (done)
                break;

            // Handle window resize (we don't resize directly in the WM_SIZE handler)
            if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
            {
                g_d3dpp.BackBufferWidth = g_ResizeWidth;
                g_d3dpp.BackBufferHeight = g_ResizeHeight;
                g_ResizeWidth = g_ResizeHeight = 0;
                ResetDevice();
            }

            // Start the Dear ImGui frame
            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport();


            //// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            ImGui::ShowDemoWindow();
            App::DrawUI(g_d3dpp.BackBufferWidth, g_d3dpp.BackBufferHeight);
            // Rendering

            ImGui::EndFrame();
            g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
            g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

            D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
            g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
            if (g_pd3dDevice->BeginScene() >= 0)
            {
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
                g_pd3dDevice->EndScene();
            }

            ImGuiIO& io = ImGui::GetIO(); (void)io;
            // Update and Render additional Platform Windows
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }

            HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

            // Handle loss of D3D9 device
            if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
                ResetDevice();
        }

        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        CleanupDeviceD3D();
        ::DestroyWindow(g_hWnd);
        ::UnregisterClassW(g_Wc.lpszClassName, g_Wc.hInstance);
    }
}


