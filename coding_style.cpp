/* Block comments only allowed  */

/* first include external header files, ascending order */
#include <iostream>
#include <string>

/* related header are put in blocks */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* internal header files go last, C++ files use .hpp extension */
#include "cube.hpp"


/* constants are UPPER_CASE */
const int SUPER_CONSTANT = 10;

/* two empty lines before start of class */
/* classname starts with capital, camelcase */
class ClassName {
/* first put public methods and variables, as they should be visible to user */
public:
    /* indentation is four whitespaces */
    ClassName();
    ~ClassName();

    /* always use const if method does not change class */
    int compute_cubishness_factor(const ClassName &other_class) const;

private:
    /* use underscore to separate words in variables */
    int cube_factor;
};
