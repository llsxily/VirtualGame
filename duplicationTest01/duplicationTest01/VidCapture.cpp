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
	m_Device->AddRef();//���ڸ�ֵ�����ı�������Ҫʹ��AddRef()���ӳ��ͷš�
	
	// Get DXGI device
	IDXGIDevice* DxgiDevice = nullptr;
	HRESULT hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DxgiDevice));
	
	// Get DXGI adapter
	IDXGIAdapter* DxgiAdapter = nullptr;
	hr = DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DxgiAdapter));
	DxgiDevice->Release();//�������ɵ�COM����Ѿ�������AddRef()��ֻ��Ҫ�ڽ���ʱ�ͷžͺá�
	DxgiDevice = nullptr;

	// Get output
	IDXGIOutput* DxgiOutput = nullptr;
	hr = DxgiAdapter->EnumOutputs(Output, &DxgiOutput);
	DxgiAdapter->Release();
	DxgiAdapter = nullptr;

	DxgiOutput->GetDesc(&m_OutputDesc);
	
	return 0;
}
