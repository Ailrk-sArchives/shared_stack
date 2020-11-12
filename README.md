# Shared stack

A simple thread safe shared stack implemented with pthread and [Linux call stack](https://twitter.com/ImogenBits/status/1325424621286518784?s=20). Linux call stack is obtained by storing data as argumnets of recursive function calls. Call stack is managed by OS directly so it will never segfault (Assume a working os of course).
