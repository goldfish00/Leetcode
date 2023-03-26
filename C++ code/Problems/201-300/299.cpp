/* 299. Bulls and Cows */
class Solution {
public:
    string getHint(string secret, string guess) {
        multiset<char> possibleCows;
        int numBull = 0;
        int numCow = 0;
        
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) {
                ++numBull;
                guess[i] = '-';
            } else {
                possibleCows.insert(secret[i]);
            }
        }
        
        for (const char& c : guess) {
            if (c == '-') {
                continue;
            }
            auto it = possibleCows.find(c);
            if (it == possibleCows.end()) {
                continue;
            }
            possibleCows.erase(it);
            ++numCow;
        }
        
        return to_string(numBull) + "A" + to_string(numCow) + "B";
    }
};

// much faster with unordered map
class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char, int> cowCharNum;
        int numBull = 0;
        int numCow = 0;
        
        for (int i = 0; i < secret.size(); ++i) {
            if (secret[i] == guess[i]) {
                ++numBull;
                guess[i] = '-';
            } else {
                ++cowCharNum[secret[i]];
            }
        }
        
        for (const char& c : guess) {
            if (c == '-') {
                continue;
            }
            
            auto it = cowCharNum.find(c);
            if (it == cowCharNum.end()) {
                continue;
            }
            if (it->second > 0) {
                --it->second;
                ++numCow;
            }
        }
        
        return to_string(numBull) + "A" + to_string(numCow) + "B";
    }
};

