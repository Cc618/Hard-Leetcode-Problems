// - Question :
// Given a matrix, find the area of the largest rectangle composed of 1s.
// - Example :
// matrix = [["1","0","1","0","0"],
//           ["1","0","1","1","1"],
//           ["1","1","1","1","1"],
//           ["1","0","0","1","0"]]
// The answer is 6 (= 3 * 2)
// - Source :
// https://leetcode.com/problems/maximal-rectangle
// - Complexity :
// O(M * N) time, O(M) space (M is rows, N is columns)

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.size() == 0)
            return 0;

        // We scan the grid and create an histogram for each row
        int maxArea = 0;
        vector<int> hist(matrix[0].size(), 0);
        // Update histogram row by row
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j)
                if (matrix[i][j] == '1')
                    hist[j]++;
                else
                    hist[j] = 0;
            maxArea = max(maxArea, largestAreaHistogram(hist));
        }

        return maxArea;
    }

    // Returns the area of the largest rectangle in an histogram
    int largestAreaHistogram(vector<int>& heights) {
        if (heights.size() == 0)
            return 0;

        // Rectangle, start pos, height
        struct R { int pos, height; };

        // The rects[i-1].height < rects[i].height
        stack<R> rects;
        rects.push({ 0, heights[0] });

        int maxArea = heights[0];
        for (int i = 1; i < heights.size(); ++i) {
            if (heights[i] > rects.top().height)
                // We can create a new rectangle with the new height
                rects.push({i, heights[i]});
            else if (heights[i] < rects.top().height) {
                // Remove each higher rectangle
                R r;
                while (rects.size() > 0 && rects.top().height > heights[i]) {
                    r = R(rects.top());
                    // Find the area between r.pos and i - 1 included
                    maxArea = max(maxArea, r.height * (i - r.pos));

                    rects.pop();
                }

                // Push a rectangle that starts at the last higher rectangle
                // position with the new height
                r.height = heights[i];
                rects.push(r);
            }
        }

        // For each remaining rectangles of the stack, compute the area
        while (rects.size() > 0) {
            auto r = rects.top();
            rects.pop();

            maxArea = max(maxArea, r.height * ((int)heights.size() - r.pos));
        }

        return maxArea;
    }
};

int main() {
    vector<vector<char>> matrix = {{'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}};

    Solution s;

    // Should be 6
    cout << s.maximalRectangle(matrix) << endl;

    return 0;
}

