#include<iostream>
#include<string>
using namespace std;
//----------------------------------------------------------------------------------------------
class Error{ //class of error
	public:
	string error_d;
	int error_code;
 	void print_error(){ //print method of error class
		cout<<error_d<<" : "<<error_code<<endl;
	}
	Error(string error_d,int error_code):error_d(error_d),error_code(error_code){ //constructor of error class
	}
};
//----------------------------------------------------------------------------------------------
class Date{ //date class
private:
	int day,month,year;
public:
	Date(int,int,int);
	Date operator+(int);
	bool operator<=(const Date&);
	bool operator>=(const Date&);
	void printDate(Date&);
	int getDAY();
	int getMONTH();
	int getYEAR();
	void setDAY(int);
	void setMONTH(int);
	void setYEAR(int);
	friend class Room;
	friend class Hotel;
};
Date::Date(int day,int month,int year){ //constructor of date class
	if (day > 30 || month > 12 || month < 0 || year < 2019){
		throw Error("Invalid book date entered",1004);
	}
	this -> day = day;
	this -> month = month;
	this -> year = year;
}
Date Date::operator+(int days){         // "+" operator for addig days to date
	Date temp(day,month,year);
	temp.day = temp.day + days;
	while (temp.day>30){
		int rest_month = temp.day / 30;
		temp.month = temp.month + rest_month;
		temp.day = temp.day - rest_month*30;
		while (temp.month>12){
			int rest_year = temp.month / 12;
			temp.year = temp.year + rest_year;
			temp.day = temp.day - rest_year*12;
		}
	}
	return temp;
};
bool Date::operator>=(const Date&other){ // ">=" and "<=" operators for compare dates
	Date now(day,month,year);
	if (other.year<now.year){
		return true;
	}
	else if (other.year==now.year&&other.month<now.month){
		return true;
	}
	else if (other.year==now.year&&other.month==now.month&&other.day<=now.day){
		return true;
	}
	else{
		return false;
	}
};
bool Date::operator<=(const Date&other){
		Date now(day,month,year);
	if (other.year>now.year){
		return true;
	}
	else if (other.year==now.year&&other.month>now.month){
		return true;
	}
	else if (other.year==now.year&&other.month==now.month&&other.day>=now.day){
		return true;
	}
	else{
		return false;
	}

};
void Date::printDate(Date& date){        //print function for printing a date
	cout<<date.getDAY()<<" "<<date.getMONTH()<<" "<<date.getYEAR()<<endl;
}
int Date::getDAY(){                      //getter and setter methods 
	return day;
};
int Date::getMONTH(){
	return month;
};
int Date::getYEAR(){
	return year;
};
void Date::setDAY(int day){
	this -> day = day;
};
void Date::setMONTH(int month){
	this -> month = month;
};
void Date::setYEAR(int year){
	this -> year = year;
};
// guest class -----------------------------------------------------------------------------
class Guest{ 
	private:
	string guest_name,guest_gender;
	int guest_age,room_no;
	public:
	Guest(string guest_name,string guest_gender,int guest_age) : guest_name(guest_name),guest_gender(guest_gender),guest_age(guest_age){
	} //constructor of Guest class
	string getGUEST_NAME(); // getter methods prototypes of Guest classes members
	string getGUEST_GENDER();
	int getGUEST_AGE();
	int getROOM_NO();
	void setGUEST_NAME(string); // setter methods prototypes of Guest classes members
	void setGUEST_GENDER(string);
	void setGUEST_AGE(int);
	void setROOM_NO(int);
	friend class Hotel;
};
string Guest::getGUEST_NAME(){
	return guest_name;
};
string Guest::getGUEST_GENDER(){
	return guest_gender;
};
int Guest::getGUEST_AGE(){
	return guest_age;
};
int Guest::getROOM_NO(){
	return room_no;
};
void Guest::setGUEST_NAME(string guest_name){
	this -> guest_name = guest_name;
};
void Guest::setGUEST_GENDER(string guest_gender){
	this -> guest_gender = guest_gender;
};
void Guest::setGUEST_AGE(int guest_age){
	this -> guest_age = guest_age;
};
void Guest::setROOM_NO(int room_no){
	this -> room_no = room_no;
};
//Room class----------------------------------------------------------------------------------------------
class Room{
public:
	int room_no,room_type,book_days,base_price;
	Date book_date;
	Guest guest;
	Room* next; //next room pointer for walking on linked list of rooms
	float daily_price;
	virtual int calculate_price(){
	} 
	virtual void print_room(){
	}
	friend class Hotel;
	friend class Date;
	Room(int room_no,int room_type,int book_days,Date book_date,Guest guest,int base_price=100,float daily_price=25 ) : room_no(room_no),room_type(room_type),book_days(book_days),book_date(book_date),guest(guest),base_price(base_price),daily_price(daily_price){		
	if (book_days > 30){
		throw Error("Number of days to book is over the limit (30)",1003); //throwing error object
	}
	}//destructor
		~Room(){
			Room* TempPtr = next;
			while( TempPtr != NULL) {
				TempPtr->next = TempPtr;
    			delete TempPtr;
	}
	next = NULL;
	}
};
class StandardRoom:public Room{ //StandardRoom class inhariting from Room class
	private:	
		int e_bed; //number of extra beds
	public:
		StandardRoom(int e_bed,int room_no,int room_type,int book_days,Date book_date,Guest guest,int base_price=100,float daily_price=25) : e_bed(e_bed),Room(room_no,room_type,book_days,book_date,guest,base_price,daily_price){
		if(e_bed > 2){
			throw Error("Number of extra beds over the limit (2) for the standard room",1000); //throwing error object
		}
		} //constructor
		friend class Hotel;
		int calculate_price();
		void print_room();
};
int StandardRoom::calculate_price(){
	return ((book_days*daily_price)+base_price+(50*e_bed));
};
void StandardRoom::print_room(){
	cout<<" Room number: "<<room_no;
	cout<<" Room type: standard"<<endl;
	cout<<" Number of extra beds:"<<e_bed<<endl;
	cout<<" Book date: ";
	book_date.printDate(book_date);
	cout<<" Booked for:"<<book_days<<"days."<<endl;
};
class DeluxeRoom:public Room{ //DeluxeRoom class inhariting from Room class
	private:
		int e_bed; //number of extra beds
		int e_bath; //number of extra bathrooms
		string view; //view of room (city or nature)
	public:
		DeluxeRoom(string view,int e_bed,int e_bath,int room_no,int room_type,int book_days,Date book_date,Guest guest,int base_price=250 ,float daily_price=75) : view(view),e_bed(e_bed),e_bath(e_bath),Room(room_no,room_type,book_days,book_date,guest,base_price,daily_price ){
		if (e_bed > 3){
			throw Error("Number of extra beds over the limit (3) for the deluxe room",1001); //throwing error object
		}
		if (e_bath > 1){
			throw Error("Number of extra bathrooms over the limit (1) for the deluxe room",1002); //throwing error object
		}
		}//constructor
		friend class Hotel;
		int calculate_price();
		void print_room();
};
int DeluxeRoom::calculate_price(){
	int price = (book_days*daily_price)+base_price+(50*e_bed)+(100*e_bath);
	if (view == "nature"){
		price = price + 100;
	}
	return price;
};
void DeluxeRoom::print_room(){
	cout<<" Room number: "<<room_no;
	cout<<" Room type: standard"<<endl;
	cout<<" Number of extra beds:"<<e_bed<<endl;
	cout<<" Number of extra bathrooms:"<<e_bath<<endl;
	cout<<" Book date: ";
	book_date.printDate(book_date);
	cout<<" Booked for:"<<book_days<<" days."<<endl;
};
//----------------------------------------------------------------------------------------------
class Hotel{ //hotel class
	private:
		string hotel_name,hotel_city;
		int nor;  // number of rooms
		int noar; // number of available rooms
		int nog;  // number of guests
		Room* rooms; //head member of linked list of rooms in hotel
	public:
		string view; //view of hotel (city or nature)
		Hotel(string,string,int,int,string,int,Room*); // Constructer prototype of this class
		void DisplayInfo();       // DisplayInfo method prototype for displaying information about hotel
		void Book(); 			  // Book method prototype for booking room in hotel
		void list_rooms(void)const{
			Room*tempPtr; //temperory pointer for printing linkec list
				if (rooms){
					tempPtr=rooms;
					while(tempPtr){
						tempPtr -> print_room();
						cout<<" Guests info:"<<endl;
						Guest _guest = tempPtr->guest;
						cout<<_guest.getGUEST_NAME()<<","<<_guest.getGUEST_GENDER()<<","<<_guest.getGUEST_AGE();
						tempPtr = tempPtr->next;}
						}
				else{
					cout << "The hotel is empty" << endl;
}
		};
		int calculate_revenue()const{
			int total_revenue=0;
			Room *tempPtr;
			if (rooms)
			{
			tempPtr=rooms;
			while(tempPtr)
			{
			total_revenue = tempPtr->calculate_price() + total_revenue;
			tempPtr = tempPtr->next;
		}
	}
			return total_revenue;
		};
		string getHN(); 		  // getter methods prototypes of Hotel classes members
		string getHC();
		int getNOR();
		int getNOAR();
		int getNOG();
		void setHN(string); 	  // setter methods prototypes of Hotel classes members
		void setHC(string);
		void setNOR(int);
		void setNOAR(int);
		void setNOG(int);
};
Hotel::Hotel(string hotel_name,string hotel_city,int nor,int noar,string view = "unknown",int nog = 0,Room* rooms=NULL){
	this -> hotel_name = hotel_name;
	this -> hotel_city = hotel_city;
	this -> nor = nor;
	this -> noar = noar;
	this -> view = view;
	this -> nog = nog;
	this -> rooms = rooms;
};
void Hotel::DisplayInfo(){ 
	cout<<" Hotel name: "<<getHN()<<endl;
	cout<<" Hotel City: "<<getHC()<<endl;
	cout<<" Number of rooms: "<<getNOR()<<endl;
	cout<<" Number of available rooms: "<<getNOAR()<<endl;
	cout<<" Number of guests: "<<getNOG()<<endl;
	cout<<" Total revenue: "<<calculate_revenue()<<endl;
	cout<<" Rooms info:\n"<<endl;
	list_rooms();
	cout<<endl;
};
void Hotel::Book(){   // method of book
		string guest_name,guest_gender;  //temperory variables of book method
		int guest_age,roomno,room_type,nod,extra_beds;
		int day,month,year;
		cout<<" enter your name: "<<endl;
		cin>>guest_name;
		cout<<" enter your gender: "<<endl;
		cin>>guest_gender;
		cout<<" enter your age: "<<endl;
		cin>>guest_age;
		Guest guest(guest_name,guest_gender,guest_age);
		while(1){
			bool settingdate = false;
			cout<<" Enter first day date:(DD MM YYYY)"<<endl;
			cin>>day>>month>>year;
			try{ //trying setting date and go on
				Date bookdate(day,month,year);
				settingdate = true;
				while(1){
					cout<<" Enter number of days: "<<endl;
					cin>>nod;
					cout<<" Enter room no: "<<endl;
					cin>>roomno;
					if (roomno>getNOR()){ //control point of room number (is that hotel has this room?)
							cout << " Room number is out of capasity!" << endl;
					}
					Room* tempPtr; //temporary pointer for controling availability of room
						if(rooms!=NULL){
							while(tempPtr){
								tempPtr=rooms;
								if (tempPtr -> room_no == roomno && tempPtr -> book_date <= bookdate && (tempPtr -> book_date)+(tempPtr -> book_days) >= bookdate){
									cout<<" Room is not available! "<<endl;
									break;
								}
								tempPtr = tempPtr->next;}
							}				
					cout<<" Enter number of extra beds: "<<endl;
					cin>>extra_beds;
					cout<<" Enter room type: (standard:0 / deluxe:1) "<<endl;
					cin>>room_type;
					if (room_type==1){
						int extra_bath;
						cout<<" Enter number of extra bathrooms: "<<endl;
						cin>>extra_bath;
						try{ //trying implement new deluxeroom
							DeluxeRoom* room = new DeluxeRoom(view,extra_beds,extra_bath,roomno,room_type,nod,bookdate,guest);
							setNOG(getNOG()+1);
							setNOAR(getNOR()-getNOG());
							if(rooms!=NULL){ //linked list olgorithm
								room -> next = rooms;
							}
							else{
								room -> next = NULL;
							}
							rooms = room;
							cout<<" Booked successfully "<<endl;
							break;
						}
						catch(Error &e){ //catching over the limit of extra bed, extra bathroom or baoking date.
							e.print_error();
						}
					}
					else if (room_type==0){
						try{ //trying new standardroom
							StandardRoom* room = new StandardRoom(extra_beds,roomno,room_type,nod,bookdate,guest);
							if(rooms){
								room -> next = rooms;
							}
							else{
								room -> next = NULL;	
							}
							rooms = room;
							cout<<" Booked successfully "<<endl;
							break;
							}
						catch(Error &e){ //catching over the limit of book date or extra bed error. 
							e.print_error();
						}
					}
					else{
						cout<<" Invalid choice "<<endl;
					}
			 	}
			}
			catch(Error &e){ //catching invalid book date error
				e.print_error();
			}
			if (settingdate == true){
				break;
			}
	}	
}
	
