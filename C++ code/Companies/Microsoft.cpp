#include <stdio.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <list>
#include <stack>
#include <queue>
using namespace std;

/* #46 Permutations 1*//*
class Solution {
private:
    vector<vector<int>> results;
    
    void backtrack(deque<int>& nums, deque<int> & permutation, int count){
        //base case
        if (count == 0) {
            results.push_back(vector<int>(permutation.begin(), permutation.end()));
            return;
        }
        for (int i = count; i > 0; --i) {
            int moved = nums.back();
            nums.pop_back();
            permutation.push_front(moved);
            backtrack(nums, permutation, count - 1);
            permutation.pop_front();
            nums.push_front(moved);
        }
    }
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        deque<int> numsQueue(nums.begin(), nums.end());
        deque<int> permutation;
        backtrack(numsQueue, permutation, int(nums.size()));
        return results;
    }
};*/


/* #47 Permutations 2*//*
class Solution {
private:
    set<vector<int>> results;
    
    void backtrack(deque<int>& nums, vector<int> & permutation, int count){
        //base case
        if (count == 0) {
            results.insert(permutation);
            return;
        }
        for (int i = count; i > 0; --i) {
            int moved = nums.back();
            nums.pop_back();
            permutation.push_back(moved);
            backtrack(nums, permutation, count - 1);
            permutation.pop_back();
            nums.push_front(moved);
        }
    }
    
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        deque<int> numsQueue(nums.begin(), nums.end());
        vector<int> permutation;
        permutation.reserve(nums.size());
        backtrack(numsQueue, permutation, int(nums.size()));
        return vector<vector<int>>(results.begin(), results.end());
    }
};*/

// without using the set, faster
/*
class Solution {
private:
    // key: the number  value: times of appearance
    unordered_map<int, int> intCounts;
    vector<vector<int>> results;
    vector<int> result;
    size_t permutationLen = 0;
    
    void remove(int num){
        --intCounts[num];
    }
    
    bool removable(int num){
        return intCounts[num] > 0;
    }
    
    void backtrack(){
        //base case
        if (result.size() == permutationLen) {
            results.push_back(result);
            return;
        }
        
        for (auto& kvPair : intCounts) {
            int chosenNumber = kvPair.first;
            if (removable(chosenNumber)){
                result.push_back(chosenNumber);
                remove(chosenNumber);
                backtrack();
                ++intCounts[chosenNumber];
                result.pop_back();
            }
        }
    }
    
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        permutationLen = nums.size();
        // initialize the map
        for (int num : nums) ++intCounts[num];
        // backtrack
        backtrack();
        return results;
    }
};*/


/* #207. Course Schedule*//* Very bad performance on this solution *//*
class Solution {
private:
    // the i-th row records all the prerequisite for course i
    vector<unordered_set<int>> prereqRelation;
    unordered_set<int> learnedCourses;
    
    bool canFinishSub(int courseId, unordered_set<int>& courses){
        // base case
        if (prereqRelation[courseId].empty()) return true;
        if (learnedCourses.find(courseId) != learnedCourses.end()){
            for (int preqId : prereqRelation[courseId]){
                if (courses.find(preqId) != courses.end()) return false;
            }
            return true;
        }
        // keep DFS
        courses.insert(courseId);
        for (auto preqId : prereqRelation[courseId]) {
            if (courses.find(preqId) != courses.end()) return false;
            if (!canFinishSub(preqId, courses)) return false;
            learnedCourses.insert(preqId);
        }
        courses.erase(courseId);
        learnedCourses.insert(courseId);
        return true;
    }
    
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        prereqRelation.resize(numCourses);
        for (const auto& pairReq : prerequisites) prereqRelation[pairReq.front()].insert(pairReq.back());
        
        for (int courseId = 0; courseId < numCourses; ++courseId) {
            if (prereqRelation[courseId].empty()) continue;
            if (learnedCourses.find(courseId) != learnedCourses.end()) continue;
            unordered_set<int> visited;
        
            if (!canFinishSub(courseId, visited)) return false;
        }
        return true;
    }
};*/


