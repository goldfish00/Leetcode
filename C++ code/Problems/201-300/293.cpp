/* 293. Flip Game */
class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        vector<string> nextStates;
        for (auto it = currentState.begin() + 1; it != currentState.end(); ++it) {
            if (*it == '+' && *(it - 1) == '+') {
                *it = '-';
                *(it - 1) = '-';
                nextStates.push_back(currentState);
                *it = '+';
                *(it - 1) = '+';
            }
        }
        return nextStates;
    }
};

