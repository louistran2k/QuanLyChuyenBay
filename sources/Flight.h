#pragma once
#include <string>
#include "Ngay_Gio.h"
#include "Airplane3.h"
#include <windows.h>
struct Ticket{
	string cmnd;
};
struct ListTicket {
    Ticket *dstk;
    int SoVeDaDat;
    int SoVeMax;
};
struct Flight{
	string idcb;
	Date NgayKhoiHanh;
	Hour GioKhoiHanh;
	string SanBayDen;
	int stt; //0: huy chuyen - 1:con ve - 2: het ve - 3:hoan tat
	string idplane;
	ListTicket lst;
		
};
typedef struct Flight FLIGHT;
struct node{
	FLIGHT data;
	node *pNext;
};
typedef struct node NODE;
struct ListFlight{
	int n=0;
	node* pHead, * pTail;
};

//==========================DINH NGHIA========================
void Input_idflight(string &result, int &temp);
Date Input_date(Date &n, int &main_temp);
void ValidateDate(int count, int &tam, int &main_temp, Date &result);
void ValidateHour(int count, int &tam, int &main_temp, Hour &result);
Hour Input_time(Hour &n, int &main_temp, Date n_ngay);
void in_thong_bao_cb(int tb);
void Input_place(string &result, int &temp);
void Choose_idplane(string &n, int &main_temp, ListPlane dsmb1);
void xoa_phai_cb();
void khung_ds_chuyen_bay();
void menu_quan_ly_chuyen_bay(int stt, ListPlane dsmb, ListFlight dscb, FLIGHT cb);
void XuatChuyenBay(FLIGHT cb);
void XuatDanhSachChuyenBay(ListFlight l);
//==========================Ve================================
void menu_quan_ly_ve_may_bay(int stt, ListFlight dscb, AVL_tree &T);
int Chon_Chuyen_Bay(ListFlight dscb);
void in_ds_ve(ListFlight &dscb, AVL_tree &T);
void GheTrongCuaChuyenBay(ListFlight dscb);
void Huy_ve(int stt,ListFlight &dscb, AVL_tree T);
void ValidateCMND(string &cmnd);
void InChuyenBayTheoNgay(int stt, ListFlight dscb);
int trang_cb_ht  =  1;
//================================================================
void cap_nhat_so_chuyen_cho_may_bay(ListFlight lf, ds_may_bay &ds_mb);
int tong_so_trang_hk(FLIGHT fl);
void in_ds_hanh_khach_theo_trang(FLIGHT fl, AVL_tree T, int &temp);
void in_ds_hanh_khach_thuoc_chuyen_bay_x(int stt, AVL_tree T, ListFlight fl);
//================================================================
string thong_bao_cb[] = {"Ngay khong hop le!!! Moi nhap lai",				//0
						 "Gio khong hop le!! Moi nhap lai	",				//1
						 "Ma chuyen bay da ton tai!! Moi nhap lai",			//2
						 "Khong duoc de trong!!Moi nhap",					//3
						 "Chuyen bay khong the cap nhat!! Moi chon lai",	//4
						 "Ban da dat ve o chuyen bay nay!!",				//5
						 "Khong co chuyen bay kha dung!!!",					//6
						 "Dat ve thanh cong.",								//7	
						 "Thong tin khong hop le! Moi nhap lai.",
						 "Huy ve thanh cong.",
						 "Chon chuyen bay de huy ve hoac ESC de thoat"						//8
						 			
};








//khoi tao list
void GetList(ListFlight &l)
{
	l.pHead = l.pTail = NULL;
}
//tao 1 node voi data = data
NODE* GetNodeFlight(FLIGHT DATA)
{
	NODE *p = new NODE; 
	if (p == NULL)
		return NULL;
	p->data = DATA; 
	p->pNext = NULL; 
	return p;
}
void initChuyenBay(FLIGHT& cb, ListPlane &dsmb) {
    cb.stt = 1;
    cb.lst.SoVeDaDat = 0;
    if (search(dsmb, cb.idplane) >=0) {
        cb.lst.SoVeMax = dsmb.ds[search(dsmb, cb.idplane)]->so_cho;
    }
    else cb.lst.SoVeMax = 0;
    
    cb.lst.dstk = new Ticket[cb.lst.SoVeMax];
    
}
void LaySoGheMB(FLIGHT& cb, ListPlane &dsmb)
{
	  if (search(dsmb, cb.idplane) >=0) {
        cb.lst.SoVeMax = dsmb.ds[search(dsmb, cb.idplane)]->so_cho;
    }
    else cb.lst.SoVeMax = 0;
	
}

//them vao dau ds
void AddHeadListFlight(ListFlight &l, FLIGHT data)
{
	NODE* p = GetNodeFlight(data);
	p->pNext = l.pHead;
	l.pHead = p;
	++l.n;
}
//them vao cuoi ds
void AddTailListFlight(ListFlight &l, Flight data)
{
	NODE *p = GetNodeFlight(data);
	if (l.pHead == NULL)
		l.pHead =l.pTail= p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	++l.n;
}
bool Checkidplane(ListPlane& dsmb, string sh) {
	for (int i = 1; i <= dsmb.sl; i++) {
		if (sh.compare(dsmb.ds[i]->so_hieu_mb) == 0)return true;
	}
	return false;
}

bool FindFlight(ListFlight l, string id){
	if (l.pHead == NULL) return NULL;
	for (NODE *p = l.pHead ; p != NULL; p = p->pNext)
		if (id.compare(p->data.idcb) == 0)
			return true;
	return false;
}
NODE* FindFlightById(ListFlight dscb, int vitri)
{
	NODE* p = dscb.pHead;
	int i=1;
//	for(int i = 1; i<=vitri;p = p->pNext)
	while(i!=vitri){
		p = p->pNext;
		i++;
	}
	
	return p;
}
NODE* FindFlightByIdplane(ListFlight dscb, string sh)
{
	NODE* p= dscb.pHead;
	for(int i=0; i<dscb.n;i++)
	{
		if(p->data.idcb==sh) return p;
		
		p= p->pNext;
	}
}
//so luot chuyen bay cua may bay sh thuc hien
int SoLuotChuyenBaySH(ListFlight l, string sh) {
    if (l.pHead == NULL)return 0;
    int dem = 0;
    NODE* p = l.pHead;
    while (p != NULL) {
        if (sh.compare(p->data.idplane) == 0)dem++;
         p = p->pNext;
    }
    return dem;
}


//huy chuyen bay
void HuyChuyenBay(Flight &cb) {
    cb.stt = 0;
    for(int i;i<cb.lst.SoVeMax;i++)
    {
    	cb.lst.dstk[i].cmnd="";
	}
	cb.lst.SoVeDaDat=0;
    
    
}
//huy chuyen bay co so hieu = sh
void HuyChuyenBaySH(ListFlight &l, string sh) {
    if (l.pHead == NULL)return ;
    NODE* p = l.pHead;
    while (p != NULL) {
        if (sh.compare(p->data.idcb) == 0) HuyChuyenBay(p->data);
        else p = p->pNext;
        
    }
    return;
}

