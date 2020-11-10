# Shared stack

A simple thread safe shared stack implemented with pthread and Linux call stack. Linux call stack is obtained by storing data as argumnets of recursive function calls. Call stack is managed by OS directly so it will never segfault (Under normal conditional of course, like, enough memory).

