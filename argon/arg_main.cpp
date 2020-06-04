#ifndef _ARG_MAIN
#define _ARG_MAIN

#include "JouHeader.h"
#include "JouStrings.h"

#include "CtrlWord.h" // ����������� �����
#include "arg_header.h"
#include "arg_irvi.cpp"
#include "USOData.h"
#include "neptun_main.h"
/*
   +--------------------------+
   |   ������ ���� �����-16   |
   +--------------------------+

   ������������ ��� ������ ������� �� ��������� ����

   +------------------------------------------+
   | N.N. ��������� ��������� �������������   |
   +------------------------------------------+
*/

void arg_aks_on (void) {
A2:
if(i==2)
        {
        e3:
        cw_K3[3] = true; // ������������ ������� "��������� �������������"
        dt = 50;         // Delta t = 50"
        // ���� = �3 (�� <437>)
        Yz1[9] = 0;      // ������ ������ � ���������
        // ������ �� �5 - ������� 0,2
        } else i++;
}

/*
   +------------------------------------+
   | N.N. ��� ���������� �������� ���   |
   +------------------------------------+
*/

void arg_spp_ikv_off (void) {
cw_K2[2] = true;   // ���������� ���-1
cw_K2[6] = true;   // ���������� ���-2
cw_Y32[2] = false; // ��������� ���-1
cw_Y32[3] = false; // ��������� ���-2
// � �������� ��������� <001>
}

/*
   +------------------------------------+
   | N.N. ������������ ������ �� ����   |
   +------------------------------------+
*/

void SetItvi (byte Mode, unsigned short Addr, unsigned short value, char z) {
irvi_string.SubString(1,2) = IntToStr(Mode).SubString(1,1);
irvi_string.SubString(3,5) = IntToStr(Addr);
irvi_string.SubString(8,7) = IntToStr(value);
irvi_string.SubString(15,1) = z;
}

/*
   +---------------------------------------------------------------+
   | B.    � � � � � � � � � � �   � � � � � � � � � � � � � � �   |
   | � � � � � � �   � � � � � � � � � �   � � � � � � � � � � �   |
   +---------------------------------------------------------------+
*/

void ku_podgot (void) {
// +----------------+
// +-- 63 ������� --+
// +----------------+
// ���������� ����-1
// ��������� ������� "��������� ����������� ����-1" ���������� ���������;
// ����� 0,6 ��� ����������� ������� ��������� � ��������� �������;
// ��� ������� ��������� � ����������� ����� ����-1 - �� ���� � ������� ���������
// �������� 2,4 ������� (����� ���� ������� ����� ��������� ������ ��� ����� ���)
// �������� 60 ������ ��������� ������ ����������
// ���� cw_b1[9] = 1, �� +0,6 ��� � ��������

}

// ��������� ������������� ������� ���������� �����������
void DKUO (void) {


}

void mode_31 (int addr, int val){
switch (addr) {   // ���������� ������
        case 40: cw_b1[val]=1; break;
        case 47: cw_b6[val]=1; break;
        case 50: cw_b10[val]=1; break;
        case 100: cw_r1[val]=1; break;
        case 107: cw_r6[val]=1; break;
        case 110: cw_a20[val]=1; break;
        case 111: cw_a21[val]=1; break;
        case 112: cw_a22[val]=1; break;
        case 246: cw_a30[val]=1; break;
        case 250: cw_a35[val]=1; break;
        case 277: cw_a19[val]=1; break;
        default: JPS(3,is_miu,is_operator,"��� ����� �����!",""); break; } }

void mode_30 (int addr, int val){
switch (addr) {   // ���������� ������
        case 40: cw_b1[val]=0; break;
        case 47: cw_b6[val]=0; break;
        case 50: cw_b10[val]=0; break;
        case 100: cw_r1[val]=0; break;
        case 107: cw_r6[val]=0; break;
        case 110: cw_a20[val]=0; break;
        case 111: cw_a21[val]=0; break;
        case 112: cw_a22[val]=0; break;
        case 246: cw_a30[val]=0; break;
        case 250: cw_a35[val]=0; break;
        case 277: cw_a19[val]=0; break;
        default: JPS(3,is_miu,is_operator,"��� ����� �����!",""); break; } }

