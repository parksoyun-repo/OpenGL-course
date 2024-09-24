#version 330 core
// 3.3의 core부터 수행할 수 있는 쉐이더코드다

layout (location = 0) in vec3 aPos;


// 쉐이더도 main이 있어야한다
void main() 
{
    gl_Position = vec4(0.5, 0.5, 0.0, 1.0);
}