# CContainerKit

基于 C 语言的扩展型容器集合库，包含常见的静态数组、动态数组、栈、队列、动态链表、通用二叉树等数据结构。适合作为新手学习 C/C++。

此库为个人学习数据结构的项目，会存在问题和不足之处。

本作者非常欢迎您在 [Discussions](https://github.com/CatIsNotFound/CContainerKit/discussions) 或 [Issues](https://github.com/CatIsNotFound/CContainerKit/issues) 中提出问题或提供建议，以帮助作者改进此项目。

> Note: 
> 
> 使用 Gitee 查看此仓库的用户，可以转到 [Issues](https://gitee.com/CatIsNotFound/ccontainer-kit/issues) 中提出问题或提供建议。

## 特性

- 支持 C11 标准的 C 语言扩展库。
- 提供了各种容器的实现，如静态数组、动态数组、栈、队列等。
- 支持任意类型变量的存储和操作。

## 快速开始

访问 [Quick Start 页面](https://catisnotfound.github.io/CContainerKit-Wiki/zh/quickstart)以快速上手此库。

## API 参考

访问 [APIs 页面](https://catisnotfound.github.io/CContainerKit-Wiki/zh/apis/)以查看所有支持的 API。

## 基本已实现容器完成情况

| 容器名称 | 完成进度 | 描述              |
|----------|----------|-----------------|
| CArray   | 85%      | 静态数组            |
| CVector  | 90%      | 动态数组            |
| CString  | 85%      | 字符串             |
| CStack | 75% | 栈 (基于 CVector)  |
| CDeque | 75% | 队列 (基于 CVector) |
| CLinkedList | 80% | 链表              |

## 正在努力实现的容器

- CTree：通用二叉树
- CMap：映射表
- CSet：集合

## 注意

- 本项目中的所有代码几乎没有添加任何的注释，若阅读代码有所困难，请借助此 [Wiki](https://catisnotfound.github.io/CContainerKit-Wiki/) 配合使用。


## 许可协议

本项目采用 [MIT 许可协议](../LICENSE.md)进行许可。请在使用前阅读并遵守许可协议。
