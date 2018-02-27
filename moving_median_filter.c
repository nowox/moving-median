/**
 * Moving Median Filter.
 * @author CHEVALLIER Yves <ycr@csem.ch>
 */
#include <stdint.h>
#include <stdlib.h>
#include "moving_median_filter.h"

static void swap_node(struct Node* a, struct Node* b) 
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
	// New value replaces the oldest
	struct Node* node = data->oldest;
	node->value = input;
	data->oldest = data->oldest->prev;

	// Sort new values
	struct Node* walk = node; 
	while (walk->index < N - 1 && walk->value > data->buffer[walk->index + 1].value) {
		swap_node(walk, &data->buffer[walk->index + 1]);
		walk = &data->buffer[walk->index + 1];
	}

	while (walk->index > 0 && walk->value < data->buffer[walk->index - 1].value) {
		swap_node(walk, &data->buffer[walk->index - 1]);
		walk = &data->buffer[walk->index - 1];
	}

	// Fill the output struct
	*min = data->buffer[0].value;
	*max = data->buffer[N - 1].value;
	*median = data->buffer[N / 2].value;
}

void median_init(MedianData* data) 
{
	struct Node* prev = &data->buffer[N - 1]; 

	for (size_t i = 0; i < N - 1; i++) {
		data->buffer[i] = (struct Node) {
			.value = 0,
			.prev = prev,
			.next = &data->buffer[i + 1],
			.index = i
		};
		prev = &data->buffer[i]; 
	}

	data->buffer[N - 1] = (struct Node) {
		.value = 0,
		.next = &data->buffer[0],
		.prev = prev,
		.index = N - 1
	};

	data->oldest = &data->buffer[N / 2];
}