string Hotel::getHN(){ //getter and setter methods
	return hotel_name;
};
string Hotel::getHC(){
	return hotel_city;
};
int Hotel::getNOR(){
	return nor;
};
int Hotel::getNOAR(){
	return noar;
};
int Hotel::getNOG(){
	return nog;
};
void Hotel::setHN(string hotel_name){
	this -> hotel_name = hotel_name;
};
void Hotel::setHC(string hotel_city){
	this -> hotel_city = hotel_city;
};
void Hotel::setNOR(int nor){
	this -> nor = nor;
};
void Hotel::setNOAR(int noar){
	this -> noar = noar;
};
void Hotel::setNOG(int nog){
	this -> nog = nog;
};
//----------------------------------------------------------------------------------------------
int main(){ 
	Hotel h1("Grand ITU Hotel","Istanbul",1200,1200,"city"); //static info of hotels
	Hotel h2("Brothers Resort Hotel","Artvin",125,125,"nature");
	Hotel h3("Vadi Hotel","Istanbul",1500,1500,"nature");
	while(1){
	cout <<"\n WELCOME TO HOTEL RESERVATION SYSTEM"<<endl;
	cout <<"\n 1. Book a room " <<"\n 2. Display hotels info "<<"\n 3. Exit \n\n ";  //main menu
	int choice;
	cin >> (choice);
	if (choice == 1){
		while(1){
		cout<<"\n Select hotel for booking "<<endl;
		cout<<" 1. Grand ITU Hotel "<<endl;
		cout<<" 2. Brothers Resort Hotel "<<endl;
		cout<<" 3. Vadi Hotel "<<endl;
		cout<<" 4. Go back\n\n ";
		int booking_choice;
		cin >> (booking_choice);
		if (booking_choice == 1){
			h1.Book();
		}
		else if (booking_choice == 2){
			h2.Book();
		}
		else if (booking_choice == 3){
			h3.Book();
		}
		else if (booking_choice == 4){
			break;
		}
		else{cout<<"invalid choice"<<endl;
			}}}
	else if (choice == 2){
		while(1){
			cout<<"\n\n Select hotel for its information "<<endl;
			cout<<"\n 1. Grand ITU Hotel "<<endl;
			cout<<" 2. Brothers Resort Hotel "<<endl;
			cout<<" 3. Vadi Hotel "<<endl;
			cout<<" 4. Go back \n"<<endl;
			int hotel_choice;
			cin >> (hotel_choice);
			if (hotel_choice == 1){
				h1.DisplayInfo();
			}
			else if (hotel_choice == 2){
				h2.DisplayInfo();
			}
			else if (hotel_choice == 3){
				h3.DisplayInfo();
			}
			else if (hotel_choice == 4){
				break;
			}
			else{
				cout<<" invalid choice"<<endl;
			}}}
	else if (choice == 3){  // exit choice
		return 0;
	}
		
	else{
		cout<<" invalid choice"<<endl;
		}}
	
}

