#include"Platform/Renderer/DX12/DX12Exception.h"
#include<comdef.h>

namespace VIEngine {
    DX12Exception::DX12Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber) :
        ErrorCode(hr),
        FunctionName(functionName),
        Filename(filename),
        LineNumber(lineNumber)
    {

    }

    std::wstring DX12Exception::ToString() const
    {
        _com_error err(ErrorCode);
        std::wstring msg = err.ErrorMessage();
        return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
    }
}