void deleteList(ListFlight &l) {
    NODE* p = new NODE();
    while (l.pHead != NULL) {
        p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
    l.n=0;
}
//ham nhap chuyen bay
void NhapChuyenBay(FLIGHT& cb,ListPlane dsmb,ListFlight &dscb) {
//    cout << "Nhap Ma Chuyen Bay: ";
//    
//        //rewind(stdin);
//        string tmp1= ValidateID();
//        
//    cout << "Nhap ngay khoi hanh(ngay/thang/nam): ";
//    NhapNgay(cb.NgayKhoiHanh);
//   cout << "Nhap gio khoi hanh(gio/phut): ";
//   NhapGio(cb.GioKhoiHanh);
//    cout << "Nhap San Bay den: ";
//    //rewind(stdin);
    //cb.SanBayDen = ValidateName();
    xoa_trai();

	string s = "THEM CHUYEN BAY";
	gotoxy(30-s.length()/2, Y_BOX-3); cout << s;
	for(int i=0 ; i<5 ; i++)
	{	
	if(i==2){
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
		gotoxy(X_BOX + td_chuyen_bay[i+1].length()+5, Y_BOX+3*i); cout<<"/  /";
		}
	else if(i==3){
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
		gotoxy(X_BOX + td_chuyen_bay[i+1].length()+5, Y_BOX+3*i); cout<<":";
		
	}
	else
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
	}
	gotoxy(X_BOX, 29);
	cout << "Note:";
	gotoxy(X_BOX, 30);
	cout << "- Ma chuyen bay co toi da 15 ky tu.";
	gotoxy(X_BOX, 31);
	cout<<"- Ngay va gio phai lon hon hien tai";

	int f=1, temp = 1; // temp la bien tam de nhan UP DOWN
	try_again: // tao diem goto
	while(true)
	{
		f = temp;
		switch(f)
		{
			case 1:
				 Input_idflight(cb.idcb, temp);
				 if(FindFlight(dscb, cb.idcb))
				 {
				 	in_thong_bao_cb(2);
					gotoxy(X_BOX+td_chuyen_bay[1].length()+3, Y_BOX);
					cout << setw(10) << setfill(char(32)) << " ";
					cb.idcb="";
					temp--;
				 	
				 };
				break;
			case 2: 
				Choose_idplane(cb.idplane, temp, dsmb);
				if(dscb.n>0)XuatDanhSachChuyenBay(dscb);
				break;
			case 3:
				Input_date(cb.NgayKhoiHanh, temp);
				
				break;
			case 4:
				Input_time(cb.GioKhoiHanh, temp, cb.NgayKhoiHanh);
				break;
				
			case 5: 
				Input_place(cb.SanBayDen, temp);
				break;
			case 6: 
				{
					string s = "Xac nhan lap chuyen bay moi";
					int x = xac_nhan(25, s);
					if(x==0)
					{
						initChuyenBay(cb, dsmb);
						AddTailListFlight(dscb, cb);
						xoa_trai();
						XuatDanhSachChuyenBay(dscb);
						return;
					}
					else if(x==1)
					{
						
						temp=5;
						xoa_xac_nhan(23);
						break;
					}
					 }
				case 7:
				xoa_trai();
				return;	 
				
				
				}
			
			
		}
	}



// chuyen bay hoan tat la true
bool ChuyenBayHoanTat(FLIGHT cb) {
   	Date d_ht = NgayHienTai();
    Hour h_ht = GioHienTai();
    if(!SoSanhNgay(cb.NgayKhoiHanh, d_ht)) return true;
    else if(SoSanhNgay(cb.NgayKhoiHanh, d_ht))
    	{
    		if(cb.NgayKhoiHanh.ngay==d_ht.ngay&&cb.NgayKhoiHanh.thang==d_ht.thang&&cb.NgayKhoiHanh.nam==d_ht.nam)
			{
				if(!SoSanhGio(cb.GioKhoiHanh, h_ht)) return true;
    			else if(SoSanhGio(cb.GioKhoiHanh, h_ht)) return false;
    		}
    		else return false;
    	
		}
}
//bool ChuyenBayConVe(FLIGHT cb) {
//    if (cb.lst.SoVeDaDat < cb.lst.SoVeMax)return true;
//    return false;
//}

void CapNhatTrangThaiChuyenBay(ListFlight &dscb) {
    NODE* p = dscb.pHead;
    for(int i=0; i<dscb.n;i++)
    {
    	if(p->data.stt!=0 && p->data.stt!=3 && ChuyenBayHoanTat(p->data))
    	{
    		p->data.stt = 3;
		}
		else if(p->data.stt==3 && !ChuyenBayHoanTat(p->data))
		{
			p->data.stt=1;
			
		}
		else if(p->data.stt==1 && p->data.lst.SoVeDaDat==p->data.lst.SoVeMax)
		{
			p->data.stt=2;
			
		}
		else if(p->data.stt==2&&p->data.lst.SoVeDaDat!=p->data.lst.SoVeMax)
		{
			p->data.stt=1;
		}
		
		
		p = p->pNext;
	}
	
}
void HieuChinhThoiGianKhoiHanh(ListFlight &dscb) {
	try_again:
	int n =	Chon_Chuyen_Bay(dscb);
	if(n==-1) return;
	NODE *p = FindFlightById(dscb, n);
	if(p->data.stt==0 || p->data.stt==3) {
	in_thong_bao_cb(4);
	goto try_again;
	}

	
	

	string s = "Chinh Sua Chuyen Bay";
	gotoxy(30-s.length()/2, Y_BOX-3); cout << s;
	for(int i=0 ; i<5 ; i++)
	{	
		if(i==2){
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
		gotoxy(X_BOX + td_chuyen_bay[i+1].length()+5, Y_BOX+3*i); cout<<"/  /";
		}
		else if(i==3){
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
		gotoxy(X_BOX + td_chuyen_bay[i+1].length()+5, Y_BOX+3*i); cout<<":";
		
		}
		else
		create_box(td_chuyen_bay[i+1], X_BOX, Y_BOX+3*i);
	}
	
	gotoxy(X_BOX+td_chuyen_bay[1].length()+3, Y_BOX);
	
	cout << p->data.idcb;
	gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
	cout<<p->data.idplane;
	gotoxy(X_BOX+td_chuyen_bay[5].length()+3, Y_BOX+12);
	cout << p->data.SanBayDen;
	gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
	cout<<p->data.NgayKhoiHanh.ngay;
	gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3, Y_BOX+6);
	cout<<p->data.NgayKhoiHanh.thang;
	gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3+3, Y_BOX+6);
	cout<<p->data.NgayKhoiHanh.nam;
	gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
	cout<<p->data.GioKhoiHanh.gio;
	gotoxy(X_BOX+td_chuyen_bay[4].length()+3+3, Y_BOX+9);
	cout<<p->data.GioKhoiHanh.phut;
	int temp=3;
	Date v_ngay = p->data.NgayKhoiHanh;
	Hour v_gio = p->data.GioKhoiHanh;
	while(true)
	{
		switch(temp)
		{
			case 3:
				{	
				Input_date(p->data.NgayKhoiHanh, temp);
				
				break;
				}
			case 4:
				{	
					Input_time(p->data.GioKhoiHanh, temp, p->data.NgayKhoiHanh);
					break;
					
				}
				case 5: 
				{
					string s = "Xac nhan sua doi";
					int x = xac_nhan(25, s);
					if(x==0)
					{
						xoa_trai();
						xoa_phai_cb();
						khung_ds_chuyen_bay();
						XuatDanhSachChuyenBay(dscb);
						return;
					}
					else if(x==1)
					{
						
						temp=4;
						xoa_xac_nhan(23);
						break;
					}
					 }
				case 7:
				p->data.NgayKhoiHanh = v_ngay;
				p->data.GioKhoiHanh = v_gio;
				xoa_trai();
				return;	
				
		}
	}
	
	
	
	
}
void XuatChuyenBay(FLIGHT cb, int i) {
	gotoxy(X_LIST, Y_LIST +5+2*i-2);
	cout<<(trang_cb_ht-1)*10+i+1;
	gotoxy(X_LIST+5, Y_LIST+5+2*i-2);
	cout<<cb.idcb;
	gotoxy(X_LIST+5+18, Y_LIST+5+2*i-2);
	cout<<cb.idplane;
	gotoxy(X_LIST+5+18+18, Y_LIST +5+2*i-2);
	cout<<cb.NgayKhoiHanh.ngay<<"/"<<cb.NgayKhoiHanh.thang<<"/"<<cb.NgayKhoiHanh.nam;
	gotoxy(X_LIST+5+18+18+13, Y_LIST +5+2*i-2);
	cout<<cb.GioKhoiHanh.gio<<":"<<cb.GioKhoiHanh.phut;
	gotoxy(X_LIST+5+18+18+13+8, Y_LIST +5+2*i-2);
	cout<<cb.SanBayDen;
	gotoxy(X_LIST+5+18+18+13+8+18, Y_LIST +5+2*i-2);
	//cout<<cb.lst.SoVeMax;
	if(cb.stt==0) cout<<"Da huy";
	else if(cb.stt==1)cout<<"Con Ve";
	else if(cb.stt==2) cout<<"Het Ve";
	else if(cb.stt==3)	cout<<"Hoan Tat";
	

}
//xuat list
int so_trang_cb(ListFlight l)
{
	if(l.n%10==0) return l.n/10;
	else return l.n/10+1;
}
void XuatDanhSachChuyenBay(ListFlight l) {
	gotoxy(X_SL+18, Y_SL); cout<<l.n;
    gotoxy(X_PAGE+7, Y_PAGE); cout<<trang_cb_ht<<"/"<<so_trang_cb(l);
    NODE* p = l.pHead;
    int a = 0;
    int i=0, vitri=0;
    int temp;
    if(trang_cb_ht!=so_trang_cb(l)) {
    	temp=trang_cb_ht*10;
	}    
	else temp=l.n; 
    
	
    for(a; a<temp;a++){
	
        if(vitri >= (trang_cb_ht-1)*10) 
		{
			XuatChuyenBay(p->data, i);
			i++;
		}
        p = p->pNext;
        vitri++;
    }
}
//=======================================DO HOA=============================================
// ======================================== CHUYEN BAY ==============================================

