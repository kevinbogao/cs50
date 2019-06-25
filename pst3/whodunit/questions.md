# Questions

## What's `stdint.h`?

`stdint.h` is a header file that provides a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They are unsigned integer types, and refer to the number of bits that can be allocated.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* `BYTE`:  1 byte
* `DWORD`: 4 bytes
* `LONG`:  4 bytes
* `WORD`:  2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of a BMP file are the character "B" and "M" in `ASCII`. They specifie the file type, and it is denoted as `0x4d42`.

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size of the bitmap file in bytes, where as `biSize` is the size of the `BITMAPINFOHEADER` only (40 bytes).

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the bitmap is a top-down BIB (Device-Independent Bitmap) and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` specifies the number of bits per pixel, hence they max number of colours per pixel.

## Why might `fopen` return `NULL` in `copy.c`?

`fopen` may return `NULL` when the input file cannot be found, or when it can create the output file to write to.

## Why is the third argument to `fread` always `1` in our code?

The third argument represents the number of items to read. Since they are is only one source file, `1` is specified as number of the elements.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

```
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
```

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO
