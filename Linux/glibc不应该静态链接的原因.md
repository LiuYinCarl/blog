# glibc不应该静态链接的原因

[Why is statically linking glibc discouraged?
](https://stackoverflow.com/questions/57476533/why-is-statically-linking-glibc-discouraged)

The reasons given in other answers are correct, but they are not the most important reason.

The most important reason why glibc should not be statically linked, is that it makes extensive internal use of dlopen, to load NSS (Name Service Switch) modules and iconv conversions. The modules themselves refer to C library functions. If the main program is dynamically linked with the C library, that's no problem. But if the main program is statically linked with the C library, dlopen has to go load a second copy of the C library to satisfy the modules' load requirements.

This means your "statically linked" program still needs a copy of libc.so.6 to be present on the file system, plus the NSS or iconv or whatever modules themselves, plus other dynamic libraries that the modules might need, like ld-linux.so.2, libresolv.so.2, etc. This is not what people usually want when they statically link programs.

It also means the statically linked program has two copies of the C library in its address space, and they might fight over whose stdout buffer is to be used, who gets to call sbrk with a nonzero argument, that sort of thing. There is a bunch of defensive logic inside glibc to try to make this work, but it's never been guaranteed to work.

You might think your program doesn't need to worry about this because it doesn't ever call getaddrinfo or iconv, but locale support uses iconv internally, which means any stdio.h function might trigger a call to dlopen, and you don't control this, the user's environment variable settings do.