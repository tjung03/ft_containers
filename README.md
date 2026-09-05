# ft_containers

C++의 `vector`, `map`, `stack`을 `ft` 네임스페이스에 구현한 42 Seoul 프로젝트입니다. 컨테이너가 사용하는 **메모리 할당·객체 수명, 반복자, 트리 노드 연결과 재균형**을 직접 다룹니다.

표준 컨테이너와 같은 연산을 수행하는 비교 코드가 함께 있으며, 벡터 삽입의 인덱스 문제를 수정하고 테스트를 추가한 개발 이력이 남아 있습니다.

## 구현과 코드 구조

| 구성 | 핵심 구현 |
| --- | --- |
| [vector.hpp](vector.hpp) | allocator로 연속 저장 공간 관리, 크기·용량 분리, 삽입·삭제·재할당 |
| [map.hpp](map.hpp) | 키·값 저장, 삽입·삭제, 조회와 범위 연산 |
| [red_black_tree.hpp](red_black_tree.hpp) · [rb_node.hpp](rb_node.hpp) | 노드 색상과 부모·자식 연결, 회전, 삽입·삭제 후 재균형 |
| [stack.hpp](stack.hpp) | 기본 컨테이너로 `ft::vector`를 사용하는 LIFO 어댑터 |
| [iterator.hpp](iterator.hpp) | 벡터·트리 반복자, const 반복자, 역방향 반복자와 traits |
| [utils.hpp](utils.hpp) | `enable_if`, `is_integral`, `pair`, 구간 비교 함수 |
| [main_ft.cpp](main_ft.cpp) · [main_std.cpp](main_std.cpp) | ft·std 컨테이너의 상태 출력과 시간 측정 코드 |
| [tester_vector.cpp](tester_vector.cpp) · [tester_map.cpp](tester_map.cpp) · [tester_stack.cpp](tester_stack.cpp) | 별도 비교 테스터의 컨테이너별 검사 |

## 구현 포인트

**벡터의 저장 공간과 원소 수명을 분리합니다.** `allocate/deallocate`로 저장 공간을 확보·반납하고, `construct/destroy`로 원소를 생성·파괴합니다. `push_back()`에서 용량이 부족하면 기존 용량의 두 배를 확보하고 원소를 복사합니다.

**맵의 노드 변경을 트리 계층에 맡깁니다.** 삽입·삭제 후 노드 색상과 연결 관계에 따라 회전·재색칠을 수행합니다. 공통 말단 노드를 사용하며 트리 반복자는 부모·자식 연결을 따라 순회합니다. 현재 `find/count/lower_bound/upper_bound`와 삽입 전 중복 검사는 순차 탐색입니다.

**반복자와 템플릿 도구를 컨테이너에서 공유합니다.** `enable_if`와 `is_integral`로 개수 인자와 범위 인자를 구분하고, `equal`과 `lexicographical_compare`로 관계 연산자를 구성합니다. 벡터의 범위 생성·삽입은 반복자 간 뺄셈을 사용하는 임의 접근 반복자 기준입니다.

## 사용 예제

헤더를 포함해 사용합니다. 아래 내용을 저장소 루트의 `example.cpp`로 저장합니다.

```cpp
#include <iostream>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

int main() {
    ft::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.insert(v.begin() + 1, 15);

    ft::map<int, int> m;
    m[2] = 20;
    m[1] = 10;

    ft::stack<int> s;
    s.push(7);
    s.push(9);
    s.pop();

    std::cout << v.at(1) << " " << m.begin()->first
              << " " << s.top() << std::endl;
}
```

```bash
c++ -std=c++98 -Wall -Wextra -Werror example.cpp -o example
./example
```

출력: `15 1 7`

## 비교 테스터 실행

Makefile의 `tester` 타깃은 `rchallie_tester`를 만듭니다. 저장소 루트에서 실행합니다.

```bash
make tester
mkdir -p tester
./rchallie_tester
```

벡터·맵·스택의 연산 결과를 표준 컨테이너와 비교하고, 상세 값을 `tester/vectors_output`, `tester/maps_output`, `tester/stacks_output`에 기록합니다. [테스터 도입 이력](https://github.com/tjung03/ft_containers/commit/d90ec7a28042c6bfc4a5fd4730b452732de39df8)

Linux/GCC에서 위 사용 예제의 출력과 비교 테스터의 전 항목 `[OK]` 출력을 확인했습니다. 해당 테스터 실행은 환경의 LeakSanitizer 제약으로 누수 검사를 끄고 진행했습니다.

## 빌드 구성과 호환성

기본 Makefile은 C++98과 AddressSanitizer를 지정합니다. `make`는 `ft_test`, `std_test`를 만들고, `make tester`는 별도 비교 테스터를 만듭니다.

`main_ft.cpp`와 `main_std.cpp`의 시간 측정에는 C++11의 `std::chrono`가 사용됩니다. 다음 설정으로 빌드할 수 있습니다. 현재 두 main의 맵·스택 테스트 본문은 주석 처리되어 있습니다.

```bash
make re CPPFLAGS='-fsanitize=address -std=c++11 -Wall -Wextra'
./ft_test
./std_test
```

이 설정은 경고를 출력하면서 빌드합니다. `map.hpp`의 `std::binary_function`은 C++11에서 deprecated, C++17에서 제거된 형식이며, 현재 구현은 해당 형식을 사용하는 학습 당시 코드입니다. [C++ 표준 변경 기록](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0636r2.html)

## 개발 기록

- [반복자와 벡터 1차 구현](https://github.com/tjung03/ft_containers/commit/6dd3fb09e2c4a0a51c4b8f8f97bbb623b1f24b02)
- [벡터 삽입의 unsigned 인덱스 감소와 다중 삽입 위치 수정](https://github.com/tjung03/ft_containers/commit/0918cdc4de93f4303d133ae9e722f883b4059824)
- [vector·map·stack 테스트 케이스 작성](https://github.com/tjung03/ft_containers/commit/182ebb12dc36c1c32337151aa6ee6d2fc8e3fe69)
