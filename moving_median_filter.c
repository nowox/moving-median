/**
 * Moving Median Filter.
 * @author CHEVALLIER Yves <ycr@csem.ch>
 */
#include <stdint.h>
#include <stdlib.h>
#include "moving_median_filter.h"

int comp(const struct Node **a, const struct Node **b) 
{
	if ((*a)->value > (*b)->value)
		return 1;
	if ((*a)->value < (*b)->value)
		return -1;
	return 0;
}

void median(float input, MedianData *data, float *median, float *min, float *max)
{	
	data->oldest->value = input;
	data->oldest = data->oldest->parent;

	qsort(data->sorted, data->length, sizeof(data->sorted[0]), comp);
	
	*min = (*data->sorted[0]).value;
	*max = (*data->sorted[data->length - 1]).value;
	*median = (*data->sorted[data->length / 2]).value;
}

MedianData* median_create(size_t length)
{
	MedianData *data = malloc(sizeof(MedianData));
	data->nodes = malloc(sizeof(struct Node) * length);
	data->sorted = malloc(sizeof(struct Node*) * length);
	data->length = length;

	data->oldest = &data->nodes[length - 1];

	for (size_t i = 0; i < length; data->oldest = &data->nodes[i], i++) {
		data->nodes[i] = (struct Node) {.value = 0, .parent = data->oldest};
		data->sorted[i] = &data->nodes[i]; 		 
	}
	return data;
}

void median_destroy(MedianData *data)
{
	free(data->sorted);
	free(data->nodes);
	free(data);
}