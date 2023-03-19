#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <assert.h>
#include <set>
#include <deque>
#include <unordered_map>
#include <queue>
#include <map>
using namespace std;

/* 282. Expression Add Operators */
class Solution {
private:
    struct Meme {
    public:
        char lastOp;
        long long lastNumber;
        long long lastAddition;
        long long result;
    };
    
    Meme genMemeWithNoop(const Meme& meme, int num) {
        auto nextMeme = meme;
        if (meme.lastOp == ' ') {
            nextMeme.result = meme.result * 10 + num;
            nextMeme.lastNumber = nextMeme.result;
            nextMeme.lastAddition = nextMeme.result;
            return nextMeme;
        }
        
        nextMeme.result -= meme.lastAddition;

        if (meme.lastOp == '+') {
            nextMeme.lastNumber = meme.lastNumber * 10 + (meme.lastNumber < 0 ? -1 : 1) * num;
            nextMeme.result += nextMeme.lastNumber;
            nextMeme.lastAddition = nextMeme.lastNumber;
            return nextMeme;
        }
        
        // '*'
        nextMeme.lastAddition /= meme.lastNumber;
        nextMeme.lastNumber = meme.lastNumber * 10 + num;
        nextMeme.lastAddition *= nextMeme.lastNumber;
        nextMeme.result += nextMeme.lastAddition;
        return nextMeme;
    }
    
    Meme genMemeWithAdd(const Meme& meme, int num) {
        auto nextMeme = meme;
        nextMeme.lastOp = '+';
        nextMeme.result = meme.result + num;
        nextMeme.lastNumber = num;
        nextMeme.lastAddition = num;
        return nextMeme;
    }
    
    Meme genMemeWithMultiply(const Meme& meme, int num) {
        auto nextMeme = meme;
        if (meme.lastOp == ' ') {
            nextMeme.lastOp = '*';
            nextMeme.result = meme.result * num;
            nextMeme.lastNumber = nextMeme.result;
            nextMeme.lastAddition = nextMeme.result;
            return nextMeme;
        }
        
        nextMeme.result -= meme.lastAddition;
        nextMeme.lastNumber = num;
        nextMeme.lastAddition *= num;
        nextMeme.result += nextMeme.lastAddition;
        nextMeme.lastOp = '*';
        return nextMeme;
    }
    
    void findWithBacktrack(const string& num, size_t nextIndex, string& result, int target, vector<string>& results, Meme meme = {' ', 0, 0, 0}){
        if (meme.result > INT_MAX) {
            return;
        }
        
        if (nextIndex == num.size()) {
            if (meme.result == target) {
                results.push_back(result);
            }
            return;
        }
        
        if (nextIndex == 0) {
            int digit = int(num[0] - '0');
            meme.lastOp = '+';
            meme.lastNumber = digit;
            meme.result = digit;
            meme.lastAddition = digit;
            
            result.push_back(num[0]);
            findWithBacktrack(num, nextIndex + 1, result, target, results, meme);
            result.pop_back();
        } else {
            // four option: no operator, or operator +, -, *
            const char& currentChar = num[nextIndex];
            int currentNum = int(currentChar - '0');
            // no op
            if (meme.lastNumber != 0) {
                result.push_back(currentChar);
                findWithBacktrack(num, nextIndex + 1, result, target, results, genMemeWithNoop(meme, currentNum));
                result.pop_back();
            }

            // with add
            result.push_back('+');
            result.push_back(currentChar);
            findWithBacktrack(num, nextIndex + 1, result, target, results, genMemeWithAdd(meme, currentNum));
            result.pop_back();
            result.pop_back();
            
            // with subtract
            result.push_back('-');
            result.push_back(currentChar);
            findWithBacktrack(num, nextIndex + 1, result, target, results, genMemeWithAdd(meme, -1 * currentNum));
            result.pop_back();
            result.pop_back();
            
            // with multiply
            result.push_back('*');
            result.push_back(currentChar);
            findWithBacktrack(num, nextIndex + 1, result, target, results, genMemeWithMultiply(meme, currentNum));
            result.pop_back();
            result.pop_back();
        }
        
    }

public:
    vector<string> addOperators(string num, int target) {
        vector<string> results;
        string result;
        findWithBacktrack(num, 0, result, target, results);

        return results;
    }
};

int main() {
    Solution S;
//    string num("105");
//    S.addOperators(num, 5);
//    string num("00");
//    S.addOperators(num, 0);
    string num("1234567");
    S.addOperators(num, 1);
    return 0;
}
