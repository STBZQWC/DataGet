// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

//#import "C:\\Windows\\SysWow64\\TeeChart2017.ocx" no_namespace
// CAxisTitle ��װ����

class CAxisTitle : public COleDispatchDriver
{
public:
	CAxisTitle() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CAxisTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisTitle(const CAxisTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IAxisTitle ����
public:
	long get_Angle()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Angle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Caption()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Caption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL Clicked(long X, long Y)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, X, Y);
		return result;
	}
	long get_Position()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Position(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IAxisTitle ����
public:

};
