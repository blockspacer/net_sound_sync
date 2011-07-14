#ifndef _TYPES_H_
#define _TYPES_H_

#include "streams.h"

struct TMapFileHeader
{
    int totalBufferSize;    //һ�����Դ�����ݵĿռ��С
    int availBufferSize;    //����д�����ݵĿռ��С
    int alreadUsedBufferSize;  //�Ѿ���������ݵĿռ��С
    int consumedBufferSize; //����������Ѿ������˵Ŀռ��С
    int packetNumbers;      //����һ�������ݰ�����
    int consumedPacketNumbers;//����������Ѿ������˵����ݰ�����
    int resveredSize;           //�����Ŀռ��С
    int maxSampleSize;          //����sample�Ĵ�С
    bool haveMediaInfo;    //��ʶý�����ͺ�����������Ϣ�Ѿ��õ�
};

struct TDataPacket
{
    int size;
    REFERENCE_TIME beginTime;
    REFERENCE_TIME endTime;
};

#endif
