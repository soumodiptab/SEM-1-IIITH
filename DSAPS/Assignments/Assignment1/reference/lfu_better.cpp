class LFUCache {
public:
    
    LFUCache(int capacity) {
        cap = capacity;
        minFreq = 0;
    }
    
    int get(int key) {
        if (keyInfo.find(key) == keyInfo.end()) {
            return -1;
        }
        updateFreq(key);
        return keyInfo[key].first;
    }
    
    void put(int key, int value) {
        if (cap <= 0) {
            return;
        }
        if (keyInfo.find(key) != keyInfo.end()) {
            keyInfo[key].first = value;
            updateFreq(key);
            return;
        }
        // key does not exist before.
        if (keyInfo.size() == cap) {
            while (freqToKeys.find(minFreq) == freqToKeys.end() || freqToKeys[minFreq].size() == 0) {
                minFreq++;
            }
            int keyToRemove = *(freqToKeys[minFreq].begin());
            keyInfo.erase(keyToRemove);
            keyLocation.erase(keyToRemove);
            freqToKeys[minFreq].pop_front();
        }
        keyInfo[key] = {value, 1};
        freqToKeys[1].push_back(key);
        keyLocation[key] = prev(freqToKeys[1].end());
        minFreq = 1;
    }
    
private:
    int cap;
    int minFreq;
    // key to {value, frequency}
    unordered_map<int, pair<int, int>> keyInfo;
    unordered_map<int, list<int>::iterator> keyLocation;
    unordered_map<int, list<int>> freqToKeys;
    
    void updateFreq(int key) {
        int oldFreq = keyInfo[key].second;
        keyInfo[key].second++;
        list<int>::iterator oldIter = keyLocation[key];
        freqToKeys[oldFreq].erase(oldIter);
        if (freqToKeys[minFreq].size() == 0) {
            minFreq++;
        }
        freqToKeys[oldFreq+1].push_back(key);
        keyLocation[key] = prev(freqToKeys[oldFreq+1].end());
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */