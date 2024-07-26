void moveZeroes(int* nums, int numsSize) {
    int startIndex = 0, endIndex = numsSize - 1;

    for (int endIndex = 0; endIndex < numsSize; endIndex++) {
        if (nums[endIndex] != 0) {
            int temp = nums[endIndex];
            nums[endIndex] = nums[startIndex];
            
        }
    }
}