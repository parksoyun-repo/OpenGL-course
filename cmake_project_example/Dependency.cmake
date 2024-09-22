
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install) #PROJECT_BINARY_DIR는 build 폴더
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
ExternalProject_Add(
    dep_spdlog  # 이름
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"  # 가져올 브랜치나 태그
    GIT_SHALLOW 1       # 가장 최신의 commit만 가져오겠다(용량 등 유리)
    UPDATE_COMMAND ""   # 다운로드 받은 코드가 구형이 되면 자동으로 최신을 받아준다 ex) "git pull" 등을 넣을수 있음. 
    PATCH_COMMAND ""    # 위에서 다운로드 받은 코드에서 뭔가 고치려고 할때 쓴다
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # Cmake Configure를 할 때 인자를 뭘 집어넣을 것인가. 
    #-D는 Definition. -DCMAKE_INSTALL_PREFIX는 CMake가 build되었을때 어디 저장할 것인가
    TEST_COMMAND "" # 자동테스트가 지정되면 어떻게 수행할 것인가. 라이브러리가 잘 만들어졌을테니 지금 우리는 필요 없다
)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) # $< : cmake에서 제공하는 문법. build단계에 작용
# Config가 debug일때는 d를 붙이고, 아니면 붙이지 말아라(ex)spdlog.d)

# glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.4"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF   # 예제 실행 안할거다
        -DGLFW_BUILD_TESTS=OFF  # 테스트 잘 되어있겠지
        -DGLFW_BUILD_DOCS=OFF   # 문서 인터넷 보면 된다
    )
# 레포지토리에 CMakeList.txt를 보면 option에 이름, 설명, 디폴트값을 알 수 있다 

set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)