/* #240. Search a 2D Matrix II *//*
class Solution {
private:
    int tar;
    bool find = false;
    
    int midPair(const pair<int, int>& range){
        return range.first + (range.second - range.first) / 2;
    }
    
    // Binary search
    // upperbound
    int findRowInd(const vector<vector<int>>& matrix, int column, pair<int, int> rowRange){
        if (matrix[rowRange.first][column] == tar || matrix[rowRange.second - 1][column] == tar){
            find = true;
            return -1;
        }
        while (matrix[rowRange.first][column] < tar) {
            int mid = midPair(rowRange);
            if (matrix[mid][column] == tar){
                find = true;
                return -1;
            }
            if (matrix[mid][column] < tar){
                rowRange.first = mid;
            }
            else {
                if (matrix[mid - 1][column] == tar){
                    find = true;
                    return -1;
                }
                if (matrix[mid - 1][column] < tar){
                    return mid;
                }
                rowRange.second = mid;
            }
        }
        
        return rowRange.first;
    }
    
    int findColumnInd(const vector<vector<int>>& matrix, int row, pair<int, int> columnRange){
        if (matrix[row][columnRange.first] == tar || matrix[row][columnRange.second - 1] == tar){
            find = true;
            return -1;
        }
        while (matrix[row][columnRange.first] < tar) {
            int mid = midPair(columnRange);
            if (matrix[row][mid] == tar){
                find = true;
                return -1;
            }
            if (matrix[row][mid] < tar){
                columnRange.first = mid;
            }
            else {
                if (matrix[row][mid - 1] == tar){
                    find = true;
                    return -1;
                }
                if (matrix[row][mid - 1] < tar){
                    return mid;
                }
                columnRange.second = mid;
            }
        }
        
        return columnRange.first;
    }
        
    
    bool findRecur(const vector<vector<int>>& matrix, pair<int, int> rowRange, pair<int, int> columnRange){
        if (tar < matrix[rowRange.first][columnRange.first] || tar > matrix[rowRange.second - 1][columnRange.second - 1]){
            return false;
        }
        
        if (rowRange.second - rowRange.first < 2){
            findColumnInd(matrix, rowRange.first, columnRange);
            return find;
        }
        
        if (columnRange.second - columnRange.first < 2){
            findRowInd(matrix, columnRange.first, rowRange);
            return find;
        }
        
        if (rowRange.second - rowRange.first > columnRange.second - columnRange.first){
            // search on the middle row
            // check is searchable
            int midRow = midPair(rowRange);
            if (tar < matrix[midRow][columnRange.first]) return findRecur(matrix, make_pair(rowRange.first, midRow), columnRange);
            if (tar > matrix[midRow][columnRange.second - 1]) return findRecur(matrix, make_pair(midRow, rowRange.second), columnRange);
            int upperCol = findColumnInd(matrix, midRow, columnRange);
            if (find) return true;
            return findRecur(matrix, make_pair(midRow + 1, rowRange.second), make_pair(columnRange.first, upperCol)) || \
            findRecur(matrix, make_pair(rowRange.first, midRow), make_pair(upperCol, columnRange.second));
        }
        else {
            // search on the middle column
            int midColumn = midPair(columnRange);
            if (tar < matrix[rowRange.first][midColumn]) return findRecur(matrix, rowRange, make_pair(columnRange.first, midColumn));
            if (tar > matrix[rowRange.second - 1][midColumn]) return findRecur(matrix, rowRange, make_pair(midColumn, columnRange.second));
            int upperRow = findRowInd(matrix, midColumn, rowRange);
            if (find) return true;
            return findRecur(matrix, make_pair(rowRange.first, upperRow), make_pair(midColumn + 1, columnRange.second)) || \
            findRecur(matrix, make_pair(upperRow, rowRange.second), make_pair(columnRange.first, midColumn));
        }
        return false;
    }
    
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (target < matrix[0][0] || target > matrix.back().back()) return false;
        tar = target;
        return findRecur(matrix, make_pair(0, int(matrix.size())), make_pair(0, matrix[0].size()));
    }
};*/


/* #311. Sparse Matrix Multiplication *//*
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        vector<vector<int>> res(mat1.size(), vector<int>(mat2[0].size(), 0));
        
        // for mat2; key: row; value: column non-zero pairs
        unordered_map<int, set<pair<int, int>>> mat2Prop;
        for (int i = 0; i < mat2.size(); ++i) {
            for (int j = 0; j < mat2[0].size(); ++j) {
                if (mat2[i][j]) mat2Prop[i].insert(make_pair(j, mat2[i][j]));
            }
        }
        // generate result
        for (int row = 0; row < mat1.size(); ++row) {
            for (int column = 0; column < mat1[0].size(); ++column) {
                int val = mat1[row][column];
                if (!val) continue;
                for (const auto& pairVal : mat2Prop[column]) {
                    res[row][pairVal.first] += val * pairVal.second;
                }
            }
        }
        
        return res;
    }
};*/


/* #386. Lexicographical Numbers *//*
class Solution {
    int num = 10;
    
    void probeDFS(int n, int curr, vector<int>& res){
        if (curr <= n) res.push_back(curr);
        else return;
        probeDFS(n, curr * 10, res);
        if (curr % 10 == 0){
            for (int i = 1; i < num; ++i) {
                if (res.size() == n) return;
                if (curr + i > n) return;
                probeDFS(n, curr + i, res);
            }
        }
    }
    
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        res.reserve(n);
        
        for (int i = 1; i < num; ++i) {
            probeDFS(n, i, res);
        }
        return res;
    }
};*/

/* #543. Diameter of Binary Tree (Similar to 124*//*
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
class Solution {
    int getDepth(TreeNode* node, int& maxDia){
        if (!node) return 0;
        if (!node->left && !node->right) return 0;
        int right = 0;
        int left = 0;
        if (node->left) right = 1 + getDepth(node->left, maxDia);
        if (node->right) left = 1 + getDepth(node->right, maxDia);
        maxDia = max(maxDia, right + left);
        return max(right, left);
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDia = 0;
        getDepth(root, maxDia);
        return maxDia;
    }
};*/


/* #622. Design Circular Queue *//*
class MyCircularQueue {
private:
    int *queue;
    int capacity;
    int size;
    int head;
    int tail;
    
    bool empty(){
        return size == 0;
    }
    
    bool full(){
        return capacity == size;
    }
    
    void increment(int& place){
        if (place == capacity - 1) place = 0;
        else place += 1;
    }
    
    void decrement(int& place){
        if (place == 0) place = capacity - 1;
        else --place;
    }
    
public:
    MyCircularQueue(int k) : queue(new int[k]), capacity(k), head(0), tail(0), size(0) {}
    
    bool enQueue(int value) {
        if (full()) return false;
        if (!empty()) increment(tail);
        queue[tail] = value;
        ++size;
        return true;
    }
    
    bool deQueue() {
        if (empty()) return false;
        --size;
        if (empty()) head = tail = 0;
        else increment(head);
        return true;
    }
    
    int Front() {
        if (empty()) return -1;
        else return queue[head];
    }
    
    int Rear() {
        if (empty()) return -1;
        else return queue[tail];
    }
    
    bool isEmpty() {
        return empty();
    }
    
    bool isFull() {
        return full();
    }
    
    ~MyCircularQueue(){
        delete []queue;
    }
};*/

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */


