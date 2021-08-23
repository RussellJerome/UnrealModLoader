#include "LoaderUI.h"
#include "Utilities/Logger.h"
#include "Memory/mem.h"
#include "Utilities/Dumper.h"

LoaderUI* LoaderUI::UI;

LoaderUI* LoaderUI::GetUI()
{
	if (!UI)
	{
		UI = new LoaderUI();
	}
	return UI;
}

HRESULT LoaderUI::LoaderResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (LoaderUI::GetUI()->pRenderTargetView) {
		LoaderUI::GetUI()->pContext->OMSetRenderTargets(0, 0, 0);
		LoaderUI::GetUI()->pRenderTargetView->Release();
	}

	HRESULT hr = ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	// Perform error handling here!

	LoaderUI::GetUI()->pDevice->CreateRenderTargetView(pBuffer, NULL, &LoaderUI::GetUI()->pRenderTargetView);
	// Perform error handling here!
	pBuffer->Release();

	LoaderUI::GetUI()->pContext->OMSetRenderTargets(1, &LoaderUI::GetUI()->pRenderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	LoaderUI::GetUI()->pContext->RSSetViewports(1, &vp);
	return hr;
}

void DrawImGui()
{
	ImGui::Begin("Unreal Mod Loader", NULL, NULL);

	ImGui::Spacing();
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	if (ImGui::Button("Dump Objects"))
	{
		Dumper::CreateObjectDumpThread();
	}
	ImGui::End();

	

	/*
	ImGui::Begin("ImGui D3D11", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
	ImGui::Spacing();

	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Client size: %.0f x %.0f", LoaderUI::GetUI()->viewport.Width, LoaderUI::GetUI()->viewport.Height);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	static bool bShowDemo = false;
	ImGui::Checkbox("Show Demo Window", &bShowDemo);

	ImGui::Spacing();
	ImGui::End();

	if (bShowDemo)
	{
		ImGui::ShowDemoWindow(&bShowDemo);
	}
	*/
}

LRESULT CALLBACK LoaderUI::hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);

	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return true;
	}

	return CallWindowProc(LoaderUI::GetUI()->hGameWindowProc, hWnd, uMsg, wParam, lParam);
}

void LoaderUI::LoaderD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (LoaderUI::GetUI()->initRendering)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&LoaderUI::GetUI()->pDevice)) &&
			SUCCEEDED(pSwapChain->GetDevice(__uuidof(LoaderUI::GetUI()->pDevice), (void**)&LoaderUI::GetUI()->pDevice)))
		{
			LoaderUI::GetUI()->pDevice->GetImmediateContext(&LoaderUI::GetUI()->pContext);
			Log::Info("D3D11Device Initialized");
		}
		else
		{
			Log::Error("Failed to initialize D3D11Device");
		}

		ID3D11Texture2D* pRenderTargetTexture = NULL;
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)) &&
			SUCCEEDED(LoaderUI::GetUI()->pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &LoaderUI::GetUI()->pRenderTargetView)))
		{
			pRenderTargetTexture->Release();
			Log::Info("D3D11RenderTargetView Initialized");
		}
		else
		{
			Log::Error("Failed to initialize D3D11RenderTargetView");
		}

		UINT numViewports = 1;
		LoaderUI::GetUI()->pContext->RSGetViewports(&numViewports, &LoaderUI::GetUI()->viewport);
		LoaderUI::GetUI()->screenCenterX = LoaderUI::GetUI()->viewport.Width / 2.0f;
		LoaderUI::GetUI()->screenCenterY = LoaderUI::GetUI()->viewport.Height / 2.0f;

		Log::Info("Viewport resolution: %.0f x %.0f", LoaderUI::GetUI()->viewport.Width, LoaderUI::GetUI()->viewport.Height);

		ImGui::CreateContext();

		HWND hGameWindow = MEM::FindWindow(GetCurrentProcessId(), L"UnrealWindow");
		LoaderUI::GetUI()->hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)LoaderUI::hookWndProc);
		ImGui_ImplWin32_Init(hGameWindow);

		ImGui_ImplDX11_CreateDeviceObjects();
		ImGui_ImplDX11_Init(LoaderUI::GetUI()->pDevice, LoaderUI::GetUI()->pContext);

		LoaderUI::GetUI()->initRendering = false;
	}

	// must call before drawing
	LoaderUI::GetUI()->pContext->OMSetRenderTargets(1, &LoaderUI::GetUI()->pRenderTargetView, NULL);

	// ImGui Rendering ---------------------------------------------

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	DrawImGui();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
