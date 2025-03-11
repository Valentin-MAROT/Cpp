#include <iostream>
#include <cmath>
using namespace std;
class Second{
    private:
        int i;
    public:
        Second(int n):i(n){};
        Second():i(0){
            cout << "Second::default" << endl;
        };
        Second(const Second& s):i(s.i%60){
            cout << "Second::copy" << endl;
        };
        int getI() const{
            return i;
        }
        void setI(int n){
            i = n;
        }
        friend ostream& operator<<(std::ostream& os, const Second& s){
            os << s.i << "s";
            return os;
        }
        bool operator<(const Second& s){
            return i < s.i;
        }
        bool operator==(const Second& s){
            return i == s.i;
        }
};

class Minute{
    private:
        int i;
    public:
        Minute(int n):i(n){};
        Minute():i(0){
            cout << "Minute::default" << endl;
        };
        Minute(const Minute& m):i(m.i%60){
            cout << "Minute::copy" << endl;
        };
        Minute(const Second& s):i((s.getI()%3600)/60){
            cout << "Minute::second" << endl;
        };
        int getI() const{
            return i;
        }
        void setI(int n){
            i = n;
        }
        friend ostream& operator<<(std::ostream& os, const Minute& m){
            os << m.i << "m";
            return os;
        }
        bool operator<(const Minute& m){
            return i < m.i;
        }
        bool operator==(const Minute& m){
            return i == m.i;
        }
        Second seconds(){
            return Second(i*60);
        }
};

class Hour{
    private:
        int i;
    public:
        Hour(int n):i(n){};
        Hour():i(0){
            cout << "Hour::default" << endl;
        };
        Hour(const Hour& h):i(h.i%24){
            cout << "Hour::copy" << endl;
        };
        Hour(const Minute& m):i((m.getI()%1440)/60){
            cout << "Hour::minute" << endl;
        };
        Hour(const Second& s):i((s.getI()%86400)/3600){
            cout << "Hour::second" << endl;
        };
        int getI() const{
            return i;
        }
        void setI(int n){
            i = n;
        }
        friend ostream& operator<<(std::ostream& os, const Hour& h){
            os << h.i << "h";
            return os;
        }
        bool operator<(const Hour& h){
            return i < h.i;
        }
        bool operator==(const Hour& h){
            return i == h.i;
        }
        Minute minutes(){
            return Minute(i*60);
        }
};

class Time{
    private:
        int i;
    public:
        Time(int n):i(n){};
        Time():i(0){};
        Time(const Time& t):i(t.i%86400){
            cout << "Time::copy" << endl;
        };
        Time(const Hour& h):i(h.getI()*3600){
            cout << "Time::hour" << endl;
        };
        Time(const Minute& m):i(m.getI()*60){
            cout << "Time::minute" << endl;
        };
        Time(const Second& s):i(s.getI()){
            cout << "Time::second" << endl;
        };
        Time(const Minute& m, const Second& s):i(m.getI()*60+s.getI()){
            cout << "Time::minute,second" << endl;
        };
        Time(const Hour& h, const Minute& m):i(h.getI()*3600+m.getI()*60){
            cout << "Time::hour,minute" << endl;
        };
        Time(const Hour& h, const Minute& m,const Second& s):i(h.getI()*3600+m.getI()*60+s.getI()){
            cout << "Time::hour,minute,second" << endl;
        };
        int getI() const{
            return i;
        }
        void setI(int n){
            i = n;
        }
        friend ostream& operator<<(std::ostream& os, const Time& t){
            int h = t.i/3600;
            int m = (t.i%3600)/60;
            int s = t.i%60;
            os << h << "h" << m << "m" << s << "s";
            return os;
        }
        bool operator<(const Time& t){
            return i < t.i;
        }
        bool operator==(const Time& t){
            return i == t.i;
        }
        Hour hours(){
            return Hour(i/3600);
        }
        Minute minutes(){
            return Minute((i%3600)/60);
        }
        Second seconds(){
            return Second(i%60);
        }
        Time operator-(const Time& t){
            Time tmp(*this);
            if(tmp.i < t.i){
                return Time(t.i-tmp.i);
            }else{
                return Time(tmp.i-t.i);
            }
        }
};

int main(){
    Second s1(10);
    Second s2(20);
    Second s3(s1);
    Second s4;
    s4 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << (s1 < s2) << endl;
    cout << (s1 == s2) << endl;
    Minute m1(10);
    Minute m2;
    Minute m3(m1);
    m2 = m1;
    Minute m4(Second(3200));
    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;
    cout << m4 << endl;
    cout << (m1 < m2) << endl;
    cout << (m1 == m2) << endl;
    cout << m1.seconds() << endl;
    Hour h1(Second(7290));
    cout << h1 << endl;
    cout << h1.minutes().seconds() << endl;
    Time t1(Second(7290));
    cout << t1 << endl;
    Time t2(Hour(2),Minute(1),Second(31));
    cout << t2 << endl;
    cout << t2.hours() << endl;
    cout << t2.minutes() << endl;
    cout << t2.seconds() << endl;
    cout << t2-t1 << endl;
    cout << (t1 < t2) << endl;
    cout << (t1 == t2) << endl;


    return 0;
}