/* #785. Is Graph Bipartite? *//*
class Solution {
    int *setMark;
    
    bool hasMaked(int vertex){
        return setMark[vertex] != -1;
    }
    
    int getSet(int vertex) {
        return setMark[vertex];
    }
    
    void setSetInd(int vertex, int set){
        setMark[vertex] = set;
    }
    
    bool dfs(int vertex, const vector<vector<int>>& graph, int setInd){
        setSetInd(vertex, setInd);
        for (int adjacentVertex : graph[vertex]){
            // if conflict
            if (hasMaked(adjacentVertex)){
                if (getSet(adjacentVertex) == setInd) return false;
            }
            else if (!dfs(adjacentVertex, graph, 1 - setInd)) return false;
        }
        return true;
    }
    
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int mark[graph.size()];
        setMark = mark;
        // initialize all pts to -1, indicating that they are not assigned to a specifix set
        for (int i = 0; i < graph.size(); ++i) {
            mark[i] = -1;
        }
        
        // DFS
        for (int i = 0; i < graph.size(); ++i) {
            if (hasMaked(i)) continue;
            if (graph[i].empty()) continue;
            if (!dfs(i, graph, 0)) return false;
        }
        return true;
    }
};*/


/* #4. Median of Two Sorted Arrays *//* According to the post in discussion, the
                                      problem can be converted to one using binary search to find i and j such that A[i] <= B[j + 1]
                                      B[j] < A[i + 1] and i + j + 2 == numEle / 2 */
// in python3
/*
class Solution:
def findMedianSortedArrays(self, A: List[int], B: List[int]) -> float:
    m, n = len(A), len(B)
    if m > n:
        A, B, m, n = B, A, n, m
    if n == 0:
        raise ValueError

    imin, imax, half_len = 0, m, int((m + n + 1) / 2)
    while imin <= imax:
        i = int((imin + imax) / 2)
        j = half_len - i
        if i < m and B[j-1] > A[i]:
            # i is too small, must increase it
            imin = i + 1
        elif i > 0 and A[i-1] > B[j]:
            # i is too big, must decrease it
            imax = i - 1
        else:
            # i is perfect

            if i == 0: max_of_left = B[j-1]
            elif j == 0: max_of_left = A[i-1]
            else: max_of_left = max(A[i-1], B[j-1])

            if (m + n) % 2 == 1:
                return max_of_left

            if i == m: min_of_right = B[j]
            elif j == n: min_of_right = A[i]
            else: min_of_right = min(A[i], B[j])

            return (max_of_left + min_of_right) / 2.0 */

/* #297. Serialize and Deserialize Binary Tree *//*
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};*/


/* Method 1: use an array and show all the nullptr
class Codec {
private:
    string nullS{"null"};
    
    bool hasChild(TreeNode* node){
        if (!node) return false;
        return node->left || node->right;
    }
    
    void writeSS(stringstream& ss, TreeNode* node){
        ss << " ";
        if (!node) ss << nullS;
        else ss << node->val;
    }
    
    // return true on success; return false if a nullptr is met
    TreeNode* getNode(const string s){
        if (s == nullS) return nullptr;
        return new TreeNode(stoi(s));
    }
    
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return string();
        
        bool hasNextLevel = false;
        if (hasChild(root)) hasNextLevel = true;
        stringstream ss;
        ss << root->val;
        deque<TreeNode*> bfsTraverse;
        bfsTraverse.push_back(root);
        int count = 1;
        
        while (hasNextLevel) {
            hasNextLevel = false;
            for (int i = 0; i < count; ++i) {
                TreeNode* curr = bfsTraverse.front();
                bfsTraverse.pop_front();
                if (!curr){
                    bfsTraverse.push_back(nullptr);
                    writeSS(ss, nullptr);
                    bfsTraverse.push_back(nullptr);
                    writeSS(ss, nullptr);
                }
                else {
                    bfsTraverse.push_back(curr->left);
                    bfsTraverse.push_back(curr->right);
                    writeSS(ss, curr->left);
                    writeSS(ss, curr->right);
                    if (!hasNextLevel){
                        if (hasChild(curr->left) || hasChild(curr->right)) hasNextLevel = true;
                    }
                }
                
            }
            count *= 2;
        }
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string word;
        // read the root
        TreeNode* root = nullptr;
        if (ss >> word) root = getNode(word);
        if (!root) return root;
        
        // dfs
        deque<TreeNode*> lastLevel;
        lastLevel.push_back(root);
        while (ss >> word) {
            TreeNode* last = lastLevel.front();
            lastLevel.pop_front();
            if (!last){
                if(! (ss >> word)) return root;
                lastLevel.push_back(nullptr);
                lastLevel.push_back(nullptr);
            }
            else {
                last->left = getNode(word);
                // right child
                if (ss >> word) last->right = getNode(word);
                else return root;
                lastLevel.push_back(last->left);
                lastLevel.push_back(last->right);
            }
        }
        
        return root;
    }
};*/

