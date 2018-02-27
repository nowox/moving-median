#include <stdio.h>
#include "moving_median_filter.h"

void print_memory(MedianData *data)
{
	printf("[ ");
	for (size_t i = 0; i < data->length; i++) {
		printf("%d ", (int)data->sorted[i]->value);
	}
	putchar(']');
}

int main(void) 
{
	int input[] = { 3, 1, 6, 5, 7, 8, 9, 0, 1 };
	MedianData *data = median_create(5);

	for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
		float min, mid, max;
		median(input[i], data, &mid, &min, &max);
		printf("%d. %d -> (min=%d\tmid=%d\tmax=%d ",
			(int)i, input[i], (int)min, (int)mid, (int)max);
		print_memory(data); 
		printf(")\n");
	}
	getchar();
	median_destroy(data);
}