/*
* Viry3D
* Copyright 2014-2019 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "D3D11Driver.h"
#include "D3D11DriverFactory.h"
#include "CommandStreamDispatcher.h"
#include "D3D11Context.h"
#include "D3D11Handles.h"
#include <utils/unwindows.h>

namespace filament
{
	namespace backend
	{
		Driver* D3D11DriverFactory::create(backend::D3D11Platform* platform)
		{
			return D3D11Driver::create(platform);
		}

		Driver* D3D11Driver::create(backend::D3D11Platform* platform)
		{
			assert(platform);
			return new D3D11Driver(platform);
		}

		D3D11Driver::D3D11Driver(backend::D3D11Platform* platform) noexcept:
			DriverBase(new ConcreteDispatcher<D3D11Driver>()),
			m_platform(*platform),
			m_context(new D3D11Context())
		{
		
		}

		D3D11Driver::~D3D11Driver() noexcept
		{
			delete m_context;
		}

		ShaderModel D3D11Driver::getShaderModel() const noexcept
		{
			return ShaderModel::GL_CORE_41;
		}

		void D3D11Driver::setPresentationTime(int64_t monotonic_clock_ns)
		{

		}

		void D3D11Driver::beginFrame(int64_t monotonic_clock_ns, uint32_t frame_id)
		{
			
		}

		void D3D11Driver::endFrame(uint32_t frame_id)
		{
			
		}

		void D3D11Driver::flush(int dummy)
		{

		}

		void D3D11Driver::createVertexBufferR(
			Handle<HwVertexBuffer> vbh,
			uint8_t bufferCount,
			uint8_t attributeCount,
			uint32_t vertexCount,
			AttributeArray attributes,
			BufferUsage usage)
		{
			
		}

		void D3D11Driver::createIndexBufferR(
			Handle<HwIndexBuffer> ibh,
			ElementType elementType,
			uint32_t indexCount,
			BufferUsage usage)
		{

		}

		void D3D11Driver::createTextureR(
			Handle<HwTexture> th,
			SamplerType target,
			uint8_t levels,
			TextureFormat format,
			uint8_t samples,
			uint32_t width,
			uint32_t height,
			uint32_t depth,
			TextureUsage usage)
		{

		}

		void D3D11Driver::createSamplerGroupR(Handle<HwSamplerGroup> sbh, size_t size)
		{

		}

		void D3D11Driver::createUniformBufferR(Handle<HwUniformBuffer> ubh, size_t size, BufferUsage usage)
		{

		}

		void D3D11Driver::createRenderPrimitiveR(Handle<HwRenderPrimitive> rph, int dummy)
		{

		}

		void D3D11Driver::createProgramR(Handle<HwProgram> rph, Program&& program)
		{

		}

		void D3D11Driver::createDefaultRenderTargetR(Handle<HwRenderTarget> rth, int dummy)
		{
			construct_handle<D3D11RenderTarget>(m_handle_map, rth, m_context);
		}

		void D3D11Driver::createRenderTargetR(
			Handle<HwRenderTarget> rth,
			TargetBufferFlags targetBufferFlags,
			uint32_t width,
			uint32_t height,
			uint8_t samples,
			TargetBufferInfo color,
			TargetBufferInfo depth,
			TargetBufferInfo stencil)
		{

		}

		void D3D11Driver::createFenceR(Handle<HwFence> fh, int dummy)
		{

		}

		void D3D11Driver::createSwapChainR(Handle<HwSwapChain> sch, void* native_window, uint64_t flags)
		{
			construct_handle<D3D11SwapChain>(m_handle_map, sch, m_context, native_window);
		}

		void D3D11Driver::createStreamFromTextureIdR(
			Handle<HwStream> stream,
			intptr_t externalTextureId,
			uint32_t width,
			uint32_t height)
		{

		}

		Handle<HwVertexBuffer> D3D11Driver::createVertexBufferS() noexcept
		{
			return Handle<HwVertexBuffer>();
		}

		Handle<HwIndexBuffer> D3D11Driver::createIndexBufferS() noexcept
		{
			return Handle<HwIndexBuffer>();
		}

		Handle<HwTexture> D3D11Driver::createTextureS() noexcept
		{
			return Handle<HwTexture>();
		}

		Handle<HwSamplerGroup> D3D11Driver::createSamplerGroupS() noexcept
		{
			return Handle<HwSamplerGroup>();
		}

		Handle<HwUniformBuffer> D3D11Driver::createUniformBufferS() noexcept
		{
			return Handle<HwUniformBuffer>();
		}

		Handle<HwRenderPrimitive> D3D11Driver::createRenderPrimitiveS() noexcept
		{
			return Handle<HwRenderPrimitive>();
		}

		Handle<HwProgram> D3D11Driver::createProgramS() noexcept
		{
			return Handle<HwProgram>();
		}

		Handle<HwRenderTarget> D3D11Driver::createDefaultRenderTargetS() noexcept
		{
			return alloc_handle<D3D11RenderTarget, HwRenderTarget>();
		}

		Handle<HwRenderTarget> D3D11Driver::createRenderTargetS() noexcept
		{
			return alloc_handle<D3D11RenderTarget, HwRenderTarget>();
		}

		Handle<HwFence> D3D11Driver::createFenceS() noexcept
		{
			return Handle<HwFence>();
		}

		Handle<HwSwapChain> D3D11Driver::createSwapChainS() noexcept
		{
			return alloc_handle<D3D11SwapChain, HwSwapChain>();
		}

		Handle<HwStream> D3D11Driver::createStreamFromTextureIdS() noexcept
		{
			return Handle<HwStream>();
		}

		void D3D11Driver::destroyVertexBuffer(Handle<HwVertexBuffer> vbh)
		{

		}

		void D3D11Driver::destroyIndexBuffer(Handle<HwIndexBuffer> ibh)
		{

		}

		void D3D11Driver::destroyRenderPrimitive(Handle<HwRenderPrimitive> rph)
		{

		}

		void D3D11Driver::destroyProgram(Handle<HwProgram> ph)
		{

		}

		void D3D11Driver::destroySamplerGroup(Handle<HwSamplerGroup> sbh)
		{

		}

		void D3D11Driver::destroyUniformBuffer(Handle<HwUniformBuffer> ubh)
		{

		}

		void D3D11Driver::destroyTexture(Handle<HwTexture> th)
		{

		}

		void D3D11Driver::destroyRenderTarget(Handle<HwRenderTarget> rth)
		{
			destruct_handle<D3D11RenderTarget>(m_handle_map, rth);
		}

		void D3D11Driver::destroySwapChain(Handle<HwSwapChain> sch)
		{
			destruct_handle<D3D11SwapChain>(m_handle_map, sch);
		}

		void D3D11Driver::destroyStream(Handle<HwStream> sh)
		{

		}

		void D3D11Driver::terminate()
		{

		}

		Handle<HwStream> D3D11Driver::createStream(void* stream)
		{
			return Handle<HwStream>();
		}

		void D3D11Driver::setStreamDimensions(Handle<HwStream> stream, uint32_t width, uint32_t height)
		{

		}

		int64_t D3D11Driver::getStreamTimestamp(Handle<HwStream> stream)
		{
			return 0;
		}

		void D3D11Driver::updateStreams(backend::DriverApi* driver)
		{

		}

		void D3D11Driver::destroyFence(Handle<HwFence> fh)
		{

		}

		FenceStatus D3D11Driver::wait(Handle<HwFence> fh, uint64_t timeout)
		{
			return FenceStatus::ERROR;
		}

		bool D3D11Driver::isTextureFormatSupported(TextureFormat format)
		{
			return false;
		}

		bool D3D11Driver::isRenderTargetFormatSupported(TextureFormat format)
		{
			return false;
		}

		bool D3D11Driver::isFrameTimeSupported()
		{
			return false;
		}

		void D3D11Driver::updateVertexBuffer(
			Handle<HwVertexBuffer> vbh,
			size_t index,
			BufferDescriptor&& data,
			uint32_t byteOffset)
		{

		}

		void D3D11Driver::updateIndexBuffer(
			Handle<HwIndexBuffer> ibh,
			BufferDescriptor&& data,
			uint32_t byteOffset)
		{

		}

		void D3D11Driver::update2DImage(
			Handle<HwTexture> th,
			uint32_t level,
			uint32_t xoffset,
			uint32_t yoffset,
			uint32_t width,
			uint32_t height,
			PixelBufferDescriptor&& data)
		{

		}

		void D3D11Driver::updateCubeImage(
			Handle<HwTexture> th,
			uint32_t level,
			PixelBufferDescriptor&& data,
			FaceOffsets faceOffsets)
		{

		}

		void D3D11Driver::setupExternalImage(void* image)
		{

		}

		void D3D11Driver::cancelExternalImage(void* image)
		{

		}

		void D3D11Driver::setExternalImage(Handle<HwTexture> th, void* image)
		{

		}

		void D3D11Driver::setExternalStream(Handle<HwTexture> th, Handle<HwStream> sh)
		{

		}

		void D3D11Driver::generateMipmaps(Handle<HwTexture> th)
		{

		}

		bool D3D11Driver::canGenerateMipmaps()
		{
			return false;
		}

		void D3D11Driver::loadUniformBuffer(Handle<HwUniformBuffer> ubh, BufferDescriptor&& data)
		{

		}

		void D3D11Driver::updateSamplerGroup(Handle<HwSamplerGroup> sbh, SamplerGroup&& samplerGroup)
		{

		}

		void D3D11Driver::beginRenderPass(
			Handle<HwRenderTarget> rth,
			const RenderPassParams& params)
		{
			auto render_target = handle_cast<D3D11RenderTarget>(m_handle_map, rth);
			m_context->current_render_target = render_target;
			m_context->current_render_pass_flags = params.flags;

			ID3D11RenderTargetView* color = nullptr;
			ID3D11DepthStencilView* depth = nullptr;

			// set render target
			if (render_target->default_render_target)
			{
				color = m_context->current_swap_chain->color_view;

				if (render_target->depth_view == nullptr)
				{
					DXGI_SWAP_CHAIN_DESC1 swap_chain_desc;
					m_context->current_swap_chain->swap_chain->GetDesc1(&swap_chain_desc);

					render_target->CreateDepth(
						m_context,
						DXGI_FORMAT_D24_UNORM_S8_UINT,
						swap_chain_desc.Width,
						swap_chain_desc.Height);
				}

				depth = render_target->depth_view;
			}
			else
			{
				color = render_target->color_view;
				depth = render_target->depth_view;
			}

			m_context->context->OMSetRenderTargets(1, &color, depth);

			// set viewport
			D3D11_VIEWPORT viewport = CD3D11_VIEWPORT(
				(float) params.viewport.left,
				(float) (params.viewport.height - (params.viewport.bottom + params.viewport.height)),
				(float) params.viewport.width,
				(float) params.viewport.height
			);
			m_context->context->RSSetViewports(1, &viewport);

			// clear
			if (params.flags.clear & filament::backend::TargetBufferFlags::COLOR)
			{
				if (color)
				{
					m_context->context->ClearRenderTargetView(color, (float*) &params.clearColor);
				}
			}
			if (params.flags.clear & filament::backend::TargetBufferFlags::DEPTH ||
				params.flags.clear & filament::backend::TargetBufferFlags::STENCIL)
			{
				UINT flags = 0;
				if (params.flags.clear & filament::backend::TargetBufferFlags::DEPTH)
				{
					flags |= D3D11_CLEAR_DEPTH;
				}
				if (params.flags.clear & filament::backend::TargetBufferFlags::STENCIL)
				{
					flags |= D3D11_CLEAR_STENCIL;
				}

				if (depth)
				{
					m_context->context->ClearDepthStencilView(depth, flags, (float) params.clearDepth, params.clearStencil);
				}
			}
		}

		void D3D11Driver::endRenderPass(int dummy)
		{
			m_context->current_render_target = nullptr;
			m_context->current_render_pass_flags = { };
		}

		void D3D11Driver::discardSubRenderTargetBuffers(
			Handle<HwRenderTarget> rth,
			TargetBufferFlags targetBufferFlags,
			uint32_t left,
			uint32_t bottom,
			uint32_t width,
			uint32_t height)
		{

		}

		void D3D11Driver::setRenderPrimitiveBuffer(
			Handle<HwRenderPrimitive> rph,
			Handle<HwVertexBuffer> vbh,
			Handle<HwIndexBuffer> ibh,
			uint32_t enabledAttributes)
		{

		}

		void D3D11Driver::setRenderPrimitiveRange(
			Handle<HwRenderPrimitive> rph,
			PrimitiveType pt,
			uint32_t offset,
			uint32_t minIndex,
			uint32_t maxIndex,
			uint32_t count)
		{

		}

		void D3D11Driver::setViewportScissor(
			int32_t left,
			int32_t bottom,
			uint32_t width,
			uint32_t height)
		{

		}

		void D3D11Driver::makeCurrent(Handle<HwSwapChain> sch_draw, Handle<HwSwapChain> sch_read)
		{
			auto swap_chain = handle_cast<D3D11SwapChain>(m_handle_map, sch_draw);
			m_context->current_swap_chain = swap_chain;
		}

		void D3D11Driver::commit(Handle<HwSwapChain> sch)
		{
			auto swap_chain = handle_cast<D3D11SwapChain>(m_handle_map, sch);
			DXGI_PRESENT_PARAMETERS parameters = { };
			HRESULT hr = swap_chain->swap_chain->Present1(1, 0, &parameters);
		}

		void D3D11Driver::bindUniformBuffer(size_t index, Handle<HwUniformBuffer> ubh)
		{

		}

		void D3D11Driver::bindUniformBufferRange(
			size_t index,
			Handle<HwUniformBuffer> ubh,
			size_t offset,
			size_t size)
		{

		}

		void D3D11Driver::bindSamplers(size_t index, Handle<HwSamplerGroup> sbh)
		{

		}

		void D3D11Driver::insertEventMarker(const char* string, size_t len)
		{

		}

		void D3D11Driver::pushGroupMarker(const char* string, size_t len)
		{

		}

		void D3D11Driver::popGroupMarker(int dummy)
		{

		}

		void D3D11Driver::readPixels(
			Handle<HwRenderTarget> src,
			uint32_t x,
			uint32_t y,
			uint32_t width,
			uint32_t height,
			PixelBufferDescriptor&& data)
		{

		}

		void D3D11Driver::readStreamPixels(
			Handle<HwStream> sh,
			uint32_t x,
			uint32_t y,
			uint32_t width,
			uint32_t height,
			PixelBufferDescriptor&& data)
		{

		}

		void D3D11Driver::blit(
			TargetBufferFlags buffers,
			Handle<HwRenderTarget> dst,
			backend::Viewport dstRect,
			Handle<HwRenderTarget> src,
			backend::Viewport srcRect,
			SamplerMagFilter filter)
		{
			
		}

		void D3D11Driver::draw(backend::PipelineState ps, Handle<HwRenderPrimitive> rph)
		{
			
		}
	}
}