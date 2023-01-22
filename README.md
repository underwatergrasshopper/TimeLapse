# Description
Measures a time lapse between two points in the code.

### Example 1

```c++
#include <windows.h>
#include <TimeLapse.h>

int main() {
    TimeLapse tl;

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
    TimeLapse tl;

    tl.Reset();

    int count = 5;
    while (count--) {
        Sleep(400);
        // Measures time difference from:
        //      Reset   - for first call of Update,
        //      Update  - for each another call of Update.
        tl.Update(); 

        printf("%fs\n", tl.Get());
    }
}
```
