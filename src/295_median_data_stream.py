# - Question :
# Create a data structure which returns the median of elements we add to it.
# - Example :
# addNum(1)
# addNum(2)
# findMedian() -> 1.5
# addNum(3)
# findMedian() -> 2
# - Source :
# https://leetcode.com/problems/find-median-from-data-stream
# - Complexity :
# add : O(N) time, O(1) space. findMedian : O(1) time, O(1) space

class MedianFinder:
    def __init__(self):
        self.data = []

    def addNum(self, num: int) -> None:
        # Binary search (find only the place where num must go)
        low = 0
        top = len(self.data) - 1
        while low <= top:
            mid = low + (top - low) // 2
            if self.data[mid] == num:
                low = mid
                break
            if self.data[mid] < num:
                low = mid + 1
            else:
                top = mid - 1

        # Add num in data at the good position
        self.data.insert(low, num)

    def findMedian(self) -> float:
        # Find just the middle value(s) and make the mean
        n = len(self.data) // 2

        # If even
        if n * 2 == len(self.data):
            return (self.data[n - 1] + self.data[n]) / 2

        return self.data[n]