/*
   +--------------------------------------------+
   | N.N. ������������ �������� �������� ����   |
   +--------------------------------------------+
*/

void ChekIrvi (AnsiString irvi_str){
irvi_type.mode = StrToInt(irvi_str.SubString(1,2)); // �������� ������ ��� ������� ������ ���� "�����"
switch (irvi_type.mode) {   // ���������� ������
        case 00: /* ������������ ��� �������������� ����� ������ ��-� 1 - 4 */ break;
        case 04: /* ������������ ����� 10-� ����� */ break;
        case 05: /* ������������ ����� 8-� ����� */ break;
        case 10: /* ���� ������� ��� */   break;
        case 11: /* ���� ������� ��� 1-� ������ */  break;
        case 12: /* ���� ������� ��� 2-� ������ */  break;
        case 14: /* ��������� ���� 10-� ����� */                       // ���� ����� 14, ��
                 irvi_type.addr = StrToInt(irvi_str.SubString(3,5));   // ����������� �������� ������
                 if(CorrectAddr(irvi_type.addr)) {                     // ��������� ������������ ������, ���� ���������, ��
                 irvi_type.value = StrToInt(irvi_str.SubString(8,7));  // ����������� ��������
                 ArgonMemoryType[irvi_type.addr] = irvi_type.value;    // ���������� ��� � ������ ������ ������
                 SetItvi(irvi_type.mode,irvi_type.addr,ArgonMemoryType[irvi_type.addr], irvi_type.z );   // ���������� ��������� �� ����
                 JPS(4,is_argon,is_irvi,"������ ����� "+               // �������� ��������� (�� ����� ������)
                 IntToStr(irvi_type.value)+" �� ������ "+IntToStr(irvi_type.addr),"");}
                 else {                                                 // ���� ����� �� ��������� ,��
                 irvi_err = true;
                 JPS(3,is_argon,is_operator,arg_addr_error,"");     }   // �������� ���������� ����������� �������� ������ �16
                 break;
        case 15: /* ��������� ���� 8-� ����� */  break;
        case 17: /* ��������� ���� 10-� ����� */ break;
        case 18: /* ��������� ���� 8-� ����� */
                // irvi_type.addr = StrToInt(irvi_str.SubString(3,5));   // ����������� �������� ������
                 // if(CorrectAddr(irvi_type.addr)) {                    // ��������� ������������ ������, ���� ���������, ��
                 //irvi_type.value = StrToInt(irvi_str.SubString(8,7));  // ����������� ��������
                // ArgonMemoryType[irvi_type.addr] = irvi_type.value;   // ���������� ��� � ������ ������ ������
                 //SetItvi(irvi_type.mode,(irvi_type.addr)+1,ArgonMemoryType[irvi_type.addr], irvi_type.z );   // ���������� ��������� �� ����
                 //mode18act=true;
                 break;
        case 21: /* ����� ������� ��� 1-� ������ */ break;
        case 22: /* ����� ������� ��� 2-� ������ */ break;
        case 24: /* ��������� ����� 10-� ����� */                      // ���� ����� 24, ��
                 irvi_type.addr = StrToInt(irvi_str.SubString(3,5));   // ����������� �������� ������ ��������� ����������
                 if(CorrectAddr(irvi_type.addr)) {                     // ��������� ������������ ������, ���� ���������, ��
                 SetItvi(irvi_type.mode,irvi_type.addr,ArgonMemoryType[irvi_type.addr], irvi_type.z ); }  // ���������� ��������� �� ����
                 else   {                                               // ���� ����� �� ��������� ,��
                 irvi_err = true;
                 JPS(3,is_argon,is_operator,arg_addr_error,"");   }     // �������� ���������� ����������� �������� ������ �16
                 break;
        case 25: /* ��������� ����� 8-� ����� */ break;
        case 27: /* ��������� ����� 10-� ����� */ break;
        case 28: /* ��������� ����� 8-� �����  */break;
        case 30: /* ��������� ��������� �������� � ����� - ������ ������� */
                 irvi_type.addr = StrToInt(irvi_str.SubString(3,5));   // ����������� �������� ������ ��������� ����������
                 if(CorrectAddr(irvi_type.addr)) {                     // ��������� ������������ ������, ���� ���������, ��
                 irvi_type.value = StrToInt(irvi_str.SubString(8,7));  // ����������� ��������
                 mode_30(irvi_type.addr,irvi_type.value); }             // ���������� ��������� �� ����
                 else   {                                              // ���� ����� �� ��������� ,��
                 irvi_err = true;
                 JPS(3,is_argon,is_operator,arg_addr_error,"");   }    // �������� ���������� ����������� �������� ������ �16
                 break;
        case 31: /* ��������� ��������� �������� � ����� - ������ ���� */
                 irvi_type.addr = StrToInt(irvi_str.SubString(3,5));   // ����������� �������� ������ ��������� ����������
                 if(CorrectAddr(irvi_type.addr)) {                     // ��������� ������������ ������, ���� ���������, ��
                 irvi_type.value = StrToInt(irvi_str.SubString(8,7));  // ����������� ��������
                 mode_31(irvi_type.addr,irvi_type.value); }             // ���������� ��������� �� ����
                 else   {                                              // ���� ����� �� ��������� ,��
                 irvi_err = true;
                 JPS(3,is_argon,is_operator,arg_addr_error,"");   }    // �������� ���������� ����������� �������� ������ �16
                 break;
        case 40: /*  */ break;
        case 41: /*  */ break;
        case 42: /*  */ break;
        case 43: /*  */ break;
        case 44: /*  */ break;
        case 45: /*  */ break;
        case 46: /*  */ break;
        case 48: /* ������ ������� */
        break;
        default: irvi_err = true;       // ���� ������ (��� ��������� �� ����)
                 JPS(3,is_argon,is_irvi,"��","");        // �������� ������ � ��������������� ������
                 JPS(3,is_miu,is_operator,"�������������� �����!","");
        irvi_type.addr = StrToInt(irvi_str.SubString(3,5));
        irvi_type.value = StrToInt(irvi_str.SubString(8,7));

        break;
}

}

