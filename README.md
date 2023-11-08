# 42-Tests-Runner
C tests runner made in c++

Run with:
``./runner`` to test all files\n
``./runner ft_strlcpy.c ft_strlcat.c`` to test specific files


## How tocreate tests?
Put your test files in /tests/c_file/test1.c

## How to modify the runner?
The source cpp file is included in /source

Compile source with:
``g++ -o runner runner.cpp -std=c++17``

## Which functions or files are supported?
All. Tests are based on the /tests/ directory structure. To test "ft_strlcpy.c" file, create a "ft_strlcpy" folder in /tests/ and then create your test files in it. Test files are usually named test1.c test2.c.. but name doesn't matter. Test files have to contain the function prototype and return 0 in case of success, or 1 in case of fail.

Test file example for ft_strlcpy:
```c
#include <bsd/string.h>

size_t ft_strlcpy(char *dst, const char *src, size_t size);

int main(void)
{
	// Create your own tests, return 1 or 0 depending on the result
	// Use printf to print your own trace (saved in /traces)
	return (0);
}
```

## Traces
The runner save your test output in /traces/file_name/test_name_trace.txt