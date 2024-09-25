#version 330 core
// 3.3의 core부터 수행할 수 있는 쉐이더코드다
// aPos에 vertices값이 vec3형태로 들어오게 된다
// location = 0이 곧 VAO attribute 0번이라는뜻
layout (location = 0) in vec3 aPos;


// 쉐이더도 main이 있어야한다
void main() 
{
    gl_Position = vec4(aPos, 1.0);
}