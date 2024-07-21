void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int nums1I = m - 1;
    int nums2I = n - 1;
    int numsI = nums1Size - 1;

    while (nums2I >= 0) {
        if (nums1I >= 0 && nums1[nums1I] > nums2[nums2I]) {
            nums1[numsI--] = nums1[nums1I--];
        }
        else {
            nums1[numsI--] = nums2[nums2I--];
        }
    }
}