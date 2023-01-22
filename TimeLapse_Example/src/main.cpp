#include <stdio.h>

#include <TimeLapse.h>

int main() {
    puts("LapseExample begin.");
    puts("All measured time lapses should be around 0.4s.");

    TimeLapse tl;

    {
        tl.Start();
        Sleep(400);
        tl.Stop();

        printf("%fs\n", tl.Get());
    }

    {
        tl.Reset();
        int count = 2;

        while (count--) {
            Sleep(400);
            tl.Update();

            printf("%fs\n", tl.Get());
        }
    }

    puts("LapseExample end.");
    return 0;
}
