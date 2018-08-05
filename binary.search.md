# 二分查找与三分查找

## 二分查找

待查找 		x

​		【1， 2， 3， 4， 5， 6， 7， 8， 9】

​		    ↑				  ↑			       ↑

​		   min			mid			     max

min 是头指针；max是尾指针；mid=(min + max) / 2

调整：

* 如果arr[mid] < x, min = mid + 1
* 如果arr[mid] > x, max = mid - 1
* 如果arr[mid] == x, 找到结果

终止条件：

 		min >= max

### 二分查找--特殊情况1

待查找		最后那个1			<收益类问题>

​		【  【1， 1， 1， 1， ==1==， 0， 0， 0， 0， 0 】

​		    ↑				       ↑			            ↑

​		   min			     mid			         max

min 是==虚拟头指针==；max是尾指针；==mid=(min + max + 1) / 2==

调整：

- 如果     arr[mid] == 1,	         ==min = mid==
- 如果     arr[mid] != x,          max = mid - 1
- 如果     mid == max,        找到结果



### 二分查找--特殊情况2

待查找		第一个1 		<花费类问题>

​		 【0， 0， 0， 0， ==1==， 1， 1， 1， 1， 1】     】

​		    ↑				   ↑			                     ↑

​		   min			 mid		                  max

min 是头指针；max是==虚拟尾指针==；mid=(min + max) / 2

调整：

- 如果     arr[mid] == 1,	         min = mid + 1
- 如果     arr[mid] != x,          ==max = mid==
- 如果     mid == max,        找到结果





## 三分查找

求解凹函数或凸函数的极值问题

【L，R】 是查找范围

m1 是【L， R】的 1/3 处

m2 是 【L， R】的 2/3 处

调整：

* 如果 f[m1] < f[m2], L = m1
* 如果 f[m2] <= f[m1], R = m2
* 如果 | m1 - m2 | < exp，找到结果









```c
int BF(int A[], int ALen, int B[], int BLen, int M) {
	int low = 0;
	int high = ALen - 1;
	int am = 0;
	int bm = 0;
	while (low <= high) {
		//A中有am个数据小于或等于A[am]
		am = (high - low) / 2 + low;
		//为了保证A[m]为下中位值，则B中应该有M - am个数据小于或等于A[am]
		bm = M - am;

		//此时am大于M，表示A中小于A[am]的元素过多，需要减少
		if (bm < 0) {
			high = am - 1;
		}
        //此时A中已有M个元素小于或等于A[am]
        else if (bm == 0) {
            //此时B中所有的元素都大于或等于A[am]，满足条件
            if (A[am] <= B[bm]) {
                return am;
            }
            //此时小于A[am]的元素过多，需要减小am
            else {
                high = am - 1;
            }
        }
        //
        else if (bm > 0 && bm < BLen) {
            if (A[am] < B[bm - 1]) {
                low = am + 1;
            }
            else if (A[am] >= B[bm - 1] && A[am] <= B[bm]) {
                return am;
            }
            else {
                high = am - 1;
            }
        }
        //此时小于或等于A[am]的元素之多为BLen + am <= M
        else if (bm == BLen) {
            //B中所有元素都小于A[am]，此时有am+bm=M个元素小于或等于A[am]
            if (B[bm - 1] <= A[am]) {
                return am;
            }
            //小于A[am]的元素过少，需要增大am
            else {
                low = am + 1;
            }
        }
        //bm > BLen，此时小于或等于A[am]的元素的个数之多为BLen+am < M，需要增大am的大小
        else if (bm > BLen) {
            low = am + 1;
        }
	}
	return -1;
}
```



​    
```C
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int * A = nums1;
    int * B = nums2;
    int ALen = nums1Size;
    int BLen = nums2Size;

    int Median = floor((ALen + BLen - 1) / 2.0);

    int m1 = 0, m2 = 0;//下中位数和上中位数
    int res = -1;

    res = BF(A, ALen, B, BLen, Median);
    if (res != -1) {
        m1 = A[res];
        if ((ALen + BLen) % 2 == 0) {
            if (res + 1 >= ALen)
                m2 = B[Median - res];
            else if (Median - res >= BLen)
                m2 = A[res + 1];
            else {
                m2 = A[res + 1] < B[Median - res] ? A[res + 1] : B[Median - res];
            }
            return 0.5*(m1 + m2);
        }
        else
            return (double)m1;
    } else {
        res = BF(B, BLen, A, ALen, Median);
        m1 = B[res];
        if ((ALen + BLen) % 2 == 0) {
            if (res + 1 >= BLen)
                m2 = A[Median - res];
            else if (Median - res >= ALen)
                m2 = B[res + 1];
            else
                m2 = B[res + 1] < A[Median - res] ? B[res + 1] : A[Median - res];
            return 0.5*(m1 + m2);
        }
        else
            return (double)m1;
    }
}
```
