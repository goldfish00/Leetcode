/* 284. Peeking Iterator */
class Iterator {
    struct Data;
     Data* data;
public:
    Iterator(const vector<int>& nums);
     Iterator(const Iterator& iter);

    //Returns the next element in the iteration.
    int next();

    //Returns true if the iteration has more elements.
    bool hasNext() const;
};

class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {}
    
    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        Iterator nextIt(*this);
        return nextIt.next();
    }
};
