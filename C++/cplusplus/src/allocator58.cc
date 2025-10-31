//第一个分支：底层直接会走malloc申请空间
//一级空间配置器

#include<iostream>
//第二个分支（默认的空间配置器）：二级空间配置器
static void* allocate(size_t __n)
{
  if (__n > 128) 
{
  //底层还是会走malloc申请空间
  }
  else 
{
  //16维的自由链表 + 内存池
  //为何这么设计，原因如下：
  //1、防止多次申请空间导致的内存碎片问题
  //2、如果申请的空间比较频繁的话，会在内核态与用户态之间进行频繁的切换，效率就不高
}
}


# ifdef __USE_MALLOC
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;
template <int __inst>
class __malloc_alloc_template 
{
public:
static void* allocate(size_t __n)
{
    void* __result = malloc(__n);
    if (nullptr == __result) 
      __result = _S_oom_malloc(__n);  //oom = out of memory  申请不成功

    return __result;
}

static void deallocate(void* __p, size_t /* __n */)
{
    free(__p);
}

};


#else
union obj {
  union obj* _M_free_list_link;
  char _M_client_data[1];
}//The client sees this.

typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
template <bool threads, int inst>
class __default_alloc_template {

# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
  static _Obj*  _S_free_list[];        
# else
  static _Obj*  _S_free_list[_NFREELISTS]; 
# endif



public:
  static void* allocate(size_t __n)
{
  void* __ret = 0;

  if (__n > 128) 
{
  malloc(__n);
  }
  else 
{
  
  //16维的数组 + 内存池
    _Obj** __my_free_list= _S_free_list + _S_freelist_index(__n);
    

    _Obj* __RESTRICT __result = *__my_free_list;
  
   if (__result == 0)
      __ret = _S_refill(_S_round_up(__n));
    else {
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  return __ret;
  
}


static void deallocate(void* __p, size_t __n)
{
  if (__n > 128)
    malloc_alloc::deallocate(__p, __n);//free
  else {
  //将节点重新链接回自由链表下进行重复使用
  //_S_free_list[3]
    _Obj**  __my_free_list = _S_free_list + _S_freelist_index(__n)= ;
    _Obj* __q = (_Obj*)__p;

 
    __q -> _M_free_list_link = *__my_free_list;
    *__my_free_list = __q;
   
  }
}
};
#endif





template <class _Tp>
class allocator 
{
typedef alloc _Alloc;
public:
  //申请空间
_Tp* allocate(size_type __n, const void* = nullptr) 
{
  return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp))) : 0;
}

//释放空间
void deallocate(pointer __p, size_type __n)
  { 
  _Alloc::deallocate(__p, __n * sizeof(_Tp)); 
}

//构建对象
void construct(pointer __p, const _Tp& __val) 
{ 
    //定位new表达式：在指定的空间上构建对象
  new(__p) _Tp(__val); //new int(10)
}
//对象的销毁
void destroy(pointer __p) 
{ 
  __p->~_Tp(); 
}
};









enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = 16}; 

union _Obj 
{
union _Obj* _M_free_list_link;
  char _M_client_data[1];    /* The client sees this.        */
};

template <bool __threads, int __inst>
typename __default_alloc_template<__threads, __inst>::_Obj* __STL_VOLATILE
__default_alloc_template<__threads, __inst> ::_S_free_list[
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
  _NFREELISTS
# else
  __default_alloc_template<__threads, __inst>::_NFREELISTS
# endif
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };


//在自由链表中取下标的函数
static  size_t _S_freelist_index(size_t __bytes) //__bytes = 32
{
return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
(32 + 8 - 1)/8 - 1 = 39/8 - 1 = 4 - 1 = 3
}

//向上取整，得到8的整数倍
static size_t  _S_round_up(size_t __bytes) //__bytes = 32
{ 
return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); 
(32 + 8 - 1)  & ~ (8 - 1) = 39 & ~7
39 = 32 + 4 + 2 + 1 = 0010 0111
7 = 4 + 2 + 1 = 0000 0111
~7 = 1111 1000

33-------->40
32-------->32
31-------->32
//....
25-------->32
24-------->24
[33, 40]--->40
[25, 32]--->32   3.x ---4
[17, 24]--->24


0010 0111
&	1111 1000
  0010 0000-------->32

0010 0110
&	1111 1000
  0010 0000-------->32

0010 0000
&	1111 1000
  0010 0000-------->32

0001 1111
&	1111 1000
  0001 1000-------->24

0010 1000
&	1111 1000
  0010 1000-------->40
}

char* __default_alloc_template::_S_start_free = nullptr;

