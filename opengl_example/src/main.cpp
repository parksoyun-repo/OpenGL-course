#include "context.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h> // GLFW선언 전에 선언 해야한다
#include <GLFW/glfw3.h>

// 윈도우의 프레임버퍼 크기가 변경되었을 때 호출하기 위한 콜백 정의
// glViewport(): OpenGL이 그림을 그릴 영역(위치 및 크기) 지정
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) 
{
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char** argv) 
{
   SPDLOG_INFO( "Start progrm");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
   SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) 
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    // opengl을 어떻게 세팅해줄것인지 힌트를 준다
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

     // glfw 윈도우 생성, 실패하면 에러 출력후 종료
     // 윈도우가 생성이 될때 OpenGL 컨텍스트도 생성이 된다
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr); // 모니터는 어떤것을 쓸 것인지, 다른 윈도우랑 컨텍스트를 쉐어할 것인지
    if (!window) 
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // 만들어진 window의 컨텍스트를 사용하겠다는것을 명시적으로 선언해줘야 한다

    // glad를 활용한 OpenGL 함수 로딩
    // opengl함수를 로딩한다. 성공하면 OpenGL function을 쓸 수 있게 된다
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    { 
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", (const char*)glVersion);


    auto context = Context::Create();
    if (!context) 
    {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }

    // 윈도우 생성 직후에는 프레임버퍼 변경 이벤트가 발생하지 않으므로 첫 호출은 수동으로 함
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);   
    // glfwPollEvents에서 해당 이벤트가 발생하면 지정한 콜백함수를 실행하라고 지정
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) // 닫혀야 하나요?
    {
        // 1/60초(윈도우를 그리는 시간 간격)마다 수행
        glfwPollEvents(); // 윈도우와 관련된 이벤트를 수집(키보드입력, 마우스 입력, 닫기, 크기변경 등)
        
        // 화면에 그림을 그리는 과정(Double Buffering)
        // 1. 프레임버퍼 2개를 준비(front/back)
        // 2. back buffer에 그림 그리기
        // 3. front와 back을 바꿔치기
        // 이렇게 하면 그림이 그려지는 과정이 노출되지 않음
        context->Render();
        glfwSwapBuffers(window);
    }

    context.reset();    // context = nullptr도 같은 효과. nullptr이 되면 메모리 소유권이 없어지면서 날아간다
    
    glfwTerminate();

    return 0;
}