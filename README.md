# QGeneCal

QGeneCal是一个可以高效求解高中生物中多种遗传学问题的项目。本项目遵守[MIT协议](https://mit-license.org/).

## QGeneCal可以做什么

我们利用集合幂级数(Set Power Series)构建了一个数学模型,运用该模型可以简单地手工计算以下问题:

- 多种基因型的个体自交,子代的表现型及比例
- 多种基因型的个体自由交配,子代的表现型及比例
- 由子代的基因型反推可能的亲本基因型
  
使用我们的方法计算量会比传统方法更小,且思路清晰,不容易出错。该模型还能处理有相互作用的等位基因,包括:

- 互补基因(Complementary gene)
- 累加作用(Additive effect)
- 抑制作用(Inhibitor)和上位效应(Epistasis)
- 基因型致死和配子致死

接着,我们利用快速沃尔什变换(Fast Walsh Transform),提出了在较低的时间复杂度下求解以上问题的算法。并采用C++实现了该算法。

## 如何使用QGeneCal


手工计算的方法参见[论文](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf)的前4章。

高效算法参见[论文](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf)的后半部分.与论文相应的C++代码如下:

- [一般情况下的计算](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/only-outbreeding/code)

- [非等位基因的相互作用](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/incomplete-dominance)

- [致死问题](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/dominant-homozygous-lethal/code)

另外,网页版的计算工具还在开发当中,目前只完成了部分内容,可以访问[网页版](https://hkfnvg-cxtaem-3000.preview.myide.io/)使用。
