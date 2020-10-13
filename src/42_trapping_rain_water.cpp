// - Question :
// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.
// - Example :
// [0,1,0,2,1,0,1,3,2,1,2,1]
// Should return 6, the web page contains an image describing this example.
// - Source :
// https://leetcode.com/problems/trapping-rain-water

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 1)
            return 0;

        int peakPtr = 1;
        int n = 0;

        deque<int> peaks;
        peaks.push_back(0);

        // Push all non surrounded peaks
        while (peakPtr < height.size()) {
            // Place peakPtr where the level increases
            for (; peakPtr < height.size() &&
                    height[peakPtr - 1] >= height[peakPtr]; ++peakPtr);

            // Place peakPtr where the level decreases again
            for (; peakPtr < height.size() &&
                    height[peakPtr - 1] <= height[peakPtr]; ++peakPtr);

            // Remove last peaks if surrounded
            while (peaks.size() >= 2) {
                int last = peaks.back();
                peaks.pop_back();

                // Don't remove it
                if (!(height[peaks.back()] >= height[last] &&
                            height[last] <= height[peakPtr - 1])) {
                    peaks.push_back(last);
                    break;
                }
            }

            // Push next peak
            peaks.push_back(peakPtr - 1);
        }

        while (peaks.size() > 1) {
            // Add surface between start and end positions
            int start = peaks.front();
            peaks.pop_front();

            int end = peaks.front();

            int rainHeight = min(height[start], height[end]);
            while (start != end) {
                n += max(0, rainHeight - height[start]);
                ++start;
            }
        }

        return n;
    }
};

int main() {
    auto s = Solution();

    vector<vector<int>> tests = {
        {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},
        {5, 2, 1, 2, 1, 5},
        {8, 8, 1, 5, 6, 2, 5, 3, 3, 9},
    };

    // Should be 6, 14, 31
    for (auto test : tests)
        cout << s.trap(test) << endl;

    return 0;
}

