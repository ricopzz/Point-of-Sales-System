#include "FuncPro.hpp"

/* GLOBAL VARIABLES */
ofstream order,add,purch,cancel;
ifstream co,prod,total;
char username[50],password[50];
User user;
int i=0;
Product product[11];

void RANDOM_ID()
{
	unsigned int microseconds;
	unsigned seed = time (0); 
	string id="012345678901";
	int strength=0,len=0;
	bool flag=false,flag1=false;
	for(int i=1;i<=12;i++)
	{
		srand(seed+i*4);
		int randomNumber = rand();
		Sleep(200); 
		id[i-1]=(randomNumber%10)+48; 
		cout<<id[i-1]; // PRINT 12 RANDOM NUMBER
	}
}

void INIT_Welcome(HANDLE WINHANDLE)
{
	remove("Order.txt"); // USES TO EMPTY THE ORDER
	while(true){
		INIT_Header("WELCOME! ");
		cout<<"\n\t1. Register"<<endl;
		cout<<"\t2. Log In"<<endl;
		cout<<"\t3. Exit";
		int x=getch();
		if(x=='1')
		{
			INIT_Register(WINHANDLE);
		}
		if(x=='2')
		{
			INIT_Login(WINHANDLE);
		} 
		if(x=='3')
		{
			system("cls");
			remove("Product.txt");
			cout<<"\n\tThank you!"<<endl;
			exit(0);
		}
	}
}

void INIT_Register(HANDLE WINHANDLE)
{
	string fname,lname;
	int age;
    char curInput;
    int iChar=0;
    
	INIT_Header("REGISTER ");
	cout<<"\tFirst name : ";cin>>fname;
	cout<<"\tLast name  : ";cin>>lname;
	cout<<"\tAge        : ";cin>>age;
	if(age<17)
	{
		cout<<"\tYou are not allowed to register!";
		exit(0);
	}
	while(true)
	{
		cout<<"\tUsername   : ";cin>>username;
		if(strlen(username)>=7)
		{
			break;
		}
		else
		{
			cout<<"\tUsername must be more than 6 characters!"<<endl;
		}
	}
	do{
		cout<<"\tPassword   : ";
		memset(password,0,50);
		
		while(1){
	    	curInput = getch();
	        if(curInput==(char)8){                // 8 IS BACKSPACE ASCII
	            if(iChar!=0){               // MUST BE NESTED IF, DON'T CHANGE TO "&&" IN ONE IF
	                cout<<"\b \b";        // HIDE THE *
	                iChar--;                // SWITCH TO PREVIOUS INDEX OF ARRAY OF CHARACTERS
	                password[iChar] = 0;
	            }
	        }
	        else if(curInput==-32) getch();
	        else if(curInput==13) break;
	        else {
	            password[iChar] = curInput;
	            cout<<"*";
	            iChar++;
	        }
	    }
		if(strlen(password)>6){
		   	cout<<endl;
		   	break;
		}
		else{
			cout<<"\n\tPassword must be more than 6 characters"<<endl;
		}
	}while(true);

	
	cout<<"\tID number  : ";RANDOM_ID();
	user=User(fname,lname,username,password,age);
	user.setBalance(0);
	cout<<endl;
	system("pause");
	INIT_Welcome(WINHANDLE);
}

void INIT_Header(char menuName[])
{
    char border[75], space[75];
    int i;

    // EMPTY ARRAY OF CHAR
    for(i=0; i<75; i++) border[i] = 0;
    for(i=0; i<75; i++)  space[i] = 0;

    // FILL HORIZONTAL LINE
    for(i=0; i<74; i++) border[i] = BL_HOR1;

    // FILL SPACE TO VAR SPACE
    for(i=0; i<74; i++) space[i] = ' ';

    // CLEAR SCREEN
    system("cls");

    // BORDER
    cout<<endl<<"\t"<<BL_TOPLEFT<<border<<BL_TOPRIGHT<<endl;
    cout<<"\t"<<BL_VERTICAL<<space<<BL_VERTICAL<<endl;
    cout<<"\t"<<BL_VERTICAL<<PROGRAM_TITLE<<"\t\t\t\t\t\t\t   "<<BL_VERTICAL<<endl;
    cout<<"\t"<<BL_VERTICAL<<menuName<<"\t\t\t\t\t\t\t\t   "<<BL_VERTICAL<<endl;
    cout<<"\t"<<BL_VERTICAL<<space<<BL_VERTICAL<<endl;
    cout<<"\t"<<BL_BOTLEFT<<border<<BL_BOTRIGHT<<endl;
    fflush(stdout);
}

