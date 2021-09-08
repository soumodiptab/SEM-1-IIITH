class LFUCache {
public: 
    //keys_count_map stores the keys with its value and frequency as a pair ie., key -> {value, freq}
    //keys_count_map stores the different frequencies that has occured with the keys mapped to it in a list
    unordered_map<int, pair<int, int>> keys_count_map;
    map<int, list<int>> keys_freq_map;
    int cap = 0;
    LFUCache(int capacity) {
        cap = capacity;
    }
    int get(int key) {
        //if the key is found, increase it frequency by 1 in keys_count_map. Remove the key from 
        //the keys_freq_map where it was stored for the previous frequency count value. 
        //Store it again in the keys_freq_map mapped to the updated frequency count.
        
        if(keys_count_map.find(key) != keys_count_map.end()) {
            int count = keys_count_map[key].second;
            keys_count_map[key].second++;
            keys_freq_map[count].remove(key);
            keys_freq_map[count+1].push_back(key);
            if(keys_freq_map[count].size() == 0) keys_freq_map.erase(count);
            return keys_count_map[key].first;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(cap <= 0) return;
        //IF key is not found, check if the capacity is already full. If yes remove the first key from the beginning  
        //of the keys_freq_map which is the least frequently used. Remove the key from the keys_count_map also.
        //ELSE update the key value in keys_count_map and increase its frequency by 1. Now remove the key from 
        //the old count value in the keys_freq_map and add the key again to the updated frequency count map.
        
        if(keys_count_map.find(key) == keys_count_map.end()) {
            if(keys_count_map.size() == cap) {
                int least = keys_freq_map.begin()->second.front();
                keys_freq_map.begin()->second.pop_front();
                keys_count_map.erase(least);
            }
            keys_count_map[key] = {value, 1};
            keys_freq_map[1].push_back(key);
        }
        else {
            keys_count_map[key].first = value;
            int count = keys_count_map[key].second;
            keys_count_map[key].second++;
            keys_freq_map[count].remove(key);
            if(keys_freq_map[count].size() == 0) keys_freq_map.erase(count);
            keys_freq_map[count+1].push_back(key);
        }
    }
};