/* Method 2: when encoutering a nullptr, stop tracking it.*//*
class Codec {
private:
    string nullS{"null"};
    
    void writeSS(stringstream& ss, TreeNode* node){
        ss << " ";
        if (!node) ss << nullS;
        else ss << node->val;
    }
    
    // return true on success; return false if a nullptr is met
    void getNode(const string s, TreeNode*& node){
        if (s == nullS) node = nullptr;
        else node = new TreeNode(stoi(s));
    }
    
    
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return string();
        
        stringstream ss;
        ss << root->val;
        deque<TreeNode*> bfsTraverse;
        bfsTraverse.push_back(root);
        
        while (!bfsTraverse.empty()) {
            TreeNode*  curr = bfsTraverse.front();
            bfsTraverse.pop_front();
            if (curr->left) bfsTraverse.push_back(curr->left);
            if (curr->right) bfsTraverse.push_back(curr->right);
            writeSS(ss, curr->left);
            writeSS(ss, curr->right);
        }
        
        return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string word;
        // read the root
        TreeNode* root = nullptr;
        if (ss >> word) getNode(word, root);
        if (!root) return root;
        
        // dfs
        deque<TreeNode*> bfsTraverse;
        bfsTraverse.push_back(root);
        while (!bfsTraverse.empty()) {
            TreeNode* curr = bfsTraverse.front();
            bfsTraverse.pop_front();
            if (ss >> word) getNode(word, curr->left);
            else break;
            if (ss >> word) getNode(word, curr->right);
            else break;
            
            if (curr->left) bfsTraverse.push_back(curr->left);
            if (curr->right) bfsTraverse.push_back(curr->right);
        }
        
        return root;
    }
};*/

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));


/* #1358. Number of Substrings Containing All Three Characters (Sliding Window)*//*
class Solution {
    int count[3];
    int numAll = 0;
    
    int getCount(char c){
        return count[c - 'a'];
    }
    
    int hasAll(){
        return count[0] > 0 && count[1] > 0 && count[2] > 0;
    }
    
    void increment(char c){
        ++count[c - 'a'];
    }
    
    void decrement(char c){
        --count[c - 'a'];
    }
    
public:
    Solution(){
        for (int i = 0; i < 3; ++i) {
            count[i] = 0;
        }
    }
    
    int numberOfSubstrings(string s) {
        int end = 0;
        while(end < s.size()) {
            increment(s[end]);
            if (hasAll()){
                numAll += int(s.length()) - end;
                break;
            }
            ++end;
        }
        
        if (!hasAll()) return numAll;
        
        for (int start = 1; start < s.length() - 2; ++start) {
            decrement(s[start - 1]);
            if (getCount(s[start - 1]) > 0){
                numAll += int(s.length()) - end;
                continue;
            }
            
            while (end < s.size() - 1) {
                ++end;
                increment(s[end]);
                if (s[start - 1] == s[end]){
                    numAll += int(s.length()) - end;
                    break;
                }
            }
            
            if (!hasAll()) return numAll;
        }
        
        return numAll;
    }
};*/


/* Longest Palindromic Substring *//*
class Solution {
private:
    int longestLen = 1;
    int start = 0;
    
public:
    string longestPalindrome(string s) {
        for (int middle = 0; middle < s.length() + 1 - longestLen / 2; ++middle){
            // search for odd length palidrome
            int length = 1;
            int startTemp = middle;
            int endTemp = middle;
            while (startTemp > 0 && endTemp < s.length() - 1){
                if (s[startTemp - 1] == s[endTemp + 1]){
                    --startTemp;
                    ++endTemp;
                    length += 2;
                }
                else break;
            }
            if (length > longestLen){
                longestLen = length;
                start = startTemp;
            }
            
            // search for even length palidrome
            if (middle + 1 == s.length()) break;
            if (s[middle] != s[middle + 1]) continue;
            length = 2;
            startTemp = middle;
            endTemp = middle + 1;
            while (startTemp > 0 && endTemp < s.length() - 1){
                if (s[startTemp - 1] == s[endTemp + 1]){
                    --startTemp;
                    ++endTemp;
                    length += 2;
                }
                else break;
            }
            if (length > longestLen){
                longestLen = length;
                start = startTemp;
            }
        }
        
        return s.substr(start, longestLen);
    }
};*/

/* Trapping Rain Water*/
/* class Solution {
private:
    vector<int> waterHeight;
    //height as the key and positions as the value
    map<int, vector<int>> sortedHeight;
    
    //return false if no greatest height available
    bool getGreatestHeight(int &indHeight){
        if(sortedHeight.empty()) return false;
        auto it = sortedHeight.begin();
        indHeight = it->second.back();
        //clean vector
        it->second.pop_back();
        //cleam map
        if(it->second.empty()) sortedHeight.erase(it);
        return true;
    }
    
    void markHeight(int &indBegin, int &indEnd, vector<int>& heights){
        int height = min(heights[indBegin], heights[indEnd]);
        if(indBegin > indEnd) swap(indBegin, indEnd);
        for(int i = indBegin + 1; i < indEnd; ++i){
            waterHeight[i] = height - heights[i];
        }
    }
    
public:
    int trap(vector<int>& height) {
        if(height.size() < 3) return 0;
        //at least 3 integers
        waterHeight.resize(height.size());
        for(int i = 0; i < height.size(); ++i){
            sortedHeight[-1 * height[i]].push_back(i);
        }
        
        int indOfGreatest1, indOfGreaatest2, transition;
        assert(getGreatestHeight(indOfGreatest1));
        assert(getGreatestHeight(indOfGreaatest2));
        markHeight(indOfGreatest1, indOfGreaatest2, height);
        //iterate
        while(getGreatestHeight(transition)){
            if (transition < indOfGreatest1) {
                markHeight(transition, indOfGreatest1, height);
                indOfGreatest1 = transition;
            }
            else if(transition > indOfGreaatest2){
                markHeight(indOfGreaatest2, transition, height);
                indOfGreaatest2 = transition;
            }
            else continue;
        }
        //calculate
        return accumulate(waterHeight.begin(), waterHeight.end(), 0);
        }
};*/