void MENU_Admin(HANDLE WINHANDLE)
{
	// INTIALIZE VARIABLES
    int iOrder = 0;
    int i;
    char iOption[3], iInput[2];
    

	while(1)
	{
		//Insert Header 
		INIT_Header("ADMIN MENU");
		
		// CREATE >
        for(i=0; i<5; i++) iOption[i] = ' ';
        iOption[iOrder] = '>';
        
        
		INIT_MenuBox_Top();
		//Choice inside box
		if(iOrder==0) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT ADD
		cout<<"  "<<iOption[0]<<iOption[0]<<"  Add   \t\t\t";
	    if(iOrder==0) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    if(iOrder==1) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT TOPUP
	    cout<<iOption[1]<<iOption[1]<<"  Top Up   \t\t";
	    if(iOrder==1) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	
		if(iOrder==2) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT LOGOUT
		cout<<iOption[2]<<iOption[2]<<"  Log Out   \t";
	    if(iOrder==2) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    
	    // Bottom box
		INIT_MenuBox_Bottom();
		
		// CONSOLE INPUT
	    iInput[0] = getch();
	
	    // CHECK INPUT
	    if(iInput[0]==-32)
	    {
	  		iInput[1] = getch();
	        switch(iInput[1])
	        {
	            case 75: if(iOrder!=0) iOrder--; break; // LEFT ARROW KEY
	            case 77: if(iOrder!=2) iOrder++; break; // RIGHT ARROW KEY
	        }
	    }
	
	    else if(iInput[0]==13) // enter key
        {
            switch(iOrder)
            {
                case 0: ADMIN_Add(WINHANDLE);  break; // GO TO ADD
                case 1: ADMIN_Topup(WINHANDLE); break; // GO TO TOPUP
                case 2: INIT_Welcome(WINHANDLE); break; // GOTO MAIN WELCOME
            }
        }
	}
}

void ADMIN_Topup(HANDLE WINHANDLE)
{
	string idName;
	int amount;
	INIT_Header("Top Up   ");
	cout<<"\n\tEnter user id : ";
	cin>>idName;
	if(idName==user.getUserN())
	{
		cout<<"\tEnter amount  : ";
		cin>>amount;
		user.addBalance(amount);
	}
	else
	{
		cout<<"\n\tUsername is not registered!"<<endl;
	}
	system("pause");
}

void INIT_Login(HANDLE WINHANDLE)
{
	// VARIABLES DECLARATION
    char iUsername[50];
    char oUsername[50] = "admin";
    char iPassword[50];
    char oPassword[50] = "admin";
    char curInput;
    int isPasswordTrue, iChar;
    
    remove("total.txt"); // REMOVE TOTAL TO KEEP 0
	remove("OrderDef.txt"); // REMOVE ORDER TO KEEP 0
    do
    {
   		INIT_Header("LOGIN    ");
	    SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTRED);
	    cout<<"\n\tSystem is locked! ";
	    SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    printf("\n\tPlease enter username & password \n");
	    
	    // GET INPUT USERNAME
	    cout<<"\n\tUsername : ";
	    cin>>iUsername;
	
	    // GET INPUT PASSWORD
		cout<<"\tPassword : ";
		memset(iPassword,0,50);
		iChar=0;
		while(1){
	        curInput = getch();
	        if(curInput==(char)8){                // 8 IS BACKSPACE ASCII
	            if(iChar!=0){               // MUST BE NESTED IF, DON'T CHANGE TO "&&" IN ONE IF
	                cout<<"\b \b";        // HIDE THE *
	                iChar--;                // SWITCH TO PREVIOUS INDEX OF ARRAY OF CHARACTERS
	                iPassword[iChar] = 0;
	            }
	        }
	        else if(curInput==-32) getch();
	        else if(curInput==13) break;
	        else {
	            iPassword[iChar] = curInput;
	            cout<<"*";
	            iChar++;
	        }
	    }
	         // CHECK IF USERNAME AND PASSWORD ARE CORRECT
	    if (strcmp(iUsername,oUsername)==0 && strcmp(iPassword,oPassword)==0)
		{
		 	MENU_Admin(WINHANDLE); // GO TO MENU
		}
		else if(strcmp(iUsername,username)==0 && strcmp(iPassword,password)==0)
		{
			INIT_Menu(WINHANDLE);
		}
	    else
	    {
	        cout<<"\n\n\tWrong username or password!"<<endl<<"\t";
	        system("pause");
        }
    }while(1);
}

