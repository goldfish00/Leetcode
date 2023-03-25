/* 295. Find Median from Data Stream */

/* Two Heap */
class MedianFinder {
private:
    int size;
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    bool hasEvenElements() {
        return size % 2 == 0;
    }
    
public:
    MedianFinder() {
        size = 0;
    }
    
    void addNum(int num) {
        if (hasEvenElements()) {
            if (maxHeap.empty()) {
                maxHeap.push(num);
            } else if (num <= minHeap.top()) {
                maxHeap.push(num);
            } else {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(num);
            }
        } else if (num >= maxHeap.top()) {
            minHeap.push(num);
        } else {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(num);
        }
        
        ++size;
    }
    
    double findMedian() {
        if (hasEvenElements()) {
            return double(minHeap.top() + maxHeap.top()) / 2;
        }
        return maxHeap.top();
    }
};

/* Multiset with pointer: vector */
class MedianFinder {
private:
    multiset<int> nums;
    multiset<int>::iterator firstMedianIt;
    
    bool hasEvenElements() {
        return nums.size() % 2 == 0;
    }
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        if (nums.empty()) {
            nums.insert(num);
            firstMedianIt = nums.begin();
            return;
        }
        
        nums.insert(num);
        if (num < *firstMedianIt && hasEvenElements()) {
            firstMedianIt = prev(firstMedianIt);
            return;
        }
        
        if (num >= *firstMedianIt && !hasEvenElements()) {
            firstMedianIt = next(firstMedianIt);
            return;
        }
    }
    
    double findMedian() {
        if (!hasEvenElements()) {
            return *firstMedianIt;
        }
        return double(*firstMedianIt + *next(firstMedianIt)) / 2;
    }
};



/* TLE */
class MedianFinder {
private:
    int size;
    map<int, int> numIndexMap;
    map<int, int>::iterator firstMedian;

public:
    MedianFinder() {
        size = 0;
    }
    
    void addNum(int num) {
        ++size;
        auto it = numIndexMap.find(num);
        if (it == numIndexMap.end()) { // not found
            auto resPair = numIndexMap.insert({num, size - 1});
            // skip checking if the num is inserted successfully
            it = next(resPair.first);
            if (it != numIndexMap.end()) {
                resPair.first->second = it->second;
            }
        } else {
            it = next(it);
        }
        
        for (auto incrementIt = it; incrementIt != numIndexMap.end(); ++incrementIt) {
            ++incrementIt->second;
        }
        
        if (size == 1) {
            firstMedian = numIndexMap.begin();
            return;
        }
        
        // update first median if in need
        int firstMedianIndex = (size - 1) / 2;
        if (firstMedianIndex == firstMedian->second) {
            return;
        }
        if (firstMedianIndex < firstMedian->second) {
            firstMedian = prev(firstMedian);
            return;
        }
        auto nextIt = next(firstMedian);
        if (nextIt == numIndexMap.end()) {
            return;
        } else if (firstMedianIndex >= nextIt->second) {
            firstMedian = nextIt;
        }
    }
    
    double findMedian() {
        if (size % 2 == 1) { // odd
            return firstMedian->first;
        }
        
        auto nextIt = next(firstMedian);
        if (nextIt == numIndexMap.end()) {
            return firstMedian->first;
        }
        
        int secondMedian = (size - 1) / 2 + 1;
        if (secondMedian >= nextIt->second) {
            return double(firstMedian->first + nextIt->first) / 2;
        }
        
        return firstMedian->first;
    }
};

int main() {
    MedianFinder f;
    f.addNum(12);
    cout << f.findMedian() << endl;
    f.addNum(10);
    cout << f.findMedian() << endl;
    f.addNum(13);
    cout << f.findMedian() << endl;
    f.addNum(11);
    cout << f.findMedian() << endl;
    f.addNum(5);
    cout << f.findMedian() << endl;
    f.addNum(15);
    cout << f.findMedian() << endl;
    f.addNum(1);
    cout << f.findMedian() << endl;
    f.addNum(11);
    cout << f.findMedian() << endl;
    f.addNum(6);
    cout << f.findMedian() << endl;
    f.addNum(17);
    cout << f.findMedian() << endl;
    f.addNum(14);
    cout << f.findMedian() << endl;
    f.addNum(8);
    cout << f.findMedian() << endl;
    f.addNum(17);
    cout << f.findMedian() << endl;
    f.addNum(6);
    cout << f.findMedian() << endl;
    f.addNum(4);
    cout << f.findMedian() << endl;
    f.addNum(16);
    cout << f.findMedian() << endl;
    f.addNum(8);
    cout << f.findMedian() << endl;
    f.addNum(10);
    cout << f.findMedian() << endl;
    f.addNum(2);
    cout << f.findMedian() << endl;
    f.addNum(12);
    cout << f.findMedian() << endl;
    f.addNum(0);
    cout << f.findMedian() << endl;
    return 0;
}
