/**
* Moving Median Filter.
* @author CHEVALLIER Yves <ycr@csem.ch>
*/
#pragma once

struct Node {
	float value;
	struct Node* parent;
};

typedef struct MedianData {
	struct Node *nodes;
	struct Node *oldest;
	struct Node **sorted;
	size_t length; // Number of nodes
} MedianData;

void median_init(MedianData* data, struct Node *nodes, struct Node **sorted, size_t length);
void median(float input, MedianData *data, float *median, float *min, float *max);