// ve khung ds chuyen bay
void khung_ds_chuyen_bay()
{	
	string tt = "DANH SACH CHUYEN BAY";
	gotoxy(X_TITLE-tt.length()/2, Y_TITLE); cout << tt;
	gotoxy(X_SL-3, Y_SL);	cout << "So luong chuyen bay: ";
	gotoxy(X_PAGE, Y_PAGE);	cout << "Trang: ";
	string s = " Tim kiem: ";
	gotoxy(X_LIST-3, Y_LIST-2);
	cout << char(218) << setw(94) << setfill(char(196)) << char(191);
	gotoxy(X_LIST-3, Y_LIST-1); cout << char(179) << s;
	gotoxy(X_LIST-3+width_list+6, Y_LIST-1); cout << char(179);
	gotoxy(X_LIST-3, Y_LIST);
	cout << char(195) << setw(6) << setfill(char(196)) << char(194) 
					  << setw(18) << setfill(char(196)) << char(194) 
					  << setw(18) << setfill(char(196)) << char(194) 
					  << setw(13) << setfill(char(196)) << char(194) 
					  << setw(8) << setfill(char(196)) << char(194) 
					  << setw(18) << setfill(char(196)) << char(194) 
					  << setw(13) << setfill(char(196)) << char(180);
	for(int i=1 ; i<=height_list-2 ; i++)
	{
		gotoxy(X_LIST-3, Y_LIST+i);
		if(i==1)
		{
			cout << char(179) << td_chuyen_bay[0]; gotoxy(X_LIST-3+6, Y_LIST+i); cout << char(179) ;
			cout 			  << td_chuyen_bay[1]; gotoxy(X_LIST-3+6+18, Y_LIST+i); cout << char(179) ;
			cout 			  << td_chuyen_bay[2]; gotoxy(X_LIST-3+6+18+18, Y_LIST+i); cout << char(179);
			cout			  << td_chuyen_bay[3]; gotoxy(X_LIST-3+6+18+18+13, Y_LIST+i); cout << char(179);
			cout			  << td_chuyen_bay[4]; gotoxy(X_LIST-3+6+18+18+13+8, Y_LIST+i); cout << char(179);
			cout			  << td_chuyen_bay[5]; gotoxy(X_LIST-3+6+18+18+13+8+18, Y_LIST+i); cout << char(179);
			cout			  << td_chuyen_bay[6]; gotoxy(X_LIST+width_list+3, Y_LIST+i); cout << char(179);
		}
		else if(i==2)
		{
			cout << char(195) << setw(6) << setfill(char(196)) << char(197)
							  << setw(18) << setfill(char(196)) << char(197)
							  << setw(18) << setfill(char(196)) << char(197) 
							  << setw(13) << setfill(char(196)) << char(197) 
							  << setw(8) << setfill(char(196)) << char(197) 
							  << setw(18) << setfill(char(196)) << char(197)  
							  << setw(13) << setfill(char(196)) << char(180);
		}
		else
		{
			cout << char(179);
			gotoxy(X_LIST-3+6, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST-3+6+18, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST-3+6+18+18, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST-3+6+18+18+13, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST-3+6+18+18+13+8, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST-3+6+18+18+13+8+18, Y_LIST+i); cout << char(179);
			gotoxy(X_LIST+width_list+3, Y_LIST+i); cout << char(179);
		}
	}
	gotoxy(X_LIST-3, Y_LIST+height_list-1);
	cout << char(192) << setw(6) << setfill(char(196)) << char(193) 
					  << setw(18) << setfill(char(196)) << char(193) 
					  << setw(18) << setfill(char(196)) << char(193) 
					  << setw(13) << setfill(char(196)) << char(193) 
					  << setw(8) << setfill(char(196)) << char(193)
					  << setw(18) << setfill(char(196)) << char(193)
					  << setw(13) << setfill(char(196)) << char(217);
}
//=============Ghi - Doc File====================
void doc_file_ds_chuyen_bay(ListFlight &ds, FLIGHT &cb, ListPlane dsmb)
{
	ifstream fin;
	fin.open("DSCB.TXT", ios_base::in);
	if(fin.fail())
	{
		in_thong_bao(6);
		return;
	}
	char temp;
	string s;

	while(!fin.eof())
	{
		getline(fin, cb.idcb, ',');
		getline(fin, cb.idplane, ',');
		fin >> cb.NgayKhoiHanh.ngay;
		fin >> temp;
		fin >> cb.NgayKhoiHanh.thang;
		fin >> temp;
		fin >> cb.NgayKhoiHanh.nam;
		fin >> temp;
		fin >> cb.GioKhoiHanh.gio;
		fin >> temp;
		fin >> cb.GioKhoiHanh.phut;
		fin >> temp;
		getline(fin, cb.SanBayDen, ',');
		LaySoGheMB(cb, dsmb);
		fin>>cb.stt;
		fin>>temp;
		fin>>cb.lst.SoVeDaDat;
		
		
		cb.lst.dstk = new Ticket[cb.lst.SoVeMax];
		if(cb.lst.SoVeDaDat!=0)
		{
			fin>>temp;
			for(int i=0; i<cb.lst.SoVeDaDat;i++)
				{	int a;
					fin>>a;
					fin>>temp;
					getline(fin,cb.lst.dstk[a-1].cmnd, ',');
					
				}
		}

	
		
		
		getline(fin, s);
		
		AddTailListFlight(ds, cb);
	}
	fin.close();
}
void ghi_file_ds_chuyen_bay(ListFlight ds)
{
	ofstream fout;
	fout.open("DSCB.txt", ios_base::out);
	for(NODE *k = ds.pHead ; k != NULL ; k = k->pNext)
	{	
		fout << k->data.idcb << ","
			 << k->data.idplane << ","
			 << k->data.NgayKhoiHanh.ngay << "/" << k->data.NgayKhoiHanh.thang << "/" <<k->data.NgayKhoiHanh.nam << ","
			 << k->data.GioKhoiHanh.gio << ":" << k->data.GioKhoiHanh.phut << ","
			 << k->data.SanBayDen << ","
			 << k->data.stt<<","<<k->data.lst.SoVeDaDat<<",";
		for(int i=0; i<k->data.lst.SoVeMax;i++)
		{
			if(!k->data.lst.dstk[i].cmnd.empty())
				{
					fout<<i+1<<","<<k->data.lst.dstk[i].cmnd<<",";
				}
			
		}
			 if(k->pNext!=NULL) fout<<endl;
	}
	fout.close();
}
void main_menu()
{	
	normal();
	AVL_tree T;
	khoi_tao_cay(T);
	doc_file_hanh_khach(T);
	ListPlane dsmb;
	dsmb.sl = 0;
	doc_ds_mb(dsmb);
	FLIGHT cb;
	ListFlight dscb;
	GetList(dscb);
	doc_file_ds_chuyen_bay(dscb, cb, dsmb);
	CapNhatTrangThaiChuyenBay(dscb);
	cap_nhat_so_chuyen_cho_may_bay(dscb, dsmb);
	
	int chon;
	
		
	do
	{
		clrscr();
		khung_chinh();
		chon = menu_dong(td, so_item1 , cot1 , dong1);
		switch(chon)
		{
			case 1: menu_quan_ly_may_bay(0, dsmb); break;
			case 2: menu_quan_ly_chuyen_bay(1, dsmb, dscb, cb); break;
			case 3: menu_quan_ly_ve_may_bay(2, dscb, T); break;
			case 4: Huy_ve(3, dscb, T);  break;
			case 5: in_ds_hanh_khach_thuoc_chuyen_bay_x(4, T, dscb); break;
			case 6: InChuyenBayTheoNgay(5, dscb); break;
			case 7: GheTrongCuaChuyenBay(dscb); break;
			case 8:
				ghi_ds_mb(dsmb);
				clear_list_mb(dsmb);
		
				ghi_file_ds_hanh_khach(T);
				xoa_ds_hanh_khach(T);
				ghi_file_ds_chuyen_bay(dscb);
				deleteList(dscb);
				normal();
				clrscr();
				return;
		}
	}
	while(1);
}
//=============================XU LY CHUYEN BAY================================
void menu_quan_ly_chuyen_bay(int stt, ListPlane dsmb, ListFlight dscb, FLIGHT cb)
{	
	trang_cb_ht = 1;
	menu_quan_ly_chung(stt);
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ESC: Tro lai ---- F2: Them chuyen bay ---- F3: Chinh sua thoi gian ---- F4: Huy chuyen bay ---- ENTER: Chon ---- PAGE UP/DOWN: Chuyen trang";
	khung_ds_chuyen_bay();
	if(dscb.n>0)XuatDanhSachChuyenBay(dscb);
	gotoxy(X_SL+18, Y_SL); cout<<dscb.n;
    gotoxy(X_PAGE+7, Y_PAGE); cout<<trang_cb_ht<<"/"<<so_trang_cb(dscb);
    int chon;
	
	char key;
	do
	{
		
		
		key = getch();
		if(key==0) key = getch();
		switch(key)
		{
		case F2:
			{
			
			FLIGHT cb1;
			NhapChuyenBay(cb1, dsmb, dscb);
			break;
			}
		case PAGE_UP:
			if(trang_cb_ht>1)
			{
				xoa_phai_cb();
				khung_ds_chuyen_bay();
				trang_cb_ht--;
				XuatDanhSachChuyenBay(dscb);
				
			}
			break;
		case PAGE_DOWN:
			if(trang_cb_ht<so_trang_cb(dscb))
			{
				xoa_phai_cb();
				khung_ds_chuyen_bay();
				trang_cb_ht++;
				XuatDanhSachChuyenBay(dscb);
				
			}
			break;
		case F3: HieuChinhThoiGianKhoiHanh(dscb); break;
		case F4: 
			{
				try_again:
				int n =	Chon_Chuyen_Bay(dscb);
				if(n==-1) return;
				NODE *p = FindFlightById(dscb, n);
				if(p->data.stt==0 || p->data.stt==3) {
				in_thong_bao_cb(4);
				goto try_again;
				}
				HuyChuyenBay(p->data);
				xoa_phai_cb();
				khung_ds_chuyen_bay();
				XuatDanhSachChuyenBay(dscb);
				
			break;
			}
		}
	}
	while(key!=ESC);
}
void Input_idflight(string &result, int &main_temp)
{	
	int count = result.length();
	gotoxy(X_BOX+td_chuyen_bay[1].length()+3, Y_BOX);
	
	show_cur(1);
	cout << result;
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 95 || (key >= 48 && key <= 57))
			{
				if(count <= 15)
				{
					if(key >= 97 && key <= 122)	key -= 32;
					cout << char(key);
					result += char(key);
					count++;
				}
			}
			else if(key == 8 && !result.empty())
			{
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				count--;
			}
			else if(key == ENTER)
			{	if(result.empty())
					{
						in_thong_bao_cb(3);
								return;
					}
				else
				main_temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == DOWN) 
				{if(result.empty())
				{
						in_thong_bao_cb(3);
						return;
					
				}
				main_temp++;
				return;
				}
			}
			else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(25, s);
				if(x==0) {
					
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(23);
					return;
					
				}
				
			
			}
		}
	}
}
//Chon so hieu may bay
void Choose_idplane(string &n, int &main_temp,ListPlane dsmb1)
{	try_again:
	show_cur(0);
	if(!n.empty())
	{	show_cur(1);
		gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
		cout<<n;
	}
	else{
	do{
	
	gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
	cout<<"Nhan Enter de chon";
	Sleep(300);
	gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
	cout<<setw(20)<<setfill(char(32))<<" ";
	Sleep(300);
	
	}while(!kbhit());
	}

	while(true)
	{	
		while(kbhit())
		{	
			int key=getch();
			 if(key==UP) {main_temp--;
			return; 
			}
			else if(key==DOWN) {
			if(n.empty())
			{
				in_thong_bao_cb(3);
						return;
				}
			
			main_temp++;
			
			return;
			}
			else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(25, s);
				if(x==0) {
					
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(23);
					return;
					
				}
				
			
			}
			else if(key==13)
			{	xoa_phai_cb();
				in_ds_mb_theo_trang(dsmb1);
				int x = chon_may_bay(dsmb1);
				if(x==-1)
				{xoa_phai_cb();
				khung_ds_chuyen_bay();
				return;
				}
				
				
				else if(x>=0){
					xoa_phai_cb();
					n = dsmb1.ds[x]->so_hieu_mb;
					
					gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
					cout<<setw(20)<<setfill(char(32))<<" ";
					gotoxy(X_BOX+td_chuyen_bay[2].length()+3, Y_BOX+3);
					cout<<n;
					main_temp++;
					khung_ds_chuyen_bay();
					
					return;
					
				}
			
			}
			
			
		}
	}
	
	
	return;
	

	
}

