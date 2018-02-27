/**
* Moving Median Filter.
* @author CHEVALLIER Yves <ycr@csem.ch>
*/
#pragma once
#define N  5

struct Node {
	float value;
	size_t index; 
	union {
		struct {
			struct Node* prev;
			struct Node* next;
		};
		struct family {
			struct Node* family[2];
		} family;
	};
};

typedef struct MedianData {
	struct Node* oldest;
	struct Node buffer[N];
} MedianData;

void median_init(MedianData* data);
void median(float input, MedianData *data, float *median, float *min, float *max);