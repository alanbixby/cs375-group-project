TODO List:
- Concurrency?
- Implement SkipList as name safe functions
- Quantify tests to compare the algorithms

In other news, I have a webserver that runs on localhost:3000 can detect and update with the CPP executable.

**Be careful to use `use rbtree int` if you want to insert numbers, otherwise they'll be treated as strings and cause wonky looking trees like this:
![](https://i.imgur.com/T5f8wOY.png)

It's a completely valid tree, but since it is string sorting, you'll have 4 > 100.