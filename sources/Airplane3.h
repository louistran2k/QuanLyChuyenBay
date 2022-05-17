#include<iostream>
#include<string>
#include"mylib.h"
#include<fstream>
#include<iomanip>
using namespace std;

#define MAX_DS_MB 300
#define ENTER 13
#define X_NOTE 3
#define Y_NOTE 38
#define X_NOTIFY 3
#define Y_NOTIFY 36
#define X_LIST 60
#define Y_LIST 10
#define width_list 88
#define height_list 23
#define X_TITLE 103
#define Y_TITLE 6
#define X_td 103
#define Y_td 6
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define ESC 27
#define X_PAGE 133
#define Y_PAGE 33
#define X_SL 60
#define Y_SL 33
#define X_BOX 3
#define Y_BOX 9
#define QUANTITY_PER_PAGE 10
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define PAGE_DOWN 81
#define PAGE_UP 73
#define LH -1
#define EH 0
#define RH 1

const int so_item1 = 8;
const int sl_td = 5;
const int cot1 = 45;
const int dong1 = 5;
int trang_mb_hien_tai = 1;
int trang_hk_hien_tai = 1;
int sl_hk = 0;

string td[so_item1] =  {" QUAN LY MAY BAY                                         ",
						" QUAN LY CHUYEN BAY                                      ",
						" DAT VE                                                  ",
						" HUY VE                                                  ",
						" DANH SACH HANH KHACH THUOC CHUYEN BAY X                 ",
						" DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY X DEN NOI Y   ",
						" DANH SACH VE CON TRONG CUA CHUYEN BAY X                 ",
						" THOAT CHUONG TRINH                                      "};

string td_may_bay[5] = {" STT ", " So hieu may bay ", " Loai ", " So cho ", " So chuyen "};
string td_chuyen_bay[7] = {" STT ", " Ma CB ", " So hieu may bay ", " Ngay ", " Gio ", " San bay den ", " Trang thai "};
string td_hanh_khach[6] = {" STT ", " So ve ", " So CMND ", " Ho ", " Ten ", " Phai "};

string thong_bao[] =   {"So hieu may bay khong duoc vuot qua 15 ky tu. Vui long kiem tra lai.",		//0
						"Loai may bay khong vuot qua 40 ky tu. Vui long kiem tra lai.",				//1
						"So cho tren may bay khong the nho hon 20 va lon hon 300.",								//2
						"Vui long dien day du cac truong.",											//3
						"Danh sach may bay da day (=300) khong the them.",							//4
						"Khong tim thay so hieu may bay trong danh sach. Vui long kiem tra lai.",	//5
						"Mo file khong thanh cong.",												//6
						"Them thanh cong.",															//7
						"So hieu may bay da co trong danh sach. Vui long kiem tra lai.",			//8
						"Xoa thanh cong.",															//9
						"Chinh sua hoan tat.",														//10
						"So CMND phai du 9 ky tu. Vui long kiem tra lai."};							//11
						
string td_xac_nhan[3] = {"Ban co muon luu khong ?"  ,
 					     "Ban co muon thoat khong ?",
					     "Ban co muon xoa khong ?"  };



// ======================================== KHAI BAO ==============================================

// =================== PHAN CHUNG ========================
int menu_dong(string menu[], int so_item, int cot, int dong);
void khung_chinh();
void khung_phu();
void create_box(string text, int x, int y);
void normal();
void highlight();
void highlight1();
void xoa_trai();
void xoa_phai();
void xoa_xac_nhan(int y);
void menu_quan_ly_chung(int stt);
void in_thong_bao(int tb);
int xac_nhan(int y, string s1);
// END PHAN CHUNG

// ===================== MAY BAY ==========================
// ============== May bay ============
struct may_bay
{
	string so_hieu_mb; // C15
	string loai; // C40
	int so_cho=0; // >=20
	int so_chuyen=0;
};
struct ds_may_bay
{
	may_bay *ds[MAX_DS_MB];
	int sl;
};
typedef struct ds_may_bay ListPlane;
// =========================================================
void ghi_may_bay(ofstream &fout, may_bay *p);
void ghi_ds_mb(ds_may_bay ds_mb);
void doc_ds_mb(ds_may_bay &ds_mb);
// =========================================================
void menu_quan_ly_may_bay(int stt, ListPlane &ds_mb);
void khung_ds_may_bay();
void in_mb_theo_dong(may_bay *mb, int vi_tri);
void in_ds_mb_theo_trang(ds_may_bay ds);
int tong_so_trang_mb(ds_may_bay ds);
void them_may_bay(ds_may_bay &ds);
int search(ds_may_bay ds, string s);
void clear_list_mb(ds_may_bay &ds_mb);
int chon_may_bay(ds_may_bay ds);
void xoa_mb(ds_may_bay &ds);
void chinh_sua_mb(ds_may_bay &ds);
bool kiem_tra_truong_trong(may_bay *p);
void shmb_tang_dan(ds_may_bay &ds);
string tim_kiem(ds_may_bay dsmb);
void insert_order(ds_may_bay &ds, may_bay *p);
// =========================================================
void nhap_sh_mb(string &result, int &temp, bool &is_exit);
void nhap_loai_mb(string &result, int &temp, bool &is_exit);
void nhap_so_cho(int &result, int &temp, bool &is_exit);
void chuan_hoa1(string &s);
// END MAY BAY


// ======================================== HANH KHACH ==============================================
// =========================================================
struct hanh_khach
{
	string CMND;
	string ho;
	string ten;
	int phai=0; // 1: nam; 2: nu; 3: khac
};
struct node_hk
{
	hanh_khach data;
	int bal_factor;
	node_hk *left, *right;
};
typedef struct node_hk *AVL_tree;
// =========================================================
//void in_ds_hanh_khach_thuoc_cb_x(int stt, AVL_tree &T);
void khung_ds_hk_thuoc_cb();
void khoi_tao_cay(AVL_tree &T);
void rotateLL(AVL_tree &T);
void rotateLR(AVL_tree &T);
void rotateRR(AVL_tree &T);
void rotateRL(AVL_tree &T);
int balance_left(AVL_tree &T);
int balance_right(AVL_tree &T);
int insert_avl_tree(AVL_tree &T, hanh_khach data);
int search_stand_for(AVL_tree &T, AVL_tree &T1);
int delete_AVL_tree_node(AVL_tree &T, hanh_khach hk);
AVL_tree tim_hk(AVL_tree T, string cmnd);
void doc_file_hanh_khach(AVL_tree &T);
void ghi_file_hanh_khach(AVL_tree T, ofstream &fout);
void ghi_file_ds_hanh_khach(AVL_tree T);
void in_hk_theo_dong(hanh_khach hk, int vi_tri);
void nhap_cmnd(string &result, bool &is_exit);
void nhap_hoten(string &result, int &temp, bool &is_exit, int stt, int vi_tri);
void chon_gioi_tinh(int &chon, int &temp, bool &is_exit);
string them_hanh_khach(AVL_tree &T);
string chinh_sua_thong_tin_hanh_khach(AVL_tree &T, bool &is_exit, hanh_khach &hk);
void xoa_ds_hanh_khach(AVL_tree &T);
void inorder(AVL_tree T);
void chuan_hoa2(string &s);
// END HANH KHACH

// ======================================== DINH NGHIA ==============================================