char* __default_alloc_template::_S_end_free = nullptr;

size_t __default_alloc_template::_S_heap_size = 0;





//1、如果想申请32字节的时候，堆空间与内存池是充足的
//__n = 32
static void* allocate(size_t __n)
{
else {
    _Obj** __my_free_list = _S_free_list + _S_freelist_index(__n) 
                            = _S_free_list[3];
  _Obj*  __result = *__my_free_list;
    
  if (__result == nullptr)
      __ret = _S_refill(_S_round_up(__n));
    else {
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  return __ret;
}
}

//__n  = 32
//该函数不会真正的申请空间，但是会调用_S_chunk_alloc申请空间，并将返回的空间进行切割，切割成
//多个等分并且挂接在对应的自由链表下面
void* __default_alloc_template::_S_refill(size_t __n)
{
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

__my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[3]


    __result = (_Obj*)__chunk;
    *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
    for (__i = 1; ; __i++) {
      __current_obj = __next_obj;
      __next_obj = (_Obj*)((char*)__next_obj + __n);
      if (__nobjs - 1 == __i) {
          __current_obj -> _M_free_list_link = 0;
          break;
      } else {
          __current_obj -> _M_free_list_link = __next_obj;
      }
    }
  return (__result);

}

//__size = 32;
//__nobjs = 20
//本来想申请32字节，但是现在一次申请了1280字节，其中的640字节通过函数进行返回，剩下的640字节
//通过 _S_end_free与_S_start_free进行控制
char* __default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
  char* __result;
  size_t __total_bytes = __size * __nobjs = 32 * 20 = 640;
  size_t __bytes_left = _S_end_free - _S_start_free = 0;

else {
      size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4)
                           = 2 * 640 = 1280 ;
  _S_start_free = (char*)malloc(__bytes_to_get) = malloc(1280);
  
  _S_heap_size += __bytes_to_get = 1280;
      _S_end_free = _S_start_free + __bytes_to_get;
      return(_S_chunk_alloc(__size, __nobjs));//递归
}

//递归调用
char* __result;
  size_t __total_bytes = __size * __nobjs = 32 * 20 = 640;
  size_t __bytes_left = _S_end_free - _S_start_free = 1280;

if (__bytes_left >= __total_bytes) {
      __result = _S_start_free;
      _S_start_free += __total_bytes;
      return(__result);
  }

}
//2、如果想申请64字节的时候，堆空间与内存池是充足的
//__n = 64
static void* allocate(size_t __n)
{
else {
  //_S_free_list[7]
  _Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);
  
  _Obj*  __result = *__my_free_list;
  
  if (__result == nullptr)
      __ret = _S_refill(_S_round_up(__n));
    else {
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  return __ret;
}

// __n = 64
void* __default_alloc_template::_S_refill(size_t __n)
{
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;


__my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[7]

  /* Build free list in chunk */
    __result = (_Obj*)__chunk;
    *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
    for (__i = 1; ; __i++) {
      __current_obj = __next_obj;
      __next_obj = (_Obj*)((char*)__next_obj + __n);
      if (__nobjs - 1 == __i) {
          __current_obj -> _M_free_list_link = 0;
          break;
      } else {
          __current_obj -> _M_free_list_link = __next_obj;
      }
    }
  return (__result);
}

//__size =64
//__nobjs = 20
char*
__default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
  char* __result;
  size_t __total_bytes = __size * __nobjs = 64 * 20 = 1280;
  size_t __bytes_left = _S_end_free - _S_start_free = 640;

else if (__bytes_left >= __size) {
      __nobjs = (int)(__bytes_left/__size) = 640/64 = 10;
      __total_bytes = __size * __nobjs = 64 * 10 = 640;
      __result = _S_start_free;
      _S_start_free += __total_bytes;
      return(__result);
  }
}


