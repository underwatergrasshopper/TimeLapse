#include <stdio.h>

#include <TimeLapse.h>

int main() {
    puts("LapseExample begin.");
    puts("All measured time lapses should be around 0.4s.");

    TimeLapseF64 tl;

    {
        tl.Start();
        Sleep(400);
        tl.Stop();

        printf("%fs\n", tl.Get());
    }

    {
        tl.Reset();
        int countdown = 2;

        while (countdown--) {
            Sleep(400);
            tl.Update();

            printf("%fs\n", tl.Get());
        }
    }

    {
        tl.Reset();
        int count = 1;

        while (count < 10) {
            Sleep(400);
            if (tl.UpdateIfAbove(1.0)) {

                printf("%fs, count=%d\n", tl.Get(), count);
                break;
            }
            count += 1;
        }
    }

    puts("LapseExample end.");
    return 0;
}