// ======================================== PHAN CHUNG ==============================================		
int menu_dong(string menu[], int so_item, int cot, int dong)
{
	normal();
	show_cur(0);
	int i, chon=0, x=0;
	for(i=0 ; i<so_item ; i++)
	{
		gotoxy(cot, dong+2*i);
		cout << menu[i];
	}
	highlight();
	gotoxy(cot, dong+chon);
	cout << menu[chon];
	char kytu;
	do
	{
		kytu = getch();
		if(kytu == 0) kytu = getch();
		switch(kytu)
		{
			case UP:
			{	if(chon==0)
				{
					normal();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					chon=so_item-1;
					x=so_item-1;
					highlight();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					break;
				}
				if(chon+1 > 1)
				{
					normal();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					chon--;
					x--;
					highlight();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
				}
				break;
			}
			case DOWN:
			{
				if(chon==so_item-1) 
				{
					normal();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					chon=0;
					x=0;
					highlight();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					break;
				}
				if(chon+1 < so_item)
				{
					normal();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
					chon++;
					x++;
					highlight();
					gotoxy(cot, dong+x+chon);
					cout << menu[chon];
				}
				break;
			}
			case 13: return chon+1;
		}
	}
	while(1);
}
// ve khung chinh
void khung_chinh()
{
	SetColor(19);
	int x=cot1-3, y=1, width = 64, height = 21;
	gotoxy(x, y-1);
	cout << char(201) << setw(width-2) << setfill(char(205)) << char(187);
	for(int i=1 ; i<=height-2 ; i++)
	{
		if(i==4)
		{
			gotoxy(x, y-1+i);
			cout << char(204) << setw(width-2) << setfill(char(205)) << char(185);
		}
		else
		{
			gotoxy(x, y-1+i);
			cout << char(186) << setw(width-2) << setfill(char(32)) << char(186);
		}
	}
	gotoxy(x, y-1+height-1);
	cout << char(200) << setw(width-2) << setfill(char(205)) << char(188);
	string s = "QUAN LY CAC CHUYEN BAY";
	gotoxy(73-s.length()/2, 2);
	cout << s;
}
// ve khung phu
void khung_phu()
{
	int x=1, y=0, width = 151, height = 40;
	for(int i=1 ; i<=height ; i++)
	{
		gotoxy(x, y-1+i);
		if(i==1)
			cout << char(201) << setw(width) << setfill(char(205)) << char(187);
		else if(i>=2 && i<=4 || i==height-1 || i==height-3)
		{
			gotoxy(x, i-1); cout << char(186);
			gotoxy(width+1, i-1); cout << char(186);
		}
		else if(i==5)
			cout << char(204) << setw(55) << setfill(char(205)) << char(203)
							  << setw(96) << setfill(char(205)) << char(185);
		else if(i==height-4)
			cout << char(204) << setw(55) << setfill(char(205)) << char(202)
							  << setw(96) << setfill(char(205)) << char(185);
		else if(i==height-2)
			cout << char(204) << setw(width) << setfill(char(205)) << char(185);
		else if(i==height)
			cout << char(200) << setw(width) << setfill(char(205)) << char(188);
		else
		{
			gotoxy(x, i-1); cout << char(186);
			gotoxy(x+55, i-1); cout << char(186);
			gotoxy(width+1, i-1); cout << char(186);
		}
	}
	gotoxy(x, height - 12);
	cout << char(204) << setw(54) << setfill(char(205)) << char(205) << char(185);
}
void create_box(string text, int x, int y)
{
	gotoxy(x, y-1);
	cout << char(218) << setw(51) << setfill(char(196)) << char(191);
	gotoxy(x, y);
	cout << char(179) << text << ": " << setw(49-text.length()) << setfill(char(32)) << char(179);
	gotoxy(x, y+1);
	cout << char(192) << setw(51) << setfill(char(196)) << char(217);
}	
void normal()
{
	SetBGColor(0);
	SetColor(15);
}
void highlight()
{
	SetBGColor(20);
	SetColor(15);
}
void highlight1()
{
	SetBGColor(15);
	SetColor(0);
}
// xoa noi dung o ben trai
void xoa_trai()
{
	show_cur(0);
	for(int i=0 ; i<28 ; i++)
	{
		if(i != 22)
		{
			gotoxy(3, Y_LIST-4+i);
			cout << setw(53) << setfill(char(32)) << " ";
		}
	}
}
// xoa noi dung o ben phai
void xoa_phai()
{
	for(int i=0 ; i<30 ; i++)
	{
		gotoxy(X_LIST-3, Y_LIST-5+i);
		cout << setw(95) << setfill(char(32)) << " ";
	}
}
void xoa_xac_nhan(int y)
{
	for(int i=0 ; i<4 ; i++)
	{
		gotoxy(3, y+i);
		cout << setw(53) << setfill(char(32)) << " ";
	}
}
int xac_nhan(int y, string s1)
{
	normal();
	show_cur(0);
	string s[2] = {"  Co   ", " Khong "};
	int x[2] = {15, 36}, chon = 0, k = s[0].length()+1;
	gotoxy(28-s1.length()/2, y-2); cout << s1;
	gotoxy(x[0]-1, y-1); cout << char(218) << setw(k) << setfill(char(196)) << char(191);
	gotoxy(x[1]-1, y-1); cout << char(218) << setw(k) << setfill(char(196)) << char(191);
	gotoxy(x[0]-1, y); cout << char(179) << s[0] << char(179);
	gotoxy(x[1]-1, y); cout << char(179) << s[1] << char(179);
	gotoxy(x[0]-1, y+1); cout << char(192) << setw(k) << setfill(char(196)) << char(217);
	gotoxy(x[1]-1, y+1); cout << char(192) << setw(k) << setfill(char(196)) << char(217);
	highlight();
	gotoxy(x[chon], y); cout << s[chon];
	int key;
	while(true)
	{
		key = getch();
		if(key == 224) key = getch();
		switch(key)
		{
			case LEFT:
				if(chon == 0)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 1;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 > 1)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon--;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case RIGHT:
				if(chon == 1) 
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 0;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 < 2)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon++;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case ENTER:
				normal();
				return chon;
		}
	}
}
void menu_quan_ly_chung(int stt)
{
	normal();
	clrscr();
	SetColor(19);
	khung_phu();
	string s = td[stt];
	chuan_hoa2(s);
	gotoxy(77-s.length()/2, 2);
	cout << s;
	normal();
	gotoxy(X_NOTIFY, Y_NOTIFY);
	cout << "Thong bao: ";
}
void in_thong_bao(int tb) // tb la so thu tu cua thong bao
{
	show_cur(0);
	gotoxy(X_NOTIFY + 12,Y_NOTIFY);
	cout << thong_bao[tb];
	Sleep(1500);
	gotoxy(X_NOTIFY + 12,Y_NOTIFY);
	cout << setw(135) << setfill(char(32)) << " ";
	show_cur(1);
}
void chuan_hoa0(string &s) // tat ca la ky tu thuong
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	// chuan hoa ki tu
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
		}
	}
}
void chuan_hoa1(string &s) // in hoa chu cai dau cua moi tu
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	// chuan hoa ki tu
	if(s[0] >= 'a' && s[0] <= 'z')
	{
		s[0] -= 32;
	}
	for(int i=1 ; i<s.length() ; i++)
	{
		if(s[i] == ' ')
		{
			i++;
			if(s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] -= 32; // in hoa ki tu dau cua moi tu
			}
		}
		else
		{
			if(s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] += 32;
			}
		}
	}
}
void chuan_hoa2(string &s) // tat ca la ky tu in hoa
{
	// xoa khoang trang dau
	while(s[0] == ' ')
	{
		s.erase(s.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(s[s.length()-1] == ' ')
	{
		s.erase(s.begin() + s.length() - 1);
	}
	// xoa khoang trang giua
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == ' ' && s[i+1] == ' ')
		{
			s.erase(s.begin() + i);
			i--;
		}
	}
	// chuan hoa ki tu
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 32;
		}
	}
}



// END PHAN CHUNG



