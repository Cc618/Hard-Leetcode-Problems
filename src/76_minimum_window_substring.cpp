// - Question :
// Given s and t, two strings, return the minimum string of s
// containing all characters of t.
// - Example :
// s = "ADOBECODEBANC", t = "ABC", answer = "BANC"
// - Source :
// https://leetcode.com/problems/minimum-window-substring
// - Complexity :
// O(n * m) time, O(1) space, n = len(s), m = len(t)
// - Warning :
// C++17 code

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty())
            return "";

        // data[char] = amount of char within this window
        unordered_map<char, int> data;

        // Same as above but for t
        unordered_map<char, int> target;
        for (auto c : t)
            if (target.find(c) == target.end())
                target[c] = 1;
            else
                ++target[c];

        // Firstly, find an initial window [0, length)
        int length = 0;
        for (;; ++length) {
            // Update data
            if (data.find(s[length]) == data.end())
                data[s[length]] = 1;
            else
                data[s[length]]++;

            // Test whether we have the initial window
            for (auto const& [c, v] : target)
                if (data.find(c) == data.end() || data[c] < target[c])
                    goto invalidWindow;

            // The window is valid, break
            ++length;
            break;

        invalidWindow:;
            // Not found initial window
            if (length == s.size())
                return "";
        }

        if (length == 0)
            return s.substr(0, 1);

        // Start of the window
        int i = 0;
        int minLength = length;
        int minStart = 0;
        while (1) {
            bool isValid = true;
            for (auto const& [c, v] : target)
                if (data.find(c) == data.end() || data[c] < v) {
                    isValid = false;
                    break;
                }

            if (isValid) {
                if (length < minLength) {
                    minLength = length;
                    minStart = i;

                    // Can't do better
                    if (minLength == 1)
                        break;
                }

                // We can try to shorten the window by removing the leftmost
                // item
                data[s[i]]--;
                ++i;
                --length;
            } else {
                // Can't increase the size of the window
                if (i + length >= s.size())
                    break;

                // Add another item
                if (data.find(s[i + length]) == data.end())
                    data[s[i + length]] = 1;
                else
                    ++data[s[i + length]];

                ++length;
            }
        }

        return s.substr(minStart, minLength);
    }
};

int main() {
    auto s = Solution();

    // Should be BANC
    cout << s.minWindow("ADOBECODEBANC", "ABC") << endl;

    return 0;
}

