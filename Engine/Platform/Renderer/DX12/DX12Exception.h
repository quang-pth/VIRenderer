#pragma once

#include"Core/pch.h"
#include<d3dx12.h>

namespace VIEngine {
    class DX12Exception {
    public:
        DX12Exception() = default;
        DX12Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

        std::wstring ToString()const;

        HRESULT ErrorCode = S_OK;
        std::wstring FunctionName;
        std::wstring Filename;
        int LineNumber = -1;
    };
}