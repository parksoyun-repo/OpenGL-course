#include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    auto buffer = BufferUPtr(new Buffer());
    
    if (!buffer->Init(bufferType, usage, data, dataSize))
        return nullptr;
    
    return std::move(buffer);
}

Buffer::~Buffer() 
{
    if (m_buffer) 
    {
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::Bind() const 
{
    // m_buffer 버퍼는 m_bufferType이라고 묶어줌
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    m_bufferType = bufferType;
    m_usage = usage;
    
    glGenBuffers(1, &m_buffer);// vertex buffer를 생성
    Bind();
    // data(vertices)의 값이 m_Buffer에 복사된다
    // usage) STATIC : 버퍼 값을 잘 안바꿀거다. DYNAMIC : 자주 바꿀거다 STREAM : 한 번 쓰고 버릴거다
    glBufferData(m_bufferType, dataSize, data, usage);
    
    return true;
}