/*
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() < 3) return 0;
        int leftInd = 0;
        int rightInd = int(height.size() - 1);
        int waterHeight = min(height[leftInd], height[rightInd]);
        int result = 0;
        while (leftInd < rightInd) {
            if (height[leftInd] < height[rightInd]){
                ++leftInd;
                if (height[leftInd] < waterHeight) result += waterHeight - height[leftInd];
                else waterHeight = min(height[leftInd], height[rightInd]);
            }
            else{
                --rightInd;
                if (height[rightInd] < waterHeight) result += waterHeight - height[rightInd];
                else waterHeight = min(height[leftInd], height[rightInd]);
            }
        }
        
        return result;
    }
};*/


/* Set Matrix Zeroes*//*
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool firstRow = false;
        bool firstColumn = false;
        for (int row = 0; row < matrix.size(); ++row){
            for (int column = 0; column < matrix[0].size(); ++column){
                if (matrix[row][column] == 0){
                    if (!firstRow && row == 0) firstRow = true;
                    if (!firstColumn && column == 0) firstColumn = true;
                    matrix[row][0] = 0;
                    matrix[0][column] = 0;
                }
            }
        }
        
        // check row and column
        for (int row = 1; row < matrix.size(); ++row) {
            if (matrix[row][0] == 0){
                for (int column = 1; column < matrix[0].size(); ++column) {
                    matrix[row][column] = 0;
                }
            }
        }
        
        for (int column = 1; column < matrix[0].size(); ++column) {
            if (matrix[0][column] == 0){
                for (int row = 1; row < matrix.size(); ++row) {
                    matrix[row][column] = 0;
                }
            }
        }
        
        if (firstColumn){
            for (int row = 0; row < matrix.size(); ++row) {
                matrix[row][0] = 0;
            }
        }
        
        if (firstRow){
            for (int column = 0; column < matrix[0].size(); ++column) {
                matrix[0][column] = 0;
            }
        }
    }
};*/

/*Rotate Image*//*
class Solution {
private:
    int sizeOfMatrix = 0;
    
    void roatateCoor(const pair<int, int>& origin, pair<int, int> &coor, int rowInd){
        if(origin.first == rowInd){
            coor.first = origin.second;
            coor.second = sizeOfMatrix - rowInd - 1;
        }
        else if(origin.first == sizeOfMatrix - rowInd - 1){
            coor.first = origin.second;
            coor.second = rowInd;
        }
        else if(origin.second == rowInd){
            coor.first = rowInd;
            coor.second = sizeOfMatrix - origin.first - 1;
        }
        else{
            coor.first = origin.second;
            coor.second = sizeOfMatrix - origin.first - 1;
        }
    }
    
    void recur(vector<vector<int>>& matrix, int layer){
        if(layer < 2) return;
        int rowInd = (int(matrix.size()) - layer) / 2;
        for(int i = 0; i < layer - 1; ++i){
            pair<int, int> coor;
            pair<int, int> origin(rowInd, rowInd + i);
            int transit = matrix[origin.first][origin.second];

            for(int count = 0; count < 4; ++count){
                roatateCoor(origin, coor, rowInd);
                int thisOne = matrix[coor.first][coor.second];
                matrix[coor.first][coor.second] = transit;
                transit = thisOne;
                origin = coor;
            }
        }
        
        recur(matrix, layer - 2);
    }
    
    
public:
    void rotate(vector<vector<int>>& matrix) {
        sizeOfMatrix = int(matrix.size());
        recur(matrix, sizeOfMatrix);
    }
};*/

/* Spiral Matrix*//*
class Solution {
private:
    int numRow = 0;
    int numCol = 0;
    
    void fill(vector<vector<int>>& matrix, vector<int>& result, vector<int>::iterator start, int rowInd){
        //base case
        if(2 * rowInd == numRow) return;
        
        //spiral assignment
        //row1
        for(int i = rowInd; i < numCol - rowInd; ++i){
            *start = matrix[rowInd][i];
            ++start;
        }
        //column1
        for(int j = rowInd + 1; j < numRow - rowInd; ++j){
            *start = matrix[j][numCol - rowInd - 1];
            ++start;
        }
        //end
        if(start == result.end()) return;
        //row2
        for(int i = numCol - 2 - rowInd; i >= rowInd; --i){
            *start = matrix[numRow - 1 - rowInd][i];
            ++start;
        }
        //column2
        for(int j = numRow - 2 - rowInd; j > rowInd; --j){
            *start = matrix[j][rowInd];
            ++start;
        }
        //end
        if(start == result.end()) return;
        //recur
        fill(matrix, result, start, rowInd + 1);
    }
    
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        numRow = matrix.size();
        numCol = matrix[0].size();
        vector<int> results(numRow * numCol);
        fill(matrix, results, results.begin(), 0);
        
        return results;
    }
};*/

