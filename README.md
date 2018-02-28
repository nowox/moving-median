# Moving Median Filter

Iterative implementation of a Moving Median Filter

```c
#include <stdlib.h>
#include "medfilt.h"

#define KERNEL  (5)

int main(void)
{
    MedfiltData data;
    MedfiltNode nodes[KERNEL];

    medfilt_init(&data, nodes, KERNEL);

    for (size_t i = 0; i < sizeof(in) / sizeof(in[0]); i++) {
        float min, mid, max;
        medfilt(in[i], &data, &mid, &min, &max);
    }

    return EXIT_SUCCESS;
}
```
