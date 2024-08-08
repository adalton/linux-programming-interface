# Exercises

1. The `tee` command reads its standard input until end-of-file, writing a copy
   of the input to standard output and to the file named in its command-line
   argument. (We show an example of the use of this command when we discuss
   FIFOs in Section 44.7.) Implement `tee` using I/O system calls. By default,
   `tee` overwrites any existing file with the given name. Implement the `-a`
   command-line option (`tee -a file`), which causes `tee` to append text to the
   end of a file if it already exists. (Refer to Appendix B for a description of
   the `getopt()` function, which can be used to parse command-line options.)

   ```c
   #include <fcntl.h>
   #include <stdbool.h>
   #include <string.h>
   #include <sys/types.h>
   #include <sys/uio.h>
   #include <unistd.h>
   
   static int tee(const char* const filename, const bool append)
   {
       char buffer[4096];
       const int fd = open(filename, O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC), 0640);
       ssize_t bytesRead;
   
       while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0) {
           write(1, buffer, bytesRead);
           write(fd, buffer, bytesRead);
       }
   
       close(fd);
   
       return 0;
   }
   
   int main(const int argc, const char* const argv[])
   {
       if (argc < 2 || argc > 3) {
           const char* const msg = "Usage: tee [-a] <filename>\n";
           write(1, msg, strlen(msg));
   
           return 1;
       }
   
       const bool append = (argc == 3) && strcmp(argv[1], "-a") == 0;
       const char* const filename = argv[argc - 1];
   
       return tee(filename, append);
   }
   ```

2. Write a program like `cp` that, when used to copy a regular file that
   contains holes (sequences of null bytes), also creates corresponding holes
   in the target file.
