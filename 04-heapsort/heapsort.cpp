#include <iostream>
#include <cstdlib>	// rand(), srand()
#include <ctime>		// time()
#include <random>		// C++11 random number generator facilities
#include <chrono>		// C++11 time library

//#define NDEBUG
#include <cassert>

using namespace std;

// heap data structure
class Heap {
		int *a;
		int heapSize, arrayLength;
		bool valid;
	public:
		Heap();
		Heap(int);
		~Heap() {delete[] a;}

		int parent(int i) { return (i-1)/2; }
		int left(int i) { return 2*i+1; }
		int right(int i) { return 2*i+2; }

		void maxHeapify(int);
		void buildMaxHeap();
		friend void heapsort(Heap &);

		void invalidate() { valid = false; }
		bool isValid() { return valid; }
		void print();
};

Heap::Heap() : a(new int[15]), heapSize(15), arrayLength(15) {
	/* srand() is passed a distinctive runtime value as a seed to initialize the
	   pseudo-random number generator. It generates a sequence of seemingly
		random values that are subsequently accessed by calls to rand() */
	srand(time(NULL));
	for (int i=0; i < 15; i++) {
		a[i] = rand() % 50 + 1; // modulo 50 + 1 returns values in the range 1-50
	}
	buildMaxHeap();
}

Heap::Heap(int size) : a(new int[size]), heapSize(size), arrayLength(size) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,50);

	for (int i=0; i < size; i++) {
		a[i] = distribution(generator);
	}
	buildMaxHeap();
}

// maintains the max-heap property: a[parent(i)] >= a[i]
void Heap::maxHeapify(int i) {
	int left = this->left(i);
	int right = this->right(i);

	// determine the largest element between a[i], a[left], and a[right]
	int largest = i;
	if (left < heapSize && a[left] > a[i]) {
		largest = left;
	}
	if (right < heapSize && a[right] > a[largest]) {
		largest = right;
	}

	int swap = a[i];
	if (largest != i) {
		a[i] = a[largest];
		a[largest] = swap;
		maxHeapify(largest);
	}
}

// builds a max-heap from an unordered array
void Heap::buildMaxHeap() {
	heapSize = arrayLength;
	for (int i=(arrayLength/2)-1; i >= 0; i--) {
		maxHeapify(i);
	}
	valid = true;
}

void heapsort(Heap &heap) {
	if (!heap.isValid()) {
		heap.buildMaxHeap();
	}

	int swap;
	for (int i = heap.arrayLength-1; i > 0; i--) {
		swap = heap.a[i];
		heap.a[i] = heap.a[0];
		heap.a[0] = swap;

		heap.heapSize--;
		heap.maxHeapify(0);
	}

	heap.invalidate();
}

void Heap::print() {
	cout << "a[";
	if (!this->isValid()) { // print the entire array
		for (int i=0; i < arrayLength-1; i++) {
			cout << a[i] << ", ";
		}
		cout << a[arrayLength-1] << "]" << endl;
	} else { // print the heap elements only
		for (int i=0; i < heapSize-1; i++) {
			cout << a[i] << ", ";
		}
		cout << a[heapSize-1] << "]" << endl;
	}
}

int main(int argc, char *argv[]) {
	Heap heap0, heap1(7), heap2(15);

	assert(heap0.isValid());
	heap0.print();
	heapsort(heap0);
	assert(!heap0.isValid());
	heap0.print();

	assert(heap1.isValid());
	heap1.print();
	heapsort(heap1);
	assert(!heap1.isValid());
	heap1.print();

	assert(heap2.isValid());
	heap2.print();
	heapsort(heap2);
	assert(!heap2.isValid());
	heap2.print();

	return 0;
}
