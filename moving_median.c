/**
 * Moving Median Filter.
 * @author CHEVALLIER Yves <ycr@csem.ch>
 */
#include <stdint.h>
#include <stdlib.h>
#include "moving_median.h"

static void swap(Node **a, Node **b)
{
	// Swap two node references in the sorted table.
	Node *temp = *a;
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
	Node *n = data->kernel;
	Node *node = data->oldest;
	node->value = input;
	data->oldest = node->parent;

	// Sort the kernel
	#define VAL(x) (n[x].sorted->value)
	for (size_t i = node->index; i < data->length - 1 && VAL(i) > VAL(i + 1); i++) {
		swap(&n[i].sorted, &n[i + 1].sorted);
	}

	for (size_t i = node->index; i > 0 && VAL(i) < VAL(i - 1); i++) {
		swap(&n[i].sorted, &n[i - 1].sorted);
	}

	// Get kernel information from sorted entries
	*min = n[0].sorted->value;
	*max = n[data->length - 1].sorted->value;
	*median = n[data->length / 2].sorted->value;
}

void median_init(MedianData *data, Node *nodes, size_t length)
{
	data->kernel = nodes;
	data->length = length;

	// Linked list initialization
	data->oldest = &data->kernel[length - 1];
	for (size_t i = 0; i < length; data->oldest = &data->kernel[i], i++) {
		data->kernel[i] = (Node) {
			.value = 0,
			.parent = data->oldest,
			.index = i,
			.sorted = &data->kernel[i]
		};
	}
}
