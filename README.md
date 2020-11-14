# Shared stack

A simple thread safe shared stack implemented with pthread and [Linux call stack](https://twitter.com/ImogenBits/status/1325424621286518784?s=20). Linux call stack is obtained by storing data as argumnets of recursive function calls. Call stack is managed by OS directly and will never give you a segfault.

Note this is a toy implementation and should not be used in production code. The stack is actually the call stack of another process, and if it's not handled with care it can create zombie process ;(.
