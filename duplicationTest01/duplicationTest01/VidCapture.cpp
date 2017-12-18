#include "stdafx.h"
#include "VidCapture.h"
#include <dxgi1_2.h>
#include <d3d11.h>


VidCapture::VidCapture()
{
	RtlZeroMemory(&m_OutputDesc, sizeof(m_OutputDesc));
}


VidCapture::~VidCapture()
{
	if (m_Device)
	{
		m_Device->Release();
		m_Device = nullptr;
	}
}


int VidCapture::initDupl(_In_ ID3D11Device* Device)
{
	// Take a reference on the device
	m_Device = Device;
	m_Device->AddRef();//对于赋值而来的变量，需要使用AddRef()来延迟释放。
	
	// Get DXGI device
	IDXGIDevice* DxgiDevice = nullptr;
	HRESULT hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DxgiDevice));
	
	// Get DXGI adapter
	IDXGIAdapter* DxgiAdapter = nullptr;
	hr = DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DxgiAdapter));
	DxgiDevice->Release();//对于生成的COM组件已经调用了AddRef()，只需要在结束时释放就好。
	DxgiDevice = nullptr;

	// Get output
	IDXGIOutput* DxgiOutput = nullptr;
	hr = DxgiAdapter->EnumOutputs(Output, &DxgiOutput);
	DxgiAdapter->Release();
	DxgiAdapter = nullptr;

	DxgiOutput->GetDesc(&m_OutputDesc);
	
	return 0;
}
