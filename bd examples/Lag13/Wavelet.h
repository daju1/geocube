// Wavelet.h: interface for the CWavelet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVELET_H__D3D57D1D_5EB5_41A8_B696_B27F9E83B74B__INCLUDED_)
#define AFX_WAVELET_H__D3D57D1D_5EB5_41A8_B696_B27F9E83B74B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct Wavelets
{
	CString name;
	short minOrder;
	short maxOrder;
};

class CWavelet  
{
public:
	CWavelet();
	virtual ~CWavelet();

};

#endif // !defined(AFX_WAVELET_H__D3D57D1D_5EB5_41A8_B696_B27F9E83B74B__INCLUDED_)