void INIT_MenuBox_Top()
{
    char border[90], space[90];
    int i;

    // EMPTY ARRAY OF CHAR
    for(i=0; i<90; i++) border[i] = 0;
    for(i=0; i<90; i++)  space[i] = 0;

    // FILL HORIZONTAL LINE
    for(i=0; i<89; i++) border[i] = BL_HOR1;

    // FILL SPACE TO VAR SPACE
    for(i=0; i<89; i++) space[i] = ' ';

    cout<<"\n\tCHOOSE MENU BY USING LEFT AND RIGHT ARROW\n";

    // TOP BORDER
    cout<<"\n\t"<<BL_TOPLEFT<<border<<BL_TOPRIGHT<<endl;
    cout<<"\t"<<BL_VERTICAL<<space<<BL_VERTICAL<<endl<<"\t"<<BL_VERTICAL;
    fflush(stdout);
}

void INIT_MenuBox_Bottom()
{
    char border[90], space[90];
    int i;

    // EMPTY ARRAY OF CHAR
    for(i=0; i<90; i++) border[i] = 0;
    for(i=0; i<90; i++)  space[i] = 0;

    // FILL HORIZONTAL LINE
    for(i=0; i<89; i++) border[i] = BL_HOR1;

    // FILL SPACE TO VAR SPACE
    for(i=0; i<89; i++) space[i] = ' ';

    // BOTTOM BORDER
    cout<<"\t\t  "<<BL_VERTICAL<<"\n\t"<<BL_VERTICAL<<space<<BL_VERTICAL<<endl;
    cout<<"\t"<<BL_BOTLEFT<<border<<BL_BOTRIGHT<<endl<<endl;
    fflush(stdout);
}

void INIT_Menu(HANDLE WINHANDLE)
{
    // INTIALIZE VARIABLES
    int iOrder = 0;
    int i;
    char iOption[5], iInput[2];
    

	while(1)
	{
		//Insert Header 
		INIT_Header("MAIN MENU ");
		
		// CREATE >
        for(i=0; i<5; i++) iOption[i] = ' ';
        iOption[iOrder] = '>';
        
        
		INIT_MenuBox_Top();
		//Choice inside box
		if(iOrder==0) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT MENU
		cout<<"  "<<iOption[0]<<iOption[0]<<"  Product\t";
	    if(iOrder==0) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    if(iOrder==1) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT ORDER
	    cout<<"  "<<iOption[1]<<iOption[1]<<"  Order    \t";
	    if(iOrder==1) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	
		if(iOrder==2) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT CANCEL
		cout<<iOption[2]<<iOption[2]<<"  Cancel    \t";
	    if(iOrder==2) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    if(iOrder==3) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT CHECKOUT
		cout<<iOption[3]<<iOption[3]<<"  Check out  \t";
	    if(iOrder==3) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    if(iOrder==4) SetConsoleTextAttribute(WINHANDLE,TEXT_LIGHTYELLOW); // HIGHLIGHT LOGOUT
		cout<<iOption[4]<<iOption[4]<<"  Log out";
	    if(iOrder==4) SetConsoleTextAttribute(WINHANDLE,TEXT_WHITE);
	    
	    // Bottom box
		INIT_MenuBox_Bottom();
		
		// CONSOLE INPUT
	    iInput[0] = getch();
	
	    // CHECK INPUT
	    if(iInput[0]==-32)
	    {
	  		iInput[1] = getch();
	        switch(iInput[1])
	        {
	            case 75: if(iOrder!=0) iOrder--; break; // LEFT ARROW KEY
	            case 77: if(iOrder!=4) iOrder++; break; // RIGHT ARROW KEY
	        }
	    }
	
	    else if(iInput[0]==13) // enter key
        {
            switch(iOrder)
            {
                case 0: MENU_Menu(WINHANDLE); break; // GO TO MENU LIST
                case 1: MENU_Order(WINHANDLE); break; // GO TO ORDER
                case 2: MENU_Cancel(WINHANDLE); break; // GOTO CANCEL
                case 3:	MENU_Checkout(WINHANDLE); break; // GO TO CHECKOUT
                case 4: INIT_Welcome(WINHANDLE); break; // GO TO LOGIN
            }
        }
	}
}

