class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        unordered_map<int, int> mp;
        for(const auto& elem : nums) 
            mp[elem] = elem;
        
        int y, best = 0;

        for(const auto &x: nums){
            if(mp.find(x -1) == mp.end()) {
                y = x + 1;
                while(mp.find(y)!=mp.end())
                    y++;
                best = max(best, y - x);
            }
        }

        return best;
    }

};