/*  Reverse Linked List*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Iterative Method
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        ListNode* reversed = head;
        head = head->next;
        reversed->next = nullptr;
        while (head) {
            ListNode* temp = head->next;
            head->next = reversed;
            reversed = head;
            head = temp;
        }
        return reversed;
    }
};*/

/* Recursion Method *//*
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        if (!head->next) return head;
        ListNode* reveredHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return reveredHead;
    }
};*/

/* Linked List Cycle *//*
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode* slow = head;
        ListNode* fast = head;
        fast = fast->next;
        while (fast) {
            if (fast == slow) return true;
            fast = fast->next;
            if (!fast) return false;
            fast = fast->next;
            slow = slow->next;
        }
        return false;
    }
};*/

/* Add Two Numbers *//*
class Solution {
private:
    bool greater10 = false;

    ListNode* add(ListNode* l1, ListNode* l2){
        int sum = l1->val + l2->val + int(greater10);
        if (sum > 9) {
            greater10 = true;
            sum -= 10;
        }
        else greater10 = false;
        return new ListNode(sum);
    }
    
    ListNode* add(ListNode* l){
        if (l->val == 9 && greater10){
            return new ListNode(0);
        }
        else{
            int sum = l->val + int(greater10);
            greater10 = false;
            return new ListNode(sum);
        }
    }
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode* resNode = nullptr;
        while (l1 && l2) {
            if (!head){
                head = add(l1, l2);
                resNode = head;
            }
            else {
                resNode->next = add(l1, l2);
                resNode = resNode->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        
        if (!l1 && !l2){
            if (greater10) resNode->next = new ListNode(1);
        }
        else{
            if (!l1) l1 = l2;
            while (l1){
                resNode->next = add(l1);
                l1 = l1->next;
                resNode = resNode->next;
            }
            if (greater10) resNode->next = new ListNode(1);
        }
        return head;
    }
};*/


/* Add Two Numbers II*//*
class Solution {
private:
    bool greater10 = false;
    
    ListNode* reverse(ListNode* l){
        if (!l) return l;
        if (!l->next) return l;
        ListNode* reversed = l;
        l = l->next;
        reversed->next = nullptr;
        
        while(l){
            ListNode* temp = l->next;
            l->next = reversed;
            reversed = l;
            l = temp;
        }
        return reversed;
    }
    
    ListNode* add(ListNode* l1, ListNode* l2){
        assert(l1);
        assert(l2);
        int sum = l1->val + l2->val + int(greater10);
        if (sum > 9){
            greater10 = true;
            sum -= 10;
        }
        else greater10 = false;
        return new ListNode(sum);
    }
    
    ListNode* add(ListNode* l){
        if (l->val == 9 && greater10) return new ListNode(0);
        else {
            int sum = l->val + int(greater10);
            greater10 = false;
            return new ListNode(sum);
        }
    }
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1 && !l2) return nullptr;
        if (!l1) return l2;
        if (!l2) return l1;
        
        l1 = reverse(l1);
        l2 = reverse(l2);
        ListNode* head = nullptr;
        ListNode* iterNode = head;
        while (l1 && l2){
            if (!head){
                head = add(l1, l2);
                iterNode = head;
            }
            else {
                iterNode->next = add(l1, l2);
                iterNode = iterNode->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        
        if (!l1 && !l2);
        else{
            if (!l1) swap(l1, l2);
            while (l1){
                iterNode->next = add(l1);
                iterNode = iterNode->next;
                l1 = l1->next;
            }
        }
        
        if (greater10){
            iterNode->next = new ListNode(int(greater10));
            greater10 = false;
        }

        return reverse(head);
    }
};*/


/* Merge Two Sorted Lists*//*
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l2 == nullptr) return l1;
        if(l1 == nullptr) return l2;
        
        ListNode* head;
        ListNode* main;
        ListNode* other;
        if(l1->val < l2->val) {
            head = main = l1;
            other = l2;
        }
        else {
            head = main = l2;
            other = l1;
        }
        
        while(main->next != nullptr && other != nullptr){
            if(other->val < (main->next)->val){
                ListNode* next = main->next;
                main->next = other;
                other = other->next;
                (main->next)->next = next;
                main = main->next;
            }
            else if(other->val >= (main->next)->val){
                main = main->next;
            }
        }
        
        if(main->next == nullptr){
            main->next = other;
        }
               
        return head;
    }
};*/

/* Merge k Sorted Lists *//*
class Solution {
private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l2 == nullptr) return l1;
        if(l1 == nullptr) return l2;
        
        ListNode* head;
        ListNode* main;
        ListNode* other;
        if(l1->val < l2->val) {
            head = main = l1;
            other = l2;
        }
        else {
            head = main = l2;
            other = l1;
        }
        
        while(main->next != nullptr && other != nullptr){
            if(other->val < (main->next)->val){
                ListNode* next = main->next;
                main->next = other;
                other = other->next;
                (main->next)->next = next;
                main = main->next;
            }
            else if(other->val >= (main->next)->val){
                main = main->next;
            }
        }
        
        if(main->next == nullptr){
            main->next = other;
        }
               
        return head;
    }
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        deque<ListNode*> queueList(lists.begin(), lists.end());
        while(queueList.size() != 1){
            ListNode* l1 = queueList.back();
            queueList.pop_back();
            ListNode* l2 = queueList.back();
            queueList.pop_back();
            queueList.push_front(mergeTwoLists(l1, l2));
        }
        
        return queueList.front();
    }
};*/

