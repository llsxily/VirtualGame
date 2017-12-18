#pragma once
class VidCapture
{
public:
	VidCapture();
	~VidCapture();
	int initDupl(_In_ ID3D11Device* Device);
	ID3D11Device* m_Device;
	DXGI_OUTPUT_DESC m_OutputDesc;
};

