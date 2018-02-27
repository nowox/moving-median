/**
* Moving Median Filter.
* @author CHEVALLIER Yves <ycr@csem.ch>
*/
#pragma once
#define N  5

struct Node {
	float value;
	struct Node* parent;
};

typedef struct MedianData {
	struct Node *oldest;
	struct Node nodes[N];
	struct Node *sorted[N];
} MedianData;

void median_init(MedianData* data);
void median(float input, MedianData *data, float *median, float *min, float *max);