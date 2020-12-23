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

接着,我们利用快速沃尔什变换(Fast Walsh Transform),提出了**在较低的时间复杂度下**求解以上问题的算法。并采用C++实现了该算法。

## 如何使用QGeneCal


手工计算的方法参见[论文](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf)的前4章。

高效算法参见[论文](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf)的后半部分.与论文相应的C++代码如下:

- [一般情况下的计算](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/only-outbreeding/code)

- [非等位基因的相互作用](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/incomplete-dominance)

- [致死问题](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/dominant-homozygous-lethal/code)

编译命令为`g++ source_file.cpp -o exec_file  -std=c++11`

另外,网页版的计算工具还在开发当中,目前只完成了部分内容,可以访问[网页版](https://hkfnvg-cxtaem-3000.preview.myide.io/)使用。

# QGeneCal

QGeneCal is a project that can efficiently solve a variety of genetic problems in high school biology. This project is licensed under the [MIT License](https://mit-license.org/)

## What Can QGeneCal Do

We use Set Power Series to build a mathematical model, which can be used to  manually calculate the following questions simply:

- Individual selfing of multiple genotypes, phenotype and proportion of offspring
- Free mating of individuals with multiple genotypes, phenotypes and proportions of offspring
- Reverse the possible parental genotype from the genotype of the offspring
  
The calculation using our method is easier than that of the traditional method, and the approach is clear. The model can also handle interacting alleles, including:

- Complementary gene
- Additive effect
- Inhibitor and Epistasis
- Genotype lethal and gamete lethal

Next, we use the Fast Walsh Transform to create an algorithm to solve the above problems with **lower time complexity** . The algorithm is implemented in C++.

## How to use QGeneCal


For manual calculation methods, please refer to the first 4 chapters of our [essay](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf).

For efficient algorithms, please refer to the second half of our [essay](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/blob/main/essay/essay.pdf). The C++ code corresponding to the paper is as follows:

- [Calculation under general conditions](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/only-outbreeding/code)

- [Non-allele interaction](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/incomplete-dominance)

- [Lethal Problem](https://github.com/Shenzhen-Middle-School-OI-team/QGeneCal/tree/main/dominant-homozygous-lethal/code)

The compilation command is `g++ source_file.cpp -o exec_file -std=c++11`

In addition, the web version of the calculation tool is still under development. At present, only part of it has been completed. You can visit the [web version](https://hkfnvg-cxtaem-3000.preview.myide.io/) to use it.
