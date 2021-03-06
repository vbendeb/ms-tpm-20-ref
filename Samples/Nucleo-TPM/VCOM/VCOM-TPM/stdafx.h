// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <Windows.h>
#include <vector>
#include <exception>

// Nucleo-L476RC based TPM on USB-VCOM
#pragma pack(push, 1)
#define TPM_VCOM_PORT TEXT("COM6")
#define SIGNALMAGIC (0x326d7054)
#define MAX_TPM_COMMAND_SIZE (1024)
#define TPM_HEADER_SIZE (10)
#define CMD_RSP_BUFFER_SIZE (MAX_TPM_COMMAND_SIZE)
typedef enum
{
    SignalNothing = 0,
    SignalShutdown,
    SignalReset,
    SignalSetClock,
    // IN {UINT32 time}
    SignalCancelOn,
    SignalCancelOff,
    SignalCommand,
    // IN {BYTE Locality, UINT32 InBufferSize, BYTE[InBufferSize] InBuffer}
    // OUT {UINT32 OutBufferSize, BYTE[OutBufferSize] OutBuffer}
    SignalResponse,
    // OUT {UINT32 OutBufferSize, BYTE[OutBufferSize] OutBuffer}
} signalCode_t;

typedef struct
{
    unsigned int magic;
    signalCode_t signal;
    unsigned int dataSize;
} signalHdr_t;

typedef union
{
    struct
    {
        unsigned int time;
    } SignalSetClockPayload;
    struct
    {
        unsigned int locality;
        unsigned int cmdSize;
        unsigned char cmd[1];
    } SignalCommandPayload;
} signalPayload_t, *pSignalPayload_t;

typedef union
{
    signalHdr_t s;
    unsigned char b[sizeof(signalHdr_t)];
} signalWrapper_t, *pSignalWrapper_t;
#pragma pack(pop)
