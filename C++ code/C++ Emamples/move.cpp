
struct Test {
    string s;
    int i;
    char c;
    long long l;
    char ch;
};

class Member {
private:
    string s;
public:
    Member(string& s): s(move(s)) {}
    
    Member(string&& s): s(s) {
        cout << "construct with string move\n";
    }
    
    Member(const Member& other) {
        cout << "Member's copy is called\n";
        s = other.s;
    }
    
    Member(Member&& other) {
        cout << "Member's copy is called with move\n";
        s = move(other.s);
        //other.s = "cleared";
    }
    
    Member operator=(const Member& other) {
        s = other.s;
        return *this;
    }
    
    Member operator=(Member&& other) {
        s = move(other.s);
        other.s = "cleared";
        return *this;
    }
    
    const string& getMessage() const {
        return s;
    }
    
    void set(char c, int index) {
        if (index >= s.size()) {
            return;
        }
        
        s[index] = c;
    }
    
    virtual void printClassName() const {
        cout << s << "\n";
    }
};

class Club : public Member {
private:
    string message;

public:
    Club(): Member("member message\n"), message("club message\n") {};
    
    void printClassName() const override {
        cout << message;
    }
};

int main() {
//    string s("message");
//    string c(move(s));
//    Member m(s);
//
//    cout << "create m1\n";
//    Member m1(m);
//    cout << m.getMessage() << "\n" << m1.getMessage() << "\n\n";
//
//    cout << "create m2\n";
//    s.push_back('o');
//    Member m2(move(s));
//    cout << m2.getMessage() << "\n";
//    s[0] = '1';
//    cout << m2.getMessage() << "\n";
//    m2.set('2', 0);
//    cout << m.getMessage() << " " << m1.getMessage() << " " << m2.getMessage() << "\n\n";
//
//    cout << "create n\n";
//    Member n(move(m));
//    cout << n.getMessage() << "\n";
//    cout << m.getMessage() << "\n";
//    Member* mem = new Club();
//    mem->printClassName();
    
    vector<int> nums{1,2,3};
    auto nums1 = move(nums);
    
    return 0;
}
