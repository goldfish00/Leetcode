/* 306. Additive Number */
class Solution {
private:
    void addRemains(string::const_reverse_iterator it, string::const_reverse_iterator itEnd, bool& shouldAddOne, deque<char>& sumChars) {
        while (it != itEnd) {
            int digitSum = int(*it - '0') + (shouldAddOne ? 1 : 0);
            if (digitSum < 10) {
                sumChars.push_front('0' + digitSum);
                shouldAddOne = false;
            } else {
                sumChars.push_front('0');
                shouldAddOne = true;
            }
            ++it;
        }
    }
    
    // s1 and s2 won't start with 0
    string strAdd(const string& s1, const string& s2) {
        bool shouldAddOne = false;
        deque<char> sumChars;

        auto s1It = s1.rbegin(), s2It = s2.rbegin();
        for (; s1It != s1.rend() && s2It != s2.rend(); ++s1It, ++s2It) {
            int digitSum = int(*s1It - '0') + int(*s2It - '0') + (shouldAddOne ? 1 : 0);
            if (digitSum < 10) {
                sumChars.push_front('0' + digitSum);
                shouldAddOne = false;
            } else {
                sumChars.push_front('0' + (digitSum - 10));
                shouldAddOne = true;
            }
        }
        
        addRemains(s1It, s1.rend(), shouldAddOne, sumChars);
        addRemains(s2It, s2.rend(), shouldAddOne, sumChars);
        
        if (shouldAddOne) {
            sumChars.push_front('1');
        }
        
        return string(sumChars.begin(), sumChars.end());
    }
    
    bool canBeAdditive(string num, int currentIndex, deque<string>& nums) {
        if (currentIndex == num.size()) {
            return nums.size() > 2;
        }
        
        if (nums.size() < 2) {
            for (int i = 0; i < (num.size() - currentIndex) / 2; ++i) {
                if (num[currentIndex] == '0' && i != 0) {
                    continue;
                }
                nums.push_back(num.substr(currentIndex, i + 1));
                if (canBeAdditive(num, currentIndex + i + 1, nums)) {
                    return true;
                }
                nums.pop_back();
            }
        } else {
            string sum = strAdd(nums.back(), *(nums.rbegin() + 1));
            if (num.size() - currentIndex < sum.size()) {
                return false;
            }
            
            bool notMatch = false;
            for (int i = 0; i < sum.size(); ++i) {
                if (num[currentIndex + i] != sum[i]) {
                    notMatch = true;
                    break;
                }
            }
            if (notMatch) {
                return false;
            }
            nums.push_back(sum);
            
            if (canBeAdditive(num, currentIndex + (int)sum.size(), nums)) {
                return true;
            }
            nums.pop_back();
        }
            
        return false;
    }
    
public:
    bool isAdditiveNumber(string num) {
        if (num.size() < 3) {
            return false;
        }
        
        deque<string> nums;
        return canBeAdditive(num, 0, nums);
    }
};

int main() {
    Solution S;
//    cout << S.isAdditiveNumber("112358") << endl;
//    cout << S.isAdditiveNumber("111") << endl;
//    cout << S.isAdditiveNumber("199100199") << endl;
//    cout << S.isAdditiveNumber("123") << endl;
    cout << S.isAdditiveNumber("199001200") << endl;
    return 0;
}