void MENU_Menu(HANDLE WINHANDLE)
{
	char word[1000];
	INIT_Header("Product  ");
	
	cout<<"\n\tName\t\t\tCode\t\tPrice"<<endl;
	prod.open("Product.txt");
	prod.read(word,1000);
	cout<<word;
	prod.close();
	cout<<endl;
	system("pause");
	
}

void ADMIN_Add(HANDLE WINHANDLE)
{
	int price;
	char name[50],code[5];
	INIT_Header("ADD      ");
	while(true)
	{
		cout<<"\n\tEnter product name  : ";
		cin>>name;
		cout<<"\tEnter product code  : ";
		cin>>code;
		cout<<"\tEnter product price : ";
		cin>>price;
		product[i]=Product(name,code,price);
		
		add.open("Product.txt", ios::ate|ios::app);
		if(strlen(name)<7){
			add<<"\t"<<product[i].getPName()<<"\t\t\t"<<product[i].getPCode()<<"\t\t"<<product[i].getPrice()<<endl;
		}
		else{
			add<<"\t"<<product[i].getPName()<<"\t\t"<<product[i].getPCode()<<"\t\t"<<product[i].getPrice()<<endl;
		}
		add.close();
		i++;
		break;
	}
}

void MENU_Order(HANDLE WINHANDLE)
{
	string code;
	int qty;
	INIT_Header("ORDER    ");
	cout<<"\n\t1. Enter product code";
	cout<<"\n\t2. Back";
	int x=getch();
	if(x=='1')
	{
		system("cls");
	
		INIT_Header("ORDER    ");
		cout<<"\n\tProduct code : ";cin>>code;
		cout<<"\n\tQuantity     : ";cin>>qty;
		
		if(code==product[0].getPCode())
		{
			product[0].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[0].getPName().length()<7){
				order<<"\t"<<product[0].getPName()<<"\t\t\t"<<product[0].getQty()<<"\t\t\t"<<product[0].getPrice()*product[0].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[0].getPName()<<"\t\t"<<product[0].getQty()<<"\t\t\t"<<product[0].getPrice()*product[0].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app);
			purch<<product[0].getPrice()*product[0].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[1].getPCode())
		{
			product[1].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[1].getPName().length()<7){
				order<<"\t"<<product[1].getPName()<<"\t\t\t"<<product[1].getQty()<<"\t\t\t"<<product[1].getPrice()*product[1].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[1].getPName()<<"\t\t"<<product[1].getQty()<<"\t\t\t"<<product[1].getPrice()*product[1].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); // write price into txt
			purch<<product[1].getPrice()*product[1].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[2].getPCode())
		{
			product[2].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[2].getPName().length()<7){
				order<<"\t"<<product[2].getPName()<<"\t\t\t"<<product[2].getQty()<<"\t\t\t"<<product[2].getPrice()*product[2].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[2].getPName()<<"\t\t"<<product[2].getQty()<<"\t\t\t"<<product[2].getPrice()*product[2].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app);
			purch<<product[2].getPrice()*product[2].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[3].getPCode())
		{
			product[3].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[3].getPName().length()<7){
				order<<"\t"<<product[3].getPName()<<"\t\t\t"<<product[3].getQty()<<"\t\t\t"<<product[3].getPrice()*product[3].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[3].getPName()<<"\t\t"<<product[3].getQty()<<"\t\t\t"<<product[3].getPrice()*product[3].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[3].getPrice()*product[3].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[4].getPCode())
		{
			product[4].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[4].getPName().length()<7){
				order<<"\t"<<product[4].getPName()<<"\t\t\t"<<product[4].getQty()<<"\t\t\t"<<product[4].getPrice()*product[4].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[4].getPName()<<"\t\t"<<product[4].getQty()<<"\t\t\t"<<product[4].getPrice()*product[4].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[4].getPrice()*product[4].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[5].getPCode())
		{
			product[5].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[5].getPName().length()<7){
				order<<"\t"<<product[5].getPName()<<"\t\t\t"<<product[5].getQty()<<"\t\t\t"<<product[5].getPrice()*product[5].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[5].getPName()<<"\t\t"<<product[5].getQty()<<"\t\t\t"<<product[5].getPrice()*product[5].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[5].getPrice()*product[5].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[6].getPCode())
		{
			product[6].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[6].getPName().length()<7){
				order<<"\t"<<product[6].getPName()<<"\t\t\t"<<product[6].getQty()<<"\t\t\t"<<product[6].getPrice()*product[6].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[6].getPName()<<"\t\t"<<product[6].getQty()<<"\t\t\t"<<product[6].getPrice()*product[6].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[6].getPrice()*product[6].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[7].getPCode())
		{
			product[7].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[0].getPName().length()<7){
				order<<"\t"<<product[7].getPName()<<"\t\t\t"<<product[7].getQty()<<"\t\t\t"<<product[7].getPrice()*product[7].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[7].getPName()<<"\t\t"<<product[7].getQty()<<"\t\t\t"<<product[7].getPrice()*product[7].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[7].getPrice()*product[7].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[8].getPCode())
		{
			product[8].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[8].getPName().length()<7){
				order<<"\t"<<product[8].getPName()<<"\t\t\t"<<product[8].getQty()<<"\t\t\t"<<product[8].getPrice()*product[8].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[8].getPName()<<"\t\t"<<product[8].getQty()<<"\t\t\t"<<product[8].getPrice()*product[8].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[8].getPrice()*product[8].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[9].getPCode())
		{
			product[9].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[9].getPName().length()<7){
				order<<"\t"<<product[9].getPName()<<"\t\t\t"<<product[9].getQty()<<"\t\t\t"<<product[9].getPrice()*product[9].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[9].getPName()<<"\t\t"<<product[9].getQty()<<"\t\t\t"<<product[9].getPrice()*product[9].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[9].getPrice()*product[9].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		if(code==product[10].getPCode())
		{
			product[10].setQty(qty);
			order.open("Order.txt",ios::ate|ios::app);
			if(product[10].getPName().length()<7){
				order<<"\t"<<product[10].getPName()<<"\t\t\t"<<product[10].getQty()<<"\t\t\t"<<product[10].getPrice()*product[10].getQty()<<endl;
			}
			else{
				order<<"\t"<<product[10].getPName()<<"\t\t"<<product[10].getQty()<<"\t\t\t"<<product[10].getPrice()*product[10].getQty()<<endl;
			}
			order.close();
			purch.open("total.txt",ios::ate|ios::app); 
			purch<<product[10].getPrice()*product[10].getQty()<<endl;
			purch.close();
			INIT_Menu(WINHANDLE);
		}
		else
		{
			cout<<"\tCode is not registered"<<endl;
			system("pause");
		}
	}
	if(x=='2')
	{
		INIT_Menu(WINHANDLE);	
	}
	else
	{
		MENU_Order(WINHANDLE);
	}
}

