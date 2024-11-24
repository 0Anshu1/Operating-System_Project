struct stat;

// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int describe(void);
int rename(const char *oldname, const char *newname);
int copy(const char *src, const char *dst);
int metadata(const char *filename, struct stat *statbuf);
int compress(const char *filename);
int decompress(const char *filename);
int getlogs(char *buffer, int size);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...) __attribute__ ((format (printf, 2, 3)));
void printf(const char*, ...) __attribute__ ((format (printf, 1, 2)));
char* gets(char*, int max);
int strlen(const char*);
void* memset(void*, int, int);
int atoi(const char*);
int memcmp(const void *, const void *, int);
void *memcpy(void *, const void *, int);

// umalloc.c
void* malloc(int);
void free(void*);