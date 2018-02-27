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
	size_t index = b->index;
	*a = *b;
	*b = node;
	a->index = node.index;
	b->index = index;
}

void median(float input, MedianData *data, float *median, float *min, float *max)
{	
	struct Node *n = data->oldest;
	n->value = input;
	data->oldest = n->parent;

	while (n->index < data->length - 1 && n->value > data->sorted[n->index + 1]->value) {
		swap(n, &data->sorted[n->index + 1]->value);
		n = &data->sorted[n->index + 1]->value;
	}
	while (n->index > 0 && n->value > data->sorted[n->index - 1]->value) {
		swap(n, &data->sorted[n->index - 1]->value);
		n = &data->sorted[n->index - 1]->value;
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

	data->oldest = &data->nodes[length - 1];

	for (size_t i = 0; i < length; data->oldest = &data->nodes[i], i++) {
		data->nodes[i] = (struct Node) {.value = 0, .parent = data->oldest, .index = i};
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