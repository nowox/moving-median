/**
 * Moving Median Filter.
 * @author CHEVALLIER Yves <ycr@csem.ch>
 */
#include <stdint.h>
#include <stdlib.h>
#include "moving_median_filter.h"

void swap(struct Node *a, struct Node *b) 
{
	struct Node node = *a;
	*a = *b;
	*b = node;
}

void median(float input, MedianData *data, float *median, float *min, float *max)
{	
	struct Node *n = data->sorted[data->oldest];
	n->value = input;
	n = n->parent;

	size_t index = data->oldest; 
	while (index < data->length - 1 && 
		data->sorted[index]->value > data->sorted[index + 1]->value) 
	{
		swap(data->sorted[index], data->sorted[index + 1]);
	}
	while (index > 0 &&
		data->sorted[index]->value < data->sorted[index - 1]->value)
	{
		swap(data->sorted[index], data->sorted[index - 1]);
	}

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
	data->oldest = length / 2;

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