#include <cassert>

#include "mat.hpp"
#include "vec.hpp"

int main(void)
{
    const dmat4 m_a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const dvec4 v_a{0, 1, 2, 3};

    const dvec4 v_b = m_a * v_a;
    assert(v_b.x == 56);
    assert(v_b.y == 62);
    assert(v_b.z == 68);
    assert(v_b.w == 74);
    
    return 0;
}
