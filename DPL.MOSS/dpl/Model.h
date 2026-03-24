#pragma once
struct IRuntimeModelModule__vtable {
	char field0_0x0;
	char field1_0x1;
	char field2_0x2;
	char field3_0x3;
	char field4_0x4;
	char field5_0x5;
	char field6_0x6;
	char field7_0x7;
	char field8_0x8;
	char field9_0x9;
	char field10_0xa;
	char field11_0xb;
	char field12_0xc;
	char field13_0xd;
	char field14_0xe;
	char field15_0xf;
	char field16_0x10;
	char field17_0x11;
	char field18_0x12;
	char field19_0x13;
	char field20_0x14;
	char field21_0x15;
	char field22_0x16;
	char field23_0x17;

	int IRuntimeModelModule;
	int Initialise;
	int GetVertexPointer;
	int UpdateModel;
	int DrawModel;
	int DrawLitModel;
	int SetDrawInterface;
};

struct IRuntimeModelModule {
	struct IRuntimeModelModule__vtable *__vtable; // Inherited from IInterface
};