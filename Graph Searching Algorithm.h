#include<iostream>
#include<string>
#include<fstream>
using namespace std;
template <typename T>
class Vector {
private:
	T * ptr;
	int size;
	int index;
public:
	Vector() {
		index=0;

		ptr = new T[100];
		size = 0;
	}
	void PushBack(T x) {

		ptr[index] = x;
		index++;
		size++;

	}
	void Display() {
		for (int i = 0; i < size; i++) {

			cout << ptr[i]<<" ";

		}
	}

	T operator[](int i) {

		T a = ptr[i];

		return a;

	}
	void reverse() {
		T temp;
		for (int i = 0; i < size / 2; i++) {
			temp = ptr[i];
			ptr[i] = ptr[size - i - 1];
			ptr[size - i - 1] = temp;

		}
	}
	Vector<T>& operator=(const Vector<T>& d) {
	
		size = d.size;
		for (int i = 0; i < d.size; i++) {
			ptr[i] = d.ptr[i];
		}
		return *this;
	}

};
template <typename t>
class q_node {
public:
	t data;
	q_node<t> * next;
	q_node<t> * prev;
};
template <typename t>
class Queue {
private:
	q_node<t> * front;
	q_node<t> * rear;
	int length;
public:
	Queue() {
		front = NULL;
		rear = NULL;
		length = 0;
	}
	bool find(t ind) {
		q_node<t> * current=front;
		bool check = 0;
		if (isEmpty()) {
			check = 0;
		}
		if (current != NULL && current->next==NULL) {
			if (current->data == ind) {
				check = 1;
			}
		}
		while (current != NULL) {
			if (current->data == ind) {
				check = 1;
				break;
			}
			current = current->next;
		}
		return check;
	}
	bool isEmpty() {
		if (length == 0)
			return true;
		else
		{
			return false;
		}

	}
	int getLength() {
		return length;
	}
	void enQueue(t val) {
		q_node <t> * s = new q_node<t>;
		s->data.distance = val.distance;
		s->data.index=val.index;
		s->data.name=val.name;
		s->data.parent=val.parent;	
		s->next = NULL;
		if (isEmpty()) {
			front = s;
			rear = s;
		}
		else {
			rear->next = s;
			rear = s;
		}
		length++;
	}
	t deQueue() {
		q_node<t> * temp = NULL;
		temp=front;
		t s;
		if (isEmpty()) {
			cout << " NO ITEM CAN BE DEQUED AS THE LIST IS EMPTY !" << endl;
		}
		else {
			s.distance = front->data.distance;
			s.index=front->data.index;
			s.name=front->data.name;
			s.parent=front->data.parent;
			temp = front->next;
			delete front;
			front = temp;
			length--;
		}
		return s;
	}
	t mindis(){
		t pf;
		if(!front){
			cout<<"empty node.......!"<<endl;
			return pf;
		}
		q_node<t> * temp=NULL;
		temp = front;
		q_node<t> * df =NULL;
		int	h=temp->data.distance;
		df = temp;
		int g;
		while (temp){
			g=temp->data.distance;
			if(g<h){
				h=g;
				df=temp;
			}
			temp=temp->next;
		}
		temp=df;
		pf=df->data;
		
		Queue k;
		temp = front;
		k.enQueue(df->data);
		while (temp){
			if(temp == df){
				pf=df->data;
			}
			else{
				k.enQueue(temp->data);
			}
			temp=temp->next;
		}
		temp=front;
		while (temp){
			temp =temp->next;
			deQueue();
		}
		temp=k.front->next;
		while (temp){
			enQueue(temp->data);
			temp=temp->next;
		}	
		return pf;
	}
	void display() {
		q_node<t>* temp1 = front;
		while (temp1!= NULL) {
			cout << temp1->data << " ";
			temp1 = temp1->next;
		}
	}
};
template <typename T>
class vertex{
public:
	string name;
	int distance;
	vertex<T> *parent;
	int index;
	T xyz;
	Vector<int> distances;
	Vector<string> paths;
	vertex<T>(){
		name="None";
		distance=10000000000;
		parent=NULL;
		index=-1;
		xyz=' ';
	}
	vertex<T>(T x,int c){
		name=t;
		distance=c;
		parent=NULL;
	}
	vertex<T> &operator=( vertex<T> &a){
		this->name=a.name;
		this->distance=a.distance;
		this->parent=a.parent;
		this->index=a.index;
		this->distances=a.distances;
		this->paths=a.paths;
		return *this;
	}
};
class graph{
private:
	char *arr;
	int **arr1;
	string *cities;
	int t_cities;
public:
	graph(){
		cities=0;
	}
	void readfile(string path){
		ifstream read(path);
		int siz=0,row=0;
		char x1;
		if(!read.is_open()){cout<<" Error in file reading "<<endl;}
		int check;
		bool chk=false;
		while(read.get(x1)){
			check=x1;
			if((check>=48 && check<=57)||check==44 || x1=='\n'){
				if(x1 == ',' && chk == false){     ///check for the size of int array
					row++;
				}
				if(x1=='\n'){
					chk = true;
				}
			}
			siz++;
		}
		cout<<"total row = "<<row<<endl;
		arr = new char [siz];
		arr1 = new int*[row];
		for(int i=0;i<row;i++){
			arr1[i] = new int [row];
		}
		ifstream read_1(path);
		int p=0;
		while(read_1.get(x1)){
			arr[p]=x1;
			p++;
		}
		int j=0,k=0;
		cities = new string [row];
		for(int i=0;i<siz;i++){
			x1=arr[i];
			check=x1;
			if((check>=48 && check<=57)||check==44 || x1=='\n'){
				if(check>=48 && check<=57){
					check=44;
					i--;
				}
				if(check==44){
					i++;
					x1=arr[i];
					check=x1;
					bool chke = true;
					int data = 0,sum=0;
					while (check>=48 && check<=57){
						data = check - 48;
						sum = sum + data ;
						sum = sum * 10;
						i++;
						x1=arr[i];
						check=x1;
						chke = false;
						if(x1=='\n'){
							sum = sum/10;
							arr1[j][k]=sum;
							j++;
							k=0;
						}
					}
					if(chke == false){
						if(x1!='\n'){
							sum = sum /10;
							arr1[j][k]=sum;
							k++;
						}
					}
				}
			}
		}
		string a;
		int f=0;
		for(int i=1;arr[i]!='\n';i++){
			if(arr[i]==',' || arr[i] == '\n'){
				cities[f]=a;
				a="";
				f++;
			}
			else{
				a=a+arr[i];
				if(arr[i+1] == '\n'){
					cities[f]=a;
					f++;
				}
			}
		}
		t_cities=f;
	}
	int getIndex(string y){
		int x;
		for(int i=0;i<t_cities;i++){
			if(y==cities[i]){
			x=i;
			break;
			}
		}
		return x;
	}
	void addcity(){
		cout<<"Enter the new city name : ";
		string a;
		cin>>a;
		string *temp = new string [t_cities+1];
		int **temp_int = new int*[t_cities+1];
		for(int i=0;i<t_cities+1;i++){
			temp_int[i] = new int [t_cities+1];
		}
		for(int i=0;i<t_cities;i++){
			temp[i]=cities[i];
			for(int j=0;j<t_cities;j++){
				temp_int[i][j]=arr1[i][j];
			}
		}
		for(int i=0;i<t_cities;i++){
			delete[] arr1[i];	
		}
		delete[] arr1;
		arr1 = new int* [t_cities+1];
		for(int i=0;i<t_cities+1;i++){
			arr1[i]= new int[t_cities+1];
		}
		temp[t_cities]=a;
		delete []cities;
		cities=new string[t_cities+1];
		t_cities++;
		for(int i=0;i<t_cities;i++){ //storing updated cities
			cities[i]=temp[i];
		}
		for(int i=0;i<t_cities-1;i++){
			for(int j=0;j<t_cities-1;j++){
				arr1[i][j]=temp_int[i][j];	
			}
		}
		for(int i=0;i<t_cities;i++){ //for placing zero at last new added city
			arr1[i][t_cities-1]=0;
			arr1[t_cities-1][i]=0;
		}
		for(int i=0;i<t_cities-1;i++){  //layout of city's index 
			cout<<i<<". "<<cities[i]<<endl;
		}
		while (true){
			int distance;
			int cityselected;
			string h;
			cout<<"Enter the number of city which you want to associate: ";
			cin>>cityselected;
			if(cityselected<t_cities-1){
				cout<<"Distance from the "<<cities[cityselected]<<": ";
				cin>>distance;
				arr1[cityselected][t_cities-1]=distance;
				arr1[t_cities-1][cityselected]=distance;
				cout<<"press 0 to add distance again: ";
				cin>>distance;
				if(distance != 0){break;}
			}
		}
		for(int i=0;i<t_cities;i++){
			for(int j=0;j<t_cities;j++){
				cout<<" "<<arr1[i][j];
			}
			cout<<endl;
		}
	}
	void drop(){
		cout<<endl;
		int nmb;
		for(int i=0;i<t_cities;i++){  //layout of city's index 
			cout<<i<<". "<<cities[i]<<endl;
		}
		string *temp;
		int **temp_int;
		while(true){
			cout<<"press number to delete corresponding city : ";
			cin>>nmb;
			if(nmb>=0 && nmb<t_cities){
				cout<<"=> Deleting the city "<<cities[nmb];
				temp = new string [t_cities];
				temp_int = new int*[t_cities];
				for(int i=0;i<t_cities;i++){
					temp_int[i] = new int [t_cities];
				}
				for(int i=0;i<t_cities;i++){
					temp[i]=cities[i];
					for(int j=0;j<t_cities;j++){
						temp_int[i][j]=arr1[i][j];
					}
				}
				for(int i=0;i<t_cities;i++){
					delete[] arr1[i];	
				}

				int gh=0,hg=0;
				cities=new string[t_cities-1];
				arr1 = new int* [t_cities-1];
				for(int i=0;i<t_cities+1;i++){
					arr1[i]= new int[t_cities-1];
				}
				for(int i=0;i<t_cities;i++){ //storing updated cities
					if(nmb!=i){
						cities[gh]=temp[i];
						cout<<cities[gh]<<endl;
						gh++;
					}
				}
				gh=0;
				hg=0;
				for(int i=0;i<t_cities;i++){
					for(int j=0;j<t_cities;j++){
						if(i!=nmb && j!=nmb){
							arr1[gh][hg]=temp_int[i][j];
							cout<<arr1[gh][hg]<<" ";
							hg++;
						}
					}
					if(i!=nmb){
						gh++;
						hg=0;
						cout<<endl;
					}
				}
				t_cities--;
				cout<<"press 0 to delete again : ";
				cin>>hg;
				if(hg!=0){
					break;
				}
			}
		}
	}
	vertex<string>* dijekstra(int x){
		vertex<string> x1;
		Queue<vertex<string>> a;
		Queue<vertex<string>> visited;
		vertex<string> * current_city=new vertex<string>[t_cities];
		vertex<string> * temp=new vertex<string>[t_cities];
		int dist;
		for(int i=0;i<t_cities;i++){
			current_city[i].name=cities[i];
			current_city[i].index=i;
			dist = current_city[i].distance;
		}
		current_city[x].distance=0;//distance of source city set to 0
		for(int i=0;i<t_cities;i++){
			a.enQueue(current_city[i]);
		}	
		int len,x23,x12;
		while(!a.isEmpty()){
			x1=a.mindis();
			visited.enQueue(x1);
			for(int i=0;i<t_cities;i++){
				x23=arr1[x1.index][i];
				if(arr1[x1.index][i]!=0){
					if(current_city[i].distance > x1.distance+arr1[x1.index][i]){
						len=a.getLength();
						for(int j=0;j<len;j++){
							temp[j]=a.deQueue();
						}
						int k=0;
						while (temp[k].name!=current_city[i].name && k<=len){
							k++;
						}
						temp[k].distance=x1.distance+arr1[x1.index][i];
						temp[k].parent=new vertex<string>;
						temp[k].parent->name=x1.name;
						current_city[i]=temp[k];
						for(int j=0;j<len;j++){
							a.enQueue(temp[j]);
						}
					}
				}
			}	
		}
		for(int i=0;i<t_cities;i++){
			current_city[i]=visited.deQueue();
		}
		return current_city;
	}
	vertex<string>* dijekstra2(int x){
		vertex<string> x1;
		Queue<vertex<string>> a;
		Queue<vertex<string>> visited;
		vertex<string> * current_city=new vertex<string>[t_cities];
		vertex<string> * current_city_1=new vertex<string>[t_cities];
		current_city_1=dijekstra(x);
		vertex<string> * temp=new vertex<string>[t_cities];
		int dist;
		for(int i=0;i<t_cities;i++){
			current_city[i].name=cities[i];
			current_city[i].index=i;
			dist = current_city[i].distance;
		}
		current_city[x].distance=0;//distance of source city set to 0
		for(int i=0;i<t_cities;i++){
			a.enQueue(current_city[i]);
		}	
		int len,x23,x12;
		while(!a.isEmpty()){
			x1=a.mindis();
			visited.enQueue(x1);
			for(int i=0;i<t_cities;i++){
				x23=arr1[x1.index][i];
				if(arr1[x1.index][i]!=0){
					int ikk=0;
					for(int ik=0;ik<t_cities;ik++){
						if(current_city[i].name == current_city_1[ik].name){
							ikk=ik;
							ik=t_cities;
						}
					}
					//cout<<current_city[i].name<<"  s  "<<current_city_1[ikk].name<<endl;
					//cout<<current_city[i].distance <<"  d "<< current_city_1[ikk].distance <<" g "<<x1.distance+arr1[x1.index][i]<<endl;
					if((current_city[i].distance>current_city_1[ikk].distance)&&(current_city[i].distance<x1.distance+arr1[x1.index][i]) || x1.distance==0){
						cout<<current_city[i].distance <<"  d "<< current_city_1[ikk].distance <<" g "<<x1.distance+arr1[x1.index][i]<<endl;
						len=a.getLength();
						for(int j=0;j<len;j++){
							temp[j]=a.deQueue();
						}
						int k=0;
						while (temp[k].name!=current_city[i].name && k<=len){
							k++;
						}
						temp[k].distances.PushBack(x1.distance);
						//cout<<x1.distance+arr1[x1.index][i]<<" ";
						temp[k].paths.PushBack(temp[k].name);
						//cout<<x1.name<<" ";
						temp[k].distance=x1.distance+arr1[x1.index][i];
						temp[k].parent=new vertex<string>;
						temp[k].parent->name=x1.name;
						///for(int i=0;i<t_cities;i++){
						//}
						current_city[i]=temp[k];
						for(int j=0;j<len;j++){
							a.enQueue(temp[j]);
						}
					}
				}
			}	
		}
		for(int i=0;i<t_cities;i++){
			current_city[i]=visited.deQueue();
			cout<<current_city[i].name<<" -> "<<current_city[i].distance<<endl;  
		}
		//hyders work is being printed over here
		
		return current_city;
	}
	void all_distance(){
		vertex<string> * currentcity=new vertex<string>[t_cities];
		cout<<"Shortest-Part from particular city"<<endl;
		for(int i=0;i<t_cities;i++){
			cout<<i<<". "<<cities[i]<<endl;
		}
		int x;
		while(true){
			cout<<"Enter the city number = ";
			cin>>x;
			if(x<t_cities && x>=0){
				break;
			}
		}
		cout<<"--- Distance from the city "<<cities[x]<<" ---"<<endl;
		currentcity=dijekstra(x);
		for(int i=0;i<t_cities;i++){
			if(currentcity[i].distance>=100000){
				cout<<"-> "<<currentcity[i].name<<" path does not exist."<<endl;
			}
			else{
				cout<<"-> "<<currentcity[i].name<<" "<<currentcity[i].distance<<endl;
			}
		}
		for(int i=0;i<t_cities;i++){
			if(currentcity[i].distance>=100000){
				cout<<"-> "<<currentcity[i].name<<" path does not exist.";
			}
			else{
				int h=i;
				int hu=0;
				while (currentcity[h].parent){
					cout<<"->"<<currentcity[h].parent->name;
					string str=currentcity[h].parent->name;
					hu=0;
					for(int k=0;k<t_cities;k++){
						if(str == currentcity[k].name){
							break;
						}
						hu++;
					}
					h=hu;
					if(h==x){
						break;
					}
				}
			}
			cout<<endl;
		}
	}
	void shortdis(){
		vertex<string> * currentcity=new vertex<string>[t_cities];
		//currentcity=dijekstra(2);
		for(int i=0;i<t_cities;i++){
			cout<<i<<". "<<cities[i]<<endl;                                                                             
		}
		int g,jk;
		while (true){
			cout<<"enter your current position : ";
			cin>>g;
			cout<<"enter your final destination : ";
			cin>>jk;
			if((g>=0 && g <t_cities) && (jk>=0 && jk<t_cities)){
				currentcity=dijekstra(g);
				for(int i=0;i<t_cities;i++){
					if(currentcity[i].name==cities[jk]){
						jk=i;
						i=t_cities;
					}
				}
				break;
			}
		}
		cout<<cities[g]<<" to "<<currentcity[jk].name<<endl;
		if(currentcity[jk].distance>100000){
			cout<<"The distance from "<<currentcity[jk].name<<" doesn't exist"<<endl;
		}
		else{
			cout<<"The distance from "<<currentcity[jk].name<<" is "<<currentcity[jk].distance<<endl;
			int x=g;
			int h=jk;
			int hu=0;
			cout<<"PATH => "<<currentcity[jk].name;
			while (currentcity[h].parent){
				cout<<" -> "<<currentcity[h].parent->name;
				string str=currentcity[h].parent->name;
				hu=0;
				for(int k=0;k<t_cities;k++){
					if(str == currentcity[k].name){
						break;
					}
					hu++;
				}
				h=hu;
				if(h==x){
					break;
				}
			}
			cout<<endl;
		}
	}
	void all_cities(){
		vertex<string> * currentcity=new vertex<string>[t_cities];
		cout<<"----- shortest paths from all cities to a specified/given city -----"<<endl;
		for(int i=0;i<t_cities;i++){
			cout<<i<<". "<<cities[i]<<endl;
		}
		int x;
		while(true){
			cout<<"Enter the city number = ";
			cin>>x;
			if(x<t_cities && x>=0){
				break;
			}
		}
		for(int i=0;i<t_cities;i++){
			currentcity=dijekstra(i);
			int jk;
			for(int k=0;k<t_cities;k++){
				if(currentcity[k].name==cities[x]){
					jk=k;
					k=t_cities;
				}
			}
			if(currentcity[jk].distance>100000){
				cout<<"path does not exit from "<<cities[i]<<endl;						
			}
			else{
				cout<<cities[i]<<" the distance is "<<currentcity[jk].distance;
				int h=jk;
				int hu=0;
				cout<<".";
				cout<<" PATH => "<<currentcity[jk].name;
				while (currentcity[h].parent){
					cout<<" -> "<<currentcity[h].parent->name;
					string str=currentcity[h].parent->name;
					hu=0;
					for(int k=0;k<t_cities;k++){
						if(str == currentcity[k].name){
							break;
						}
						hu++;
					}
					h=hu;
					if(h==i){
						break;
					}
				}
				cout<<endl;
			}
		}
	}
};
void menu(){
	graph a;
	a.readfile("GraphData.csv");
	cout<<"------------MAPS------------"<<endl;
	while (true){
		cout<<"1. Add the city."<<endl;
		cout<<"2. Drop the city."<<endl;
		cout<<"3. Distances from one city to all other city."<<endl;
		cout<<"4. From specific city to specific city."<<endl;
		cout<<"5. Shortest paths from all cities to a specified/given city."<<endl;
		cout<<"6. press any other key to exit."<<endl;
		cout<<"Enter the funtionality number : ";
		int x;
		cin>>x;
		cout<<endl;
		if(x==1){
			a.addcity();
		}
		else if(x==2){
			a.drop();
		}
		else if(x==3){
			a.all_distance();
		}
		else if(x==4){
			a.shortdis();
		}
		else if(x==5){
			a.all_cities();
		}
		else{
			cout<<"------thank you------"<<endl;
			break;
		}
		cout<<endl;
	}
}