// ======================================== MAY BAY ==============================================
void ghi_may_bay(ofstream &fout, may_bay *p)
{
	chuan_hoa0(p->so_hieu_mb);
	chuan_hoa0(p->loai);
	fout << p->so_hieu_mb << "," << p->loai << "," << p->so_cho;
}
void ghi_ds_mb(ds_may_bay ds_mb)
{
	ofstream fout;
	fout.open("DSMB.TXT", ios_base::out);
	for(int i=0 ; i<ds_mb.sl ; i++)
	{
		ghi_may_bay(fout, ds_mb.ds[i]);
		if(i != (ds_mb.sl-1))
		{
			fout << endl;
		}
	}
	fout.close();
}
void doc_ds_mb(ds_may_bay &ds_mb)
{
	ifstream fin;
	fin.open("DSMB.TXT", ios_base::in);
	if(fin.fail())
	{
		in_thong_bao(6);
		return;
	}
	do
	{
		ds_mb.ds[ds_mb.sl] = new may_bay;
		string temp;
		getline(fin, ds_mb.ds[ds_mb.sl]->so_hieu_mb, ',');
		chuan_hoa2(ds_mb.ds[ds_mb.sl]->so_hieu_mb);
		getline(fin, ds_mb.ds[ds_mb.sl]->loai, ',');
		chuan_hoa2(ds_mb.ds[ds_mb.sl]->loai);
		fin >> ds_mb.ds[ds_mb.sl]->so_cho;
		if(!fin.eof())
		{
			getline(fin, temp);
		}
		ds_mb.sl++;
	}
	while(!fin.eof());
	fin.close();
}
void clear_list_mb(ds_may_bay &ds_mb)
{
	while(ds_mb.sl > 0)
	{
		delete ds_mb.ds[ds_mb.sl-1];
		ds_mb.sl--;
	}
}
// ve khung ds may bay
void khung_ds_may_bay()
{
	string tt = "DANH SACH MAY BAY";
	gotoxy(X_td-tt.length()/2, Y_td); cout << tt;
	string s = " Tim kiem: ";
	gotoxy(X_LIST, Y_LIST - 2);
	cout << char(218) << setw(width_list) << setfill(char(196)) << char(191);
	gotoxy(X_LIST, Y_LIST - 1);
	cout << char(179) << s; gotoxy(X_LIST+width_list, Y_LIST - 1); cout << char(179);
	gotoxy(X_LIST, Y_LIST);
	cout << char(195) << setw(6) << setfill(char(196)) << char(194) 
					  << setw(18) << setfill(char(196)) << char(194) 
					  << setw(43) << setfill(char(196)) << char(194) 
					  << setw(9) << setfill(char(196)) << char(194) 
					  << setw(12) << setfill(char(196)) << char(180);
	for(int i=1 ; i<=height_list-2 ; i++)
	{
		gotoxy(X_LIST, Y_LIST+i);
		if(i==1)
		{
			cout << char(179) << td_may_bay[0]; gotoxy(X_LIST+6, Y_LIST+i); cout << char(179) ;
			cout 			  << td_may_bay[1]; gotoxy(X_LIST+6+18, Y_LIST+i); cout << char(179) ;
			cout 			  << td_may_bay[2]; gotoxy(X_LIST+6+18+43, Y_LIST+i); cout << char(179);
			cout			  << td_may_bay[3]; gotoxy(X_LIST+6+18+43+9, Y_LIST+i); cout << char(179);
			cout			  << td_may_bay[4]; gotoxy(X_LIST+width_list, Y_LIST+i); cout << char(179);
		}
		else if(i==2)
		{
			cout << char(195) << setw(6) << setfill(char(196)) << char(197) 
							  << setw(18) << setfill(char(196)) << char(197) 
							  << setw(43) << setfill(char(196)) << char(197) 
							  << setw(9) << setfill(char(196)) << char(197) 
							  << setw(12) << setfill(char(196)) << char(180);
		}
		else
		{
			cout << char(179);
			gotoxy(X_LIST+6, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+18, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+18+43, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+18+43+9, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+width_list, Y_LIST+i); cout << char(179);
		}
	}
	gotoxy(X_LIST, Y_LIST+height_list-1);
	cout << char(192) << setw(6) << setfill(char(196)) << char(193) 
					  << setw(18) << setfill(char(196)) << char(193) 
					  << setw(43) << setfill(char(196)) << char(193) 
					  << setw(9) << setfill(char(196)) << char(193) 
					  << setw(12) << setfill(char(196)) << char(217);
}
void menu_quan_ly_may_bay(int stt, ds_may_bay &ds_mb)
{
	menu_quan_ly_chung(stt);
	gotoxy(X_NOTE, Y_NOTE);
	cout << "F2: Them may bay -- F3: Xoa may bay -- F4: Chinh sua thong tin -- F5: Tim kiem -- ENTER: Chon -- ESC: Quay lai -- PAGE UP/PAGE DOWN: Chuyen trang";
	khung_ds_may_bay();
	trang_mb_hien_tai = 1;
	in_ds_mb_theo_trang(ds_mb);
	char key;
	do
	{
		key = getch();
		if(key == 0 || key == 224) key = getch();
		switch(key)
		{
			case PAGE_UP:
				if(trang_mb_hien_tai > 1)
				{
					trang_mb_hien_tai--;
					xoa_phai();
					in_ds_mb_theo_trang(ds_mb);
				}
				break;
			case PAGE_DOWN:
				if(trang_mb_hien_tai < tong_so_trang_mb(ds_mb))
				{
					trang_mb_hien_tai++;
					xoa_phai();
					in_ds_mb_theo_trang(ds_mb);
				}
				break;
			case F2:
				them_may_bay(ds_mb);
				xoa_trai();
				break;
			case F3:
				xoa_mb(ds_mb);
				xoa_trai();
				gotoxy(X_LIST + 12, Y_LIST - 1);
				cout << "                                                     ";
				in_ds_mb_theo_trang(ds_mb);
				break;
			case F4:
				chinh_sua_mb(ds_mb);
				xoa_trai();
				gotoxy(X_LIST + 12, Y_LIST - 1);
				cout << "                                                     ";
				in_ds_mb_theo_trang(ds_mb);
				break;
			case F5:
				tim_kiem(ds_mb);
				gotoxy(X_LIST + 12, Y_LIST - 1);
				cout << "                                                     ";
				in_ds_mb_theo_trang(ds_mb);
				break;
			case ESC:
				break;
		}
	}
	while(key!=ESC);
}
void in_mb_theo_dong(may_bay *mb, int vi_tri)
{
	gotoxy(X_LIST+7, Y_LIST+3+vi_tri);
	cout << " " << mb->so_hieu_mb << setw(16-mb->so_hieu_mb.length()) << setfill(char(32)) << " ";
	gotoxy(X_LIST+8+17, Y_LIST+3+vi_tri);
	cout << " " << mb->loai << setw(41-mb->loai.length()) << setfill(char(32)) << " ";
	gotoxy(X_LIST+8+18+42, Y_LIST+3+vi_tri);
	cout << " " << mb->so_cho << setw(7-to_string(mb->so_cho).length()) << setfill(char(32)) << " ";
	gotoxy(X_LIST+8+18+43+8, Y_LIST+3+vi_tri);
	cout << " " << mb->so_chuyen << setw(10-to_string(mb->so_chuyen).length()) << setfill(char(32)) << " ";
}
void in_ds_mb_theo_trang(ds_may_bay ds)
{
	int i, x;
	khung_ds_may_bay();
	if(ds.sl == 0) return;
	x = (trang_mb_hien_tai-1)*10;
	for(i=0 ; ((i+x) < ds.sl && i<10) ; i++)
	{
		gotoxy(X_LIST+1, Y_LIST+3+i*2);
		cout << " " << i+1+x << setw(4-to_string(i+1+x).length()) << setfill(char(32)) << " "; // in stt
		in_mb_theo_dong(ds.ds[i+(trang_mb_hien_tai-1)*10], i*2);
	}
	gotoxy(X_SL, Y_SL); 
	cout << "So luong may bay: " << ds.sl;
	gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang: " << trang_mb_hien_tai << "/" << tong_so_trang_mb(ds);
}
int tong_so_trang_mb(ds_may_bay ds)
{
	if(ds.sl%10 == 0) return ds.sl/10;
	else return ds.sl/10 + 1;
}
void nhap_sh_mb(string &result, int &temp, bool &is_exit)
{
	int count = result.length();
	gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX);
	cout << result;
	bool is_one = false;
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 48 && key <= 57))
			{
				if(count <= 15)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
					is_one = 0;
				}
			}
			else if(key == 95)
			{
				if(count <= 15)
				{
					if(is_one == 0 && count != 0)
					{
						cout << char(key);
						result += char(key);
						count++;
						is_one = 1;
					}
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
				if(result[count-1] == 95) is_one = 1;
				else is_one = 0;
			}
			else if(key == ENTER)
			{
				temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == DOWN) temp++;
				return;
			}
			else if(key == ESC)
			{
				is_exit = 1;
				return;
			}
		}
	}
}
void nhap_loai_mb(string &result, int &temp, bool &is_exit)
{
	int count = result.length();
	gotoxy(X_BOX+td_may_bay[2].length()+3, Y_BOX+3);
	cout << result;
	bool is_one = 0;
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 48 && key <= 57))
			{
				if(count <= 40)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
					is_one = 0;
				}
			}
			else if(key == 95 || key == 32 || key == 45)
			{
				if(count <= 40)
				{
					if(is_one == 0 && count != 0)
					{
						cout << char(key);
						result += char(key);
						count++;
						is_one = 1;
					}
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
				if(result[count-1] == 95 || result[count-1] == 32 || result[count-1] == 45)
					is_one = 1;
				else
					is_one = 0;
			}
			else if(key == ENTER)
			{
				temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == DOWN)
				{
					temp++;
					return;
				}
				else if(key == UP)
				{
					temp--;
					return;
				}
			}
			else if(key == ESC)
			{
				is_exit = 1;
				return;
			}
		}
	}
}
void nhap_so_cho(int &result, int &temp, bool &is_exit)
{
	string s = to_string(result);
	int count = s.length();
	gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6);
	if(result != 0) cout << s;
	else s = "";
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if(key >= 48 && key <= 57)
			{
				result = result*10 + (key-48);
				cout << char(key);
				s += char(key);
				count++;
			}
			else if(key == 8 && s.length() > 0)
			{
				int r = result%10;
				result = (result-r)/10;
				cout << "\b" << " " << "\b";
				s.erase(s.end()-1);
				count--;
			}
			else if(key == ENTER)
			{
				temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == UP)
				{
					temp--;
					return;
				}
			}
			else if(key == ESC)
			{
				is_exit = 1;
				return;
			}
		}
	}
}
void them_may_bay(ds_may_bay &ds)
{
	xoa_trai();
	if(ds.sl == MAX_DS_MB)
	{
		in_thong_bao(4);
		return;
	}
	string s = "THEM MAY BAY";
	gotoxy(30-s.length()/2, Y_BOX-3); cout << s;
	for(int i=0 ; i<3 ; i++)
	{
		create_box(td_may_bay[i+1], X_BOX, Y_BOX+3*i);
	}
	gotoxy(X_BOX, 29);
	cout << "Note:";
	gotoxy(X_BOX, 30);
	cout << "- So hieu may bay co toi da 15 ky tu.";
	gotoxy(X_BOX, 31);
	cout << "- Loai may bay co toi da 40 ky tu.";
	gotoxy(X_BOX, 32);
	cout << "- So cho phai lon hon hoac bang 20.";
	int temp = 1; // temp la bien tam de nhan UP DOWN
	bool is_exit = 0;
	may_bay *p = new may_bay;
	try_again: // tao diem goto
	while(true)
	{
		show_cur(1);
		switch(temp)
		{
			case 1:
				nhap_sh_mb(p->so_hieu_mb, temp, is_exit);
				if(is_exit == 1)
				{
					int xn = xac_nhan(19, td_xac_nhan[1]);
					if(xn == 0)
						return;
					else
					{
						is_exit = 0;
						xoa_xac_nhan(17);
						goto try_again;
					}
				} 
				break;
			case 2:
				nhap_loai_mb(p->loai, temp, is_exit);
				if(is_exit == 1)
				{
					int xn = xac_nhan(19, td_xac_nhan[1]);
					if(xn == 0)
						return;
					else
					{
						is_exit = 0;
						xoa_xac_nhan(17);
						goto try_again;
					}
				} 
				break;
			case 3:
				nhap_so_cho(p->so_cho, temp, is_exit);
				if(is_exit == 1)
				{
					int xn = xac_nhan(19, td_xac_nhan[1]);
					if(xn == 0)
						return;
					else
					{
						is_exit = 0;
						xoa_xac_nhan(17);
						goto try_again;
					}
				} 
				break;
			case 4:
				if(kiem_tra_truong_trong(p) == 0)
				{
					if(p->so_hieu_mb.empty())
					{
						temp = 1;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX);
						break;
					}
					else if(p->loai.empty())
					{
						temp = 2;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[2].length()+3, Y_BOX+3);
						break;
					}
					else if(p->so_cho <= 0)
					{
						temp = 3;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6);
						break;
					}
				}
				else if(search(ds, p->so_hieu_mb) >= 0)
				{
					in_thong_bao(8);
					temp = 1;
					goto try_again;
					gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX);
					break;
				}
				else if(p->so_cho < 20 || p->so_cho > 300)
				{
					in_thong_bao(2);
					temp = 3;
					goto try_again;
					gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6);
					break;
				}
				else 
				{
					int xn = xac_nhan(19, td_xac_nhan[0]);
					if(xn == 0)
					{
						chuan_hoa2(p->loai);
						insert_order(ds, p);
						in_thong_bao(7);
						in_ds_mb_theo_trang(ds);
						return;
					}
					else
					{
						xoa_xac_nhan(17);
						temp = 1;
						show_cur(1);
						goto try_again;
					}
				}
		}
	}
}
// Kiem tra tat ca cac truong da co du lieu hay chua => 1: da du ; 0: chua du
bool kiem_tra_truong_trong(may_bay *p)
{
	if(!p->so_hieu_mb.empty() && !p->loai.empty() && p->so_cho > 0) return 1;
	else
	{
		in_thong_bao(3);
		return 0;
	}	
}
// Tim vi tri cua so hieu may bay
int search(ds_may_bay ds, string s)
{
	for(int i=0 ; i<ds.sl ; i++)
	{
		if(ds.ds[i]->so_hieu_mb == s)
		{
			return i;
		}
	}
	return -1;
}
int chon_may_bay(ds_may_bay ds)
{
	try_again:
	int key = 0, vi_tri_cu = 0, vi_tri_hien_tai = 0, x, y;
	if(ds.sl > 0)
	{
		highlight1();
		gotoxy(X_LIST+1, Y_LIST+3+vi_tri_hien_tai*2);
		x = vi_tri_hien_tai+1+(trang_mb_hien_tai-1)*10;
		cout << " " << x << setw(4-to_string(x).length()) << setfill(char(32)) << " ";
		in_mb_theo_dong(ds.ds[0 + (trang_mb_hien_tai-1)*10], 0);
		normal();
	}
	while(true)
	{
		while(kbhit())
		{
			key = getch();
			if(key == 224) key = getch();
			switch(key)
			{
				case UP:
				{
					if(vi_tri_hien_tai > 0)
					{
						vi_tri_cu = vi_tri_hien_tai;
						vi_tri_hien_tai--;
						highlight1();
						gotoxy(X_LIST+1, Y_LIST+3+vi_tri_hien_tai*2);
						x = vi_tri_hien_tai+1+(trang_mb_hien_tai-1)*10;
						cout << " " << x << setw(4-to_string(x).length()) << setfill(char(32)) << " ";
						in_mb_theo_dong(ds.ds[vi_tri_hien_tai+ (trang_mb_hien_tai-1)*10], vi_tri_hien_tai*2);
						normal();
						in_mb_theo_dong(ds.ds[vi_tri_cu+ (trang_mb_hien_tai-1)*10], vi_tri_cu*2);
						gotoxy(X_LIST+1, Y_LIST+3+vi_tri_cu*2);
						y = vi_tri_cu+1+(trang_mb_hien_tai-1)*10;
						cout << " " << y << setw(4-to_string(y).length()) << setfill(char(32)) << " ";
					}
					break;
				}
				case DOWN:
				{
					if(vi_tri_hien_tai < QUANTITY_PER_PAGE-1 && vi_tri_hien_tai + (trang_mb_hien_tai-1)*10 < ds.sl-1)
					{
						vi_tri_cu = vi_tri_hien_tai;
						vi_tri_hien_tai++;
						highlight1();
						gotoxy(X_LIST+1, Y_LIST+3+vi_tri_hien_tai*2);
						x = vi_tri_hien_tai+1+(trang_mb_hien_tai-1)*10;
						cout << " " << x << setw(4-to_string(x).length()) << setfill(char(32)) << " ";
						in_mb_theo_dong(ds.ds[vi_tri_hien_tai+ (trang_mb_hien_tai-1)*10], vi_tri_hien_tai*2);
						normal();
						in_mb_theo_dong(ds.ds[vi_tri_cu+ (trang_mb_hien_tai-1)*10], vi_tri_cu*2);
						gotoxy(X_LIST+1, Y_LIST+3+vi_tri_cu*2);
						y = vi_tri_cu+1+(trang_mb_hien_tai-1)*10;
						cout << " " << y << setw(4-to_string(y).length()) << setfill(char(32)) << " ";
					}
					break;
				}
				case PAGE_UP:
				{
					if(trang_mb_hien_tai > 1)
					{
						trang_mb_hien_tai--;
						xoa_phai();
						in_ds_mb_theo_trang(ds);
						goto try_again;
					}
					break;
				}
				case PAGE_DOWN:
				{
					if(trang_mb_hien_tai < tong_so_trang_mb(ds))
					{
						trang_mb_hien_tai++;
						xoa_phai();
						in_ds_mb_theo_trang(ds);
						goto try_again;
					}
					break;
				}
				case ENTER:
				{
					return vi_tri_hien_tai + (trang_mb_hien_tai-1)*10;
				}
				case ESC:
				{
					normal();
					return -1;
				}
				case F5:
					string s = tim_kiem(ds);
					if(s != "")
						return search(ds, s);
					else
						return -1;
			}
		}
	}
}
void xoa_mb(ds_may_bay &ds)
{
	int x = chon_may_bay(ds);
	if(x < 0) return;
	if(x >= 0)
	{
		string s = "XOA MAY BAY";
		gotoxy(28-s.length()/2, Y_BOX-3); cout << s;
		int xn = xac_nhan(11, td_xac_nhan[2]);
		if(xn == 0)
		{
			delete ds.ds[x];
			for(int i=x ; i<ds.sl-1 ; i++)
			{
				ds.ds[i] = ds.ds[i+1];
			}
			ds.sl--;
			in_thong_bao(9);
			in_ds_mb_theo_trang(ds);
		}
		else
		{
			normal();
			xoa_trai();
			return;
		}
	}
}
void chinh_sua_mb(ds_may_bay &ds)
{
	show_cur(0);
	int x = chon_may_bay(ds);
	if(x < 0) return;
	bool is_exit = 0;
	if(x >= 0)
	{
		string s = "CHINH SUA MAY BAY";
		gotoxy(30-s.length()/2, Y_BOX-3); cout << s;
		for(int i=0 ; i<3 ; i++)
		{
			create_box(td_may_bay[i+1], X_BOX, Y_BOX+3*i);
		}
		gotoxy(X_BOX, 30);
		cout << "Note:";
		gotoxy(X_BOX, 31);
		cout << "- So hieu may bay co toi da 15 ky tu.";
		gotoxy(X_BOX, 32);
		cout << "- Loai may bay co toi da 40 ky tu.";
		gotoxy(X_BOX, 33);
		cout << "- So cho phai lon hon hoac bang 20.";
		string shmb, lmb;
		int sc;
		shmb = ds.ds[x]->so_hieu_mb;
		lmb = ds.ds[x]->loai;
		sc = ds.ds[x]->so_cho;
		gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX); cout << shmb;
		gotoxy(X_BOX+td_may_bay[2].length()+3, Y_BOX+3); cout << lmb;
		gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6); cout << sc;
		int temp = 1;
		try_again:
		while(true)
		{
			show_cur(1);
			switch(temp)
			{
				case 1:
					nhap_sh_mb(shmb, temp, is_exit);
					if(is_exit == 1)
					{
						int xn = xac_nhan(19, td_xac_nhan[1]);
						if(xn == 0)
							return;
						else
						{
							is_exit = 0;
							xoa_xac_nhan(17);
							goto try_again;
						}
					}
					break;
				case 2:
					nhap_loai_mb(lmb, temp, is_exit);
					if(is_exit == 1)
					{
						int xn = xac_nhan(19, td_xac_nhan[1]);
						if(xn == 0)
							return;
						else
						{
							is_exit = 0;
							xoa_xac_nhan(17);
							goto try_again;
						}
					}
					break;
				case 3:
					nhap_so_cho(sc, temp, is_exit);
					if(is_exit == 1)
					{
						int xn = xac_nhan(19, td_xac_nhan[1]);
						if(xn == 0)
							return;
						else
						{
							is_exit = 0;
							xoa_xac_nhan(17);
							goto try_again;
						}
					}
					break;
				case 4:
					if(shmb.empty())
					{
						in_thong_bao(3);
						temp = 1;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX);
						break;
					}
					else if(lmb.empty())
					{
						in_thong_bao(3);
						temp = 2;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[2].length()+3, Y_BOX+3);
						break;
					}
					else if(sc <= 0)
					{
						in_thong_bao(3);
						temp = 3;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6);
						break;
					}
					else if(sc < 20 && sc > 300)
					{
						in_thong_bao(2);
						temp = 3;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[3].length()+3, Y_BOX+6);
						break;
					}
					else if(search(ds, shmb) >= 0 && search(ds, shmb) != x)
					{
						in_thong_bao(8);
						temp = 1;
						goto try_again;
						gotoxy(X_BOX+td_may_bay[1].length()+3, Y_BOX);
						break;
					}
					else 
					{
						int xn = xac_nhan(19, td_xac_nhan[0]);
						if(xn == 0)
						{
							chuan_hoa2(lmb);
							ds.ds[x]->so_hieu_mb = shmb;
							ds.ds[x]->loai = lmb;
							ds.ds[x]->so_cho = sc;
							in_thong_bao(10);
							shmb_tang_dan(ds);
							in_ds_mb_theo_trang(ds);
							return;
						}
						else
							return;
					}
			}
			
		}
	}
	
}
// Sap xep shmb tang dan = insertion sort
void shmb_tang_dan(ds_may_bay &ds)
{
	may_bay *p;
	int i, j;
	for(i = 1 ; i < ds.sl ; i++)
	{
		p = ds.ds[i];
		for(j = i-1 ; j >= 0 && p->so_hieu_mb.compare(ds.ds[j]->so_hieu_mb) < 0 ; j--)
			ds.ds[j+1] = ds.ds[j];
		ds.ds[j+1] = p;
	}
}
void insert_order(ds_may_bay &ds, may_bay *p)
{
	int temp;
	for(int i=0 ; i<ds.sl ; i++)
	{
		if(p->so_hieu_mb > ds.ds[i]->so_hieu_mb && p->so_hieu_mb <= ds.ds[i+1]->so_hieu_mb)
		{
			temp = i+1;
			break;
		}
	}
	for(int i=ds.sl ; i>temp ; i--)
	{
		ds.ds[i] = ds.ds[i-1];
	}
	ds.ds[temp] = p;
	ds.sl++;
}
string tim_kiem(ds_may_bay dsmb)
{
	show_cur(1);
	string result, temp;
	int vi_tri = 0, count = 0, temp1, temp2, temp3;
	bool is_one = 0;
	gotoxy(X_LIST + 12, Y_LIST - 1);
	ds_may_bay ds_tam;
	while(true)
	{
		if(kbhit())
		{
			gotoxy(X_LIST + 12, Y_LIST - 1);
			cout << result;
			int key = getch();
			if(key == 224) key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 48 && key <= 57))
			{
				if(count <= 40)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
					is_one = 0;
				}
			}
			else if(key == 95 || key == 32 || key == 45)
			{
				if(count <= 40)
				{
					if(is_one == 0)
					{
						cout << char(key);
						result += char(key);
						count++;
						is_one = 1;
					}
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
				if(result[count-1] == 95 || result[count-1] == 32 || result[count-1] == 45)
					is_one = 1;
				else
					is_one = 0;
			}
			else if(key == ENTER)
			{
				show_cur(0);
				temp3 = chon_may_bay(ds_tam);
				if(temp3 < 0)
					temp = "";
				else
					temp = ds_tam.ds[temp3]->so_hieu_mb;
				return temp;
			}
			else if(key == ESC)
			{
				gotoxy(X_LIST + 12, Y_LIST - 1);
				cout << "                                                     ";
				in_ds_mb_theo_trang(dsmb);
				show_cur(0);
				temp = "";
				return temp;
			}
			show_cur(0);
			for(int i=0 ; i<19 ; i++)
			{
				gotoxy(X_LIST+1, Y_LIST+3+i); cout << setw(86) << setfill(char(32)) << " ";
				gotoxy(X_LIST+6, Y_LIST+3+i); cout << char(179);
				gotoxy(X_LIST+6+18, Y_LIST+3+i); cout << char(179);
				gotoxy(X_LIST+6+18+43, Y_LIST+3+i); cout << char(179);
				gotoxy(X_LIST+6+18+43+9, Y_LIST+3+i); cout << char(179);
			}
			vi_tri = 0;
			for(int i=0 ; i<dsmb.sl ; i++)
			{
				temp1 = dsmb.ds[i]->so_hieu_mb.find(result);
				temp2 = dsmb.ds[i]->loai.find(result);
				if(temp1!=-1 || temp2!=-1)
				{
					if(vi_tri < 10)
					{
						ds_tam.ds[vi_tri] = dsmb.ds[i];
						gotoxy(X_LIST+3, Y_LIST+3+vi_tri*2);
						cout << temp1;
						gotoxy(X_LIST+1, Y_LIST+3+vi_tri*2);
						cout << " " << vi_tri+1 << setw(4-to_string(vi_tri+1).length()) << setfill(char(32)) << " "; // in stt
						in_mb_theo_dong(dsmb.ds[i], vi_tri*2);
						vi_tri++;
						ds_tam.sl = vi_tri;
					}
				}
			}
			show_cur(1);
			gotoxy(X_LIST + 12 + count, Y_LIST - 1);
		}
	}
}



