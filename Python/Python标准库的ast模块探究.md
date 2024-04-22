# Python 标准库 ast 模块探究

因为最近在研究 cpython 的 ast 生成过程，所以对 cpython 的标准库中的 ast 产生了兴趣，这里主要分析以下 cpython 的 `ast.parse` 函数的原理，使用的 cpython 版本为 `Python 3.13.0a6+`，使用这个版本的原因是因为 cpython 3.13 给 `ast.parse` 函数增加了一个 `optimize` 关键字参数，可以用来获取优化后的 AST，更符合程序实际执行中使用的 AST。

`ast.parse` 函数定义在 `Lib/ast.py` 中，内容如下。

```python
def parse(source, filename='<unknown>', mode='exec', *,
          type_comments=False, feature_version=None, optimize=-1):
    """
    Parse the source into an AST node.
    Equivalent to compile(source, filename, mode, PyCF_ONLY_AST).
    Pass type_comments=True to get back type comments where the syntax allows.
    """
    flags = PyCF_ONLY_AST
    if optimize > 0:
        flags |= PyCF_OPTIMIZED_AST
    if type_comments:
        flags |= PyCF_TYPE_COMMENTS
    if feature_version is None:
        feature_version = -1
    elif isinstance(feature_version, tuple):
        major, minor = feature_version  # Should be a 2-tuple.
        if major != 3:
            raise ValueError(f"Unsupported major version: {major}")
        feature_version = minor
    # Else it should be an int giving the minor version for 3.x.
    return compile(source, filename, mode, flags,
                   _feature_version=feature_version, optimize=optimize)
```

主要的逻辑定义在 `compile` 函数中，`compile` 是一个 builtin函数，实际是一个 C 函数，下面将主要的逻辑注释一下。

