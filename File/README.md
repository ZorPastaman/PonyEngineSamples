# File samples

Shows how to use the file module.

Nowadays, we can use `std::filesystem` for any operation with files. 
But it misses one important thing - async operations.
That's why Pony Engine provides a dedicated file module - for async read/write operations.
For anything sync, use `std::filesystem`.

## Samples

| Sample             | Description                |
|:-------------------|:---------------------------|
| [FileRead](Read)   | Shows how to read a file.  |
| [FileWrite](Write) | Shows how to write a file. |
