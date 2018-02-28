/**
 * Moving Median Filter.
 * @author CHEVALLIER Yves <ycr@csem.ch>
 */
#include <stdint.h>
#include <stdlib.h>
#include "moving_median_filter.h"

static void swap(struct Node **a, struct Node **b) 
{
	// Swap two node references in the sorted table.
	struct Node *temp = *a;
	*a = *b;
	*b = temp;

	// Preserve index. Used to retrive the node position in the sorted table.
	size_t index = (*a)->index;
	(*a)->index = (*b)->index; 
	(*b)->index = index;
}

void median(float input, MedianData *data, float *median, float *min, float *max)
{	
	// New value replaces the oldest
	struct Node *n = data->kernel;
	struct Node *new_node = data->oldest;
	new_node->value = input;
	data->oldest = new_node->parent;

	// Sort the kernel
	size_t i = new_node->index;
	while (i < data->length - 1 && n[i].sorted->value > n[i + 1].sorted->value) {
		swap(&n[i].sorted, &n[i + 1].sorted);
		i++;
	}

	i = new_node->index;
	while (i > 0 && n[i].sorted->value < n[i - 1].sorted->value) {
		swap(&n[i].sorted, &n[i - 1].sorted);
		i--;
	}

	// Get kernel information from sorted entries
	*min = n[0].sorted->value;
	*max = n[data->length - 1].sorted->value;
	*median = n[data->length / 2].sorted->value;
}

void median_init(MedianData *data, struct Node *nodes, size_t length)
{
	data->kernel = nodes;
	data->length = length;

	// Linked list initialization
	data->oldest = &data->kernel[length - 1];
	for (size_t i = 0; i < length; data->oldest = &data->kernel[i], i++) {
		data->kernel[i] = (struct Node) {
			.value = 0, 
			.parent = data->oldest, 
			.index = i, 
			.sorted = &data->kernel[i]
		}; 		 
	}
}