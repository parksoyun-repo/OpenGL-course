#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

int main(int argc, const char** argv) {
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

     // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr); // 모니터는 어떤것을 쓸 것인지, 다른 윈도우랑 컨텍스트를 쉐어할 것인지
    if (!window) 
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) // 닫혀야 하나요?
    {
        // 1/60초(윈도우를 그리는 시간 간격)마다 수행
        glfwPollEvents(); // 윈도우와 관련된 이벤트를 수집(키보드입력, 마우스 입력, 닫기, 크기변경 등)
    }

    glfwTerminate();

    return 0;
}