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
        printf("%g ", data->kernel[i].sorted->value);
    }
    printf("]");
}

static void display(MedfiltData *data,
    size_t i, float in, float min, float mid, float max)
{
    printf("u[%zu] = %g -> min=%g mid=%g max=%g kernel=", i, in, min, mid, max);
    kernel2str(data);
    printf("\n");
}


#define KERNEL  (5)
#define NAN  (0./0.)

int main(void)
{
    const float in[] = { 3, 1, 6, 5, 7, 8, 9, 0, 1 };

    MedfiltData data;
    MedfiltNode nodes[KERNEL];
    medfilt_init(&data, nodes, NAN, KERNEL);

    for (size_t i = 0; i < sizeof(in) / sizeof(in[0]); i++) {
        float min, mid, max;
        medfilt(&data, in[i], &mid, &min, &max);
        display(&data, i, in[i], min, mid, max);
    }

    return EXIT_SUCCESS;
}
