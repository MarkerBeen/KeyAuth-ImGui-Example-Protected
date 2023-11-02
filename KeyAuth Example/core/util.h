#pragma once
#include "encryption/xorstr.hpp"
#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <random>
#include <winioctl.h>
#pragma warning(disable:4191 4099)
#pragma warning(disable:4996)

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LUGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

namespace Util
{
	RECT rc;
	std::string random_string(const int len)
	{
		const std::string alpha_numberic("ABCDEFGHIJKLMNOPRSTUVZabcdefghijklmnoprstuvz1234567890");
		std::default_random_engine generator{ std::random_device{}() };
		const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numberic.size() - 1 };
		std::string str(len, 0);
		for (auto& it : str)
		{
			it = alpha_numberic[distribution(generator)];
		}
		return str;
	}

	/* set the gay fucking color */
	void SetColor(unsigned short color)
	{
		HANDLE con = 0;
		con = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(con, color);
	}

	/* clear the console */
	void Clear()
	{
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(console, topLeft);
		return;
	}

	/* get hwid */
	static std::string get_hwid() {
		std::string m_sResult;

		HANDLE m_hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (m_hFile == INVALID_HANDLE_VALUE)
			return { };

		std::unique_ptr< std::remove_pointer <HANDLE >::type, void(*)(HANDLE) > m_hDevice
		{
		m_hFile, [](HANDLE handle)
		{
		CloseHandle(handle);
		}
		};

		STORAGE_PROPERTY_QUERY m_PropertyQuery;
		m_PropertyQuery.PropertyId = StorageDeviceProperty;
		m_PropertyQuery.QueryType = PropertyStandardQuery;

		STORAGE_DESCRIPTOR_HEADER m_DescHeader;
		DWORD m_dwBytesReturned = 0;
		if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
			&m_DescHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &m_dwBytesReturned, NULL))
			return { };

		const DWORD m_dwOutBufferSize = m_DescHeader.Size;
		std::unique_ptr< BYTE[] > m_pOutBuffer{ new BYTE[m_dwOutBufferSize] { } };

		if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
			m_pOutBuffer.get(), m_dwOutBufferSize, &m_dwBytesReturned, NULL))
			return { };

		STORAGE_DEVICE_DESCRIPTOR* m_pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(m_pOutBuffer.get());
		const DWORD m_dwSerialNumberOffset = m_pDeviceDescriptor->SerialNumberOffset;
		if (m_dwSerialNumberOffset == 0)
			return { };

		m_sResult = reinterpret_cast<const char*>(m_pOutBuffer.get() + m_dwSerialNumberOffset);
		m_sResult.erase(std::remove_if(m_sResult.begin(), m_sResult.end(), std::isspace), m_sResult.end());

		return m_sResult;
	}
}