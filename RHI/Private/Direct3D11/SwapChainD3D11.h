#pragma once
#include "SwapChain.h"
#include "D3D11Platform.h"

namespace Nome::RHI
{

class CSwapChainD3D11 : public CSwapChain
{
public:
    //Only for internal use
    CSwapChainD3D11(IDXGISwapChain* inSwapChain);
    ~CSwapChainD3D11();

    void Resize(int width, int height) override;

private:
    IDXGISwapChain* SwapChain;
};

} /* namespace Nome::RHI */