//Ngay gio
Date Input_date(Date &n, int &main_temp)
{	
Date v = NgayHienTai();
int temp1 = 1;
	while(true){
		switch(temp1)
		{
			case 1: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 2: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 3: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(0, temp1, main_temp, n);
				break;
			}
			default: {
				
				if (!NgayHopLe(n)&&main_temp==4)
				{
					in_thong_bao_cb(0);
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					cout << setw(10) << setfill(char(32)) << " ";
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					cout<<"  /  /";
					temp1=1;
					main_temp--;
				}
				if(!SoSanhNgay(n, v))
				{
					in_thong_bao_cb(0);
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					cout << setw(10) << setfill(char(32)) << " ";
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					cout<<"  /  /";
					temp1=1;
					main_temp--;
					
				}
				else
				
				return n;
				
			
				
				break;
				
				}
		}
		
		
	}
		
		
		
	
}
void ValidateDate(int count, int &tam, int &main_temp, Date &result)
{

	
	
	while (true)
	{
		
		while (kbhit())
		{
			int key = _getch();
			
				if (key >= 48 && key <= 57 && count <4){
					if(tam==1&&count==2) {
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					cout<<setw(2)<<setfill(char(32))<<" ";
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
					result.ngay=0;
				}
				else if(tam==2&&count==2)
				{	gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3, Y_BOX+6);
					cout<<setw(2)<<setfill(char(32))<<" ";
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3, Y_BOX+6);
				  	result.thang =0;
				}
				else if(tam==3&&count==0)
				{	gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3+3, Y_BOX+6);
					cout<<setw(4)<<setfill(char(32))<<" ";
					gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3+3, Y_BOX+6);
					result.nam=0;
				}
				int f = key - 48;
			
					cout << f;
					if(tam==1)result.ngay = result.ngay * 10 + (f);
					else if(tam==2)result.thang = result.thang * 10 + (f);
					else if(tam==3)result.nam = result.nam * 10 + (f);
					if(count==3&&tam<=2)
						{
							tam++;
							return;
							
						}
					count++;
				
			}
		
			
			else if (key == 13)
			{
				tam++;
				if(tam==4) main_temp++;

				return;

			}
			
			else if(key==75 && tam>1)
			{	tam--;
				return;
				
			}
			else if(key==77 && tam<3)
			{	tam++;
				return;
				
			}
			else if (key == 8 && count >2)
			{
				cout << "\b" << " " << "\b";
				
				if(tam==1) result.ngay /= 10;
				else if(tam==2) result.thang /=10;
				else if(tam==3) result.nam /=10;
				count--;
			}
			else if(key == 80)
				{	tam=4;
					main_temp++;
					return;
				}
				else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(25, s);
				if(x==0) {
				tam=4;
					
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(23);
					return;
					
				}
				
			
			}
			else if(key == 72)
				{	tam=4;
					main_temp--;
					return;
				}
			
		}

		}
}
Hour Input_time(Hour &n, int &main_temp, Date n_ngay)
{	Hour v= GioHienTai();
	Date  v_ngay= NgayHienTai();

	int temp1 = 1;
	while(true){
		switch(temp1)
		{
			case 1: {
				gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
				
				show_cur(1);
				
				ValidateHour(2, temp1, main_temp, n);
				break;
			}
			case 2: {
				gotoxy(X_BOX+td_chuyen_bay[4].length()+3+3, Y_BOX+9);
				show_cur(1);
				ValidateHour(2, temp1, main_temp,n);
				break;
			}
		
			default: {
				
				if (!GioHopLe(n)&&main_temp==5)
				{	
					in_thong_bao_cb(1);
					gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
					cout << setw(10) << setfill(char(32)) << " ";
					gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
					cout<<"  :";
					temp1=1;
					main_temp--;
				}
				else if(n_ngay.ngay==v_ngay.ngay&&n_ngay.thang==v_ngay.thang&&n_ngay.nam==v_ngay.nam)
				{
					if(!SoSanhGio(n, v))
					{
					in_thong_bao_cb(1);
					gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
					cout << setw(10) << setfill(char(32)) << " ";
					gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
					cout<<"  :";
					temp1=1;
					main_temp--;
					}
				}
				else 
				return n;
				break;
				
			
				
				
			};
		}

}
}


void ValidateHour(int count, int &tam, int &main_temp, Hour &result)
{
	
	
	while (true)
	{
		
		while (kbhit())
		{
			int key = _getch();
			if (key >= 48 && key <= 57 && count <4)
			{	if(tam==1&&count==2) 
					{	gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
						cout<<setw(2)<<setfill(char(32))<<" ";
						gotoxy(X_BOX+td_chuyen_bay[4].length()+3, Y_BOX+9);
						result.gio=0;
					}
				else if (tam==2&&count==2) 
					{	gotoxy(X_BOX+td_chuyen_bay[4].length()+3+3, Y_BOX+9);
						cout<<setw(2)<<setfill(char(32))<<" ";
						gotoxy(X_BOX+td_chuyen_bay[4].length()+3+3, Y_BOX+9);
						result.phut=0;
					}
					int f = key-48;
					cout << f;
					if(tam==1) result.gio = result.gio * 10 + (f);
					else if(tam==2) result.phut = result.phut*10 +(f);
					if(count==3&&tam<2)
					{
						tam++;
						return;
						
					}
					count++;
				
			}
			
			else if (key == 13)
			{
				tam++;
				if(tam==3) main_temp++;

				return;

			}
			
			else if(key==75 && tam>1)
			{	tam--;
				return;
				
			}
			else if(key==77 && tam<2)
			{	tam++;
				return;
				
			}
			else if (key == 8 && count >2)
			{
				cout << "\b" << " " << "\b";
				if(tam==1) result.gio /= 10;
				else if(tam==2) result.phut /= 10;
				count--;
			}
			else if(key == 80)
				{	tam=3;
					main_temp++;
					return;
				}
			else if(key == 72)
				{	tam=3;
					main_temp--;
					return;
				}
			else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(25, s);
				if(x==0) {
					tam=4;
					
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(23);
					return;
					
				}
				
			
			}
			
		}

		}
	}
