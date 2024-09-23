#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

// 매크로 선언
// ##은 사용시 두 단어를 붙여준다(ex. klassName ## UPtr -> klassNameUPtr)
// using은 aliasing. 이름을 간략하게 할 뿐
#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

// optional<>이 없을땐 메모리를 할당해 로드해서 로드에 실패하면 null포인터인거고 null체크해서 로드에 실패했다는걸 알았는데,
// 이 방식은 메모리를 할당하기 때문에 memory leak의 가능성이 있음
// optional을 쓰면 로드실패시 string을 꺼낼수 없게해준다. 메모리 할당 안해도 됨
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__