#include <iostream>
#include <dxgi.h>
#include <wrl.h>
#include <tchar.h>
#include <string>

#pragma comment(lib,"dxgi.lib")

using namespace std;
//using namespace Microsoft;



int main(void)
{
	Microsoft::WRL::ComPtr<IDXGIFactory> Factory;
	Microsoft::WRL::ComPtr<IDXGIAdapter> Adapter;

	HRESULT hr = CreateDXGIFactory(
		IID_PPV_ARGS(&Factory));
	

	if (FAILED(hr))
		cout << "DXGIFactory 생성에 실패했습니다."
		<< endl;
	else
	{
		for (int i = 0 ; 
			Factory->EnumAdapters(i, &Adapter) != DXGI_ERROR_NOT_FOUND ;
			++i)
		{
			DXGI_ADAPTER_DESC Desc;
			Adapter->GetDesc(&Desc);


			_tprintf(_T("[%ls] %lu Byte\n"), 
				Desc.Description,
				Desc.DedicatedVideoMemory);

			//cout << "[ " << Desc.Description << " ]"\
				<< Desc.DedicatedVideoMemory << endl;
		}
	}

	return 0;
}