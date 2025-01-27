#pragma once

#include <Main.h>
#include <d3d11_4.h>
#include <Direct3D11Inject.h>
#include "gw2al_api.h"

namespace GW2Radial
{

class Direct3D11Loader : public Direct3D11Inject
{
public:
	Direct3D11Loader() = default;

	void PrePresentSwapChain();
	void PostCreateSwapChain(HWND hwnd, ID3D11Device* dev, IDXGISwapChain* swc);
	void PreResizeSwapChain();
	void PostResizeSwapChain(uint w, uint h);

	void Init(gw2al_core_vtable* gAPI);
};

inline Direct3D11Loader* GetD3D11Loader() { return static_cast<Direct3D11Loader*>(&Direct3D11Inject::i()); }

}
