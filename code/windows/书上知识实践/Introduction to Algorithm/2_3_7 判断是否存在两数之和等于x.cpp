/*
Input:数组arr,数字x
Output:是否存在两数存在于arr,其和为x

方法一:
1.排序 o(nlogn)
2.遍历每个元素A[i],并用二分查找查找是否存在x-A[i]也在arr中,o(nlogn)

方法二:
1.构建arr2,大小和arr相等,每个元素arr2[i]=x-arr[i],o(n)
2.将arr和arr2合到一起,排序,判断是否存在相邻元素相等o(nlogn)
*/