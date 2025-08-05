# JellyLog

~ ***JLog*** *(Requires C++ 20)*

A simple logging system originally created for the Nova language toolchain, it is:
- Easy to use
- Cross-platform (Windows and Ansi consoles)
- Very small

This makes it perfect to use in performance critical applications, or specialised cases where other types of logging would never be needed

> [!NOTE]
> This logging system is limited, and more features may be added later down the line

## How to use

Simply copy over the entire `include` directory to your workspace, and add it to your include search paths

CMake example:
```cmake
# ...

# As an example, where it has been installed to a 'libs' directory
include_directories(libs/include)
```

And include the main file (or others) in your source or header files:

```c++
#include "jlog/JLog.h"

int main() {
    JLOG_INFO("Hello, world!"); // Will print "Hello, world!" in yellow (as default)
}
```

---

## Other

*Submit issues or feature requests to the GitHub page*