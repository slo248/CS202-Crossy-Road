# Coding rules

1. `namespace std` [is not allowed](https://stackoverflow.com/a/1452738).
2. All code must use **inline braces**. (open bracket on the same line with condition)
3. [Variables and functions must have sensible names](https://www.youtube.com/watch?v=-J3wNP6u5YU), the only exception is `i` in a `for-loop`.
4. We should use [Camel case](https://en.wikipedia.org/wiki/Camel_case) to name things (except classes and structs) like `getStudentsInCourse()`.
5. [Don't comment too much](https://www.youtube.com/watch?v=Bf7vDBBOBUA), try to write codes that make sense instead.
6. Use [`#include` guard](https://www.learncpp.com/cpp-tutorial/header-guards/) for all header files (the traditional `#ifndef`, `#define`, `#endif` would be better as the modern `#pragma once` is not official in C++).

---

# Github rules

0. We should use branches for all features and never code on the main branch (we can set this up on Github). Below is a demonstration of branching, each branch is formed to program a specific feature.

    ![](https://hackmd.io/_uploads/HyypvJcv3.png)

1. Most branches should be named like this: 
    - For feature branches: **feat/(project-name)-(task-name-with-hyphen)**.
    - For hotfix branches (when in emergency, fixing new-found bugs that have been merged,...): **hotfix/(project-name)-(task-name-with-hyphen)**.
    - For refactor branches (re-organize code, files, folders,...): **refactor/(project-name)-(task-name-with-hyphen)** (This should only be opened when there is enough consensus among members).

    - For example, the branch for the task **Create a school year** in the **Course Management System** should be named **feat/CMS-create-a-school-year**.
2. **Everyone must write sensible commit message.** (No ".", you should not write general messages like "fix bugs", "remove bugs",...). If you need to commit some small changes, you should consider [**git squash**](https://stackoverflow.com/a/5189600).
3. Everyone should resolve all errors and warnings before commiting.
4. No one could push code into the main branch directly. Only merging from other branches are allowed.
5. Before merging the branch, a [pull request](https://viblo.asia/p/tao-pull-request-dung-cach-bWrZnwkrlxw) for the branch must be opened and all changes in it must be approved **by at least 2 people**.
    - A pull request is opened when you want to merge your branch into the main branch.
    - A pull request can only be opened when **the code is ready for review**.
    - It can have the same name as the branch for simplicity's sake.
    - It should have a description about **what have been done in the code** and **how to use the new feature** to make review easier.
    - It should be linked to the corresponding Trello (or Jira,...) task to make it easier to find.
6. Please **no merging other branches to yours**. When your [branch](https://backlog.com/git-tutorial/vn/stepup/stepup1_1.html) needs features that have been merged in the main branch, you should [rebase](https://www.atlassian.com/git/tutorials/rewriting-history/git-rebase) your branch into the main branch (instead of merging that branch then seperating it again, it would be annoying and cause us a lot of trouble 😥). Below is a picture demonstration of rebase.
    ![](https://hackmd.io/_uploads/HJCfY5Ovh.png)
    ![](https://hackmd.io/_uploads/B1icLnCbT.png)
    * When you are on a feature branch: `git rebase main`
7. Try to estimate the day you will complete your task and set it up in Trello (or Jira,...)
8. ALWAYS add a new line at the end of a file - GITHUB SUGGESTS THIS!![](https://hackmd.io/_uploads/BJX0-3AWa.png)

---

##### Note: More rules might be added later on.
