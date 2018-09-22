# 字符串匹配算法(2)

## 字典树

![](/home/yu_dong/Pictures/2018-08-04 15-12-18屏幕截图.png)

* 红色节点： 当前节点独立成词
* 白色：不成词

![](/home/yu_dong/Pictures/2018-08-04 15-16-06屏幕截图.png)

[^答linux 截图工具案]: [a, aae, af, c, fz, fzc, fzd]

> 单词排序 时间复杂度 O(n) 
>
> 字典树存储效率极低，只有千分之，几浪费空间 。

## 双数组字典树

> 记录式改计算式存储节点信息，放弃边信息的存储

> > 完全二叉树：
>
> ![](/home/yu_dong/Pictures/2018-08-04 16-28-17屏幕截图.png)

> 双数组字典树
>
> ![](/home/yu_dong/Pictures/2018-08-04 16-28-59屏幕截图.png)
>
>  答案—例：
>
> ![](/home/yu_dong/Pictures/2018-08-04 17-02-37屏幕截图.png)



> base 计算相关节点的子节点地址
>
> ![](/home/yu_dong/Pictures/2018-08-04 16-31-49屏幕截图.png)
>
> check 存储父节点坐标
>
> ![](/home/yu_dong/Pictures/2018-08-04 16-35-35屏幕截图.png)

*怎样标记独立成词？*



> 将check数组中存储的父节点地址置为负
>
> ![](/home/yu_dong/Pictures/2018-08-04 16-36-48屏幕截图.png)

*怎样确定根节点base的值*

> 根节点base值加上孩子节点编号的位置需要为空以便存储孩子节点



![](/home/yu_dong/Pictures/2018-08-04 16-59-39屏幕截图.png)

