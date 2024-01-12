// DP: all methods have time complexity O(n)
class MinStack {
private:
    stack<int> nums;
    stack<int> minMeme;
    
public:
    MinStack() {}
    
    void push(int val) {
        nums.push(val);
        if (nums.size() == 1) {
            minMeme.push(val);
            return;
        }
        minMeme.push(min(minMeme.top(), val));
    }
    
    void pop() {
        nums.pop();
        minMeme.pop();
    }
    
    int top() {
        return nums.top();
    }
    
    int getMin() {
        return minMeme.top();
    }
};
