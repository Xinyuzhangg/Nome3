#pragma once
#include "BufferVk.h"
#include "CopyContext.h"
#include "ImageVk.h"
#include "RenderContext.h"
#include "VkCommon.h"
#include <memory>
#include <mutex>
#include <vector>

namespace RHI
{

// A general command buffer recorder
class CCommandContextVk : public std::enable_shared_from_this<CCommandContextVk>,
                          public IRenderContext
{
public:
    typedef std::shared_ptr<CCommandContextVk> Ref;

    CCommandContextVk(CDeviceVk& p, uint32_t qfi, bool deferredContext = false);
    virtual ~CCommandContextVk();

    void BeginBuffer();
    void EndBuffer();

    // For internal use only
    VkCommandBuffer GetBuffer() const { return CmdBuffer; }

    void TransitionImage(CImage* image, EResourceState newState);

    // Copy commands
    void CopyBuffer(CBuffer* src, CBuffer* dst, const std::vector<CBufferCopy>& regions) override;
    void CopyImage(CImage* src, CImage* dst, const std::vector<CImageCopy>& regions) override;
    void CopyBufferToImage(CBuffer* src, CImage* dst,
                           const std::vector<CBufferImageCopy>& regions) override;
    void CopyImageToBuffer(CImage* src, CBuffer* dst,
                           const std::vector<CBufferImageCopy>& regions) override;
    void BlitImage(CImage* src, CImage* dst, const std::vector<CImageBlit>& regions,
                   EFilter filter) override;
    void ResolveImage(CImage* src, CImage* dst, const std::vector<CImageResolve>& regions) override;

    void ExecuteCommandList(CCommandList* commandList) override;
    CCommandList::Ref FinishCommandList() override;
    void Flush(bool wait = false) override;

    // Render commands
    void BeginRenderPass(CRenderPass::Ref renderPass, CFramebuffer::Ref framebuffer,
                         const std::vector<CClearValue>& clearValues) override;
    void NextSubpass() override;
    void EndRenderPass() override;
    void BindPipeline(CPipeline* pipeline) override;
    void BindBuffer(CBuffer* buffer, size_t offset, size_t range, uint32_t set, uint32_t binding,
                    uint32_t index) override;
    void BindBufferView(CBufferView* bufferView, uint32_t set, uint32_t binding,
                        uint32_t index) override;
    void BindImageView(CImageView* imageView, uint32_t set, uint32_t binding,
                       uint32_t index) override;
    void BindSampler(CSampler* sampler, uint32_t set, uint32_t binding, uint32_t index) override;
    void BindIndexBuffer(CBuffer* buffer, size_t offset, EFormat format) override;
    void BindVertexBuffer(uint32_t binding, CBuffer* buffer, size_t offset) override;
    void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
              uint32_t firstInstance) override;
    void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
                     int32_t vertexOffset, uint32_t firstInstance) override;

    // Called by the device when a batch is done
    void DoneWithCmdBuffer(VkCommandBuffer b);

protected:
    static void Convert(VkOffset3D& dst, const COffset3D& src);
    static void Convert(VkExtent3D& dst, const CExtent3D& src);
    static void Convert(VkImageSubresourceLayers& dst, const CImageSubresourceLayers& src);
    static void Convert(VkImageCopy& dst, const CImageCopy& src);
    static void Convert(VkImageResolve& dst, const CImageResolve& src);
    static void Convert(VkBufferImageCopy& dst, const CBufferImageCopy& src);
    static void Convert(VkImageBlit& dst, const CImageBlit& src);

protected:
    CDeviceVk& Parent;
    bool bIsDeferred;
    uint32_t QueueType;
    VkCommandPool CmdPool;
    VkCommandBuffer CmdBuffer = VK_NULL_HANDLE;

    std::mutex GarbageMutex;
    std::vector<VkCommandBuffer> GarbageBuffers;

    // Render states kept track of
    VkRect2D RenderArea;
};

} /* namespace RHI */