void Input_place(string &result, int &main_temp)
{
	int count = result.length();
	bool isSpaced = false;
	gotoxy(X_BOX+td_chuyen_bay[5].length()+3, Y_BOX+12);
	show_cur(1);
	
	while(true)
	{
		while(kbhit())
		{
			int key = getch();
			if((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 95 || key == 32 )
			{
				if (!isSpaced && key == 32 &&result.at(result.length()-1)!= static_cast<char>(32) )
				{
					cout << (char)key;
					result += (char)key;
					
					isSpaced = true;
				}
				else if(key >= 97 && key <= 122)	{
					key -= 32;
					cout << char(key);
					result += char(key);
			
					isSpaced = false;
					}
				
			}
			else if(key == 8 && !result.empty())
			{	
				
				cout << "\b" << " " << "\b";
				result.erase(result.end()-1);
				isSpaced = false;
			}
			
				
			
			else if(key == ENTER)
			{	if(result.at(result.length()-1)== static_cast<char>(32))
					{
						result.erase(result.end()-1);
						main_temp++;
						return;
						}	
				else 
				main_temp++;
				return;
			}
			else if(key == 224)
			{
				key = getch();
				if(key == DOWN) main_temp++;
				else if(key == UP) main_temp--;
				return;
			}
			else if (key==27)
			{
				
				string s = "Thoat se khong luu chuyen bay";
				int x = xac_nhan(25, s);
				if(x==0) {
					
				main_temp=7;
				return;
				
				}
				else if(x==1){
					xoa_xac_nhan(23);
					return;
					
				}
				
			
			}
		}
	}
}
void xoa_phai_cb()
{
	
	for(int i=0 ; i<30 ; i++)
	{
		gotoxy(X_LIST-3, Y_LIST-5+i);
		cout << setw(95) << setfill(char(32)) << " ";
	}
	return;
}


void in_thong_bao_cb(int tb) // tb la so thu tu cua thong bao
{
//const int x = wherex(), y = wherey(); // luu lai vi tri con tro truoc khi xuong in tb
	gotoxy(X_NOTIFY + 12,Y_NOTIFY);
	cout << thong_bao_cb[tb];
	//char c=getch();
	Sleep(1500);

		gotoxy(X_NOTIFY + 12,Y_NOTIFY);
		cout << setw(135) << setfill(char(32)) << " ";
	
//gotoxy(x, y); // tro lai vi tri con tro ban dau
}
int Chon_Chuyen_Bay(ListFlight dscb)
{	trang_cb_ht = 1;
	NODE *p = dscb.pHead;
	int chon=(trang_cb_ht-1)*10+1;
	int i=0;
	gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3);
	cout<<" <<<<";
	while(true)
	{	
		while(kbhit())
		{
			int key = getch();
			if(key==DOWN && chon<dscb.n&&i<=10)
			{	
				if(chon%10==0){
					trang_cb_ht++;
					xoa_phai_cb();
					khung_ds_chuyen_bay();
					XuatDanhSachChuyenBay(dscb);
					i=0;
					gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
					cout<<" <<<<";
					chon++;
					
				}
				else
				{
				
				gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
				cout<<setw(5)<<setfill(char(32))<<" ";
				chon++;
				i++;
				gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
				cout<<" <<<<";
			}
				
				
			}
			else if(key==UP && chon>=1 && chon!=1)
			{	
					if(chon%10==1){
					trang_cb_ht--;
					xoa_phai_cb();
					khung_ds_chuyen_bay();
					XuatDanhSachChuyenBay(dscb);
					i=9;
					gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
					cout<<" <<<<";
						chon--;
				}
				else
				{
				
				gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
				cout<<setw(5)<<setfill(char(32))<<" ";
				chon--;
				i--;
				gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
				cout<<" <<<<";
				}
				
				
			}
			else if(trang_cb_ht!=so_trang_cb(dscb)&& key==PAGE_DOWN)
			{
					trang_cb_ht++;
					xoa_phai_cb();
					khung_ds_chuyen_bay();
					XuatDanhSachChuyenBay(dscb);
					i=0;
					gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
					cout<<" <<<<";
					chon=(trang_cb_ht-1)*10+1;
					
				
			}
			else if(trang_cb_ht!=1&& key==PAGE_UP)
			{
				trang_cb_ht--;
					xoa_phai_cb();
					khung_ds_chuyen_bay();
					XuatDanhSachChuyenBay(dscb);
					i=0;
					gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
					cout<<" <<<<";
				chon=(trang_cb_ht-1)*10+1;
				
			}
			else if(key==13)
			{	
			gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
			cout<<setw(5)<<setfill(char(32))<<" ";
				return chon;
			}
			else if(key==ESC)
			{
			gotoxy(X_LIST +p->data.idcb.length()+11, Y_LIST+3+2*i);
			cout<<setw(5)<<setfill(char(32))<<" ";
			return -1;
				
			}
			else if(key==PAGE_UP&&trang_cb_ht>1)
			{
				chon=(trang_cb_ht-1)*10+1;
			}
			else if(key==PAGE_DOWN&&trang_cb_ht<so_trang_cb(dscb))
			{
				chon=(trang_cb_ht-1)*10+1;
			}
				
			
			
			
		}
	}
}

