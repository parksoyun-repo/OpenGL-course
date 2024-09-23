#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader {
public:
    static ShaderUPtr CreateFromFile(const std::string& filename,
    GLenum shaderType);

    ~Shader();
    // m_shader의 값(쉐이더 아이디)는 외부에서 함부로 manipulating하면 안되기 때문에 Get은 있는데 Set은 없다
    uint32_t Get() const { return m_shader; }    
private:
    // constructor, 초기화하는 함수가 private
    // 생성자가 private면 밖에서 생성할 수가 없다
    // 이 쉐이더를 생성하려면 CreateFromFile를 통하지 않으면 할 수 없게 한다
    Shader() {}
    bool LoadFile(const std::string& filename, GLenum shaderType);
    uint32_t m_shader { 0 }; // opengl쉐이더 오브젝트의 아이디를 저장할 멤버
};

#endif // __SHADER_H__