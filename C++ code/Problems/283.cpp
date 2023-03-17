/* 283. Move Zeroes */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        vector<int>::iterator it0 = nums.begin();
        // find the first zero
        while (it0 != nums.end() && *it0 != 0) {
            ++it0;
        }
        while (it0 != nums.end()) {
            auto it1 = it0 + 1;
            while (it1 != nums.end() && *it1 == 0) {
                ++it1;
            }
            if (it1 == nums.end()) {
                return;
            }
            
            swap(*it1, *it0);
            while (it0 != nums.end() && *it0 != 0) {
                ++it0;
            }
        }
    }
};

int main() {
    vector<int> num{0, 1, 0, 3, 12};
}

