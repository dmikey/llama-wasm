
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "run.h"

extern uint32_t register_func(uint32_t ptr, uint32_t len, uint32_t buf, uint32_t blen)
    __attribute__((__import_module__("blockless"), __import_name__("register")));

__attribute__((export_name("runCompletion")))
uint32_t
runCompletion(int32_t ptr, uint32_t len, int32_t result_ptr, uint32_t result_len)
{
    unsigned char *ptr_u8 = (unsigned char *)ptr;
    unsigned char *result = (unsigned char *)result_ptr;

    const char *rs = "this result from module b";
    uint32_t l = strlen(rs) < result_len ? strlen(rs) : result_len;
    memcpy(result, rs, l);

    char params[len + 1];
    memcpy(params, ptr_u8, len);
    params[len] = '\0'; // null-terminate the string

    printf("this module b recv from module a: %s\n", params);

    return 0;
}

__attribute__((export_name("alloc")))
int32_t
alloc(uint32_t size)
{
    void *ptr = malloc(size);
    return (int32_t)ptr;
}

__attribute__((export_name("dealloc"))) void dealloc(int32_t ptr, uint32_t size)
{
    free((void *)ptr);
}

__attribute__((export_name("_initialize"))) void _initialize()
{
    printf("register");
    const char *method = "{\"module\":\"blsLlama\", \"methods\":[\"runModel\"]}";
    uint32_t m_ptr = (uint32_t)method;
    uint8_t rs[256] = {0};
    uint32_t v = register_func(m_ptr, strlen(method), (uint32_t)rs, 256);
    if (v != 0)
    {
        printf("%s\n", rs);
    }
}

int main()
{
    return 0;
}