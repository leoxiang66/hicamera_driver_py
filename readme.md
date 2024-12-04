

# HiKVision Camera APIs

This project provides a set of utility functions for interacting with cameras using the MvCamera SDK. It includes functionality for image capturing, device configuration, parameter management, IEEE 1588, action commands, etc.

## **File Structure**

```
.
├── include/                # Header files
├── src/                    # Source files
├── Makefile                # Build system
└── readme.md               # Project documentation
```

## **Dependencies**

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., `g++`).
- **MvCamera SDK**: [机器视觉工业相机客户端MVS V3.0.1 (Linux)](https://www.hikrobotics.com/cn/machinevision/service/download/?module=0)
- **Make**: To build the project using the provided Makefile.

---

## **API**
1. [timer](https://github.com/leoxiang66/hikvision_camera_api/blob/cpp/include/timer.h)
2. [utils](https://github.com/leoxiang66/hikvision_camera_api/blob/cpp/include/utils.h)

---



## **Build Instructions**

### **1. Build the Project**

To compile the source code, run:

```sh
make
```

This will create the `main` executable in the `build/` directory.

---

### **2. Run the Program**

To execute the compiled program, run:

```sh
make run
```

This will run the `main` executable.

---

### **3. Install the Utility Code**

To install the utility headers and library files to your system (e.g., `/usr/local/include` and `/usr/local/lib`), run:

```sh
make install
```

This will:
- Copy the header files from `include/` to `/usr/local/include/hikvision_api`.
- Build a static library (`libhikvision_api.a`) and install it to `/usr/local/lib`.

You can then use these utilities in other projects by including the headers and linking against the library.

---

### **4. Uninstall the Utility Code**

To remove the installed headers and library files, run:

```sh
make uninstall
```

This will:
- Remove the header files from `/usr/local/include/hikvision_api`.
- Remove the static library (`libhikvision_api.a`) from `/usr/local/lib`.

---

## **Using the Installed Utility in Other Projects**

Once installed, you can use the utility code in other projects:

### **1. Include the Headers**

In your source code, include the headers like this:

```cpp
#include <hikvision_api/utils.h>
#include <hikvision_api/timer.h>
```

### **2. Link the Library**

When compiling your project, specify the include path and link the library:

```sh
g++ -o my_program my_program.cpp -lhikvision_api -L/usr/local/lib -I/usr/local/include
```

---

## **Clean the Build**

To clean up all build artifacts, run:

```sh
make clean
```

This will remove the `build/` directory and any intermediate files.

---

## **License**

MIT License

Copyright (c) [2024] [XIANG Tao]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## **Contact**

For questions, issues, or contributions, feel free to open an issue.

