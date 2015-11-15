/*****************************************************************************
 * "Medical Store Management System" 
 *
 * This code performs various operations mainly used in medical store.
 *
 * Copyright (C) 2015 Twinkle Parmar
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<termios.h>
#include<unistd.h>
int i;
int bill_ret;
//function for auto increment customer & supplier Id.
int getcust_id();
int getsupp_id();
//function for welcome & main menu
void welcome();
void main_menu();
//function for supplier menu
void supplier();
void supp_entry();
void supp_list();
void sup_update();
void search();
void search_id();
void search_name();
//function for customer menu
void customer();
void cust_search();
void search_cid();
void search_cname();
void cust_entry();
void cust_list();
void cust_update();
//function for medicine menu
void medicine();
void medi_sale();
void stock();
void update_stock();
void medi_entry();
void medi_search();
//function for bill
int bill();
void sale_rpt();
void profit_rpt();
void pur_rpt();
//===================================structures =========================
//Structure for supplier
struct supplier {
	int supp_id;
	char supp_name[25];
	char city[20];
	char mob_no[11];
        char email[50];
};
struct supplier temp1;
FILE *ptr1;
//Structure for customer
struct customer {
	int cust_id;
	char cust_name[30];
	char city[20];
	char mob_no[11];
	char email[50];

};
struct customer temp_c;
FILE *ptr1;
//Structure for medical
struct medical {
	char id[20];
	char medi_name[20];
	int rack;
	char cabnit[2];
	int quantity;
	float sale;
	float total;
	float unit;
	float cost;
	float profit;
	float bye;
	int qty;
	char pur_date[15];
	char exp_date[15];
	char manu_date[15];
	int bill_no;
	char comp_name[20];
	char supp_name[30];
};
struct medical temp;
struct medical x[20];
FILE *ptr;
char a[10];
//Structure for bill
struct bill {
	char billno[6];
	char cname[30];
	char mediname[30];
	int medi_qty;
	float medi_rate;
	float total;
	int day;
	int month;
	int year;

};
struct bill bil;
FILE *ptrbill;
//Structure for purchase
struct purchase_report {
	char medi_id[6];
	char medir_name[20];
	char supp_name[30];
	int sDay,sMonth,sYear;
	int qty;
	float rate;
	float total;
};
struct purchase_report p_r;
FILE *ptrp_r;
//================================In main calling function==========
int main() {
	char name[15];
	char pass[15];
	int count = 0;
	system("clear");
	start:
		printf("\n*********************************************************\n");
		printf(" \t\tLOGIN TO MEDICAL STORE MANAGEMENT\t\t ");
		printf("\n*********************************************************\n");
		printf("\tEnter user name :");
		gets(name);
		printf("\n");
		printf("\tEnter password  :");
		gets(pass);
		if(strcmp(name,"twinkle") || strcmp(pass,"twinkle")) {
		system("clear");
		printf("Please Enter vailid Username & Passward!!!!!");
		count++;
		printf("%d chance left!!!!",3-count);
		system("clear");
	if(count == 3)
		exit(0);
	else
		goto start;
	}
	else {
		main_menu();
	}
	return 0;
}
//=========================Time & Date ====================
int t(void) {
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	printf("\nDate: %d-%d-%d ",now->tm_mday,now->tm_mon,now->tm_year);
	printf("\nTime: %d:%d:%d",now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
}
//=========================getsupp_id =======================
int getsupp_id() {
	FILE *fp;
	fp = fopen("supplier.dat","a");
	if(fp == NULL) {
		printf("Data not Found.....");
		return 0;
	}
	else {	
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.city, temp1.mob_no)!=EOF) {
		}
	 }
         temp1.supp_id = temp1.supp_id+1;
	 fclose(fp);
	 return temp1.supp_id;
}
//=========================getcust_id =======================
int getcust_id() {
	FILE *fp;
	fp = fopen("customer.dat","a");
	if(fp == NULL) {
		printf("Data not Found.....");
		return 0;
	}
	 else {
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city)!=EOF) {
		}
	 }
	 temp_c.cust_id = temp_c.cust_id+1;
	 fclose(fp);
	 return temp_c.cust_id;
}
//===========================main ===================
void main_menu(){
	char ch;
	do {
		system("clear");
		t();   //this function display date & time
		printf("\n=============================================\n");
		printf("\n\t\tWELCOME TO MEDICAL STORE MANAGEMENT ");
		printf("\n=============================================\n");
		printf("\n\t  Supplier Info");
		printf("\n\t  Customer Info");
		printf("\n\t  Medicine");
		printf("\n\t  Bill");
		printf("\n\t  Exit\n");
		printf("\n");
		printf("\nPress First Character for further Menu:  ");
		ch = toupper(getchar());
		switch(ch) {
			case 'S':
				supplier();
				break;
			case 'C':
				customer();
				break;
			case 'M':
				medicine();
				break;
			case 'B':
				bill();
				break;
			default:
				printf("Plese Enter right character ONLY (S,C,M,B).");
		}
	}while(ch!='E' && bill_ret != 10);
	printf("\n");
	exit(0);
}
//=========================For supplier ==========================
void supplier() {
	char ch;
	do {
		printf("\n----------------");
		printf("\nSupplier MENU");
		printf("\n----------------");
		printf("\n Add New Supplier");		
		printf("\n Update Supplier");
		printf("\n List of Existing Supplier");
		printf("\n Search Supplier ");
		printf("\n Main Menu\n");
		printf("Press First Character for further Operation: ");
		ch = toupper(getchar());
		system("clear");
		switch(ch) {
			case 'A':
				 supp_entry();
				 break;
			case 'U':
				 sup_update();
				 break;
			case 'L':
				 supp_list();
				 break;
			case 'S':
				search();
			 	break;
			case 'M':
				main_menu();
			 	break;
			default:
				printf("\nPlese Enter right character ONLY (A,L,U,S,M).");
		}
	}while(ch != 'M');

}
//========FOR SUPPLIERS ENTRY=================
void supp_entry()
{
 char ch;
 FILE *fp;
 system("clear");
	   fp=fopen("supplier.dat","a");
	   if(fp==NULL)
	   {
		printf("\n Can not open file!!");
		return;
	   }
	   system("clear");
	   ch='y';
	   while(ch=='y')
	   {
		printf("\n\t=================SUPPLIER ENTRY=================\n");
		temp1.supp_id=getsupp_id();
		printf("\n\n\tSupplier ID :");		
		printf("%d",temp1.supp_id);
		printf("\n\n\tSupplier NAME : ");
		scanf("%s",temp1.supp_name);
		printf("\n\n\tCITY: ");
		scanf("%s",temp1.city);	
		printf("\n\n\tCONTACT NO: ");
		scanf("%s",temp1.mob_no);
		printf("\n\n\tEMAIL ID: ");
		scanf("%s",temp1.email);               
		gets(temp1.email);
		printf("\n\t(S) Save");
		printf("\n\t(C) Cancel");
		printf("\n\tPress First character for the operation : ");
		scanf("%c",&ch);
		if(ch=='s' || ch=='S')
		{
			fprintf(fp,"%d %s %s %s %s\n",temp1.supp_id,temp1.supp_name,temp1.mob_no, temp1.city,temp1.email);
			fprintf(fp,"\n");
			printf("\n Added Successfully!!!!!");
		
		}
	   }
	   fclose(fp);
}

//========SUPPLIERS UPDATE=================
void sup_update() {
	FILE *fp1, *fp2;
	char filename[40],s1[40];
	char c;
	int line, temp = 1;
	printf("Enter file name: "); 
	scanf("%s", filename);
	fp1 = fopen(filename, "r");  //supplier.dat
	c = getc(fp1);
	fp2 = fopen("updatesupp", "w");
	printf("\nEnter ID of supplier to be updated:");
	scanf("%d", &line);
	while (c != EOF) {
        			printf("%c", c);
				if (c =='\n') {
 	          		 	temp++;
					printf("%d",temp);
				}
				if (temp != line) {
        				putc(c, fp2);

				}
				else {
					while ((c = getc(fp1)) != '\n') {
            				}
          			printf("\tEnter new data:");
				scanf("%s",s1);
             			fprintf(fp2,"\n");
            			fputs(s1, fp2);  
           		        temp++;
				}
        	c = getc(fp1);
    	}
        fclose(fp1);
	fclose(fp2);
}
//=========FOR SUPPLIER DISPLAY LIST ==========
void supp_list() {
	char ch;
	FILE *ptr1;
	system("clear");
	ptr1 = fopen("supplier.dat","r");
	if(ptr1 == NULL) {
		printf("\n\t Can not open File..! ");exit(0);
	}
	ch = fgetc(ptr1);
	while(ch != EOF) {
			printf("%c",ch);
			ch = fgetc(ptr1);
	}
	fclose(ptr1);
        getchar();
}
//======================search supplier==================
void search() {
	int ch;
	do {
		printf("\n\nTwo options Available for searching ");
		printf("\nSearch by");
		printf("\n 1. ID number");
		printf("\n 2.Name");
		printf("\nReturn");
		printf("\n Press First charecter for the operation : ");
		ch = toupper(getchar());
		system("clear");
	   	switch(ch) {
			case 'I':
				search_id();
				break;
			case 'N':
				search_name();
				break;
			case 'R':
				supplier();
				break;
			default:
				printf("\nPlease enter right choice!!!!!");
		}
	   }while(ch != 'R');
}
//=============================== Search by id =============================
void search_id() {
	int id;
	FILE *fp;
	fp = fopen("supplier.dat","r");
	if(fp == NULL) {
		printf("file can't open!!!!");
	}
	system("clear");
	printf("\n Enter id to be searched:");
	scanf("%d",&id);
	printf("\nID.\tSUPPLIER NAME.\tCITY.\tPH.NO"); 
	while(fscanf(fp,"%d %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.mob_no,temp1.city)!=EOF) {
		if(temp1.supp_id == id) {
			printf("\n%d",temp1.supp_id);
			printf("\t%s",temp1.supp_name);
			printf("\t\t%s",temp1.city);
			printf("\t%s",temp1.mob_no);
			break;
		}
	}
	if(temp1.supp_id != id) {
		printf("\n Record not found!");
	}
	fclose(fp);
	getchar();
}
//============================ Search by name =============================
void search_name() {
	char name[20];
	FILE *fp;
	fp = fopen("supplier.dat","r");
	if(fp == NULL) {
		printf("file can't open!!!!");
	}
	system("clear");
	printf("\n Enter Supplier Name to be searched : ");
	scanf("%s",name);
	printf("\nID.\tSUPPLIER NAME.\tCITY.\tPH.NO.");
	while(fscanf(fp,"%d %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.mob_no, temp1.city)!=EOF) {
		if(strcmp(temp1.supp_name,name) == 0) {
			printf("\n %d",temp1.supp_id);
			printf("\t %s",temp1.supp_name);
			printf("\t%s",temp1.city);
			printf("\t%s",temp1.mob_no);
			break;
		}
	   }
	   if(strcmp(temp1.supp_name,name)!=0) {
		printf("\n Record not found!!!");
	   }
	   fclose(fp);
	   getchar();
}
//=========================For customer ===========================
void customer() {
	char ch;
	do {
	 	printf("\n\n---------------");
	  	printf("\nCustomer Menu.");
	  	printf("\nAdd New Customer");
	  	printf("\nUpdate Customer");
	  	printf("\nList of Existing Customer ");
	  	printf("\nSearch Customer");
		printf("\nMain Menu");
	  	printf("\nPress First Character for further Operations  ");
	  	ch = toupper(getchar());
          	system("clear");
	  	switch(ch) {
			case 'A':
				cust_entry();
				break;
			case 'U':
				cust_update();
				break;
			case 'L':
				cust_list();
				break;
			case 'S':
				cust_search();
				break;
			case 'M':
				main_menu();
			 	break;
			default:
				printf("\nPlese Enter right character ONLY (A,L,U,S,M).");
		}
	}while(ch!='M');

}
//========FOR CUSTOMER ENTRY=================
void cust_entry() {
 char ch;
 FILE *fp;
 system("clear");
	   fp=fopen("customer.dat","a");
	   if(fp == NULL) {
		printf("\n Can not open file!!");
		return;
	   }
	   system("clear");
	   ch='y';
	   while(ch=='y') {
		printf("\n\t----CUSTOMER ENTRY---\n");
		temp_c.cust_id=getcust_id();
		printf("\nCUSTOMER ID :");		
		printf("%d",temp_c.cust_id);
		printf("\nCUSTOMER NAME : ");
		scanf("%s",temp_c.cust_name);
		printf("\nCITY: ");
		scanf("%s",temp_c.city);	
		printf("\nCONTACT NO: ");
		scanf("%s",temp_c.mob_no);
		printf("\nEMAIL ID: ");
		scanf("%s",temp_c.email);               
		gets(temp_c.email);
		printf("\nSave");
		printf("\nCancel");
		printf("\n Press First character for the operation : ");
		scanf("%c",&ch);
		if(ch=='s' || ch=='S') {
			fprintf(fp,"%d %s %s %s %s\n",temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email);
			fprintf(fp,"\n");
			printf("\nCustomer Added Successfully!!!!!");
		
		}
	   }
	   fclose(fp);
}
//============CUSTOMER update=================
void cust_update() {
	FILE *fp1, *fp2;
	char filename[40],s1[40];
	char c;
	int line, temp = 1;
	printf("Enter file name: "); 
	scanf("%s", filename);
	fp1 = fopen(filename, "r");  //customer.dat
	c = getc(fp1);
	fp2 = fopen("updatedcust", "w");
	printf("\nEnter line no. to be updated:");
	scanf("%d",&line);
	while (c != EOF) {
        			printf("%c", c);
				if (c =='\n') {
 	          		 	temp++;
					printf("%d",temp);
				}
				if (temp != line) {
        				putc(c, fp2);

				}
				else {
				while ((c = getc(fp1)) != '\n') {
            							}
            			printf("\tEnter new text:");
				scanf("%s",s1);
             			fprintf(fp2,"\n");
            			fputs(s1, fp2);  
           		        temp++;
				}
		c = getc(fp1);
	}
	fclose(fp1);
	fclose(fp2);
}
//=========FOR CUSTOMER DISPLAY LIST ==========
void cust_list() {
	char ch;
	FILE *ptr1;
	system("clear");
	ptr1 = fopen("customer.dat","r");
	if(ptr1 == NULL) {
		printf("\n\t Can not open File..! ");exit(0);
		
	}
	ch = fgetc(ptr1);
	while(ch!=EOF) {
			printf("%c",ch);
			ch=fgetc(ptr1);
	}
	fclose(ptr1);
	getchar();
}
//======================search CUSTOMER==================
void cust_search() {
	int chr;
	do {
		printf("\n\nTwo options Available for searching ");
		printf("Search by");
		printf("\nID number");
		printf("\nName");
		printf("\nReturn");
		printf("\nPress First charecter for the operation : ");
		chr=toupper(getchar());
      		system("clear");
		switch(chr) {
			case 'I':
				search_cid();
				break;
			case 'N':
				search_cname();
				break;
			case 'R':
				customer();
				break;
			default:
		    		printf("\nPlease enter right choice!!!!!");
		}		
	}while(chr!='R');
	getchar();
}
//===========================Search by CustomerId=========================
void search_cid() {
	int id;
	FILE *fp;
	fp=fopen("customer.dat","rb");
	printf("\n Enter id to be searched:");
	scanf("%d",&id);
	printf("\nID.\tCUSTOMER NAME.\tCITY.\tMOBILE.NO.");
	while(fscanf(fp,"%d %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city)!=EOF) {
		if(temp_c.cust_id==id) {	
			printf("\n%d",temp_c.cust_id);
			printf("\t%s",temp_c.cust_name);
			printf("\t\t%s",temp_c.city);
			printf("\t%s",temp_c.mob_no);
			break;
		}
	   }
	if(temp_c.cust_id!=id) {
		printf("\nRecord not found!");
	}
	fclose(fp);
	getchar();
}
/*****************************search by CUSTOMERname******************************/
void search_cname() {
	char name[20];
	FILE *fp;
	fp = fopen("customer.dat","rb");
	printf("  Enter Customer Name to be searched:");
	scanf("%s",name);
	printf("\nID.\tCUSTOMER NAME.\tCITY.\tMOBILE.NO.");
	while(fscanf(fp,"%d %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city)!=EOF) {
		if(strcmp(temp_c.cust_name,name)==0) {
			printf("\n%d",temp_c.cust_id);
			printf("\t%s",temp_c.cust_name);
			printf("\t%s",temp_c.city);
			printf("\t%s",temp_c.mob_no);
			break;
		}
	}
	if(strcmp(temp_c.cust_name,name)!=0) {
		printf("\nRecord not found!");
	}
	fclose(fp);
	getchar();
}
//=========================For Medicine ===========================
void medicine() {
	char ch;
	do {
	  system("clear");
	  printf("\n\n\t********** Medicine Menu **********");
	  printf("\n\n\t=======================================");
	  printf("\n\t(P) Purchase New Medicine");
	 // printf("\n\t(S) Sale Medicine");
	  printf("\n\t(C) Stock of Medicine");
	  printf("\n\t(A) Search Medicine");
	  printf("\n\t(M) Main Menu");
	  printf("\n\n\tPress First Character for further Operations:");
          ch=toupper(getchar());
	 	 switch(ch) {
			case 'P':medi_entry();
				 break;
			case 'C':stock();
			 	 break;
			case 'A':medi_search();
				 break;
			case 'M':main_menu();
				 break;
			default:
				break;
		}
	}while(ch!='M');
}
//============================ FOR MEDICINE PURCHASE    ===================
void medi_entry() {
	char ch,id[20];
	time_t t = time(0);   
	struct tm * now = localtime( & t );
	int f;
	FILE *fp;
	ptrp_r=fopen("purreport.dat","a");
	ch = 'Y';
	while(ch=='Y') {
		printf("\n\t================= MEDICINE PURSHASE =================\n"); {
			printf("\n\tMEDICINE ID: ");
			scanf("%s",temp.id);
			strcpy(id,temp.id);
			fp=fopen("medical.dat","a");
			while((fread(&temp,sizeof(temp),1,fp))==1) {
				if(strcmp(id,temp.id)==0) {
					f=1;
					break;
				}
			}
			fclose(fp);
			if(f==1) {
				printf("\n\tID Allready Exists");
				getchar();
				medi_entry();
			}
			else {
				ptr=fopen("medical.dat","a+b");
				strcpy(temp.id,id);
				strcpy(p_r.medi_id,temp.id);
			}
			printf("\n\tMEDICINE NAME: ");
                        scanf("%s",temp.medi_name);
			strcpy(p_r.medir_name,temp.medi_name);
			printf("\n\tENTER RACK NO: ");
			scanf("%d",&temp.rack);
			printf("\n\tCABINIT NO: ");
			scanf("%s",temp.cabnit);
			printf("\n\tCOMPANY NAME: ");
                        scanf("%s",temp.comp_name);
			printf("\n\tSUPPLIER NAME: ");
                        scanf("%s",temp.supp_name);
			strcpy(p_r.supp_name,temp.supp_name);
			printf("\n\tUNIT COST   Rs:  ");
			scanf("%f",&temp.unit);
			p_r.rate=temp.unit;
			printf("\n\tSALE COST   Rs: ");
			scanf("%f",&temp.sale);
			printf("\n\tQUANTITY      :  ");
			scanf("%d",&temp.quantity);
			p_r.qty=temp.quantity;
			printf("\n\tMFG.DATE(dd-mm-yyyy): ");
			scanf("%s",temp.manu_date);
			printf("\n\tEXP.DATE(dd-mm-yyyy): ");
			scanf("%s",temp.exp_date);
			printf("\n\t==========================================================");
			temp.total=temp.quantity*temp.sale;
			printf("\n\tTOTAL SALE COST = Rs. %.2f",temp.total);
			temp.cost=(temp.unit*temp.quantity);
			printf("\n\tTOTAL UNIT COST = Rs. %.2f",temp.cost);
			p_r.total=temp.cost;
			p_r.sDay=now->tm_mday;
			p_r.sMonth=now->tm_mon;
			p_r.sYear=now->tm_year;
		}
		printf("\n\n\t(S) Save");
		printf("\n\t(C) Cancel");
		printf("\n\tPress First charecter for the operation : ");
		ch=toupper(getchar());
                scanf("%c",&ch);
		if(ch=='s' || ch=='S') {
			fwrite(&temp,sizeof(temp),1,fp);
                	fprintf(ptrp_r,"%s %s %s %d %.2f %.2f %d %d %d\n",p_r.medi_id,p_r.medir_name,p_r.supp_name,p_r.qty,p_r.rate,p_r.total,p_r.sDay,p_r.sMonth,p_r.sYear);
                	fprintf(ptrp_r,"\n");
			printf("\nMedicine Added sucessfully!!!!!!");
		}

	   }
	   fclose(ptr);
	   fclose(ptrp_r);
}

//===========================MEDICINE STOCK=====================================
void stock() {
 	int c;
	do {
		system("clear");
		ptr1=fopen("medical.dat","r");
		if(ptr1==NULL) {
			printf("\n\t Can not open File! ");
		}
		system("clear");
		printf(" \nSTOCK OF MEDICINE ");
		printf("\nID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
		printf("\n==================================================================\n");
		while((fread(&temp,sizeof(temp),1,ptr1))==1) {
			printf("\n%s",temp.id);
			printf("\t%s",temp.medi_name);
			printf("\t\t%d",temp.quantity);
			printf("\t%s",temp.supp_name);
			printf("\t\t%s",temp.exp_date);
		}
		printf("\nPress 0 for main menu ");
		c = (getchar());
		switch (c) {
			case '0':
				 main_menu();
				 break;
		}

	   }while(c != '1');
	   //getchar();
}
//=============================== FOR MEDICINE SEARCH ====================
void medi_search() {
	char mid[6];
	ptr1=fopen("medical.dat","r");
	if(ptr1==NULL) {
		printf("\n\t Can not open File! ");
	}
	printf("\n\tEnter Medicine Id to be searched : ");
	scanf("%s",mid);
	printf(" \n MEDICINE ");
	printf("\nID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
	printf("\n==================================================================\n");
	while((fread(&temp,sizeof(temp),1,ptr1))==1) {
		if(strcmp(mid,temp.id)==0) {
			printf("\b%s",temp.id);
			printf(" %s",temp.medi_name);
			printf(" %d",temp.quantity);
			printf(" %s",temp.supp_name);
			printf(" %s",temp.exp_date);
			break;
		}

	}
	if(strcmp(mid,temp.id)!=0) {
		printf("Not in Stock.....");
	}
	getchar();

}
//============================ FOR MEDICINE UPDATE =====================
void update_stock() {
	char mid[6];
	int j,a,count=0,n;
	system("clear");
	ptr=fopen("medical.dat","rb");
	if(ptr==NULL) {
		printf("\n\t Can not open File! ");
	}
	system("clear");
	printf("\n\tUPDATE MEDICINE QUANTITY "); 
	printf("\n\tEnter medicine id to be update qty: ");
	scanf("%s",mid);
	j=0;
	while((fread(&temp,sizeof(temp),1,ptr))==1) {
		if((strcmp(temp.id,mid)<0) || (strcmp(temp.id,mid)>0)) {
			x[j] = temp;
			j++;
		}
		else {
			printf("\n\tMedicine Name     : %s",temp.medi_name);
			printf("\n\tQuantity in stock : %d",temp.quantity);
			printf("\n\tQuantity want to update : ");
			scanf("\t%d",&a);
			x[j]=temp;
			x[j].quantity=(x[j].quantity+a);
			x[j].total=(x[j].quantity*temp.sale);
			x[j].cost=(x[j].quantity*temp.unit);
			x[j].bye=(x[j].sale*a);
			x[j].qty=a;
			j++;
			count++;
		}
	   }
	   if (count==0) {
		 system("clear");
		 printf("\n\tNot in stock!!!!!!");
		 return;
	   }
	   fclose(ptr);
	   n = j;
	   system("clear");
	   ptr=fopen("medical.dat","wb");
	   for(i=0; i<n; i++)
	   fwrite(&x[i],sizeof(x[i]),1,ptr);
	   fclose(ptr);
}
void pur_rpt_daily() {
	int j,d,m,y;
	float total=0.00;
	ptrp_r=fopen("purreport.dat","r");
	if(ptrp_r==NULL) {
		printf("\n\t Can not open File! ");
	}
	system("clear");  
	printf("Enter Date(dd-mm-yyyy):  ");
	scanf("%d-%d-%d",&d,&m,&y);
	system("clear");
	printf("\nPress Enter to go to REPORT MENU ...........");
	printf("\nPurchase Report");
	printf("\nID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date");
	printf("\n===================================================================");
	j=14;
	while(fscanf(ptrp_r,"%s %s %s %d %f %f %d %d %d\n",p_r.medi_id,p_r.medir_name,p_r.supp_name,&p_r.qty,&p_r.rate,&p_r.total,&p_r.sDay,&p_r.sMonth,&p_r.sYear)!=EOF) {
		if(d==p_r.sDay &&m== p_r.sMonth && y==p_r.sYear) {
		printf("%s",p_r.medi_id);
		printf("%s",p_r.medir_name);
		printf("%s",p_r.supp_name);
		printf("%d",p_r.qty);
		printf("%.2f",p_r.rate);
		printf("%.2f",p_r.total);
		printf("%d-%d-%d",p_r.sDay,p_r.sMonth,p_r.sYear);
		j+=2;
		total=total+p_r.total;
		}
	   }
	   printf("-------------------------------------------------------------------");
	   printf("Total:        %.2f",total);
	   getchar();
}
/*Bill Calculate*/
int bill() {
	int ret;
    	time_t td = time(0);   // get time now
	struct tm * now = localtime( & td );
	FILE *ptrbill;
	char id[6];
	int d1,m,y;
	float netamt=0.0;
	d1=now->tm_mday;
	m=now->tm_mon;
	y=now->tm_year;
	ptrbill=fopen("dbbill.dat","r");
	printf("Enter bill no: ");
	scanf("%s",id);
	printf("Bill No: ");
	printf(" %s",id);
	printf("\nDate : ");
	printf("%d-%d-%d",d1,m,y);
	printf("\nMedicine_Name\tCustomer_Name\tQty\tRate\tTotal\n");
	printf("\n---------------------------------------------------------------------");
        printf("\n---------------------------------------------------------------------");     
	while(fscanf(ptrbill,"%s %s %s %d %f %f %d %d %d",bil.billno,bil.cname,bil.mediname,&bil.medi_qty,&bil.medi_rate,&bil.total,&bil.day,&bil.month,&bil.year)!=EOF) {
		       do {
				if(strcmp(id,bil.billno)==0) {       
					printf("\n%s",bil.mediname);
					printf("\t\t%s",bil.cname);
					printf("\t\t%d",bil.medi_qty);
					printf("\t%.2f",bil.medi_rate);
					printf("\t%.2f",bil.total);
					netamt=netamt+bil.total;
				}  
			}while(feof(ptrbill));
	 }
	 printf("\n---------------------------------------------------------------------");
	 printf("\nNet Amount : ");
	 printf("%.2f",netamt);
	 fclose(ptrbill);
	 printf("\n Do you want to continue press 1 otherwise press 2\t");
	 scanf("%d", &ret);
	 if(ret == 1)
		main_menu();
	 else
	   	return(10);
	return 0;
}

