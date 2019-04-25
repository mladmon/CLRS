#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Heap data structure implementation
template <class T> class Heap {
	vector<T> h;
	unsigned h_size = 0;

	unsigned parent(unsigned i) { return (i+1)/2 - 1; }
	unsigned left(unsigned i)   { return i*2 + 1; }
	unsigned right(unsigned i)  { return i*2 + 2; }
	void maxHeapify(unsigned i);
	void buildMaxHeap();

  public:
	Heap() = default;
	Heap(const vector<T> &vec) : h(vec), h_size(vec.size()) { buildMaxHeap(); }
	Heap(T *arr, unsigned size) : h(arr, arr+size), h_size(size) { buildMaxHeap(); }
	void insert(T ele);
	T max();
	T extractMax();
	void increaseKey(unsigned, T);
	void print();
};

template <class T> void Heap<T>::maxHeapify(unsigned i) {
	unsigned max_i = i;
	if (left(i) < h_size && h[left(i)] > h[max_i]) {
		max_i = left(i);
	}
	if (right(i) < h_size && h[right(i)] > h[max_i]) {
		max_i = right(i);
	}
	if (max_i != i) {
		T temp = h[i];
		h[i] = h[max_i];
		h[max_i] = temp;
		maxHeapify(max_i);
	}
}

template <class T> void Heap<T>::buildMaxHeap() {
	for (int i=h_size/2-1; i >= 0; --i) {
		maxHeapify(i);
	}
}

template <class T> void Heap<T>::insert(T ele) {
	if (h.size() == h_size) {
		h.push_back(ele);
	} else {
		h[h_size] = ele;
	}
	h_size++;
	increaseKey(h_size-1, ele);
}

template <class T> T Heap<T>::max() {
	return h[0];
}

template <class T> T Heap<T>::extractMax() {
	T max = h[0];
	h[0] = h[--h_size];
	maxHeapify(0);

	return max;
}

template <class T> void Heap<T>::increaseKey(unsigned i, T val) {
	h[i] = val;
	while (i > 0 && h[parent(i)] < h[i]) {
		T temp = h[i];
		h[i] = h[parent(i)];
		h[parent(i)] = temp;
		i = parent(i);
	}
}

template <class T> void Heap<T>::print() {
	for (int i=0; i < h_size; ++i) {
		cout << h[i] << " ";
	}
	cout << endl;
}

// use the Heap data structure to implement heapsort() trivially
template <class T> void heapsort(T arr[], unsigned size) {
	Heap<T> heap(arr, size);
	for (int i=size-1; i >= 0; --i) {
		arr[i] = heap.extractMax();
	}
}

int main() {
	Heap<string> h0;
	h0.insert("hello");
	h0.insert("mario");
	h0.insert("admon");
	h0.insert("steph");
	h0.insert("curry");
	cout << "h0: "; h0.print();

	cout << endl << "-----------------------" << endl << endl;

	Heap<int> h1(vector<int>{1, -13, 12, 21, 7, 8, 5, 8});
	cout << "h1: "; h1.print();
	cout << "insert: 49, 17" << endl;
	h1.insert(49);
	h1.insert(17);
	h1.print();
	cout << "h1.max(): " << h1.max() << endl;
	h1.print();
	cout << "h1.extractMax(): " << h1.extractMax() << endl;
	h1.print();
	cout << "increasing a[6] to 15" << endl;
	h1.increaseKey(6, 15);
	h1.print();

	cout << endl << "-----------------------" << endl << endl;

	double nums[] = {1.7, -3.4218, 12, 4.9, 3.33, 4.90001, 22};
	cout << "nums[]: ";
	for (auto &d : nums) cout << d << " "; cout << endl;

	Heap<double> h2(nums, sizeof(nums)/sizeof(nums[0]));
	cout << "h2: "; h2.print();

	cout << "sorting nums[]" << endl;
	heapsort(nums, sizeof(nums)/sizeof(nums[0]));
	cout << "nums[]: "; for (auto &d : nums) cout << d << " "; cout << endl;


	cout << endl << "-----------------------" << endl << endl;

	Heap<char> h3{{'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'}};
	cout << "h3: "; h3.print();
	cout << "inserting: 'H', 'a'" << endl;
	h3.insert('H');
	h3.insert('a');
	cout << "calling extractMax() 2 times" << endl;
	h3.extractMax();
	h3.extractMax();
	h3.print();

	cout << endl << "-----------------------" << endl << endl;

	char letters[] {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'};
	cout << "letters[]: "; for (auto &c : letters) cout << c << " "; cout << endl;


	cout << "sorting letters[]" << endl;
	heapsort(letters, sizeof(letters)/sizeof(letters[0]));
	cout << "letters[]: "; for (auto &c : letters) cout << c << " "; cout << endl;

	cout << endl << "-----------------------" << endl << endl;

	// use the Heap data structure to "implement" a priority queue
	Heap<int> priority_queue(vector<int> {5, 22, 17, 1, 3, 18, 5});
	cout << "priority_queue: "; priority_queue.print();
	cout << "extractMax(): " << priority_queue.extractMax() << endl;
	priority_queue.print();
	cout << "insert(20): "; priority_queue.insert(20); priority_queue.print();
	cout << "popping: ";
	for (int i=0; i<4; ++i) cout << priority_queue.extractMax() << " "; cout << endl;
	priority_queue.print();

	return 0;
}
