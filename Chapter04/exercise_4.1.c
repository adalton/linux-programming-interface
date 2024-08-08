/**
 * Note: This implementation intentionally omits error checking.
 */
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