// END MAY BAY


// ======================================== HANH KHACH ==============================================
// ve khung ds hanh khach thuoc chuyen bay X
void khung_ds_hk_thuoc_cb()
{
	string tt1 = "DANH SACH HANH KHACH THUOC CHUYEN BAY                ";
	gotoxy(X_td-tt1.length()/2, Y_td); cout << tt1;
	string tt2 = "Ngay gio khoi hanh:      ,           . Noi den:                    ";
	gotoxy(X_td-tt2.length()/2, Y_td+1); cout << tt2;
	gotoxy(X_LIST, Y_LIST);
	cout << char(218) << setw(6) << setfill(char(196)) << char(194) 
					  << setw(8) << setfill(char(196)) << char(194) 
					  << setw(12) << setfill(char(196)) << char(194) 
					  << setw(35) << setfill(char(196)) << char(194) 
					  << setw(20) << setfill(char(196)) << char(194) 
					  << setw(7) << setfill(char(196)) << char(191);
	for(int i=1 ; i<=height_list-2 ; i++)
	{
		gotoxy(X_LIST, Y_LIST+i);
		if(i==1)
		{
			cout << char(179) << td_hanh_khach[0]; gotoxy(X_LIST+6, Y_LIST+i); cout << char(179);
			cout			  << td_hanh_khach[1]; gotoxy(X_LIST+6+8, Y_LIST+i); cout << char(179);
			cout 			  << td_hanh_khach[2]; gotoxy(X_LIST+6+8+12, Y_LIST+i); cout << char(179);
			cout			  << td_hanh_khach[3]; gotoxy(X_LIST+6+8+12+35, Y_LIST+i); cout << char(179);
			cout			  << td_hanh_khach[4]; gotoxy(X_LIST+6+8+12+35+20, Y_LIST+i); cout << char(179);
			cout			  << td_hanh_khach[5]; gotoxy(X_LIST+width_list, Y_LIST+i); cout << char(179);
		}
		else if(i==2)
		{
			cout << char(195) << setw(6) << setfill(char(196)) << char(197) 
							  << setw(8) << setfill(char(196)) << char(197) 
							  << setw(12) << setfill(char(196)) << char(197) 
							  << setw(35) << setfill(char(196)) << char(197) 
							  << setw(20) << setfill(char(196)) << char(197) 
							  << setw(7) << setfill(char(196)) << char(180);
		}
		else
		{
			cout << char(179);
			gotoxy(X_LIST+6, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+8, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+8+12, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+8+12+35, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+6+8+12+35+20, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+width_list, Y_LIST+i); cout << char(179);
		}
	}
	gotoxy(X_LIST, Y_LIST+height_list-1);
	cout << char(192) << setw(6) << setfill(char(196)) << char(193) 
					  << setw(8) << setfill(char(196)) << char(193) 
					  << setw(12) << setfill(char(196)) << char(193) 
					  << setw(35) << setfill(char(196)) << char(193) 
					  << setw(20) << setfill(char(196)) << char(193) 
					  << setw(7) << setfill(char(196)) << char(217);
}
void khoi_tao_cay(AVL_tree &T)
{
	T = NULL;
}
void rotateLL(AVL_tree &T)
{
	AVL_tree T1 = T->left;
	T->left = T1->right;
	T1->right = T;
	switch(T1->bal_factor)
	{
		case LH:
			T->bal_factor = EH;
			T1->bal_factor = EH;
			break;
		case EH:
			T->bal_factor = LH;
			T1->bal_factor = RH;
			break;
	}
	T = T1;
}
void rotateRR(AVL_tree &T)
{
	AVL_tree T1 = T->right;
	T->right = T1->left;
	T1->left = T;
	switch(T1->bal_factor)
	{
		case RH:
			T->bal_factor = EH;
			T1->bal_factor = EH;
			break;
		case EH:
			T->bal_factor = RH;
			T1->bal_factor = LH;
			break;
	}
	T = T1;
}
void rotateLR(AVL_tree &T)
{
	AVL_tree T1 = T->left;
	AVL_tree T2 = T1->right;
	T1->right = T2->left;
	T2->left = T1;
	T->left = T2->right;
	T2->right = T;
	switch(T2->bal_factor)
	{
		case LH:
			T->bal_factor = RH;
			T1->bal_factor = EH;
			break;
		case EH:
			T->bal_factor = EH;
			T1->bal_factor = EH;
			break;
		case RH:
			T->bal_factor = EH;
			T1->bal_factor = LH;
			break;
	}
	T2->bal_factor = EH;
	T = T2;
}
void rotateRL(AVL_tree &T)
{
	AVL_tree T1 = T->right;
	AVL_tree T2 = T1->left;
	T1->left = T2->right;
	T2->right = T1;
	T->right = T2->left;
	T2->left = T;
	switch(T2->bal_factor)
	{
		case RH:
			T->bal_factor = LH;
			T1->bal_factor = EH;
			break;
		case EH:
			T->bal_factor = EH;
			T1->bal_factor = EH;
			break;
		case LH:
			T->bal_factor = EH;
			T1->bal_factor = RH;
			break;
	}
	T2->bal_factor = 0;
	T = T2;
}
int balance_left(AVL_tree &T)
{
	switch(T->left->bal_factor)
	{
		case LH:
			rotateLL(T);
			return 2;
		case EH:
			rotateLL(T);
			return 1;
		case RH:
			rotateLR(T);
			return 2;
	}
}
int balance_right(AVL_tree &T)
{
	switch(T->right->bal_factor)
	{
		case RH:
			rotateRR(T);
			return 2;
		case EH:
			rotateRR(T);
			return 1;
		case LH:
			rotateRL(T);
			return 2;
	}
}
int insert_avl_tree(AVL_tree &T, hanh_khach data)
{
	int res;
	if(T != NULL)
	{
		if(T->data.CMND.compare(data.CMND) == 0)
		{
			return 0;
		}
		else if(T->data.CMND.compare(data.CMND) > 0)
		{
			res = insert_avl_tree(T->left, data);
			if(res < 2)
			{
				return res;
			}
			switch(T->bal_factor)
			{
				case RH:
					T->bal_factor = EH;
					return 1;
				case EH:
					T->bal_factor = LH;
					return 2;
				case LH:
					balance_left(T);
					return 1;
			}
		}
		else
		{
			res = insert_avl_tree(T->right, data);
			if(res < 2)
			{
				return res;
			}
			switch(T->bal_factor)
			{
				case LH:
					T->bal_factor = EH;
					return 1;
				case EH:
					T->bal_factor = RH;
					return 2;
				case RH:
					balance_right(T);
					return 1;
			}
		}
	}
	T = new node_hk;
	T->data = data;
	T->bal_factor = EH;
	T->left = NULL;
	T->right = NULL;
	return 2;
}
int search_stand_for(AVL_tree &T, AVL_tree &T1)
{
	int res;
	if(T1->left != NULL)
	{
		res = search_stand_for(T, T1->left);
		if(res < 2)
			return res;
		switch(T1->bal_factor)
		{
			case LH: 
				T1->bal_factor = EH;
				return 2;
			case EH:
				T1->bal_factor = RH;
				return 1;
			case RH:
				return balance_right(T1);
		}
	}
	else
	{
		T->data.CMND = T1->data.CMND;
		T = T1;
		T1 = T1->right;
		return 2;
	}
}
int delete_AVL_tree_node(AVL_tree &T, hanh_khach hk)
{
	int res;
	if(T == NULL)
		return 0;
	if(T->data.CMND > hk.CMND)
	{
		res = delete_AVL_tree_node(T->left, hk);
		if(res < 2)
			return res;
		switch(T->bal_factor)
		{
			case LH:
				T->bal_factor = EH;
				return 2;
			case EH:
				T->bal_factor = RH;
				return 1;
			case RH:
				return balance_right(T);
		}
	}
	else if(T->data.CMND < hk.CMND)
	{
		res = delete_AVL_tree_node(T->right, hk);
		if(res < 2)
			return res;
		switch(T->bal_factor)
		{
			case RH:
				T->bal_factor = EH;
				return 2;
			case EH:
				T->bal_factor = LH;
				return 1;
			case LH:
				return balance_left(T);
		}
	}
	else
	{
		AVL_tree T1 = T;
		if(T->left == NULL)
		{
			T = T->right;
			res = 2;
		}
		else if(T->right == NULL)
		{
			T = T->left;
			res = 2;
		}
		else
		{
			res = search_stand_for(T1, T->right);
			if(res < 2)
				return res;
			switch(T->bal_factor)
			{
				case RH:
					T->bal_factor = EH;
					return 2;
				case EH:
					T->bal_factor = LH;
					return 1;
				case LH:
					return balance_left(T);
			}
			delete T1;
			return res;
		}
	}
}
void doc_file_hanh_khach(AVL_tree &T)
{
	ifstream fin;
	fin.open("DSHK.txt", ios_base::in);
	if(fin.fail())
	{
		in_thong_bao(6);
		return;
	}
	while(!fin.eof())
	{
		hanh_khach hk;
		getline(fin, hk.CMND,',');
		getline(fin, hk.ho,',');
		getline(fin, hk.ten,',');
		fin >> hk.phai;
		string temp;
		getline(fin, temp);
		if(T == NULL)
		{
			node_hk* p = new node_hk;
			p->data = hk;
			p->bal_factor = 0;
			p->left = NULL;
			p->right = NULL;
			T = p;
		}
		else
		{
			insert_avl_tree(T, hk);
		}
		sl_hk++;
	}
	fin.close();
}
void ghi_file_hanh_khach(AVL_tree T, ofstream &fout)
{
	if(T != NULL && !T->data.CMND.empty())
	{
		ghi_file_hanh_khach(T->left, fout);
		fout << T->data.CMND << "," << T->data.ho << "," << T->data.ten << "," << T->data.phai;
		fout << endl;
		ghi_file_hanh_khach(T->right, fout);
	}
}
void ghi_file_ds_hanh_khach(AVL_tree T)
{
	ofstream fout;
	fout.open("DSHK.TXT", ios_base::out);
	ghi_file_hanh_khach(T, fout);
	fout.close();
}
AVL_tree tim_hk(AVL_tree T, string cmnd)
{
	if(T!=NULL)
	{
		AVL_tree p;
		p = T;
		while(p != NULL)
		{
			if(p->data.CMND == cmnd)
			{
				return p;
			}
			else if(p->data.CMND > cmnd)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
	}
	return NULL;
}
void in_hk_theo_dong(hanh_khach hk, int vi_tri)
{
	gotoxy(X_LIST+15, Y_LIST+3+vi_tri);
	cout << " " << hk.CMND;
	gotoxy(X_LIST+15+12, Y_LIST+3+vi_tri);
	cout << " " << hk.ho;
	gotoxy(X_LIST+15+12+35, Y_LIST+3+vi_tri);
	cout << " " << hk.ten;
	gotoxy(X_LIST+15+12+35+20, Y_LIST+3+vi_tri);
	if(hk.phai == 0)	cout << " Nam ";
	else if(hk.phai == 1)	cout << " Nu  ";
	else cout << " Khac";
}
void nhap_cmnd(string &result, bool &is_exit)
{
	show_cur(1);
	int count = result.length();
	gotoxy(X_BOX+td_hanh_khach[2].length()+3, Y_BOX);
	cout << result;
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if(key >= 48 && key <= 57)
			{
				if(count < 9)
				{
					cout << char(key);
					result += char(key);
					count++;
				}
			}
			else if(key == 8 && result.length() > 0)
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
			}
			else if(key == ENTER)
			{
				return;
			}
			else if(key == ESC)
			{
				is_exit = 1;
				return;
			}
		}
	}
}
void nhap_hoten(string &result, int &temp, bool &is_exit, int stt, int vi_tri)
{
	show_cur(1);
	int count = result.length();
	gotoxy(X_BOX+td_hanh_khach[stt].length()+3, Y_BOX + vi_tri);
	cout << result;
	bool is_one = false;
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122))
			{
				if(count <= 100)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
					is_one = 0;
				}
			}
			else if(key == 32 || key == 39 || key == 46)
			{
				if(count <= 100)
				{
					if(is_one == 0 && count != 0)
					{
						cout << char(key);
						result += char(key);
						count++;
						is_one = 1;
					}
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
				if(result[count-1] == 39 || result[count-1] == 32 || result[count-1] == 46)
					is_one = 1;
				else
					is_one = 0;
			}
			else if(key == ENTER)
			{
				temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == DOWN)
				{
					if(temp < 3) temp++;
					return;
				}
				else if(key == UP)
				{
					if(temp > 1) temp--;
					return;
				}
			}
			else if(key == ESC)
			{
				is_exit = 1;
				return;
			}
		}
	}
}
void chon_gioi_tinh(int &chon, int &temp, bool &is_exit)
{
	normal();
	show_cur(0);
	string s[3] = {" Nam  ", " Nu   ", " Khac "};
	int x[3] = {12, 27, 43}, y = 18;
	for(int i=0 ; i<3 ; i++)
	{
		gotoxy(x[i], y); cout << s[i];
	}
	highlight();
	gotoxy(x[chon], y); cout << s[chon];
	int key;
	while(true)
	{
		key = getch();
		if(key == 224) key = getch();
		switch(key)
		{
			case LEFT:
				if(chon == 0)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 2;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 > 1)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon--;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case RIGHT:
				if(chon == 2) 
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon = 0;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
					break;
				}
				if(chon+1 < 3)
				{
					normal();
					gotoxy(x[chon], y); cout << s[chon];
					chon++;
					highlight();
					gotoxy(x[chon], y); cout << s[chon];
				}
				break;
			case UP:
				temp--;
				normal();
				show_cur(1);
				return;
			case DOWN:
				temp++;
				normal();
				show_cur(1);
				return;
			case ENTER:
				temp++;
				normal();
				return;
			case ESC: 
				is_exit = 1;
				return;
		}
	}
}
string them_hanh_khach(AVL_tree &T)
{
	show_cur(1);
	hanh_khach hk;
	bool is_exit = 0;
	int temp = 1, f = 1;
	string s1 = "NHAP THONG TIN";
	gotoxy(30-s1.length()/2, Y_BOX-3); cout << s1;
	create_box(td_hanh_khach[2], X_BOX, Y_BOX);
	again:
	nhap_cmnd(hk.CMND, is_exit);
	if(is_exit == 1)
	{
		int xn = xac_nhan(19, td_xac_nhan[1]);
		if(xn == 0)
			return "";
		else
		{
			is_exit = 0;
			xoa_xac_nhan(17);
			goto again;
		}
	}
	if(hk.CMND.length() < 9)
	{
		in_thong_bao(11);
		goto again;
	}
	if(tim_hk(T, hk.CMND) == NULL)
	{
		try_again: // tao diem goto
		for(int i=1 ; i<4 ; i++)
		{
			create_box(td_hanh_khach[2+i], X_BOX, Y_BOX+3*i);
		}
		while(true)
		{
			f = temp;
			switch(f)
			{
				case 1:
					nhap_hoten(hk.ho, temp, is_exit, 3, 3);
					if(is_exit == 1)
					{
						int xn = xac_nhan(22, td_xac_nhan[1]);
						if(xn == 0)
							return "";
						else
						{
							is_exit = 0;
							xoa_xac_nhan(20);
							goto try_again;
						}
					}
					break;
				case 2:
					nhap_hoten(hk.ten, temp, is_exit, 4, 6);
					if(is_exit == 1)
					{
						int xn = xac_nhan(22, td_xac_nhan[1]);
						if(xn == 0)
							return "";
						else
						{
							is_exit = 0;
							xoa_xac_nhan(20);
							goto try_again;
						}
					}
					break;
				case 3:
					chon_gioi_tinh(hk.phai, temp, is_exit);
					if(is_exit == 1)
					{
						int xn = xac_nhan(22, td_xac_nhan[1]);
						if(xn == 0)
							return "";
						else
						{
							is_exit = 0;
							xoa_xac_nhan(20);
							goto try_again;
						}
					}
					break;
				case 4:
					if(hk.ho.empty())
					{
						in_thong_bao(3);
						temp = 1;
						goto try_again;
						gotoxy(X_BOX+td_hanh_khach[3].length()+3, Y_BOX+3);
						break;
					}
					else if(hk.ten.empty())
					{
						in_thong_bao(3);
						temp = 2;
						goto try_again;
						gotoxy(X_BOX+td_hanh_khach[4].length()+3, Y_BOX+6);
						break;
					}
					else 
					{
						int xn = xac_nhan(22, td_xac_nhan[0]);
						if(xn == 0)
						{
							chuan_hoa2(hk.ho);
							chuan_hoa2(hk.ten);
							insert_avl_tree(T, hk);
							in_thong_bao(7);
							xoa_trai();
							return hk.CMND;
						}
						else
						{
							xoa_xac_nhan(20);
							temp = 1;
							gotoxy(X_BOX + td_hanh_khach[3].length() + 3, Y_BOX+3);
							cout << hk.ho;
							gotoxy(X_BOX + td_hanh_khach[4].length() + 3, Y_BOX+6);
							cout << hk.ten;
							normal();
							show_cur(0);
							string s[3] = {" Nam  ", " Nu   ", " Khac "};
							int x[3] = {12, 27, 43}, y = 18;
							for(int i=0 ; i<3 ; i++)
							{
								gotoxy(x[i], y); cout << s[i];
							}
							highlight();
							gotoxy(x[hk.phai], y); cout << s[hk.phai];
							normal();
							goto try_again;
						}
					}
			}
		}
	}
	else
	{
		AVL_tree T1 = tim_hk(T, hk.CMND);
		for(int i=1 ; i<4 ; i++)
		{
			create_box(td_hanh_khach[2+i], X_BOX, Y_BOX+3*i);
		}
		hanh_khach hk;
		hk.CMND = T1->data.CMND;
		hk.ho = T1->data.ho;
		hk.ten = T1->data.ten;
		hk.phai = T1->data.phai;
		gotoxy(X_BOX + td_hanh_khach[3].length() + 3, Y_BOX+3);
		cout << hk.ho;
		gotoxy(X_BOX + td_hanh_khach[4].length() + 3, Y_BOX+6);
		cout << hk.ten;
		normal();
		show_cur(0);
		string s[3] = {" Nam  ", " Nu   ", " Khac "};
		int x[3] = {12, 27, 43}, y = 18;
		for(int i=0 ; i<3 ; i++)
		{
			gotoxy(x[i], y); cout << s[i];
		}
		highlight();
		gotoxy(x[hk.phai], y); cout << s[hk.phai];
		normal();
		
		return chinh_sua_thong_tin_hanh_khach(T, is_exit, hk);
		if(is_exit == 1) return "";
	}
}
string chinh_sua_thong_tin_hanh_khach(AVL_tree &T, bool &is_exit, hanh_khach &hk)
{
	int key;
	while(true)
	{
		if(kbhit())
		{
			key = getch();
			if(key == F2)
			{
				normal();
				show_cur(1);
				int f = 1, temp = 1;
				try_again:
				while(true)
				{
					f = temp;
					switch(f)
					{
						case 1:
							nhap_hoten(hk.ho, temp, is_exit, 3, 3);
							if(is_exit == 1)
							{
								int xn = xac_nhan(22, td_xac_nhan[1]);
								if(xn == 0)
									return "";
								else
								{
									temp = 1;
									is_exit = 0;
									xoa_xac_nhan(20);
								}
							}
							break;
						case 2:
							nhap_hoten(hk.ten, temp, is_exit, 4, 6);
							if(is_exit == 1)
							{
								int xn = xac_nhan(22, td_xac_nhan[1]);
								if(xn == 0)
									return "";
								else
								{
									temp = 1;
									is_exit = 0;
									xoa_xac_nhan(20);
								}
							}
							break;
						case 3:
							chon_gioi_tinh(hk.phai, temp, is_exit);
							if(is_exit == 1)
							{
								int xn = xac_nhan(22, td_xac_nhan[1]);
								if(xn == 0)
									return "";
								else
								{
									temp = 1;
									is_exit = 0;
									xoa_xac_nhan(20);
								}
							}
							break;
						case 4:
							if(hk.ho.empty())
							{
								in_thong_bao(3);
								temp = 1;
								goto try_again;
								gotoxy(X_BOX+td_hanh_khach[3].length()+3, Y_BOX);
								break;
							}
							if(hk.ten.empty())
							{
								in_thong_bao(3);
								temp = 2;
								goto try_again;
								gotoxy(X_BOX+td_hanh_khach[4].length()+3, Y_BOX);
								break;
							}
							else 
							{
								int xn = xac_nhan(22, td_xac_nhan[0]);
								if(xn == 0)
								{
									chuan_hoa2(hk.ho);
									chuan_hoa2(hk.ten);
									delete_AVL_tree_node(T, hk);
									insert_avl_tree(T, hk);
									in_thong_bao(10);
									is_exit == 1;
									xoa_trai();
									return hk.CMND;
								}
								else
								{
									xoa_xac_nhan(20);
									temp = 1;
									goto try_again;
								}
							}
					}
				}
	
			}
			else if(key == ENTER)
			{
				is_exit == 1;
				xoa_trai();
				return hk.CMND;
			}
		}	
	}
}
void xoa_ds_hanh_khach(AVL_tree &T)
{
	if(T != NULL)
	{
		xoa_ds_hanh_khach(T->left);
		xoa_ds_hanh_khach(T->right);
		delete_AVL_tree_node(T, T->data);
	}
}
//void inorder(AVL_tree T)
//{
//	if(T != NULL)
//	{
//		inorder(T->left);
//		cout << T->data.CMND << endl;
//		inorder(T->right);
//	}
//}




// END HANH KHACH