//3、如果想申请96字节的时候，堆空间与内存池是充足的
//__n = 96
static void* allocate(size_t __n)
{
else {
  //_S_free_list[11]
  _Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);
  
  _Obj*  __result = *__my_free_list;
  
  if (__result == nullptr)
      __ret = _S_refill(_S_round_up(__n));
    else {
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  return __ret;
}

// __n = 96
void* __default_alloc_template::_S_refill(size_t __n)
{
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

__my_free_list = _S_free_list + _S_freelist_index(__n);

    __result = (_Obj*)__chunk;
    *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
    for (__i = 1; ; __i++) {
      __current_obj = __next_obj;
      __next_obj = (_Obj*)((char*)__next_obj + __n);
      if (__nobjs - 1 == __i) {
          __current_obj -> _M_free_list_link = 0;
          break;
      } else {
          __current_obj -> _M_free_list_link = __next_obj;
      }
    }
  return (__result);
}

//__size = 96
//__nobjs = 20
char* __default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
  char* __result;
  size_t __total_bytes = __size * __nobjs = 96 * 20 = 1920;
  size_t __bytes_left = _S_end_free - _S_start_free = 0;

else {
      size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4)
                           = 2 * 1920 + _S_round_up(1280 >> 4)
               = 3840 + 80 = 3920;
  _S_start_free = (char*)malloc(__bytes_to_get) = malloc(3920);
  
  _S_heap_size += __bytes_to_get = 1280 + 3920 = 5200;
      _S_end_free = _S_start_free + __bytes_to_get;
      return(_S_chunk_alloc(__size, __nobjs));//递归调用
}
//递归调用
char* __result;
  size_t __total_bytes = __size * __nobjs = 96 * 20 = 1920;
  size_t __bytes_left = _S_end_free - _S_start_free = 3920;

if (__bytes_left >= __total_bytes) {
      __result = _S_start_free;
      _S_start_free += __total_bytes;
      return(__result);
  }

}


//4、如果想申请72字节的时候，堆空间与内存池没有连续的72字节
//__n = 72
static void* allocate(size_t __n)
{
else {
  //_S_free_list[8]
  _Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);
  
  _Obj*  __result = *__my_free_list;
  
  if (__result == nullptr)
      __ret = _S_refill(_S_round_up(__n));
    else {
      *__my_free_list = __result -> _M_free_list_link;
      __ret = __result;
    }
  }

  return __ret;
}


// __n = 72
void* __default_alloc_template::_S_refill(size_t __n)
{
  int __nobjs = 20;
  char* __chunk = _S_chunk_alloc(__n, __nobjs);
  _Obj* __STL_VOLATILE* __my_free_list;
  _Obj* __result;
  _Obj* __current_obj;
  _Obj* __next_obj;
  int __i;

if (1 == __nobjs) return(__chunk);
}


//__size = 72
//__nobjs = 20
char* __default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
  char* __result;
  size_t __total_bytes = __size * __nobjs = 72 * 20 = 1440;
  size_t __bytes_left = _S_end_free - _S_start_free = 0;

else {
      size_t __bytes_to_get =  2 * __total_bytes + _S_round_up(_S_heap_size >> 4)
                           = 2 * 1440 + _S_round_up(5200 >> 4)
               > 2880;
   _S_start_free = (char*)malloc(__bytes_to_get);
   
    if (nullptr == _S_start_free) 
    {
      size_t __i;
      _Obj** __my_free_list;
      _Obj* __p;
      
      //__i = 72  80  88  96
      for (__i = 72; __i <= 128; __i += 8) 
      {
        //_S_free_list[8]  _S_free_list[9] _S_free_list[10] _S_free_list[11]
        __my_free_list = _S_free_list + _S_freelist_index(__i);
        __p = *__my_free_list;
        
        if (0 != __p) 
        {
                  *__my_free_list = __p -> _M_free_list_link;
                  _S_start_free = (char*)__p;
                  _S_end_free = _S_start_free + __i;
                  return(_S_chunk_alloc(__size, __nobjs));//递归调用
                 
              }
      }
      
      
    }
    
//递归调用
char* __result;
  size_t __total_bytes = __size * __nobjs = 72 * 20 = 1440;
  size_t __bytes_left = _S_end_free - _S_start_free = 96;

else if (__bytes_left >= __size) {
      __nobjs = (int)(__bytes_left/__size) = 96/72 = 1;
      __total_bytes = __size * __nobjs = 72 * 1 = 72;
      __result = _S_start_free;
      _S_start_free += __total_bytes;
      return(__result);
  }
}



总结
1、_S_freelist_index 函数的作用就是为了在自由链表中取下标
2、_S_round_up 向上取整，得到8的整数倍
3、allocate函数的作用是为了申请空间，但是该函数不会直接申请空间，会调用 _S_refill，但是_S_refill函数也不会申请空间，但是会调用_S_chunk_alloc申请空间
4、_S_chunk_alloc函数是真正申请空间的函数，会将申请的结果可能会一分为二，其中一部分进行返回，另外一部分交给两个指针_S_start_free与_S_end_free进行控制，该函数还可能进行递归调用
5、_S_refill 函数的作用就是将_S_chunk_alloc返回的空间进行切割操作，然后挂接在对应的自由链表下面
6、对于空间配置器而言，所申请空间在内存的那个位置呢？堆空间
