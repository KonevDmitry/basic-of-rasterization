#include "clear_rendertarget.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdexcept>


cg::ClearRenderTarget::ClearRenderTarget(unsigned width, unsigned height):
    width(width),
    height(height)
{
    frame_buffer.reserve(static_cast<size_t>(width * height));
}

cg::ClearRenderTarget::~ClearRenderTarget()
{
    frame_buffer.clear();
}

void cg::ClearRenderTarget::Clear()
{
    frame_buffer.reserve(static_cast<size_t>(width * height));
}

void cg::ClearRenderTarget::Save(std::string filename) const
{
    int result = stbi_write_png(filename.c_str(), 
        width, height, 3, 
        frame_buffer.data(), width * sizeof(color));
    if (result != 1) {
        throw std::runtime_error("Can't save");
    }
}

void cg::ClearRenderTarget::SetPixel(unsigned x, unsigned y, color color)
{
    if (x < width && y < height)
        frame_buffer[y * width + x] = color;
}
