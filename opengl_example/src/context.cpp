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
    
    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}

void Context::Render() 
{
    glClear(GL_COLOR_BUFFER_BIT);   // State-using function : 화면에 있는 색상 버퍼를 실제로 지움
    //(지우는 색은 glClearColor에서 설정함)

    glUseProgram(m_program->Get());
    glDrawArrays(GL_POINTS, 0, 1);
}