void MENU_Cancel(HANDLE WINHANDLE)
{
	INIT_Header("CANCEL   ");
	cout<<"\tDeleting order ";Sleep(500);cout<<". ";Sleep(500);cout<<". ";Sleep(500);cout<<". ";Sleep(500);
	order.open("Order.txt");
	order<<"";
	order.close();
	cancel.open("total.txt");
	cancel<<"0";
	cancel.close();
}

void MENU_Checkout(HANDLE WINHANDLE)
{
	INIT_Header("CHECKOUT ");
	int tot,sum,tax,totalh,remain,bal;
	
	char word[10000];
	// current date/time based on current system
   	time_t nowt = time(0);
    // convert now to string form
    char* dt = ctime(&nowt);
    cout<<"\n\t"<<dt<< endl;
	
	cout<<"\tName\t\t\t"<<"Quantity\t\t"<<"Price\t"<<endl; 
	co.open("Order.txt");
	co.read(word,1000);
	cout<<word;
	co.close();
	total.open("total.txt");
	while(total>>tot){
		sum+=tot;
	}
	total.close();
	tax=sum*0.1;
	totalh=sum+tax;
	bal=user.getBalance();
	remain=bal-totalh;
	cout<<"\n\tSubtotal\t\t\t\t\t"<<sum;
	cout<<"\n\tTax\t\t\t\t\t\t"<<tax;
	cout<<"\n\tTotal\t\t\t\t\t\t"<<totalh;
	cout<<"\n\tBalance\t\t\t\t\t\t"<<bal;
	cout<<"\n\tCheck out now? (y/n)";
	char x= getch();
	if(x=='y'){
		if(user.getBalance()<totalh){
			cout<<"\n\tInsufficient amount!"<<endl;
			remove("total.txt"); 
			system("pause");
			INIT_Welcome(WINHANDLE);
		}
		else{
			cout<<"\n\tThank you for purchasing!"<<endl;
			user.setBalance(remain);
			remove("total.txt");
			system("pause");
			INIT_Welcome(WINHANDLE);
		}
	}
	if(x=='n'){
		INIT_Menu(WINHANDLE);
	}
	else{
		MENU_Checkout(WINHANDLE);
	}
}
