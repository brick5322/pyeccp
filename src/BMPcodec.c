#include <libCodec/BMPcodec.h>
#include <stdlib.h>

int isValid(BMPFileHeader *pFHeader)
{
	switch (pFHeader->identifier)
	{
	case 0x4d42:
	case 0x4142:
	case 0x4943:
	case 0x5043:
	case 0x4349:
	case 0x5450:
		break;
	default:
		return 0;
	}
	return 1;
}

void BMPFileHeader_default_set(BMPFileHeader *pFHeader)
{
	pFHeader->dataOffset = 0x36;
	pFHeader->fileSz = 0;
	pFHeader->identifier = 0x4d42;
	pFHeader->resevered = 0;
}

void BMPInfoHeader_default_set(BMPInfoHeader *pIHeader)
{
	pIHeader->bitInfoHeadersz = 0x28;
	pIHeader->width = 0;
	pIHeader->height = 0;
	pIHeader->planes = 1;
	pIHeader->bitCount = _24Bits;
	pIHeader->compression = 0;
	pIHeader->dataSz = 0;
	pIHeader->DPMw = 0x2e23;
	pIHeader->DPMh = 0x2e23;
	pIHeader->colors = 0;
	pIHeader->importantColors = 0;
}

unsigned int BMPcodec_resize(BMPcodec *pcodec, unsigned int width, int height, BitCount bitCount) {
    if (!width && !height)
        return pcodec->info_header.dataSz;
    if (width)
        pcodec->info_header.width = width;
    if (height)
        pcodec->info_header.height = height;
    pcodec->info_header.bitCount = bitCount;
    int bytecount = bitCount / 8;

    unsigned int w = ((pcodec->info_header.width * bytecount - 1) / 4 + 1) * 4;

    pcodec->info_header.dataSz = w * pcodec->info_header.height;
    pcodec->f_header.fileSz = pcodec->info_header.dataSz + pcodec->info_header.bitInfoHeadersz + 14;
    return pcodec->info_header.dataSz;
}

unsigned char *BMPcodec_buffer_alloc(BMPcodec *pcodec) {
    return malloc(pcodec->info_header.dataSz);
}

BMPcodec *BMPcodec_alloc(stream *stm)
{
	BMPcodec *ret = malloc(sizeof(BMPcodec));
	if (!ret)
		return ret;
	ret->stm = stm;
	BMPFileHeader_default_set(&ret->f_header);
	BMPInfoHeader_default_set(&ret->info_header);
	return ret;
}

unsigned int BMPcodec_getpos(BMPcodec *pcodec,unsigned int row,int column) {
    unsigned int w = ((pcodec->info_header.width * pcodec->info_header.bitCount / 8 - 1) / 4 + 1)*4 ;
    return row*w+column*pcodec->info_header.bitCount / 8;
}

unsigned int BMPcodec_write(BMPcodec *pcodec, unsigned int sz)
{
	return pcodec->stm->write(pcodec->stm, sz);
}

unsigned int BMPcodec_writeAll(BMPcodec *pcodec)
{
    return pcodec->stm->write(pcodec->stm, pcodec->info_header.width * pcodec->info_header.height * pcodec->info_header.bitCount / 8);
}

unsigned int BMPcodec_read(BMPcodec *pcodec, unsigned int sz)
{
	return pcodec->stm->read(pcodec->stm, sz);
}

unsigned int BMPcodec_readAll(BMPcodec *pcodec)
{
    return pcodec->stm->read(pcodec->stm, pcodec->info_header.width * pcodec->info_header.height * pcodec->info_header.bitCount / 8);
}

int BMPcodec_readHeader(BMPcodec *pcodec)
{
	pcodec->stm->handler_subject = &pcodec->f_header.identifier;
	pcodec->stm->read(pcodec->stm, 14);
	if (!isValid(&pcodec->f_header))
		return 0;
	pcodec->stm->read(pcodec->stm, 4);
	unsigned int len = pcodec->info_header.bitInfoHeadersz - 4;
	pcodec->stm->read(pcodec->stm, len);
	return 0;
}

int BMPcodec_writeHeader(BMPcodec *pcodec)
{
	pcodec->stm->handler_subject = &pcodec->f_header.identifier;
	pcodec->stm->write(pcodec->stm, 14);
	pcodec->stm->write(pcodec->stm, pcodec->info_header.bitInfoHeadersz);
	return 0;
}

void BMPcodec_free(BMPcodec *pcodec)
{
	free(pcodec);
}

void BMPcodec_fill(BMPcodec *pcodec,color32 c) {
    size_t size = pcodec->info_header.dataSz / pcodec->info_header.height;
    unsigned char *buffer = malloc(size);
    switch (pcodec->info_header.bitCount) {
        case _8Bits:
            for (int i = 0; i < size; i++)
                buffer[i] = c.b;
            break;
        case _16Bits:
            for (int i = 0; i < size; i++)
                    buffer[i] = i%2?c.a:c.b;

            break;
        case _24Bits:
            for (int i = 0; i < size; i++)
                switch (i%3) {
                case 0:
                    buffer[i] = c.b;
                    break;
                case 1:
                    buffer[i] = c.g;
                    break;
                case 2:
                    buffer[i] = c.r;
                    break;
                }
            break;
        case _32Bits:
            for (int i = 0; i < size; i++)
                switch (i%3) {
                    case 0:
                        buffer[i] = c.b;
                        break;
                    case 1:
                        buffer[i] = c.g;
                        break;
                    case 2:
                        buffer[i] = c.r;
                        break;
                    case 3:
                        buffer[i] = c.a;
                        break;
                }
        default:
            break;
    };
    for (int i = 0; i < pcodec->info_header.height; i++) {
        pcodec->stm->handler_subject = buffer;
        BMPcodec_write(pcodec, size);
    }
    free(buffer);
}