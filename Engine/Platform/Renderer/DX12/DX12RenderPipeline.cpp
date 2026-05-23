#include"Platform/Renderer/DX12/DX12RenderPipeline.h"
#include"Platform/Renderer/DX12/DX12RendererContext.h"
#include"Platform/Renderer/DX12/DX12Shader.h"
#include"Platform/Renderer/DX12/DX12InputAssembler.h"
#include"Platform/Renderer/DX12/DX12RenderPipelineLayout.h"
#include"Core/Application.h"

namespace VIEngine {
    DEFINE_RTTI(DX12RenderPipeline, RenderPipeline::RunTimeType)

    RenderPipeline* RenderPipeline::Create(const RenderPipelineAttribute& attribute) {
        return new DX12RenderPipeline(Application::Get().GetRenderer()->GetContext(), attribute);
    }

    DX12RenderPipeline::DX12RenderPipeline(RendererContext* rendererContext, const RenderPipelineAttribute& attribute)
        : RenderPipeline(attribute), mPipelineState()
    {
        mRendererContext = static_cast<DX12RendererContext*>(rendererContext);
        
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
        pipelineDesc.VS.pShaderBytecode = mAttribute.pShader->GetShaderByteCode(EShaderStageFlag::VERTEX);
        pipelineDesc.VS.BytecodeLength = mAttribute.pShader->GetShaderByteCodeSize(EShaderStageFlag::VERTEX);
        pipelineDesc.PS.pShaderBytecode = mAttribute.pShader->GetShaderByteCode(EShaderStageFlag::PIXEL);
        pipelineDesc.PS.BytecodeLength = mAttribute.pShader->GetShaderByteCodeSize(EShaderStageFlag::PIXEL);
        pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // サンプルマスクを指定。0xffffffffならすべてのサンプルが有効
        // TODO: ラスタライザーステートクラス作成
        pipelineDesc.RasterizerState.MultisampleEnable = false; // マルチサンプリングを有効にするかどうか。今回はマルチサンプリングを使用しないのでfalseを指定
        pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // カリングモードを指定。今回は三角形の表も裏も両方表示したいのでD3D12_CULL_MODE_NONEを指定
        pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // 塗りつぶしモードを指定。D3D12_FILL_MODE_WIREFRAMEならワイヤーフレーム表示になるが、今回は通常の塗りつぶし表示にしたいのでD3D12_FILL_MODE_SOLIDを指定
        pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効にするかどうか。これをtrueにしておくと、深度が0以下のピクセルがクリップされる。今回は有効にしておく
        // TODO: ブレンドステートクラス作成
        pipelineDesc.BlendState.AlphaToCoverageEnable = false; // アルファトゥカバレッジを有効にするかどうか。マルチサンプリングのみで意味がある機能なので、今回はマルチサンプリングを使用しないためfalseを指定
        pipelineDesc.BlendState.IndependentBlendEnable = false; // 独立ブレンドを有効にするかどうか。複数のレンダーターゲットを使用する場合に、レンダーターゲットごとに異なるブレンド設定を使用できるようになるが、今回はレンダーターゲットは1つだけなのでfalseを指定
        // TODO: レンダリングターゲットクラス作成
        D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc = {};
        defaultRenderTargetBlendDesc.BlendEnable = false; // ブレンドを有効にするかどうか。今回はブレンドを使用しないのでfalseを指定
        defaultRenderTargetBlendDesc.LogicOpEnable = false; // ロジックオペレーションを有効にするかどうか。今回はロジックオペレーションを使用しないのでfalseを指定
        defaultRenderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // レンダーターゲットの書き込みマスクを指定。今回はすべてのチャンネルを書き込み可能にするのでD3D12_COLOR_WRITE_ENABLE_ALLを指定

        pipelineDesc.BlendState.RenderTarget[0] = defaultRenderTargetBlendDesc;

        DX12InputAssembler* inputAssembler = static_cast<DX12InputAssembler*>(mAttribute.pInputAssembler);
        pipelineDesc.InputLayout.pInputElementDescs = inputAssembler->GetElementDesc().data();
        pipelineDesc.InputLayout.NumElements = inputAssembler->GetElementDesc().size();
        pipelineDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED; 
        pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        pipelineDesc.NumRenderTargets = 1;
        pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        pipelineDesc.SampleDesc.Count = 1;
        pipelineDesc.SampleDesc.Quality = 0;

        DX12RenderPipelineLayout* pipelineLayout = static_cast<DX12RenderPipelineLayout*>(mAttribute.pPipelineLayout);
        pipelineDesc.pRootSignature = pipelineLayout->GetRootSignature();

        DX12CheckException(mRendererContext->GetDevice()->CreateGraphicsPipelineState(
            &pipelineDesc,
            IID_PPV_ARGS(&mPipelineState)
        ));
    }

    DX12RenderPipeline::~DX12RenderPipeline() {

    }
}