//=========================Quan Ly Ve=================
void menu_quan_ly_ve_may_bay(int stt, ListFlight dscb, AVL_tree &T)
{	menu_quan_ly_chung(stt);
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ESC: Tro lai ---- F2: Chinh sua thong tin hanh khach";
	gotoxy(X_BOX, 29);
	cout << "Note:";
	gotoxy(X_BOX, 30);
	cout << "- voi moi so CMND, ban chi dat duoc 1  ve/ 1 chuyen";
//	gotoxy(X_BOX, 31);
//	cout<<"- Ngay va gio phai lon hon hien tai";
		
char key;
	do
	{
		in_ds_ve(dscb, T);
		do{
			xoa_trai();
			gotoxy(X_NOTIFY + 12,Y_NOTIFY);
			cout<<"An phim bat ki de dat them ve hoac an ESC de thoat";
			Sleep(500);
			gotoxy(X_NOTIFY + 12,Y_NOTIFY);
			cout<<setw(50)<<setfill(char(32))<<" ";
			Sleep(500);
			
		}while(!kbhit());
		key = getch();
//		if(key==0) key = getch();
//		switch(key)
//		{
//			case F2: in_ds_ve(dscb);break;
//			case F3: break;
//			case F5: break;
//		}
//	}
	}while(key!=ESC);
}
void ChuyenBayKhaDung(ListFlight dscb, ListFlight &dscb_kd, string cmnd)
{
	NODE* p = dscb.pHead;
	for(int i = 0; i<dscb.n; i++)
	{	int temp=0;
		for(int i=0;i<p->data.lst.SoVeMax;i++)
		{
			if(p->data.lst.dstk[i].cmnd==cmnd)
			{
				temp=1;
				break;
			}
		}
		if(p->data.stt==1&&temp==0)
		{
			AddTailListFlight(dscb_kd,p->data);
				
		}
		p = p->pNext;
	}
	return;
}
void in_trang_ve(int max, int &chon, FLIGHT cb, bool &hit)
{	int vitri=(trang_cb_ht-1)*104+1;
	hit = false;
	for(int i=0; i<13;i++)
	{
		for(int j=0; j<8;j++)
		{	if(j>=4)
			{ 	
				if(!cb.lst.dstk[vitri-1].cmnd.empty())
				{
					gotoxy(X_LIST + 5*j+24, Y_LIST+2*i-2);
					SetColor(20);
					cout<<vitri;
					if(chon==vitri) hit=true;
					
				}
				else if(vitri==chon)
				{	
					gotoxy(X_LIST + 5*j+24, Y_LIST+2*i-2);
					SetColor(10);
					cout<<vitri;
							
				}
				
				else
				{
					gotoxy(X_LIST + 5*j+24, Y_LIST+2*i-2);
					SetColor(15);
					cout<<vitri;
					
				} 
				if(vitri==max) return;
			
				vitri++;
			
			} 
			else
			{
			
			if(!cb.lst.dstk[vitri-1].cmnd.empty())
			{
				gotoxy(X_LIST + 5*j+19, Y_LIST+2*i-2);
				SetColor(20);
				cout<<vitri;
				if(chon==vitri) hit=true;;
				
				
			}	
			else if(vitri==chon)
				{	
					gotoxy(X_LIST + 5*j+19, Y_LIST+2*i-2);
					SetColor(10);
					cout<<vitri;
							
				}
		
			else
				{
					
					gotoxy(X_LIST + 5*j+19, Y_LIST+2*i-2);
					SetColor(15);
					cout<<vitri;
					
					
					
				} 
			if(vitri==max) return;
			vitri++;
			}
			
			
		}
	}
	
}
int tong_trang_ve(FLIGHT cb)
{
	if(cb.lst.SoVeMax%104 ==0 ) return cb.lst.SoVeMax/104;
	else return cb.lst.SoVeMax/104 + 1;
}
void in_ds_ve(ListFlight &dscb, AVL_tree &T)
{	show_cur(0);
	trang_cb_ht=1;
	ListFlight dscb_kd;
	GetList(dscb_kd);
	string cmnd;
	cmnd = them_hanh_khach(T);
	xoa_trai();
	
	ChuyenBayKhaDung(dscb, dscb_kd, cmnd);
	if(dscb_kd.n==0)
	{
		in_thong_bao_cb(6);
		return;
	}
	gotoxy(X_BOX, 29);
	cout << "Note:";
	gotoxy(X_BOX, 30);
	cout << "- voi moi so CMND, ban chi dat duoc 1  ve/ 1 chuyen";
	khung_ds_chuyen_bay();
	XuatDanhSachChuyenBay(dscb_kd);
	int n =	Chon_Chuyen_Bay(dscb_kd);
	if(n==-1) return;
	xoa_phai_cb();
	NODE *p_temp = FindFlightById(dscb_kd, n);
	NODE* p = FindFlightByIdplane(dscb, p_temp->data.idcb);
	int so_trang_ve = tong_trang_ve(p->data);
	int max=p->data.lst.SoVeMax;
	int chon=1;
	bool hit=false;
		
	in_trang_ve(max, chon, p->data,hit);
		while(hit)
		{
			chon++;
			in_trang_ve(max, chon, p->data,hit);
		}
		
	
	char key;
	do
	{		key = getch();
			if(key==0) key==getch();
			
			switch(key)
			{
			
			
			case PAGE_DOWN:
			{	if(trang_cb_ht<so_trang_ve)
				{
			
				xoa_phai_cb();
				trang_cb_ht++;
				chon=(trang_cb_ht-1)*104+1;
				in_trang_ve(max, chon, p->data,hit);
				try_again1:
				if(hit)
				{
					chon++;
					in_trang_ve(max, chon, p->data,hit);
					goto try_again1;
				}
				
				}
				
				break;
			}
			case PAGE_UP: 
			{	if(trang_cb_ht>1)
				{
				xoa_phai_cb();
				trang_cb_ht--;
				chon=(trang_cb_ht-1)*104+1;
				in_trang_ve(max, chon, p->data,hit);
				try_again2:
				if(hit)
				{
					chon++;
					in_trang_ve(max, chon, p->data,hit);
					goto try_again2;

				}
				
				}
			
				break;
			}
			case LEFT:
				{
					if(chon!=1)
					{
					
						if(chon==(trang_cb_ht-1)*104+1) 
						{
						trang_cb_ht--;
						xoa_phai_cb();
						}
						chon--;
						in_trang_ve(max, chon, p->data,hit);
						try_again3:
						if(chon==(trang_cb_ht-1)*104+1&&hit&&chon!=1) 
						{
						trang_cb_ht--;
						xoa_phai_cb();
						chon--;
						in_trang_ve(max, chon, p->data,hit);
						}
						if(hit&&chon!=1)
						{
							chon--;
							in_trang_ve(max, chon, p->data,hit);
							goto try_again3;	
						}
					}
					
					if(chon==1)
					{	try_again4:
						if(hit)
						{
						chon++;
						in_trang_ve(max, chon, p->data,hit);
						goto try_again4;
						}
						
					}
						
					
					break;
				}
			case RIGHT:
				{
					if(chon!=max)
					{	if(chon==trang_cb_ht*104) 
						{
						trang_cb_ht++;
						xoa_phai_cb();
						}
						chon++;
						in_trang_ve(max, chon, p->data,hit);
						try_again5:
						if(chon==trang_cb_ht*104&&hit&&chon!=max) 
						{
						trang_cb_ht++;
						xoa_phai_cb();
						chon++;
						in_trang_ve(max, chon, p->data,hit);
						
						}
							
						if(hit&&chon!=max)
						{
							chon++;
							in_trang_ve(max, chon, p->data,hit);
							goto try_again5;
						}
					}
					
					if(chon==max)
					{	try_again6:
						if(hit){
					
						chon--;
						in_trang_ve(max, chon, p->data,hit);
						goto try_again6;
					}
						
					}
					break;
					
				}
			case UP:
				{
					if(chon>8)
					{
						
						if(chon<=(trang_cb_ht-1)*104+8&&chon>(trang_cb_ht-1)*104) 
						{
						trang_cb_ht--;
						xoa_phai_cb();
						}
						
						
						chon-=8;
						in_trang_ve(max, chon, p->data,hit);
						try_again7:
						if(chon<=(trang_cb_ht-1)*104+8 && chon>(trang_cb_ht-1)*104 && hit) 
						{
							
							trang_cb_ht--;
							xoa_phai_cb();
							chon-=8;
							in_trang_ve(max, chon, p->data,hit);
						
						
						}
						if(chon<=(trang_cb_ht)*104&&chon>(trang_cb_ht)*104-8&&hit)
						{
							chon-=8;
							in_trang_ve(max, chon, p->data,hit);
						}
						
						if(hit)
						{
							chon++;
							in_trang_ve(max, chon, p->data,hit);
							goto try_again7;
						}
						
					
					
					}
					break;
				
				}
			case DOWN:
				{	int temp;
					temp = max-8;
					
					if(chon>temp&&chon<=temp+(8-max%8))
					{	
						chon=max;
						in_trang_ve(max, chon, p->data,hit);
						try_again8:
						if(hit)
						{
							chon--;;
							in_trang_ve(max, chon, p->data,hit);
							goto try_again8;
						}
						
					}
					else if(chon<=temp)
					{	
						
						if(chon<=(trang_cb_ht)*104&&chon>(trang_cb_ht)*104-8) 
							{
							trang_cb_ht++;
							xoa_phai_cb();
							}
							chon+=8;
							in_trang_ve(max, chon, p->data,hit);
							try_again9:
						if(chon<=(trang_cb_ht)*104&&chon>(trang_cb_ht)*104-8&&hit) 
							{
							trang_cb_ht++;
							xoa_phai_cb();
							chon+=8;
							in_trang_ve(max, chon, p->data,hit);
							
							}
						if(chon>(trang_cb_ht-1)*104&&chon<=(trang_cb_ht-1)*104+8&&hit)
						{
							chon+=8;
							in_trang_ve(max, chon, p->data,hit);
						}
						if(hit)
							{
							chon--;
							in_trang_ve(max, chon, p->data,hit);
							goto try_again9;
							}
					}
					
					
					
					break;
					
				}
			case ENTER:
				{
					
		
					if(!cmnd.empty())
					{
						xoa_trai();
						gotoxy(X_BOX, 29);
						cout << "Note:";
						gotoxy(X_BOX, 30);
						cout << "- voi moi so CMND, ban chi dat duoc 1  ve/ 1 chuyen";
						string s = "Xac nhan dat ghe";
						int x= xac_nhan(20, s);
						if(x==0)
						{
						p->data.lst.dstk[chon-1].cmnd = cmnd; 
						xoa_trai();
						xoa_phai_cb();
						in_thong_bao_cb(7);
						p->data.lst.SoVeDaDat++;
						CapNhatTrangThaiChuyenBay(dscb);
						deleteList(dscb_kd);
						return;
							
						}
						else 
						{
						xoa_trai();
						gotoxy(X_BOX, 29);
						cout << "Note:";
						gotoxy(X_BOX, 30);
						cout << "- voi moi so CMND, ban chi dat duoc 1  ve/ 1 chuyen";
						chon=(trang_cb_ht-1)*104+1;
						in_trang_ve(max, chon, p->data,hit);
						while(hit)
							{
								chon++;
								in_trang_ve(max, chon, p->data,hit);
							}
						
						}
					
					
					}
					
					break;
					
					
					
				}
		}
	} while(key!=ESC);
	deleteList(dscb_kd);
	return;
}
void ChuyenBayConGhe(ListFlight dscb, ListFlight &dscb_kd, string cmnd)
{
	NODE* p = dscb.pHead;
	for(int i = 0; i<dscb.n; i++)
	{	
		if(p->data.stt==1)
		{
			AddTailListFlight(dscb_kd,p->data);
				
		}
		p = p->pNext;
	}
	return;
}
void GheTrongCuaChuyenBay(ListFlight dscb)
{
	menu_quan_ly_chung(6);
	khung_ds_chuyen_bay();
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ESC: Tro lai ---- ENTER: Chon ---- PAGE UP/DOWN : Chuyen trang";
	show_cur(0);
	

	string cmnd;
	ListFlight dscb_kd;
	try_again:
	trang_cb_ht=1;
	normal();
		
	GetList(dscb_kd);
	ChuyenBayConGhe(dscb, dscb_kd, cmnd);
	if(dscb_kd.n==0)
	{
		in_thong_bao_cb(6);
		return;
	}
	khung_ds_chuyen_bay();
	XuatDanhSachChuyenBay(dscb_kd);
	int n =	Chon_Chuyen_Bay(dscb_kd);
	if(n==-1) return;
	xoa_phai_cb();
	NODE *p = FindFlightById(dscb_kd, n);
	int so_trang_ve = tong_trang_ve(p->data);
	int max=p->data.lst.SoVeMax;
	int chon;
	bool hit=false;
					gotoxy(80, 6);
					cout<<setw(50)<<setfill(char(32))<<" ";
					gotoxy(75, 6);
					cout<<"SO GHE CON TRONG CUA CHUYEN BAY "<<p->data.idcb<<" LA "<<p->data.lst.SoVeMax-p->data.lst.SoVeDaDat<<" GHE";
	in_trang_ve(max, chon, p->data,hit);
	char key;
	
	while(true){
		key = getch();
		if(key==0) key==getch();
		switch(key)
		{
			case PAGE_UP:
				{
					if(trang_cb_ht>1)
					{
						xoa_phai_cb();
						trang_cb_ht--;
						gotoxy(80, 6);
						cout<<setw(50)<<setfill(char(32))<<" ";
						normal();
					gotoxy(75, 6);
					cout<<"SO GHE CON TRONG CUA CHUYEN BAY "<<p->data.idcb<<" LA "<<p->data.lst.SoVeMax-p->data.lst.SoVeDaDat<<" GHE";
						in_trang_ve(max, chon, p->data,hit);
					}
					break;
				}
			case PAGE_DOWN:
				{
					if(trang_cb_ht<so_trang_ve)
					{
			
						xoa_phai_cb();
						trang_cb_ht++;
						gotoxy(80, 6);
						cout<<setw(50)<<setfill(char(32))<<" ";
						normal();
						gotoxy(75, 6);
						cout<<"SO GHE CON TRONG CUA CHUYEN BAY "<<p->data.idcb<<" LA "<<p->data.lst.SoVeMax-p->data.lst.SoVeDaDat<<" GHE";
						in_trang_ve(max, chon, p->data,hit);
					}
					break;
				}
			case ESC:
				{	deleteList(dscb_kd);
					xoa_phai_cb();
			 		 goto try_again; 
					  break;
				}
			
			}
	
	
	}
}
void Ds_ChuyenBay_Da_Dat(ListFlight &dscb, ListFlight &dscb_kd, string cmnd)
{
	NODE* p = dscb.pHead;
	for(int i=0; i<dscb.n;i++)
	{
		for(int j=0; j<p->data.lst.SoVeMax;j++)
		{
			if(p->data.lst.dstk[j].cmnd==cmnd)
			{
				AddTailListFlight(dscb_kd, p->data);
				break;
			}
		}
		p = p->pNext;
	}
	
}
void Huy_ve(int stt, ListFlight &dscb, AVL_tree T)
{	normal();
	menu_quan_ly_chung(stt);
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ESC: Tro lai";
	show_cur(0);
	trang_cb_ht=1;
	string cmnd;
	string s;
	int x;
	create_box("Nhap CMND", X_BOX, Y_BOX);
	ValidateCMND(cmnd);
	
	xoa_trai();
	if(cmnd=="a") return;
	

	try_again:
	in_thong_bao_cb(10);
	ListFlight dscb_kd;
	GetList(dscb_kd);
	Ds_ChuyenBay_Da_Dat(dscb, dscb_kd, cmnd);
	if(dscb_kd.n==0)
	{
		in_thong_bao_cb(6);
		return;
	}
	khung_ds_chuyen_bay();
	XuatDanhSachChuyenBay(dscb_kd);
	int n =	Chon_Chuyen_Bay(dscb_kd);
	if(n==-1) return;
	xoa_phai_cb();
	NODE *p_temp = FindFlightById(dscb_kd, n);
	NODE* p = FindFlightByIdplane(dscb, p_temp->data.idcb);
//	int key = ENTER;
//	while(true)
//	{
//		while(kbhit())
//		{
//			if(n<0) key = getch();
//			if(key==ENTER)
//			{
//				for(int i=0;i<p->data.lst.SoVeMax;i++)
//					{
//						if(cmnd==p->data.lst.dstk[i].cmnd)
//						{
//							p->data.lst.dstk[i].cmnd="";
//							p->data.lst.SoVeDaDat--;
//							break;
//						}
//				
//					}
//			temp++;
//			in_thong_bao_cb(9);
//			deleteList(dscb_kd);
//			goto try_again;
//			}	
//			else if(key==ESC)
//			{
//				deleteList(dscb_kd);
//				return;	
//			}
//}

	if(n>=0)
	{
	
	s = "Ban co muon huy ve khong?";
	x =xac_nhan(25, s);
	 xoa_xac_nhan(23);
	if(x==0){
		for(int i=0;i<p->data.lst.SoVeMax;i++)
		{
			if(cmnd==p->data.lst.dstk[i].cmnd)
			{
				p->data.lst.dstk[i].cmnd="";
				p->data.lst.SoVeDaDat--;
				break;
			}
				
		}
		in_thong_bao_cb(9);
		CapNhatTrangThaiChuyenBay(dscb);
		deleteList(dscb_kd);
		goto try_again;
	}
	else{
		deleteList(dscb_kd);
		goto try_again;	
	}
	
	}
	char key=getch();
	 if(key==ESC)
	{
	deleteList(dscb_kd);
	return;
}	
}
void ValidateCMND(string &cmnd)
{	show_cur(1);
	
	gotoxy(X_BOX + 12, Y_BOX );
	int count = 0;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			if (key >= 48 && key <= 57 && count <9)
			{
				int f = key - 48;
				if (count == 0 && key == 48)
				{
					continue;
				}
				else
				{
					cout << f;
					cmnd+=char(key);
					count++;
				}
			}
			else if (key == 13)
			{
				if(cmnd.length()<9)
				{
					in_thong_bao_cb(8);
					gotoxy(X_BOX + 12+cmnd.length(), Y_BOX );
					
				}
				else
				return;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				count--;
				cmnd.erase(cmnd.length()-1);
			}
			else if(key==ESC)
			{
				if(cmnd.empty()) {
				cmnd="a";
				return;
				}
				else
				{ 
				string s = "Ban co muon thoat khong?";
				int x=xac_nhan(25, s);
				if(x==0) return;
				else if(x==1)
				{
					xoa_xac_nhan(23);
					show_cur(1);
					gotoxy(X_BOX + 12+cmnd.length(), Y_BOX );
				}
				}

		}
	}
	
}
return;
}
void LayChuyenBayNgayX(ListFlight dscb, ListFlight &dscb_kd, Date n, string s)
{
	NODE* p = dscb.pHead;
	for(int i=0; i<dscb.n;i++)
	{
		if(p->data.NgayKhoiHanh.ngay==n.ngay&&p->data.NgayKhoiHanh.thang==n.thang&&p->data.NgayKhoiHanh.nam==n.nam&&p->data.SanBayDen==s)
		{
			AddTailListFlight(dscb_kd, p->data);
		}
		p = p->pNext;
	}
}
void XuatChuyenBay1(FLIGHT cb, int i) {
	gotoxy(X_LIST, Y_LIST +5+2*i-2);
	cout<<(trang_cb_ht-1)*10+i+1;
	gotoxy(X_LIST+5, Y_LIST+5+2*i-2);
	cout<<cb.idcb;
	gotoxy(X_LIST+5+18, Y_LIST+5+2*i-2);
	cout<<cb.idplane;
	gotoxy(X_LIST+5+18+18, Y_LIST +5+2*i-2);
	cout<<cb.NgayKhoiHanh.ngay<<"/"<<cb.NgayKhoiHanh.thang<<"/"<<cb.NgayKhoiHanh.nam;
	gotoxy(X_LIST+5+18+18+13, Y_LIST +5+2*i-2);
	cout<<cb.GioKhoiHanh.gio<<":"<<cb.GioKhoiHanh.phut;
	gotoxy(X_LIST+5+18+18+13+8, Y_LIST +5+2*i-2);
	cout<<cb.SanBayDen;
	gotoxy(X_LIST+5+18+18+13+8+18, Y_LIST +5+2*i-2);
	//cout<<cb.lst.SoVeMax;
	if(cb.stt==0) cout<<"Da huy";
	else if(cb.stt==1)cout<<cb.lst.SoVeMax - cb.lst.SoVeDaDat;
	else if(cb.stt==2) cout<<"Het Ve";
	else if(cb.stt==3)	cout<<"Hoan Tat";
	

}
void XuatDanhSachChuyenBay1(ListFlight l) {
	gotoxy(X_SL+18, Y_SL); cout<<l.n;
    gotoxy(X_PAGE+7, Y_PAGE); cout<<trang_cb_ht<<"/"<<so_trang_cb(l);
    NODE* p = l.pHead;
    int a = 0;
    int i=0, vitri=0;
    int temp;
    if(trang_cb_ht!=so_trang_cb(l)) {
    	temp=trang_cb_ht*10;
	}    
	else temp=l.n; 
    
	
    for(a; a<temp;a++){
	
        if(vitri >= (trang_cb_ht-1)*10) 
		{
			XuatChuyenBay1(p->data, i);
			i++;
		}
        p = p->pNext;
        vitri++;
    }
}
Date Input_date1(Date &n, int &main_temp)
{	
int temp1 = 1;
	while(true){
		switch(temp1)
		{
			case 1: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 2: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(2, temp1, main_temp, n);
				break;
			}
			case 3: {
				gotoxy(X_BOX+td_chuyen_bay[3].length()+3+3+3, Y_BOX+6);
				show_cur(1);
				ValidateDate(0, temp1, main_temp, n);
				break;
			}
			default: {
				
				
				return n;
				
			
				
				break;
				
				}
		}
		
		
	}
}
void InChuyenBayTheoNgay(int stt, ListFlight dscb)
{
	trang_cb_ht=1;
	td_chuyen_bay[6] = " So Ve Con";
	menu_quan_ly_chung(6);
	
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ESC: Tro lai ---- PAGE UP/DOWN: Chuyen trang";
	show_cur(0);
	

	
	Date n;
	string s;
	ListFlight dscb_kd;
	int main_temp=0;
	char key;
	
while(true){
	try_again:
	switch(main_temp)
	{	case 0 : main_temp=1; break;
		case 1 :
				{	xoa_trai();
				trang_cb_ht=1;
					GetList(dscb_kd);
					create_box(td_chuyen_bay[3], X_BOX, Y_BOX+6);
					gotoxy(X_BOX + td_chuyen_bay[3].length()+5, Y_BOX+6); cout<<"/  /";
					Input_date1(n, main_temp);	
					break;
				}
		case 2 :
				{	s="";
					create_box(td_chuyen_bay[5], X_BOX, Y_BOX+12);
					Input_place(s, main_temp);
					LayChuyenBayNgayX(dscb, dscb_kd, n, s);
						if(dscb_kd.n==0)
							{
								in_thong_bao_cb(6);
								main_temp=0;
								goto try_again;
							}
					xoa_trai();
					khung_ds_chuyen_bay();
					gotoxy(80, 6);
					cout<<setw(50)<<setfill(char(32))<<" ";
					gotoxy(80, 6);
					cout<<"DANH SACH CHUYEN BAY NGAY: "<<n.ngay<<"/"<<n.thang<<"/"<<n.nam<<" DEN: "<<s;
					
					XuatDanhSachChuyenBay1(dscb_kd);
					
					break;
					
				}
	
		case 3 :
			{
			
	while(true){
		show_cur(0);
		key=getch();
		if(key==0) key==getch();
		switch(key)
		{
			case PAGE_UP:
			if(trang_cb_ht>1)
			{
				xoa_phai_cb();
				khung_ds_chuyen_bay();
				gotoxy(80, 6);
				cout<<setw(50)<<setfill(char(32))<<" ";
				gotoxy(80, 6);
				cout<<"DANH SACH CHUYEN BAY NGAY: "<<n.ngay<<"/"<<n.thang<<"/"<<n.nam<<" DEN: "<<s;
				trang_cb_ht--;
				XuatDanhSachChuyenBay1(dscb_kd);
				
			}
			break;
		case PAGE_DOWN:
			if(trang_cb_ht<so_trang_cb(dscb_kd))
			{
				xoa_phai_cb();
				khung_ds_chuyen_bay();
				gotoxy(80, 6);
					cout<<setw(50)<<setfill(char(32))<<" ";
					gotoxy(80, 6);
					cout<<"DANH SACH CHUYEN BAY NGAY: "<<n.ngay<<"/"<<n.thang<<"/"<<n.nam<<" DEN: "<<s;
				trang_cb_ht++;
				XuatDanhSachChuyenBay1(dscb_kd);
				
			}
			break;
			case ESC:
				{	
					deleteList(dscb_kd);
					xoa_phai_cb();
					xoa_trai();
					main_temp = 0;
					goto try_again;
			 		 
					  break;
				}
			
			
			}
	
	
	}
			}
			case 7: 
			{	
				td_chuyen_bay[6] = " Trang thai ";
				deleteList(dscb_kd);
				return;
			}
}
}
}
	
