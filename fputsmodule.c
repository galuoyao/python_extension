#include <Python.h>

static PyObject *method_fputs(PyObject *self, PyObject *args, PyObject *kw) {
    char *str, *filename = NULL;
    int bytes_copied = -1;

    /* Parse arguments */
    // 设置两个参数的keywords分别为 content，filename
    char *kwlist[] = {"content", "filename", NULL};
    if(!PyArg_ParseTupleAndKeywords(args, kw, "ss", kwlist, &str, &filename)) {
        return NULL;
    }

    FILE *fp = fopen(filename, "w");
    bytes_copied = fputs(str, fp);
    fclose(fp);

    return (PyObject *)Py_BuildValue("i", bytes_copied);
}

static PyMethodDef FputsMethods[] = {
    {"fputs", method_fputs, METH_VARARGS | METH_KEYWORDS, "Python interface for fputs C library function"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fputsmodule = {
    PyModuleDef_HEAD_INIT,
    "fputs",
    "Python interface for the fputs C library function",
    -1,
    FputsMethods
};