#ifndef LS_BITMAP_H
#define LS_BITMAP_H

#include "win32.h"
#include "lsCRT.h"
#include "lsMath.h"
#include "lsBuffer.h"

struct Bitmap
{
    void *data;
    
    u32 width;
    u32 height;
    
    u32 headerSize;
    u32 compression;
    u32 pixelBufferSize;
    
    u64 size;
    
    b32 isTopToBottom;
};

extern "C"
{
    void ls_bitmapLoad(string Path, Bitmap *bitmap);
    void ls_bitmapWrite(string Path, u8 *data, s32 width, s32 height);
};

#endif //LS_BITMAP_H


#ifdef LS_BITMAP_IMPLEMENTATION

void ls_bitmapLoad(string Path, Bitmap *bitmap)
{
    char *bitmapFile;
    u64 bitmapFileSize = ls_readFile(Path.data, &bitmapFile, 0);
    
    b32 isWindowyfied = FALSE;
    u32 PixelOffset = *((u32 *)((char *)bitmapFile + 10));
    u32 HeaderSize = *((u32 *)((char *)bitmapFile + 14));
    
    s32 Width = *((s32 *)((char *)bitmapFile + 18));
    s32 Height = *((s32 *)((char *)bitmapFile + 22));
    if(Height < 0) { isWindowyfied = TRUE; }
    Height = ls_abs(Height);
    
    u32 Compression = *((u32 *)((char *)bitmapFile + 30));
    
    u32 PixelBufferSize = *((u32 *)((char *)bitmapFile + 34));
    
    bitmap->data = ((char *)bitmapFile + PixelOffset);
    bitmap->width = Width;
    bitmap->height = Height;
    bitmap->headerSize = HeaderSize;
    bitmap->compression = Compression;
    bitmap->pixelBufferSize = PixelBufferSize;
    bitmap->size = bitmapFileSize;
    bitmap->isTopToBottom = isWindowyfied;
    
    return;
}

void ls_bitmapWrite(string Path, u8 *data, s32 width, s32 height)
{
    const u32 bytesPerPixel = 4;
    
    const u32 sizeOfData    = width*height*bytesPerPixel;
    const u32 sizeOfDIB     = sizeof(BITMAPV5HEADER);
    const u32 sizeOfHeader  = 14;
    
    const u32 sizeInFile = sizeOfHeader + sizeOfDIB + sizeOfData;
    const u32 dataOffset = sizeOfHeader + sizeOfDIB;
    
    BITMAPV5HEADER bmpH = {};
    
    bmpH.bV5Size          = sizeof(BITMAPV5HEADER);
    bmpH.bV5Width         = width;
    bmpH.bV5Height        = height;
    bmpH.bV5Planes        = 1;
    bmpH.bV5BitCount      = 32;
    bmpH.bV5Compression   = BI_RGB;
    bmpH.bV5SizeImage     = 0; //May be set to 0 for BI_RGB
    bmpH.bV5XPelsPerMeter = 0;
    bmpH.bV5YPelsPerMeter = 0;
    bmpH.bV5ClrUsed       = 0;
    bmpH.bV5ClrImportant  = 0;
    bmpH.bV5RedMask       = 0;
    bmpH.bV5GreenMask     = 0;
    bmpH.bV5BlueMask      = 0;
    bmpH.bV5AlphaMask     = 0;
    bmpH.bV5CSType        = 0;
    bmpH.bV5Endpoints     = {};
    bmpH.bV5GammaRed      = 0;
    bmpH.bV5GammaGreen    = 0;
    bmpH.bV5GammaBlue     = 0;
    bmpH.bV5Intent        = 0;
    bmpH.bV5ProfileData   = 0;
    bmpH.bV5ProfileSize   = 0;
    bmpH.bV5Reserved      = 0;
    
    buffer buff = ls_bufferInit(MBytes(4));
    
    ls_bufferAddByte(&buff, 'B');
    ls_bufferAddByte(&buff, 'M');
    ls_bufferAddDWord(&buff, sizeInFile);
    ls_bufferAddDWord(&buff, 0);
    ls_bufferAddDWord(&buff, dataOffset);
    ls_bufferAddDataClean(&buff, &bmpH, sizeof(BITMAPV5HEADER));
    ls_bufferAddDataClean(&buff, data, sizeOfData);
    
    ls_writeFile(Path.data, buff.data, buff.cursor, FALSE);
}

#endif //IMPLEMENTATION