/* Intersection of Two Linked Lists*//*
class Solution {
private:
    int getSize(ListNode* head){
        int size = 0;
        while (head) {
            head = head->next;
            ++size;
        }
        return size;
    }
    
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int sizeA = getSize(headA);
        int sizeB = getSize(headB);
        // set headA to be the one of greater size
        if (sizeA < sizeB) {
            swap(headA, headB);
            swap(sizeA, sizeB);
        }
        for (int i = 0; i < sizeA - sizeB; ++i) {
            headA = headA->next;
        }
        while (headA) {
            if (headB == headA) return headB;
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;
    }
};*/

/* #138 Copy List with Random Pointer: there is a very clever way as explained in the solution #3 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
/*
class Solution {
private:
    // key: node in the originial list; value: node in the new list
    unordered_map<Node*, Node*> dict;
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        if (dict.find(head) != dict.end()) return dict[head];
        Node* newHead = new Node(head->val);
        dict[head] = newHead;
        newHead->random = copyRandomList(head->random);
        newHead->next = copyRandomList(head->next);
        return newHead;
    }
};*/

/* Validate Binary Search Tree */
/**
 * Definition for a binary tree node.*/
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 /*
class Solution {
private:
    bool hadINTMIN = false;
    bool hadINTMAX = false;
    
    bool isValidRecur(TreeNode *root, int upperbound, int lowerbound){
        if (root == nullptr) return true;
        //check upperbound
        if (upperbound != INT_MAX && root->val >= upperbound) return false;
        else if (upperbound == INT_MAX && hadINTMAX && root->val == INT_MAX) return false;
        if (root->val == INT_MAX) hadINTMAX = true;
        //check lowerbound
        if (lowerbound != INT_MIN && root->val <= lowerbound) return false;
        else if (lowerbound == INT_MIN && hadINTMIN && root->val == INT_MIN) return false;
        if (root->val == INT_MIN) hadINTMIN = true;
        
        return isValidRecur(root->left, min(root->val, upperbound), lowerbound) && isValidRecur(root->right, upperbound, max(root->val, lowerbound));
    }
    
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->val == INT_MIN) hadINTMIN = true;
        else if (root->val == INT_MAX) hadINTMAX = true;
        return isValidRecur(root->left, root->val, INT_MIN) && isValidRecur(root->right, INT_MAX, root->val);
    }
};*/



/* -------------------
                                -----TreeTraversal -------------
                                                                            -----------------*/

/*  Binary Tree Inorder Traversal *//*
class Solution {

public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> Stack;
        vector<int> nums;
        
        while (root) {
            Stack.push(root);
            root = root->left;
        }
        
        while (!Stack.empty()) {
            TreeNode* current = Stack.top();
            Stack.pop();
            nums.push_back(current->val);
            if (current->right) {
                current = current->right;
                while (current) {
                    Stack.push(current);
                    current = current->left;
                }
            }
        }
        
        return nums;
    }
};*/


/* Lowest Common Ancestor of a Binary Search Tree *//*
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //set p to be smaller than q
        if (p->val > q->val) swap(p, q);
        // base cases
        if (!root) return nullptr;
        if (root == p) return root;
        if (root == q) return root;
        if (root->val > p->val && root->val < q->val) return root;
        
        // recursive step
        if (root->val < p->val) return lowestCommonAncestor(root->right, p, q);
        else return lowestCommonAncestor(root->left, p, q);
    }
};*/


/* Lowest Common Ancestor of a Binary Tree */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/*
class Solution {
private:
    bool findPath(TreeNode* root, TreeNode* target, deque<TreeNode*>& path){
        // base case
        if (root == target){
            path.push_back(root);
            return true;
        }
        if (!root) return false;
        
        // recursive step
        path.push_back(root);
        if (findPath(root->left, target, path)) return true;
        if (findPath(root->right, target, path)) return true;
        path.pop_back();
        return false;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q) return root;
        deque<TreeNode*> pathP;
        deque<TreeNode*> pathQ;
        if (!findPath(root, p, pathP)) return nullptr;
        if (!findPath(root, q, pathQ)) return nullptr;
        
        TreeNode* lcA = nullptr;
        while (pathP.front() == pathQ.front()){
            lcA = pathP.front();
            pathP.pop_front();
            pathQ.pop_front();
            if (pathP.empty() || pathQ.empty()) break;
        }
        return lcA;
    }
};*/


