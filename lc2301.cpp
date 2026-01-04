#include "defaults.hpp"

class Solution {
    using CharMap = unordered_map<char, unordered_set<char>>;

    bool canTransform(const string& sub, const string& target,
                      const CharMap& charMap) {
        assert(sub.size() == target.size());

        for (int i = 0; i < sub.size(); i++) {
            if (sub[i] == target[i]) {
                continue;
            }

            auto it = charMap.find(sub[i]);

            if (it == charMap.end()) {
                return false;
            }

            if (it->second.find(target[i]) == it->second.end()) {
                return false;
            }
        }

        return true;
    }

public:
    bool matchReplacement(string s, string sub,
                          vector<vector<char>>& mappings) {
        CharMap charMap;

        for (const auto& mapping : mappings) {
            charMap[mapping[0]].insert(mapping[1]);
        }

        int subSize = sub.size();
        int n = s.size();

        for (int i = 0; i <= n - subSize; i++) {
            string target = s.substr(i, subSize);
            if (canTransform(sub, target, charMap)) {
                return true;
            }
        }

        return false;
    }
};
