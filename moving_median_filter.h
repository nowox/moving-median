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
	struct Node **sorted;
	size_t oldest;
	size_t length; // Number of nodes
} MedianData;

MedianData* median_create(size_t length);
void median_destroy(MedianData* data);
void median(float input, MedianData *data, float *median, float *min, float *max);