class JP {

/* void blok_3 () {
if(cw_a7[1]) cw_b1[7]=1;
else {
        if(cw_C7[1]) {
                if(!cw_a14[9]&&!cw_a8[7]) cw_b1[7]=1;
                else
                     }
     }
if(cw_C3[0]&&cw_C3[2])

}; */

void blok_10 () {
cw_b1[11]=1;
cw_A4[0]=0; cw_A4[1]=0; cw_A4[2]=0; cw_A4[3]=0;
cw_A4[4]=0; cw_A4[6]=0; cw_A4[7]=0; cw_A4[8]=0;
cw_A4[9]=0; cw_A4[10]=0; cw_A4[13]=0; cw_A4[14]=0;
cw_A4[15]=0; cw_A9[0-15]=0; cw_A5[0-15]=0; };

};

static bool self_test_pr;

int self_test_long () {
 // ���������� ���������������� - �������
 // ��� ������ ���� �������� ������������
 // ��������� ���, ���, ��������� � ��� ���������� ������ (��-1 - ��-7)
 self_test_pr = 1;
 return 3; }

int self_test_short () { // ���������� ���������������� - ��������
 // ��� ������ ���� �������� ������������
 // ��������� ���, ���, ��������� � ���������� ������ (��-1, 2, 4, 5, 6)
 if(USO_Booled[3][13]||
    USO_Booled[3][2]||
    USO_Booled[3][3]||
    USO_Booled[3][4]){
     self_test_pr = 1;
     return 0;
   } else {
  // �������-������� ���������� ������ ������ ���� ��������� �-�� ���������
     self_test_pr = 1;
     JPS(3,is_argon,is_operator,"���� �� ��������, �.�. ��� ������ ��� ������������.","");
     return 1; }}

void arg_acc_handler(int Result) {
// ���������� �������� -  + �� +
// ��� �� ���������� ������� ������� ������ (� ����������� �� ���������� �����)
USO_Booled[10][1]=1; // "������ ����" �� ���
USO_Booled[9][7]=1;  // "������ ��" (���������???)
USO_Booled[3][10]=0;
USO_Booled[3][11]=0;
co_priz =1;
arg_work_pr=0;
}

#endif //_ARG_MAIN
