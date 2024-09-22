cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_project_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/main.cpp)

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # PROJECT_NAME프로젝트를 컴파일 할때 DEP_INCLUDE_DIR가 필요하다
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR}) # PROJECT_NAME를 링크시킬떄 DEP_LIB_DIR경로를 포함 시켜라(안하면 링크 에러)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) # 링크할 라이브러리의 실제 이름(확장자명은 붙이지 않음)

# C에서 #define WINDOW_HEIGHT 960과 같은 문법을 소스코드 안이 아닌 여기서 수행할 수 있도록 해준다
target_compile_definitions(${PROJECT_NAME} PUBLIC
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}

)

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST}) # PROJECT_NAME를 컴파일 하려면 DEP_LIST(의존성 리스트)을 먼저 컴파일 하고 해라.
#안하면 병렬로 둘이 같이 진행이 된다