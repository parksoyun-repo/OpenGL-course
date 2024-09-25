#include "context.h"

ContextUPtr Context::Create() 
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
     return std::move(context);

}
bool Context::Init() 
{
    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // top left
    };
    uint32_t indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    m_vertexLayout = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 12);

    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

    // attribute array를 따로 세팅 할 필요가 없다. element array는 정수값이 들어갈거라는것을 이미 알기떄문에
	m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

    // unique pointer는 shared pointer로 바로 변환 가능
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    
    if (!vertShader || !fragShader)
        return false;
    
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());
    
    m_program = Program::Create({fragShader, vertShader});  // {} 에 두면 벡터
    
    if (!m_program)
        return false;
    
    SPDLOG_INFO("program id: {}", m_program->Get());
    
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);// State-setting function : 화면을 무슨 색으로 지울까? 
    
    return true;
}

void Context::Render() 
{
    glClear(GL_COLOR_BUFFER_BIT);   // State-using function : 화면에 있는 색상 버퍼를 실제로 지움
    //(지우는 색은 glClearColor에서 설정함)

    m_program->Use();
    //glDrawArrays(GL_TRIANGLES, 0, 6); // 0번부터 시작, 점 6개
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 인덱스가 6개 타입은 uint
}
