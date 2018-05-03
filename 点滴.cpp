   字符串转16进制
   s8 dest[80] = {0};
    s8* p = dest;
    for (s32 i = 0; i < nBufLen; i++)
    {
        g_snprintf(p + i * 2, sizeof(dest) - i * 2, "%02X", pbyNameBuf[i]);
//         highByte = pbyNameBuf[i] >> 4;
//         lowByte = pbyNameBuf[i] & 0x0f;
// 
//         highByte += 0x30;
// 
//         if (highByte > 0x39)
//             dest[i * 2] = highByte + 0x07;
//         else
//             dest[i * 2] = highByte;
// 
//         lowByte += 0x30;
//         if (lowByte > 0x39)
//             dest[i * 2 + 1] = lowByte + 0x07;
//         else
//             dest[i * 2 + 1] = lowByte;
    }
