# Moving Median Filter

Iterative implementation of a Moving Median Filter

```c
#include <stdlib.h>
#include "medfilt.h"

#define KERNEL  (5)
#define NAN  (0. / 0.)

int main(void)
{
    const float in[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };

    MedfiltData data;
    MedfiltNode nodes[KERNEL];

    medfilt_init(&data, nodes, NAN, KERNEL);

    for (size_t i = 0; i < sizeof(in) / sizeof(in[0]); i++) {
        float min, mid, max;
        medfilt(in[i], &data, &mid, &min, &max);
    }

    return EXIT_SUCCESS;
}
```

The included `test_medfilt` would return:

```
$ make run
cc -std=c99 -Wall -O2   -c -o test_medfilt.o test_medfilt.c
cc -std=c99 -Wall -O2   -c -o medfilt.o medfilt.c
ar rc libmedfilt.a medfilt.o
cc test_medfilt.o -o test -lmedfilt -L.
./test
u[0] = 3 -> min=-nan mid=-nan max=3 kernel=[ -nan -nan -nan -nan 3 ]
u[1] = 1 -> min=-nan mid=-nan max=3 kernel=[ -nan -nan -nan 1 3 ]
u[2] = 4 -> min=-nan mid=1 max=4 kernel=[ -nan -nan 1 3 4 ]
u[3] = 1 -> min=-nan mid=1 max=4 kernel=[ -nan 1 1 3 4 ]
u[4] = 5 -> min=1 mid=3 max=5 kernel=[ 1 1 3 4 5 ]
u[5] = 9 -> min=1 mid=4 max=9 kernel=[ 1 1 4 5 9 ]
u[6] = 2 -> min=1 mid=4 max=9 kernel=[ 1 2 4 5 9 ]
u[7] = 6 -> min=1 mid=5 max=9 kernel=[ 1 2 5 6 9 ]
u[8] = 5 -> min=2 mid=5 max=9 kernel=[ 2 5 5 6 9 ]
u[9] = 3 -> min=2 mid=5 max=9 kernel=[ 2 3 5 6 9 ]
```
