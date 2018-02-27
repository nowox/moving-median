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

void median_init(MedianData* data, struct Node *nodes, struct Node **sorted, size_t length)
{
	data->nodes = nodes; 
	data->sorted = sorted; 
	data->length = length; 

	data->oldest = &data->nodes[length - 1];

	for (size_t i = 0; i < length; data->oldest = &data->nodes[i], i++) {
		data->nodes[i] = (struct Node) {.value = 0, .parent = data->oldest};
		data->sorted[i] = &data->nodes[i]; 		 
	}
}