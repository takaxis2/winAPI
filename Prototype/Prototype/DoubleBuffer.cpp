#include "DoubleBuffer.h"


CDoubleBuffer* CDoubleBuffer::m_pInstance = NULL;

CDoubleBuffer::CDoubleBuffer(void) : m_iBufferIndex(0)
{
	
}

CDoubleBuffer::~CDoubleBuffer(void)
{

}

// ���� ����
void CDoubleBuffer::CreateBuffer(const int& _width, const int& _height)
{
	CONSOLE_CURSOR_INFO DeCursor;            // �ܼ�â �����̴� Ŀ��
	COORD size = { CONSOL_MAX_WIDTH, CONSOL_MAX_HEIGHT };     // ���� ũ�⸦ �����ϴ� ����ü
	SMALL_RECT rect;                    // â ũ�⸦ �����ϴ� ����ü

	rect.Left = 0;
	rect.Right = _width;
	rect.Top = 0;
	rect.Bottom = _height;

	// 1�� ���� ����
	m_HBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE , 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_HBuffer[0], size);  // ���� ũ�� ����
	SetConsoleWindowInfo(m_HBuffer[0], TRUE, &rect); // â ũ�� ����


	// 2�� ���� ����
	m_HBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE , 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_HBuffer[1], size);  // ���� ũ�� ����
	SetConsoleWindowInfo(m_HBuffer[1], TRUE, &rect); // â ũ�� ����


	DeCursor.dwSize = 1;
	DeCursor.bVisible = FALSE;


	SetConsoleCursorInfo(m_HBuffer[0], &DeCursor); // 1�� ���ۿ� �����̴� Ŀ�� ����
	SetConsoleCursorInfo(m_HBuffer[1], &DeCursor); // 2�� ���ۿ� �����̴� Ŀ�� ����
}

// ���� ����
void CDoubleBuffer::WriteBuffer(int x, int y, char* _str, int _color)
{
	DWORD dw;                           // ��ǥ ���� ����ü
	COORD CursorPosition = { (short)x, (short)y };    // ��ǥ ����

	// ��ǥ �̵�
	SetConsoleCursorPosition(m_HBuffer[m_iBufferIndex], CursorPosition);

	SetColor(_color);

	// ���ۿ� ����
	WriteFile(m_HBuffer[m_iBufferIndex], _str, strlen(_str), &dw, NULL);
}

void CDoubleBuffer::WriteBuffer(int x, int y, int _ivalue, int _color)
{
	DWORD dw;	// ��ǥ ���� ����ü
	COORD CursorPosition = { (short)x, (short)y };    // ��ǥ ����

	// ��ǥ �̵�
	SetConsoleCursorPosition(m_HBuffer[m_iBufferIndex], CursorPosition);

	char* cStr = NULL;

	cStr = new char[sizeof(int) + 1];
	_itoa(_ivalue, cStr, 10);

	SetColor(_color);
	// ���ۿ� ����
	WriteFile(m_HBuffer[m_iBufferIndex], cStr, strlen(cStr), &dw, NULL);
}

// ���� ��ȯ
void CDoubleBuffer::FlippingBuffer()
{
	// ���� Ȱ��ȭ. ������ ������ �ѹ��� ���
	SetConsoleActiveScreenBuffer(m_HBuffer[m_iBufferIndex]);
	m_iBufferIndex = !m_iBufferIndex; // ���� ���� ����
}

// ���� �����
void CDoubleBuffer::ClearBuffer()
{
	COORD Coor = { 0, 0 };  // �Ʒ� �Լ��� ���� ����ü
	DWORD dw;               // �Ʒ� �Լ��� ���� ����ü

	// �ش� ������ Coor ��ǥ���� ' '���� ä���� ������ ��ó�� �����
	FillConsoleOutputCharacter(m_HBuffer[m_iBufferIndex], ' ', CONSOL_MAX_WIDTH * CONSOL_MAX_HEIGHT, Coor, &dw);
}

// ���� ����
void CDoubleBuffer::DestroyBuffer()
{
	MyCloseHandle(m_HBuffer[0]);    // 1�� ���� ����
	MyCloseHandle(m_HBuffer[1]);    // 2�� ���� ����
	// (HANDLE�� ������ �������� �״��. �ش� ������ ���� HANDLE Ŀ�θ� ����)
}

// �����ϰ� CloseHandle�� ó���ϱ� ���� MyCloseHandle ����
bool CDoubleBuffer::MyCloseHandle(HANDLE& hFile)
{
	if (INVALID_HANDLE_VALUE != hFile)
	{
		hFile = INVALID_HANDLE_VALUE;
	}
	return false;
}

void CDoubleBuffer::SetColor(int color)
{
	SetConsoleTextAttribute(m_HBuffer[m_iBufferIndex], color);
}
