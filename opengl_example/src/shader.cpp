#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) 
{
    // shader의 메모리는 함수를 나가는 순간 해제된다
    auto shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;

    // move함수를 이용해서 포인터의 소유권을 밖으로 이전시켜 함수 밖에서도 메모리가 해제되지 않도록(사용가능) 한다
    return std::move(shader);
}

Shader::~Shader()
{
    // 클래스가 소멸되기 전에 정리하기
    if (m_shader)//이게 빈값이 아니면 opengl프로젝트가 만들어져 있다는 의미다. 지워야함
    {
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) 
{
    auto result = LoadTextFile(filename);
    if (!result.has_value()) // return 값이 optional이기 때문에 Load에 실패하면 값이 없다
        return false;

    // 읽어온 result값은 매우 길 수 있다.
    // 이때 &(레퍼런스)없이 auto(또는 std::string)로 받아오면 읽어온 긴 값이 code에 그대로 할당 -> 메모리 copy가 일어난다
    // result에서 읽어온 값을(메모리를) 그대로 활용하고 싶으면 레퍼런스로 사용한다
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();
    
    // create and compile shader
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // 쉐이더가 1개니까 &를 통해 첫번째 주소값만 넘긴다
    glCompileShader(m_shader);

    // check compile error
    int success = 0;
    // iv : int vector(pointer) -> 즉 integer pointer
    // 쉐이더의 정보를 얻어온다. success를 통해 컴파일이 성공했는지 아닌지를 알 수 있다(실패는 0)
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

    if (!success) 
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog); // 실패시 왜 쉐이더가 실패했는지 얻어온다
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
return true;
}