// =======================================================================
// =======================================================================
// =======================================================================
int tong_so_trang_hk(FLIGHT fl)
{
	if(fl.lst.SoVeDaDat % 10 == 0) return fl.lst.SoVeDaDat / 10;
	else return fl.lst.SoVeDaDat / 10 + 1; 
}
void in_ds_hanh_khach_theo_trang(FLIGHT fl, AVL_tree T, int &temp)
{
	ListTicket ltk = fl.lst;
	string s;
	khung_ds_hk_thuoc_cb();
	if(ltk.SoVeDaDat == 0) return;
	int i, x, vi_tri = 0;
	AVL_tree T1;
	x = (trang_hk_hien_tai-1) * 10;
	for(i=temp ; i<ltk.SoVeMax ; i++)
	{
		s = ltk.dstk[i].cmnd;
		if(!s.empty() && vi_tri < 10)
		{
			gotoxy(X_LIST+2, Y_LIST+3+vi_tri*2); cout << vi_tri+x+1;
			gotoxy(X_LIST+8, Y_LIST+3+vi_tri*2); cout << i+1;
			T1 = tim_hk(T, s);
			in_hk_theo_dong(T1->data, vi_tri * 2);
			vi_tri ++;
			temp = i+1;
		}
	}
	gotoxy(X_SL, Y_SL); 
	cout << "So luong hanh khach: " << ltk.SoVeDaDat;
	gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang: " << trang_hk_hien_tai << "/" << tong_so_trang_hk(fl);
}
void in_ds_hanh_khach_thuoc_chuyen_bay_x(int stt, AVL_tree T, ListFlight fl)
{
	menu_quan_ly_chung(stt);
	gotoxy(X_NOTE, Y_NOTE);
	cout << "ENTER: Chon ---- ESC: Thoat ---- PAGE UP/PAGE DOWN: Chuyen trang";
	bool is_exit0 = 0;
	int sl = -1, max, vi_tri[max], key1;
	try_again:
	int temp = 0, n = 1;
	trang_cb_ht = 1;
	khung_ds_chuyen_bay();
	XuatDanhSachChuyenBay(fl);
	int x = Chon_Chuyen_Bay(fl);
	if(x < 0) return;
	xoa_phai();
	NODE *p = FindFlightById(fl, x);
	max = tong_so_trang_hk(p->data)+1;
	vi_tri[++sl] = temp;
	in_ds_hanh_khach_theo_trang(p->data, T, temp);
	if(sl<max) vi_tri[++sl] = temp;
	gotoxy(X_td+12, Y_td); cout << p->data.idcb;
	gotoxy(X_td-13, Y_td+1); cout << p->data.GioKhoiHanh.gio << ":" << p->data.GioKhoiHanh.phut;
	gotoxy(X_td-6, Y_td+1); cout << p->data.NgayKhoiHanh.ngay << "/" << p->data.NgayKhoiHanh.thang << "/" << p->data.NgayKhoiHanh.nam;
	gotoxy(X_td+15, Y_td+1); cout << p->data.SanBayDen;
	while(true)
	{
		if(kbhit())
		{
			key1 = getch();
			if(key1 == 224) key1 = getch();
			switch(key1)
			{
				case PAGE_UP:
					if(trang_hk_hien_tai > 1)
					{
						trang_hk_hien_tai--;
						xoa_phai();
						if(n<max-1)
						{
							n++;
							temp = vi_tri[sl-n];
							in_ds_hanh_khach_theo_trang(p->data, T, temp);
							gotoxy(X_td+12, Y_td); cout << p->data.idcb;
							gotoxy(X_td-13, Y_td+1); cout << p->data.GioKhoiHanh.gio << ":" << p->data.GioKhoiHanh.phut;
							gotoxy(X_td-6, Y_td+1); cout << p->data.NgayKhoiHanh.ngay << "/" << p->data.NgayKhoiHanh.thang << "/" << p->data.NgayKhoiHanh.nam;
							gotoxy(X_td+15, Y_td+1); cout << p->data.SanBayDen;
						}
					}
					break;
				case PAGE_DOWN:
					if(trang_hk_hien_tai < max-1)
					{
						trang_hk_hien_tai++;
						xoa_phai();
						if(sl < max-1)
						{
							temp = vi_tri[sl];
						}
						else
						{
							if(n>=0)
							{
								n--;
								temp = vi_tri[sl-n];
							}
						}
						in_ds_hanh_khach_theo_trang(p->data, T, temp);
						if(sl<max-1) vi_tri[++sl] = temp;
						gotoxy(X_td+12, Y_td); cout << p->data.idcb;
						gotoxy(X_td-13, Y_td+1); cout << p->data.GioKhoiHanh.gio << ":" << p->data.GioKhoiHanh.phut;
						gotoxy(X_td-6, Y_td+1); cout << p->data.NgayKhoiHanh.ngay << "/" << p->data.NgayKhoiHanh.thang << "/" << p->data.NgayKhoiHanh.nam;
						gotoxy(X_td+15, Y_td+1); cout << p->data.SanBayDen;
					}
					break;
				case ESC:
					xoa_phai();
					trang_hk_hien_tai = 1;
					goto try_again;
			}
		}
	}
}
void cap_nhat_so_chuyen_cho_may_bay(ListFlight lf, ds_may_bay &ds_mb)
{
	int thu_tu;
	for(NODE *k = lf.pHead ; k != NULL ; k = k->pNext)
	{
		if(k->data.stt == 3)
		{
			thu_tu = search(ds_mb, k->data.idplane);
			ds_mb.ds[thu_tu]->so_chuyen++;
		}
	}
}
