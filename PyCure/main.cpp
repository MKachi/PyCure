#include <PyCure.h>

using namespace PyCure;

//PyObject* TestFunc(PyObject* self)
//{
//	PyObject* result;
//	printf("Call Cpp TestFunc!\n");
//	Py_INCREF(Py_None);
//	result = Py_None;	// return ����
//	return result;
//}
//
//PyObject* Multiple(PyObject* self, PyObject* args)
//{
//	PyObject* result;
//	int a, b;
//	Py_INCREF(args);
//	PyArg_ParseTuple(args, "II", &a, &b);
//	result = PyType(a * b);
//	return result;
//}
//
//// �Լ��� ���
//// METH_KEYWORDS	: �Լ��� PyCFunctionWithKeywords Ÿ�� ���ڴ� PyArg_ParseTupleAndKeywords�Լ��� ���
//// METH_NORARGS		: ���ڰ� ����
//// METH_O			: ���ڰ� �ϳ��� ���
//// METH_CLASS		: Ŭ������ �޼ҵ��� ���
//// METH_STATIC		: Ŭ������ �޼ҵ��� ���
//static PyMethodDef ExtMethods[] =
//{ 
//	{ "TestFunc", (PyCFunction)TestFunc, METH_NOARGS, "Excute a TestFunc" },{ NULL, NULL, 0, NULL },
//	{ "Multiple", (PyCFunction)Multiple, METH_VARARGS, "Excute a Multiple" },{ NULL, NULL, 0, NULL }
//};
//
//// ��⿡ ���
//static PyModuleDef PyExtModule =
//{ PyModuleDef_HEAD_INIT, "PyCureDemo", NULL, -1, ExtMethods };
//
//PyMODINIT_FUNC PyInit_Ext1()
//{
//	// ����� ����
//	return PyModule_Create(&PyExtModule);
//}

int main()
{
//	PyImport_AppendInittab("PyCureDemo", PyInit_Ext1);
	PyCure_Initialize();

	PyModule module = PyCure_ImportModule("Sample01");

	int result;

	// Get global variable 'o'
	result = GetVar<int>(module, "o");
	printf("Get o : %d\n", result);

	// Set global variable 'o'
	printf("\n");
	SetVar(module, "o", 9999);
	result = GetVar<int>(module, "o");
	printf("Set o : %d\n", result);

	// Call function 'Case1()'
	printf("\n");
	CallFunc<void>(module, "Case1");

	// Call function 'Case2()'
	printf("\n");
	result = CallFunc<int>(module, "Case2");
	printf("Case2 return : %d\n", result);

	// Call function 'Case3(a)'
	printf("\n");
	PyTuple tuple = TupleCallFunc(module, "Case3", 2);
	result = GetTupleItem<int>(tuple, 0);
	const char* str = GetTupleItem<const char*>(tuple, 1);
	printf("Case3 return : %d, %s\n", result, str);

	// Call function 'Add(a, b)'
	printf("\n");
	result = CallFunc<int>(module, "Add", PyCureArgs(2, PyType(1), PyType(1)));
	printf("Add return : %d\n", result);

	// Import Python class
	PyClass Ang = CreatePyClass(module, "Ang");

	// Get class Ang local variable '_a'
	printf("\n");
	result = Ang->GetLocalVar<int>("_a");
	printf("Get class Ang _a : %d\n", result);

	// Set class Ang local variable '_a'
	printf("\n");
	Ang->SetLocalVar("_a", 99);
	result = Ang->GetLocalVar<int>("_a");
	printf("Set class Ang _a : %d\n", result);

	// Call class Ang Method 'GetA()'
	printf("\n");
	result = Ang->CallMethod<int>("GetA");
	printf("class Ang GetA return : %d\n", result);

	// Call class Ang Method 'SetA(a)'
	printf("\n");
	Ang->CallMethod<void>("SetA", PyCureArgs(1, PyType(100)));
	result = Ang->CallMethod<int>("GetA");
	printf("class Ang SetA : %d\n", result);

	PyCure_Finalize();
	return 0;
}