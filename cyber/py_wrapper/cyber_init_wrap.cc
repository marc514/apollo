/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <Python.h>  //20200330fromMarc:for using python_api in cc
#include <string.h>

#include "cyber/py_wrapper/py_init.h"

static PyObject *cyber_py_init(PyObject *self, PyObject *args) {
  char *data = nullptr;
  Py_ssize_t len = 0;
  if (!PyArg_ParseTuple(args, const_cast<char *>("s#:cyber_py_init"), &data,
                        &len)) {
    AERROR << "cyber_py_init:PyArg_ParseTuple failed!";
    Py_RETURN_FALSE;
  }
  std::string module_name(data, len);
  bool is_init = apollo::cyber::py_init(module_name);
  if (is_init) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyObject *cyber_py_ok(PyObject *self, PyObject *args) {
  bool is_ok = apollo::cyber::py_ok();
  if (is_ok) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyObject *cyber_py_shutdown(PyObject *self, PyObject *args) {
  apollo::cyber::py_shutdown();
  return Py_None;
}

static PyObject *cyber_py_is_shutdown(PyObject *self, PyObject *args) {
  bool is_shutdown = apollo::cyber::py_is_shutdown();
  if (is_shutdown) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyObject *cyber_py_waitforshutdown(PyObject *self, PyObject *args) {
  apollo::cyber::py_waitforshutdown();
  return Py_None;
}

/////////////////////////////////////////////////////////////////////
//global for whole page, init module
//20200330fromMarc: PyMethodDef
//PyMethodDef结构体有四个字段。
//第一个是一个字符串，表示在Python中对应的方法的名称；
//第二个是对应的C代码的函数；
//第三个是一个标致位，表示该Python方法是否需要参数，METH_NOARGS表示不需要参数，METH_VARARGS表示需要参数；
//第四个是一个字符串，它是该方法的doc属性，这个不是必须的，可以为NULL。
//PyMethodDef结构体数组最后以 {NULL, NULL, 0, NULL}结尾。（感觉好像不是必须的，但是通常都这么做那我们也这么做吧） 
//注意：以上的用法都是针对Python2的，在Python3中又有些不同。
//首先Python3中模块的初始化函数PyMODINIT_FUNC创建的函数名格式由init<moduel_name>变为了PyInit_<module_name>
//(module_name == _cyber_init)，并且还需要返回一个 module 类型的变量；
//其次Python3中创建module对象的函数由Py_InitModule变为了PyModule_Create，如下:
//   PyMODINIT_FUNC PyInit__cyber_init(void) {
//    PyObject m;
//    m = PyModule_Create(&_cyber_init_module);//PyModule_Create需要传入PyModuleDef类型的指针
//    if (m == NULL)
//      return NULL;
//    return m;
//   }
//   static struct PyModuleDef _cyber_init_module = {
//   PyModuleDef_HEAD_INIT,
//   “_cyber_init”,        / name of module /
//   NULL,                 / module documentation, may be NULL /
//   -1,                   / size of per-interpreter state of the module, or -1 if the module keeps state in global variables. /
//   _cyber_init_methods   / A pointer to a table of module-level functions, described by PyMethodDef values. Can be NULL if no functions are present. /
//   };
/////////////////////////////////////////////////////////////////////
static PyMethodDef _cyber_init_methods[] = {
    // global fun
    {"py_init", cyber_py_init, METH_VARARGS, ""},
    {"py_ok", cyber_py_ok, METH_NOARGS, ""},
    {"py_shutdown", cyber_py_shutdown, METH_NOARGS, ""},
    {"py_is_shutdown", cyber_py_is_shutdown, METH_NOARGS, ""},
    {"py_waitforshutdown", cyber_py_waitforshutdown, METH_NOARGS, ""},

    {NULL, NULL, 0, NULL} /* sentinel */
};

///Init function of this module, 20200330fromMarc: executed when import
///the function name must be init<moduel_name>, here module_name: _cyber_init
PyMODINIT_FUNC init_cyber_init(void) {
  Py_InitModule("_cyber_init", _cyber_init_methods);
}  //20200330fromMarc: Py_InitModule in Python2,arg1: module_name; arg2: module_methods
