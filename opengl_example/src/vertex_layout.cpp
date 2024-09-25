#include "vertex_layout.h"

VertexLayoutUPtr VertexLayout::Create() 
{
    auto vertexLayout = VertexLayoutUPtr(new VertexLayout());
    vertexLayout->Init();
    return std::move(vertexLayout);
}

VertexLayout::~VertexLayout() 
{
    if (m_vertexArrayObject) 
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
}

void VertexLayout::Bind() const 
{
    glBindVertexArray(m_vertexArrayObject); // 지금부터 사용할 VAO는 m_vertexArrayObject이거다
}

void VertexLayout::SetAttrib(uint32_t attribIndex, int count, uint32_t type, bool normalized, size_t stride, uint64_t offset) const 
{
    
    // attribIndex번째 attribute를 쓸거다
    glEnableVertexAttribArray(attribIndex);
    
    // vertices가 어떤식으로 점을 구성하고 있는지 알려준다
    // attribIndex번째 attribute는 type값이 count개고 각각의 값은 type이고 nomalizing 여부,
    // 다음 attribute는 type값 stride개 건너뛰면 되고, offset은 offset이다(offset번부터 시작한다)
    glVertexAttribPointer(attribIndex, count, type, normalized, stride, (const void*)offset);
}

void VertexLayout::Init() 
{
    glGenVertexArrays(1, &m_vertexArrayObject); // VAO를 1개 만들겠다
    Bind();
}