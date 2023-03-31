#Paul stinkt
import ctypes
#DataStructures.py
class PEParserBase(ctypes.Structure):
    _fields_ = [("hFile", ctypes.c_void_p),
        ("dwFileSize", ctypes.c_ulong),
        ("bytes", ctypes.c_ulong),
        ("fileBuffer",ctypes.c_void_p)]
class PEHEADER(ctypes.Structure):
    _fields_ = [("test", PEParserBase)]
#FunctionWrapper.py
def testWrapper(peParserBase, _instanceDLL):
    _instanceDLL.test.argtypes = [ctypes.POINTER(PEParserBase)]
    _instanceDLL.test.restype = ctypes.POINTER(PEParserBase)
    return _instanceDLL.test(ctypes.byref(pEParserBase))
def test2Wrapper(pEHEADER, _instanceDLL):
    _instanceDLL.test2.argtypes = [ctypes.POINTER(PEHEADER)]
    _instanceDLL.test2.restype = ctypes.POINTER(PEHEADER)
    return _instanceDLL.test2(ctypes.byref(pEHEADER))

pEParserBase = PEParserBase()
pEHEADER = PEHEADER()

_test = ctypes.CDLL('PeParserPythonWrapper.dll')

pPEParserBase = testWrapper(pEParserBase, _test)
pPEHEADER = test2Wrapper(pEHEADER, _test)

print(testWrapper(pEParserBase, _test).contents.bytes)
print(hex(ctypes.addressof(pEParserBase)), pEParserBase.bytes)
print(hex(ctypes.addressof(pPEParserBase.contents)), pEParserBase.bytes)