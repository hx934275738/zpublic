// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

///> Protocol Buffers
#ifdef _DEBUG
#pragma comment(lib, "libprotobuf_d.lib")
#else
#pragma comment(lib, "libprotobuf.lib")
#endif

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <functional>
#include <thread>