#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include"string.h"

/*
  从键盘获得汉字的编码
  在中文windows下，默认编码方式为GB2312, 每个汉字由两个字节组成。
  函数的目的是：把这个汉字的高字节写入 pc1指向的位置，低字节写入 pc2指向的位置
*/

int get_han_zi(unsigned char* pc1, unsigned char* pc2)

{
	char buf[100];
	printf("\n请输入一个汉字：");
	gets(buf);
	if (strlen(buf) != 2) return -1;
	*pc1 = buf[0];
	*pc2 = buf[1];

	if (*pc1 < 0xa1) return -2;

	if (*pc2 < 0xa1) return -2;

	return 0;

}

void load_han_zi(unsigned char* buf, unsigned char c1, unsigned char c2)

{

	int n = (c1 - 0xa1) * 94 + (c2 - 0xa1); // 计算在文件中的位置
	FILE* fp = fopen("han.dat", "rb");
	if (fp == NULL) {
		printf("汉字库打开错！");
		exit(1);
	}

	fseek(fp, n * 32L, SEEK_SET);

	for (int i = 0; i < 32; i++) {
		buf[i] = (unsigned char)fgetc(fp);
	}

	fclose(fp);

}
/*
  显示汉字
  buf: 从文件中读出的汉字字模信息，32字节，说明同上
  italic: =1，如果要求斜体， =0 正常
  kx: 水平放大率
  ky: 垂直放大率
  fill: 用于填充的字符
*/

void show_han_zi(unsigned char* buf, int italic, int kx, int ky, char fill)
{
	for (int i = 0; i < 16; i++) {
		for (int k1 = 0; k1 < ky; k1++) {
			\
				printf("\n");
			if (italic) {
				for (int k3 = 0; k3 < 15 - i; k3++)
					printf(" ");
			}

			for (int j = 0; j < 16; j++) {
				if (buf[i * 2 + (j / 8)] & (0x80 >> (j % 8)))
					for (int k2 = 0; k2 < kx; k2++)
						printf("%c", fill);

				else
					for (int k2 = 0; k2 < kx; k2++)
						printf(" ");
			}
		}
	}
}

void write_to_file(unsigned char* buf, int italic, int kx, int ky, char fill)

{

	FILE* fp = fopen("han.txt", "w");

	for (int i = 0; i < 16; i++) {
		for (int k1 = 0; k1 < ky; k1++) {
			fputc('\n', fp);
			if (italic) {
				for (int k3 = 0; k3 < 15 - i; k3++)
					fputc(' ', fp);
			}

			for (int j = 0; j < 16; j++) {
				if (buf[i * 2 + (j / 8)] & (0x80 >> (j % 8)))
					for (int k2 = 0; k2 < kx; k2++)
						fputc(fill, fp);
				else
					for (int k2 = 0; k2 < kx; k2++)
						fputc(' ', fp);

			}

		}

	}

	fclose(fp);

}

int set_zoom_k(int* pk)

{
	printf("请输入放大率(1-4)：");
	char buf[100];
	gets(buf);
	int n = atoi(buf);
	if (n < 1 || n>4) return -1;
	*pk = n;
	return 0;

}

char get_fill_char()

{

	for (;;) {
		printf("请输入用于填充的字符");
		char c = getch();
		if (c > 32 && c < 125) return c;
	}

}

int main(、、)

{
	system("title Zhoi 汉字测试");

	unsigned char han_zi_buf[32];  // 存储16点阵汉字的字模
	int font_italic = 0;
	int font_kx = 1;  // 水平放大率
	int font_ky = 1;  // 垂直放大率
	char fill_char = '@';  // 填充字符

	for (;;) {

		printf("\n ^^^^^^^^^^^Zhoi 汉字程序测试^^^^^^^^^^^\nDesigned by han and refered by a nice person\n");

		printf("1. 输入一个汉字\n");

		printf("2. 切换斜体\n");

		printf("3. 设置水平放大\n");

		printf("4. 设置垂直放大\n");

		printf("5. 设置填充字符\n");

		printf("6. 输出到文件han.txt\n");

		printf("7. 退出\n");

		printf("----------------\n");

		printf("请选择相应的数字\n");

		char c = (char)getch();

		switch (c) {

		case '1':

		{
			unsigned char c1;
			unsigned char c2;
			if (get_han_zi(&c1, &c2) != 0)
				printf("\n输入无效！\n");
			else {
				load_han_zi(han_zi_buf, c1, c2);
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			}
		}
		break;

		case '2':
			font_italic = (font_italic + 1) % 2;
			show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '3':
			if (set_zoom_k(&font_kx) != 0)
				printf("\n输入无效！\n");
			else
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '4':
			if (set_zoom_k(&font_ky) != 0)
				printf("\n输入无效！\n");
			else
				show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '5':
			fill_char = get_fill_char();
			show_han_zi(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '6':
			write_to_file(han_zi_buf, font_italic, font_kx, font_ky, fill_char);
			break;

		case '7':
			exit(0);
			break;

		default:
			printf("\n您的选择无效！\n");
		}
	}

}