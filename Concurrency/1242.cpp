#include <iostream>
// unordered_multiset here
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

class HtmlParser {
public:
    vector<string> getUrls(string url);
};

/* 1242. Web Crawler Multithreaded *//* use two threads */
class SolutionWith2Thread {
private:
    mutex mtx;
    condition_variable cv;
    unordered_set<string> crawledPages;
    unordered_set<string> uncrawledPages;
    string hostName;
    int crawlingThreads = 0;
    
    bool belongToHostName(const char& c) {
        return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || (c == '-') || (c == '.');
    }
    
    // agreement: url is in the format of "http://leetcode.com/problems"
    string parseHostName(const string& url) {
        assert(url.length() > 7);
        auto it = url.begin() + 7;
        int len = 0;
        
        while (it != url.end() && belongToHostName(*it)) {
            ++it;
            ++len;
        }
        return url.substr(7, len);
    }
    
    bool haveSameHostName(const string& s1) {
        return parseHostName(s1) == hostName;
    }
    
    bool stopWaiting() {
        return !uncrawledPages.empty() || crawlingThreads == 0;
    }
    
    bool hasNotCrawled(const string& url) {
        return crawledPages.find(url) == crawledPages.end();
    }
    
    bool notPlannedToSrawl(const string& url) {
        return uncrawledPages.find(url) == uncrawledPages.end();
    }
    
    void singleThreadCrawl(HtmlParser htmlParser) {
        while (1) {
            string url;
            // get next available url
            {
                unique_lock<mutex> lk(mtx);
                cv.wait(lk, [this]{return stopWaiting();});
                if (crawlingThreads == 0 && uncrawledPages.empty()) {
                    return;
                }
                assert(!uncrawledPages.empty());
                url = *uncrawledPages.begin();
                uncrawledPages.erase(uncrawledPages.begin());
                ++crawlingThreads;
            }
            
            // crawl
            vector<string> urls = htmlParser.getUrls(url);
            vector<string> validUrls;
            for (const auto& crawledUrl : urls) {
                if (haveSameHostName(crawledUrl) && hasNotCrawled(crawledUrl) && notPlannedToSrawl(crawledUrl)) {
                    validUrls.push_back(crawledUrl);
                }
            }
            
            mtx.lock();
            crawledPages.insert(url);
            cout << url << " has been crawled!\n";
            for (const auto& validUrl : validUrls) {
                uncrawledPages.insert(validUrl);
            }
            --crawlingThreads;
            cv.notify_all();
            mtx.unlock();
        }
    }
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        hostName = parseHostName(startUrl);
        uncrawledPages.insert(startUrl);
        
        thread t1(&Solution::singleThreadCrawl, this, htmlParser);
        thread t2(&Solution::singleThreadCrawl, this, htmlParser);
        
        t1.join();
        t2.join();
        
        return vector<string>(crawledPages.begin(), crawledPages.end());
    }
};

class SolutionWithMaximumThreads {
private:
    int thread_num;
    string hostname;
    queue<string> q;
    unordered_set<string> seen;
    int working = 0;
    bool done;
    mutex m;
    condition_variable cv;
    
    string extractHostName(string& url){
        int start = url.find('/') + 2;
        int end =  url.find('/', start);
        if(end == string::npos)
            return url.substr(start);
        return url.substr(start, end - start);
    }
    vector<thread> workers;
    
    // this a worker thread that will be doing tasks.
    void startWorker(HtmlParser* parser){
        while(true){
            unique_lock<mutex> ul(m);
            // wait until there are some tasks OR
            // we are done executing
            cv.wait(ul, [&](){
                return q.size() > 0 || done;
            });
            // if done, return.
            if(done)
                return;
            // indicate that this thread is in progress
            working++;
            string item = q.front(); q.pop();
            ul.unlock();
            // since getUrls can take a lot of time, release the lock.
            auto accessible = parser->getUrls(item);
            
            // acquire the lock and add tasks.
            ul.lock();
            for(auto& url : accessible){
                // if it has been seen already or the host name doesn't match, ignore it.
                if(seen.count(url) || extractHostName(url) != hostname)
                    continue;
                seen.insert(url);
                q.push(url);
            }
            working--;
            
            // IF
            //   1) no thread is processing
            //   2) no tasks are available even after executing this task
            // THEN we are done.
            if(working == 0 && q.empty()){
                done = true;
            }
            // notify all the threads either about finishing or about availability of tasks.
            cv.notify_all();
        }
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        // get the hostname for this url.
        // mark it as seen.
        hostname = extractHostName(startUrl);
        seen.insert(startUrl);
        done = false;
        // get number of supported threads
        thread_num = thread::hardware_concurrency();
        // push the first task to do.
        q.push(startUrl);
        
        // start bunch of worker threads.
        for(int i = 0; i < thread_num; i++){
            workers.emplace_back(&Solution::startWorker, this, &htmlParser);
        }
        
        // join those threads so that crawl is a blocking call
        for(auto &t : workers){
            t.join();
        }
        // return every unique processed string
        return vector<string>(seen.begin(), seen.end());
    }
};


