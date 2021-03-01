#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

const char *nombre_archivo = "archivo.dat";

struct Estudiante
{
	int codigo;
	char nombres[50];
	char apellidos[50];
	int telefono;
};

void abrir();
void ingresar();
void buscarindice();
void modificar();
void buscar();
void eliminar();
void menu();

main (){
	menu();
}

void abrir(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");;
	}
	Estudiante estudiante;
	int registro = 0;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"___________________________________________________________"<<endl;
	cout<<"id"<<"Codigo"<<"Nombres     "<<"Apellidos      "<<"Telefono"<<endl;
	do{
		cout<<"___________________________________________________________"<<endl;
		cout<<registro<<" | "<<estudiante.codigo<<" | "<<estudiante.nombres<<" | "<<estudiante.apellidos<<" | "<<estudiante.telefono<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		registro+=1;
	} while (feof(archivo) ==0);
	cout<<endl;
	fclose(archivo);
}

void ingresar(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Estudiante estudiante;
	string nombre,apellido;

	do{
		fflush(stdin);
		cout<<"Ingrese el Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingrese Los Nombres:";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		cout<<"Ingrese Los Apellidos:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		cout<<"Ingrese el Telefono:";
		cin>>estudiante.telefono;
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"Desea Agregar Otro Nombre (s/n):";
		cin>>continuar;
	} while(continuar=='s'||continuar=='S');

	fclose(archivo);
	abrir();
}

void buscarindice()
{
	FILE* archivo = fopen(nombre_archivo,"rb");
	int pos=0;
	cout<<"Que registro desea ver (id): "; cin>>pos;
	fseek(archivo,pos* sizeof(Estudiante), SEEK_SET);
	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"Codigo: "<<estudiante.codigo<<endl;
	cout<<"Nombres: "<<estudiante.nombres<<endl;
	cout<<"Apellidos: "<<estudiante.apellidos<<endl;
	cout<<"Telefono: "<<estudiante.telefono<<endl;
	fclose(archivo);
}

void modificar()
{
	FILE* archivo = fopen(nombre_archivo,"r+b");
	string nombre, apellido;
	Estudiante estudiante;
	int id=0;
	cout<<"Que registro desea modificar (id): "; cin>>id;
	fseek(archivo,id* sizeof(Estudiante), SEEK_SET);
	cout<<"Ingrese nuevo codigo: ";cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingrese nuevo nombre: ";getline(cin, nombre);
	strcpy(estudiante.nombres, nombre.c_str());
	cout<<"Ingrese nuevo apellido: ";getline(cin, apellido);
	strcpy(estudiante.apellidos, apellido.c_str());
	cout<<"Imgrese nuevo telefono: "; cin>>estudiante.telefono;
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
	
}

void buscar()
{
	FILE* archivo = fopen(nombre_archivo,"rb");	
	int	 indice=0,pos=0,cod= 0;
	cout<<"Buscar Codigo:";
	cin>>cod;
	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	do{
		if (estudiante.codigo ==cod){
			pos = indice;
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		indice+=1;
	} while (feof(archivo)==0);
	cout<<"_____________"<<pos<<"__________________"<<endl;
	fseek(archivo,pos * sizeof(Estudiante),SEEK_SET);
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"Codigo: "<<estudiante.codigo<<endl;
	cout<<"Nombres: "<<estudiante.nombres<<endl;
	cout<<"Apellidos: "<<estudiante.apellidos<<endl;
	cout<<"Telefono: "<<estudiante.telefono<<endl;
	fclose(archivo);	
}

void eliminar()
{
	int id;
	Estudiante estudiante;
	FILE * archivo=fopen(nombre_archivo,"rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	cout<<"Busque el codigo del registro que desea eliminar: ";cin>>id;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	while(!feof(archivo))
	{
		fwrite(&estudiante,sizeof(Estudiante),1,auxiliar);
		if(estudiante.codigo==id)
		{
			int pos=ftell(auxiliar)-sizeof(Estudiante);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}
	cout<<"Registro eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("archivo.dat");
	rename("auxiliar.dat","archivo.dat");
}


void menu()
{
	int opc;
	string opcion;
	cout<<"------------------- Menu de manejo de archivos -------------------"<<endl;
	cout<<"1. Leer archivo"<<endl;
	cout<<"2. Agregar registro"<<endl;
	cout<<"3. Modificar registro"<<endl;
	cout<<"4. Buscar por id"<<endl;
	cout<<"5. Buscar por codigo"<<endl;
	cout<<"6. Eliminar registro"<<endl;
	cout<<"\nQue opcion quiere ejecutar: "; cin>>opc;
	switch(opc)
	{
		case 1:
			system("cls");
			abrir();
		break;
		case 2:
			system("cls");
			ingresar();
		break;
		case 3:
			system("cls");
			abrir();
			modificar();
		break;
		case 4:
			system("cls");
			abrir();
			buscarindice();
		break;
		case 5:
			system("cls");
			abrir();
			buscar();
		break;
		case 6:
			abrir();
			eliminar();
		break;
		default:
			cout<<"Esa opcion no existe"<<endl;
		break;
	}
	cout<<"Desea probar otra opcion (s/n): "; cin>>opcion;
	if(opcion=="s"||opcion=="S")
	{
		system("cls");
		menu();
	}
	else
	{
		cout<<"Proceso terminado"<<endl;
	}
}

/*
void eliminarporindice()
{
	FILE* archivo = fopen(nombre_archivo,"rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	int indice=0;
	Estudiante estudiante;
	cout<<"Busque el indice del registro que desea eliminar: ";cin>>indice;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	int des= fseek(archivo,indice* sizeof(Estudiante), SEEK_SET);
	while(!feof(archivo))
	{
		fwrite(&estudiante,sizeof(Estudiante),1,auxiliar);
		if(des==indice)
		{
			int pos=ftell(auxiliar)-sizeof(Estudiante);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}
	cout<<"Producto eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("archivo.dat");
	rename("auxiliar.dat","archivo.dat");
}
*/
