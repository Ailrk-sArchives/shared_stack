# Shared stack

A simple thread safe shared stack implemented with pthread and Linux call stack. Linux call stack is accesseed by storing data as argumnets of recursive function calls. Call stack is managed by OS directly so it will never segfault (assume enough memory and a working linux).
