# Description
Measures a time lapse between two points in the code.

## HOWTO: Run tests manually
To run all tests for Visual Studio\*, call `Test.bat`.             
To run all tests for MinGW\*\*, call `MinGW_Test.bat`.     
To run selected tests for MinGW\*\*, call `MinGW_Test.bat run <build_target> <architecture>` from `ToStr_Test` folder, where
```
<build_target>
    Release
    Debug
<architecture>
    64
    32
```
.
<sup>\*) To be able compile, add path to MSBuild bin folder in `TimeLapse/TestCache.bat`:
```
set MSBUILD_PATH=<path>
```
.
</sup>        
<sup>\*\*) To be able compile with 64 bit and 32 bit gcc, add paths to mingw bin folder in `TimeLapse/TimeLapse_Example/MinGW_MakeCache.bat`:
```
set MINGW32_BIN_PATH=<path>
set MINGW64_BIN_PATH=<path>
```
.
</sup>

## Builds and tests results

Compiler: **MSVC** (automated)

| Test Platform | Target Platform | Environment | Architecture | Build and Test |
|-|-|-|-|-|
| Windows Server 2022, Windows Server 2019 | Windows 10 |  Visual Studio 2022, Visual Studio  2019 | x86, x86_64 | [![Build and Test](https://github.com/underwatergrasshopper/TimeLapse/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/underwatergrasshopper/TimeLapse/actions/workflows/build_and_test.yml) |

 Compiler: **LLVM CLang MinGW** (automated)

| Test Platform | Target Platform | Environment | Architecture | Build and Test |
|-|-|-|-|-|
| Windows Server 2022 | Windows 10 | MinGW-W64 (LLVM Clang 15.0.0) | x86, x86_64 |  [![Build and Test (MinGW)](https://github.com/underwatergrasshopper/TimeLapse/actions/workflows/build_and_test_mingw.yml/badge.svg)](https://github.com/underwatergrasshopper/TimeLapse/actions/workflows/build_and_test_mingw.yml) |

## Examples

### Example 1

```c++
#include <windows.h>
#include <TimeLapse.h>

int main() {
    TimeLapseF64 tl;

    tl.Start();
    Sleep(400);
    tl.Stop();

    printf("%fs\n", tl.Get());
}
```

### Example 2

```c++
#include <windows.h>
#include <TimeLapse.h>

int main() {
    TimeLapseF64 tl;

    tl.Reset();

    int countdown = 5;
    while (countdown--) {
        Sleep(400);
        // Measures time difference from:
        //      Reset   - for first call of Update,
        //      Update  - for each another call of Update.
        tl.Update(); 

        printf("%fs\n", tl.Get());
    }
}
```

### Example 3

```c++
#include <windows.h>
#include <TimeLapse.h>

int main() {
    TimeLapseF64 tl;

    tl.Reset();

    int count = 1;
    while (count < 10) {
        Sleep(400);

        if (tl.UpdateIfAbove(1.0)) {
            // Measures difference only if difference would be bigger than 1 second.
            printf("%fs, count=%d\n", tl.Get(), count);
            break;
        }
        count += 1;
    }
}
```
