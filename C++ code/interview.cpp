#include <stdio.h>
#include <iostream>
#include <deque>
using namespace std;

class MyCircularQueue{
private:
    int* table;
    int startInd;
    int size;
    int capacity;
    
    int increment(int ind){
        if (ind == capacity - 1) return 0;
        else return ind + 1;
    }
    
    int getLastInd(){
        return (startInd + size - 1) % capacity;
    }
    
    
public:
    /* Constructor, set the size of the queue to be k. */
    MyCircularQueue(int k): table(new int[k]), startInd(0), size(0), capacity(k){};
    
    /* Get the front item from the queue. If the queue is empty, return -1. */
    int Front(){
        if (isEmpty()) return -1;
        else return table[startInd];
    }
    
    /* Get the last item from the queue. If the queue is empty, return -1.*/
    int Rear(){
        if (isEmpty()) return -1;
        return table[getLastInd()];
    }
    
    /* Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value){
        if (isFull()) return false;
        ++size;
        table[getLastInd()] = value;
        return true;
    }
    
    /*Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue(){
        if (isEmpty()) return false;
        --size;
        startInd = increment(startInd);
        return true;
    }
    
    /* Checks whether the circular queue is empty or not. */
    bool isEmpty(){return size == 0;}
    
    /* Checks whether the circular queue is full or not. */
    bool isFull(){return size == capacity;}
    
    ~MyCircularQueue(){delete [] table;}
};


extern long getTime();

class cpuTest{
private:
    long timeInterval = 5 * 60 * 1000;
    deque<pair<long, int>> loadQueue;
    double queueAvg = 0;
    
    void deleteQueue(){
        if (loadQueue.empty()) return;
        while (!loadQueue.empty()) {
            if (getTime() - loadQueue.front().second > timeInterval){
                // update avg
                if (loadQueue.size() == 1) queueAvg = 0;
                else queueAvg = (queueAvg * loadQueue.size() - loadQueue.front().first) / (loadQueue.size() - 1);
                // delete
                loadQueue.pop_front();
            }
            else break;
        }
    }
    
public:
    void record(int load){
        deleteQueue();
        // update average
        queueAvg = (queueAvg * loadQueue.size() + load) / (loadQueue.size() + 1);
        loadQueue.push_back(make_pair(getTime(), load));
    }
    
    double average(){
        deleteQueue();
        return queueAvg;
    }
};


class Calculate{
private:
    deque<double> numbers;
    deque<char> operators;
    
    bool isNumber(char c){
        if (int(c - '0') >= 0 && int(c - '0') <= 9) return true;
        return false;
    }
    
    bool isOperator(char c){
        if (c != '+' && c != '-' && c != '*' && c != '/') return false;
        return true;
    }
    
    void genStack(const string& s){
        bool prevIsNumber = false;
        for (int ind = 0; ind < s.length();) {
            if (s[ind] == ' ') {
                ++ind;
                continue;
            }
            if (!isNumber(s[ind]) && !isOperator(s[ind])) throw runtime_error("Invalid Input\n");
            if (isOperator(s[ind])){
                if (!prevIsNumber) throw runtime_error("Two operators in a row!\n");
                prevIsNumber = false;
                operators.push_back(s[ind]);
                ++ind;
            }
            // is number
            else{
                if (prevIsNumber) throw runtime_error("Two numbers in a row!\n");
                prevIsNumber = true;
                
                // range [ind, numberEnd]
                int numberEnd = ind;
                while (numberEnd < s.size()) {
                    if (numberEnd == s.size() - 1){
                        numbers.push_back(stoi(s.substr(ind, numberEnd - ind + 1)));
                        return;
                    }
                   
                    if (isNumber(s[numberEnd + 1])) ++numberEnd;
                    else {
                        numbers.push_back(stoi(s.substr(ind, numberEnd - ind + 1)));
                        ind = numberEnd + 1;
                        break;
                    }
                }
            }
        }
    }
    
    double operating(double num1, double num2, char c){
        if (c == '+') return num1 + num2;
        if (c == '-') return num1 - num2;
        if (c == '/') return num1 / num2;
        if (c == '*') return num1 * num2;
        throw runtime_error("Operator not valid\n");
    }
    
    bool priorTo(char c1, char c2){
        if ((c1 == '*' || c1 == '/')) return true;
        else if (c2 == '+' || c2 == '-') return true;
        return false;
    }
    
public:
    // input 1 + 2 * 3; 2 * 3 + 1; 2 * 2 * 4 + 1; 2 * 2 / 3
    double getResult(string s){
        numbers.clear();
        operators.clear();
        
        genStack(s);
        // stack operation
        while (!operators.empty()) {
            double subsequent = numbers.back();
            numbers.pop_back();
            double current = numbers.back();
            numbers.pop_back();
            char op = operators.back();
            operators.pop_back();
            
            if (operators.size() == 0){
                numbers.push_back(operating(current, subsequent, op));
                break;
            }
            if (priorTo(op, operators.back())){
                numbers.push_back(operating(current, subsequent, op));
            }
            else {
                char op2 = operators.back();
                operators.pop_back();
                double prev = numbers.back();
                numbers.pop_back();
                
                // push back
                numbers.push_back(operating(prev, current, op2));
                numbers.push_back(subsequent);
                operators.push_back(op);
            }
        }
        
        return numbers.front();
    }
};


int main(){
    Calculate c1;
    cout << "1 - 2 * 3 = " << c1.getResult("1 - 2 * 3") << "\n";
    cout << "2 *3 + 1 = " << c1.getResult("2 * 3 + 1") << "\n";
    cout << "3 + 2 * 2 + 4 * 6 / 3 = " << c1.getResult("3 + 2 * 2 + 4 * 6 / 3") << "\n";
    
    cout << "2 2*2 * 4 + 1 = " << c1.getResult("2 2*2 * 4 + 1 = ") << "\n";
    
    return 0;
}
