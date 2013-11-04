#ifndef _COMPYTE_PRIVATE_OPENCL
#define _COMPYTE_PRIVATE_OPENCL

#include "private.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#ifdef DEBUG
#include <assert.h>

#define CTX_TAG "ocl ctx "
#define BUF_TAG "ocl buf "
#define KER_TAG "ocl kern"

#define TAG_CTX(c) memcpy((c)->tag, CTX_TAG, 8)
#define TAG_BUF(b) memcpy((b)->tag, BUF_TAG, 8)
#define TAG_KER(k) memcpy((k)->tag, KER_TAG, 8)
#define ASSERT_CTX(c) assert(memcmp((c)->tag, CTX_TAG, 8))
#define ASSERT_BUF(b) assert(memcmp((b)->tag, BUF_TAG, 8))
#define ASSERT_KER(k) assert(memcmp((k)->tag, KER_TAG, 8))
#define CLEAR(o) memset((o)->tag, 0, 8);

#else
#define TAG_CTX(c)
#define TAG_BUF(b)
#define TAG_KER(k)
#define ASSERT_CTX(c)
#define ASSERT_BUF(b)
#define ASSERT_KER(k)
#define CLEAR(o)
#endif

typedef struct _cl_ctx {
#ifdef DEBUG
  char tag[8];
#endif
  cl_context ctx;
  cl_command_queue q;
  char *exts;
  void *blas_handle;
  cl_int err;
  unsigned int refcnt;
} cl_ctx;

struct _gpudata {
#ifdef DEBUG
  char tag[8];
#endif
  cl_mem buf;
  cl_event ev;
  cl_ctx *ctx;
  unsigned int refcnt;
};

struct _gpukernel {
#ifdef DEBUG
  char tag[8];
#endif
  cl_kernel k;
  cl_event ev;
  gpudata **bs;
  cl_ctx *ctx;
  unsigned int refcnt;
};

COMPYTE_LOCAL cl_ctx *cl_make_ctx(cl_context ctx);
COMPYTE_LOCAL cl_context cl_get_ctx(void *ctx);
COMPYTE_LOCAL cl_command_queue cl_get_stream(void *ctx);
COMPYTE_LOCAL gpudata *cl_make_buf(void *c, cl_mem buf);
COMPYTE_LOCAL cl_mem cl_get_buf(gpudata *g);

#endif
