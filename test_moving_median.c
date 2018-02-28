/**
 * Example of moving median.
 */
#include <stdio.h>
#include <stdlib.h>
#include "moving_median.h"

static void kernel2str(MedianData *data)
{
	printf("[ ");
	for (size_t i = 0; i < data->length; i++) {
		printf("%d ", (int)data->kernel[i].sorted->value);
	}
	printf("]");
}

static void display(MedianData *data, size_t i, int in, int min, int mid, int max) {
	printf("u[%d] = %d -> min=%d mid=%d max=%d kernel=", (int)i, in, min, mid, max);
	kernel2str(data);
	printf("\n");
}


#define KERNEL  (5)

int main(void)
{
	const int input[] = { 3, 1, 6, 5, 7, 8, 9, 0, 1 };

	MedianData data;
	struct Node nodes[KERNEL];
	median_init(&data, nodes, KERNEL);

	for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
		float min, mid, max;
		median(input[i], &data, &mid, &min, &max);
		display(&data, i, input[i], (int)min, (int)mid, (int)max);
	}
	getchar();

	return EXIT_SUCCESS;
}