/* #208 Implement Trie (Prefix Tree) *//*
class Trie {
private:
    class TrieNode{
    private:
        TrieNode* nodeTable[26];
        bool exist = false;
        
        void recurDelete(TrieNode** table){
            for (int i = 0; i < 26; ++i){
                if (table[i]){
                    recurDelete(table[i]->nodeTable);
                    delete table[i];
                    table[i] = nullptr;
                }
            }
        }
        
        TrieNode** putChar(TrieNode** curTable, char c, bool isLast){
            if (!curTable[c - 'a']) curTable[c - 'a'] = new TrieNode(isLast);
            else if (isLast) curTable[c - 'a']->exist = true;
            return curTable[c - 'a']->nodeTable;
        }
        
    
    public:
        TrieNode(){
            for (int i = 0; i < 26; ++i) nodeTable[i] = nullptr;
        }
        
        TrieNode(bool isLast) : exist(isLast){
            for (int i = 0; i < 26; ++i) nodeTable[i] = nullptr;
        }
        
        void insert(const string& word){
            TrieNode** curr = nodeTable;
            for (int i = 0; i < word.size(); ++i){
                curr = putChar(curr, word[i], i == int(word.size()) - 1);
            }
        }
        
        // return nullptr if not found
        TrieNode* find(const string& word){
            TrieNode* curr = this;
            for (char c : word){
                if (curr->nodeTable[c - 'a']) curr = curr->nodeTable[c - 'a'];
                else return nullptr;
            }
            return curr;
        }
        
        bool hasPrefix(){
            if (exist) return true;
            for (int i = 0; i < 26; ++i){
                if (nodeTable[i]) return true;
            }
            return false;
        }
        
        bool exists(){ return exist;}
        
        void setExist(){exist = true;}
        
        TrieNode* nextNode(char c){ return nodeTable[c - 'a'];}
        
        ~TrieNode(){
            recurDelete(nodeTable);
        }
    };
    
    // member var
    TrieNode* root;
    
public:
    Trie() : root(new TrieNode) {}
    
    void insert(string word) {
        if (word.empty()) root->setExist();
        root->insert(word);
    }
    
    bool search(string word) {
        TrieNode* nodePtr = root->find(word);
        if (!nodePtr) return false;
        return nodePtr->exists();
    }
    
    bool startsWith(string prefix) {
        TrieNode* nodePtr = root->find(prefix);
        if (!nodePtr) return false;
        return nodePtr->hasPrefix();
    }
    
    // recursively delete all the node
    ~Trie(){delete root;}
};*/



/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

/* WildCard matching*//*
class Solution {
private:
    bool isMatch(char c1, char c2){
        if (c2 == '?' || c2 == '*' || c2 == c1) return true;
        return false;
    }

public:
    bool isMatch(string s, string p) {
        if (s.empty() && p.empty()) return true;
        if (s.empty()){
            for (char c : p){
                if (c != '*') return false;
            }
            return true;
        }
        if (p.empty()) return false;
        
        vector<vector<bool>> dpTable(p.size(), vector<bool>(s.size(), false));
        // initialize
        for(int pInd = 0; pInd < p.size(); ++pInd){
            for (int sInd = 0; sInd < s.size(); ++sInd){
                if (pInd == 0 && sInd == 0){
                    if (isMatch(s[sInd], p[pInd])) dpTable[0][0] = true;
                    else return false;
                }
                else{
                    if (p[pInd] == '*'){
                        // sInd > 0
                        if (sInd != 0){
                            if (dpTable[pInd][sInd - 1]){
                                dpTable[pInd][sInd] = true;
                                continue;
                            }
                        }
                        if (pInd != 0){
                            if (dpTable[pInd - 1][sInd]){
                                dpTable[pInd][sInd] = true;
                                continue;
                            }
                        }
                        if (sInd != 0 && pInd != 0){
                            if (dpTable[pInd - 1][sInd - 1]){
                                dpTable[pInd][sInd] = true;
                                continue;
                            }
                        }
                    }
                    
                    if (isMatch(s[sInd], p[pInd])){
                        if (sInd != 0 && pInd != 0){
                            if (dpTable[pInd - 1][sInd - 1]){
                                dpTable[pInd][sInd] = true;
                            }
                        }
                        if (sInd == 0){
                            bool allStar = true;
                            for (int i = 0; i < pInd; ++i){
                                if (p[i] != '*') {
                                    allStar = false;
                                    break;
                                }
                            }
                            if (allStar) dpTable[pInd][sInd] = true;
                        }
                    }
                }
            }
        }
        
        return dpTable[p.size() - 1][s.size() - 1];
    }
};*/

/* Matrix Search*/
class Solution {
private:
    vector<vector<int>>* matrixPtr;
    int numRow;
    int numColumn;
    
    bool hasLeft(int column){return column != 0;}
    
    bool hasRight(int column){return column != numColumn - 1;}
    
    bool hasUp(int row){return row != 0;}
    
    bool hasDown(int row){return row != numRow - 1;}
    
    int getLeft(int row, int column){return (*matrixPtr)[row][column - 1];}
    
    int getRight(int row, int column){return (*matrixPtr)[row][column + 1];}
    
    int getUp(int row, int column){return (*matrixPtr)[row - 1][column];}
    
    int getDown(int row, int column){return (*matrixPtr)[row + 1][column];}
    
    int getVal(int row, int column){return (*matrixPtr)[row][column];}
    
    void moveRight(int& column){++column;}
    
    void moveLeft(int& column){--column;}
    
    void moveUp(int& row){--row;}
    
    void moveDown(int& row){++row;}
    
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        matrixPtr = &matrix;
        numRow = matrix.size();
        numColumn = matrix[0].size();
        
        int row = 0;
        int column = 0;
        while(1){
            int curr = getVal(row, column);
            if (curr == target) return true;
            if (curr < target){
                if (hasRight(column)){
                    if (getRight(row, column) <= target){
                        moveRight(column);
                        continue;
                    }
                }
                if (hasDown(row)){
                    if (getDown(row, column)){
                        moveDown(row);
                    }
                    else return false;
                }
                else return false;
            }
            else {
                if (hasLeft(column)){
                    if (getLeft(row, column) >= target){
                        moveLeft(column);
                        continue;
                    }
                    if (getUp(row, column)){
                        moveUp(row);
                    }
                    else return false;
                }
                else return false;
            }
        }
    }
};



int main(){
    Solution S;
    //vector<string> words{"zzyy","zy","zyy"};
    //vector<vector<char>> board{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    vector<int> nums{1, 1, 2};
    vector<vector<int>> matrix{{1,3,5,7},{10,11,16,20},{23,30,34,50}};
    S.searchMatrix(matrix, 13);
    
    return 0;
}
