//---------------------------------------------------------------------------
#ifndef in_con
#define in_con

#pragma hdrstop

#include "inpu_connect.h"
#include "ICN_header.h"
#include "USOData.h"
#include <vcl.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

void SendHeaderAssign (PacketIDtype _PacketIDNum){
   PacketHeaderType.PacketID = _PacketIDNum;
}

void ResetCRC (unsigned short CRC) {
 CRC = 0;
}

void CalcCRC (unsigned short CRC, void* Buffer, unsigned short Size) {

CRC = sizeof(Buffer)+Size;
  /* __asm{
    push edi
    Mov ecx, [Size]
    Jcxz Exit
    mov  edx,[CRC]
    mov  ax,[edx]
    mov  edi,[Buffer]
    Cycle:Add AL,[edi]
          Adc AH,0
          Inc edi
    Loop Cycle
    Mov [edx],ax
    Exit:
    pop edi
  }   */
}

void SendPrim(void* Buffer, unsigned short Size) {
  CalcCRC(PacketFooterType.CRC, Buffer, Size);
}

void SendHeader (PacketIDtype PacketIDNum, unsigned short Size) {
   PacketHeaderType.Size = Size;
   SendHeaderAssign(PacketIDNum);
   PacketHeaderType.No++;
   ResetCRC(PacketFooterType.CRC);
}

void MyIntToBin(int dig,bool* b, size_t bsize)
{
    for(size_t i=0; i<bsize; ++i)
        b[i]= dig& 1<<i ;
}

void SendToInpuData (void){
char *S[4];

S[0]+= (int)USO_Booled[0][0];
S[0]+= (int)USO_Booled[0][1];
S[0]+= (int)USO_Booled[0][2];
S[0]+= (int)USO_Booled[0][3];
}



__int64 XToDec(String number, Byte radix)
{
  String alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  __int64 result = 0, factor = 1;
  if (radix > 1 && radix <= alphabet.Length())
  {
    int count = 0;
    number = number.UpperCase();
    for (int i = number.Length(); i >= 1; i--)
      for (int j = 1; j <= radix; j++)
        if (number[i] == alphabet[j])
        {
          result += factor * (j - 1);
          factor *= radix;
          count++;
          break;
        }
    if (count < number.Length())
      result = 0;
  }
  return result;
}

String DecToX(__int64 number, Byte radix)
{
  String result = "", alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (radix > 1 && radix <= alphabet.Length())
  {
    do
    {
      result = String(alphabet[number % radix + 1]) + result;
      number /= radix;
    }
    while (number > 0);
  }
  return result;
}

String XtoY(String number, Byte from_radix, Byte to_radix)
{
  return DecToX(XToDec(number, from_radix), to_radix);
}

#endif // in_con
