/**
 * Example of moving median.
 */
#include <stdio.h>
#include <stdlib.h>
#include "medfilt.h"

static void kernel2str(MedfiltData *data)
{
    printf("[ ");
    for (size_t i = 0; i < data->length; i++) {
        printf("%d ", (int)data->kernel[i].sorted->value);
    }
    printf("]");
}

static void display(MedfiltData *data, size_t i, int in, int min, int mid, int max) {
    printf("u[%d] = %d -> min=%d mid=%d max=%d kernel=", (int)i, in, min, mid, max);
    kernel2str(data);
    printf("\n");
}


#define KERNEL  (5)

int main(void)
{
    const int in[] = { 3, 1, 6, 5, 7, 8, 9, 0, 1 };

    MedfiltData data;
    MedfiltNode nodes[KERNEL];
    medfilt_init(&data, nodes, KERNEL);

    for (size_t i = 0; i < sizeof(in) / sizeof(in[0]); i++) {
        float min, mid, max;
        medfilt(in[i], &data, &mid, &min, &max);
        display(&data, i, in[i], (int)min, (int)mid, (int)max);
    }

    return EXIT_SUCCESS;
}