```c
static PyObject *
builtin_compile_impl(PyObject *module, PyObject *source, PyObject *filename,
                     const char *mode, int flags, int dont_inherit,
                     int optimize, int feature_version)
/*[clinic end generated code: output=b0c09c84f116d3d7 input=cc78e20e7c7682ba]*/
{
    // source 参数就是我们的源代码字符串或者AST字符串
    // optimize 是优化等级参数
    // mode 是编译模式，可以看下 cpython ast 模块文档了解
    PyObject *source_copy;
    const char *str;
    int compile_mode = -1;
    int is_ast;
    int start[] = {Py_file_input, Py_eval_input, Py_single_input, Py_func_type_input};
    PyObject *result;

    PyCompilerFlags cf = _PyCompilerFlags_INIT;
    cf.cf_flags = flags | PyCF_SOURCE_IS_UTF8;
    if (feature_version >= 0 && (flags & PyCF_ONLY_AST)) {
        cf.cf_feature_version = feature_version;
    }

    if (flags &
        ~(PyCF_MASK | PyCF_MASK_OBSOLETE | PyCF_COMPILE_MASK))
    {
        PyErr_SetString(PyExc_ValueError,
                        "compile(): unrecognised flags");
        goto error;
    }
    /* XXX Warn if (supplied_flags & PyCF_MASK_OBSOLETE) != 0? */

    if (optimize < -1 || optimize > 2) {
        PyErr_SetString(PyExc_ValueError,
                        "compile(): invalid optimize value");
        goto error;
    }

    if (!dont_inherit) {
        PyEval_MergeCompilerFlags(&cf);
    }

    if (strcmp(mode, "exec") == 0)
        compile_mode = 0;
    else if (strcmp(mode, "eval") == 0)
        compile_mode = 1;
    else if (strcmp(mode, "single") == 0)
        compile_mode = 2;
    else if (strcmp(mode, "func_type") == 0) {
        if (!(flags & PyCF_ONLY_AST)) {
            PyErr_SetString(PyExc_ValueError,
                            "compile() mode 'func_type' requires flag PyCF_ONLY_AST");
            goto error;
        }
        compile_mode = 3;
    }
    else {
        const char *msg;
        if (flags & PyCF_ONLY_AST)
            msg = "compile() mode must be 'exec', 'eval', 'single' or 'func_type'";
        else
            msg = "compile() mode must be 'exec', 'eval' or 'single'";
        PyErr_SetString(PyExc_ValueError, msg);
        goto error;
    }
	// 这里检查下 source 参数是不是一个 AST 字符串，如果是，那就不需要转化为 AST 的步骤了
    is_ast = PyAST_Check(source);
    if (is_ast == -1)
        goto error;
    if (is_ast) {
        if ((flags & PyCF_OPTIMIZED_AST) == PyCF_ONLY_AST) {
            // return an un-optimized AST
            result = Py_NewRef(source);
        }
        else {
            // Return an optimized AST or code object

            PyArena *arena = _PyArena_New();
            if (arena == NULL) {
                goto error;
            }
		   // 如果编译参数说明只需要生成 AST，则生成（优化的） AST 后就会返回
            if (flags & PyCF_ONLY_AST) {
                // 验证一下 AST 的合法性
                mod_ty mod = PyAST_obj2mod(source, arena, compile_mode);
                if (mod == NULL || !_PyAST_Validate(mod)) {
                    _PyArena_Free(arena);
                    goto error;
                }
                // 如果参数说需要优化AST，则进行优化
                if (_PyCompile_AstOptimize(mod, filename, &cf, optimize,
                                           arena) < 0) {
                    _PyArena_Free(arena);
                    goto error;
                }
                result = PyAST_mod2obj(mod);
            }
            else {
                // 参数说还需要编译 AST
                mod_ty mod = PyAST_obj2mod(source, arena, compile_mode);
                if (mod == NULL || !_PyAST_Validate(mod)) {
                    _PyArena_Free(arena);
                    goto error;
                }
                // 直接将 AST 字符字符串编译为 code object
                result = (PyObject*)_PyAST_Compile(mod, filename,
                                                   &cf, optimize, arena);
            }
            _PyArena_Free(arena);
        }
        goto finally;
    }
	// 如果传入的 source 参数是代码，而不是 AST，则需要先编译 AST，然后根据参数决定是否
    // 需要优化 AST 以及是否需要将 AST 编译为代码对象（也就是字节码）
    str = _Py_SourceAsString(source, "compile", "string, bytes or AST", &cf, &source_copy);
    if (str == NULL)
        goto error;
	// 这里进行主要逻辑
    result = Py_CompileStringObject(str, filename, start[compile_mode], &cf, optimize);

    Py_XDECREF(source_copy);
    goto finally;

error:
    result = NULL;
finally:
    Py_DECREF(filename);
    return result;
}
```

`Py_CompileStringObject` 函数负责将代码解析为 AST，AST 优化，AST 编译为字节码。

```c
PyObject *
Py_CompileStringObject(const char *str, PyObject *filename, int start,
                       PyCompilerFlags *flags, int optimize)
{
    PyCodeObject *co;
    mod_ty mod;
    PyArena *arena = _PyArena_New();
    if (arena == NULL)
        return NULL;
	// 将代码编译为 AST
    mod = _PyParser_ASTFromString(str, filename, start, flags, arena);
    if (mod == NULL) {
        _PyArena_Free(arena);
        return NULL;
    }
    if (flags && (flags->cf_flags & PyCF_ONLY_AST)) {
        if ((flags->cf_flags & PyCF_OPTIMIZED_AST) == PyCF_OPTIMIZED_AST) {
            // 优化 AST
            if (_PyCompile_AstOptimize(mod, filename, flags, optimize, arena) < 0) {
                return NULL;
            }
        }
        PyObject *result = PyAST_mod2obj(mod);
        _PyArena_Free(arena);
        return result;
    }
    // AST 编译为字节码
    co = _PyAST_Compile(mod, filename, flags, optimize, arena);
    _PyArena_Free(arena);
    return (PyObject *)co;
}
```

具体各个子步骤是比较复杂的逻辑，这里就不做介绍了。这篇文章的目的主要是为了梳理一下 `ast.parse` 这个函数的底层细节和大概流程。