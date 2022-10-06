#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct Empleados
{
	char nombre[20];
	char apellido[20];
	long dni;
	int edad;
	long legajo;
	int cargo;
	int antiguedad;	
	int borrado;
	
}Empleados;

struct Recibos
{
	char nomb[25];
	char ape[25];
	long legaj;
	int carg;
	int antigued;
	long numrecibo;
    float obrasocial;
	float jubilacion;
	float haberes;
	float descuentos;
	float liquidacion;
	float antig;
	float sueldo;
	int sepelio;
	int accidentes;
	int mes;
	int anio;
	int porc;
}Recibos;

void menu();
void altaempleado(FILE* pf);
void listado(FILE* pf);
void alta2(FILE* pf, long aux);
void bajaempleado(FILE* pf);
void modificarempleado(FILE* pf);
int generarrecibo(FILE* pf, FILE* pf2);
void listarporfecha(FILE* pf2);
void listarporempleado(FILE* pf2);
void mostrarempleado(FILE* pf);
void ordenarempleado(struct Empleados vec[],int tam);

FILE* pf;
FILE* pf2;
  
struct Empleados emp;
struct Recibos rec;

int main()
{
	
	menu();
  
	return 0;
}

void menu()
{
  int a;
  do{
	system("cls");
	printf("--------------------------------------MENU PRINCIPAL------------------------------------------- \n");
	printf("  1-Altas de empleados\n");
	printf("  2-Baja de empleados  \n");
	printf("  3-Modificar empleados  \n");
	printf("  4-Mostrar empleados por orden alfabetico  \n");
	printf("  5-Generar recibo de sueldo \n");
    printf("  6-Mostrar todos los recibos de sueldo de un mes y a%co en particular\n ",164); 
    printf(" 7-Mostrar el recibo de sueldo de un empleado en particular, indicando mes y a%co\n ",164);
    printf(" 8-Salir \n ");
    printf("---------------------------------------------------------------------------------------------- \n");
	printf("\nIngrese una Opcion: ");
    scanf ("%d",&a);
    
    
    switch (a)  {
  		system ("cls");
  		case 1: altaempleado(pf);
        break;
		
		system ("cls");
    	case 2: bajaempleado(pf);
    	break;
            
        system ("cls");
        case 3: modificarempleado(pf);
		break;
            
        system ("cls");
    	case 4: mostrarempleado(pf);
        break;
            
    	system ("cls");
    	case 5: generarrecibo(pf, pf2);
    	break;
            
        system ("cls");
        case 6: listarporfecha(pf2);
        break;
        
		system ("cls");
        case 7: listarporempleado(pf2);
        break;
  	}
  
	} while (a!=8);

}


void altaempleado(FILE* pf)
{
	system("cls");
	struct Empleados emp;
	int bandera=0;
	long legajo;
	int mod;
	int alt;
	printf("Ingrese el numero de legajo del empleado: ");
	scanf("%d",&legajo);
	fflush(stdin);
	pf=fopen("empleados.bin","ab");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1)
	{
		if(legajo==emp.legajo)
		{
			system("cls");
			printf("Empleado ya registrado: \n");
			printf("\nNumero de DNI: %d ",emp.dni);
			printf("Apelido: %s \n",emp.apellido);
			printf("Nombre: %s \n",emp.nombre);
			if(emp.borrado==1)
			{
				printf("\nEl Empleado esta dado de Baja \n");
				printf("\nDesea dar de Alta 1  | Salir 2\n");
				scanf("%d",&alt);
				if(alt==1)
				{
					alta2(pf,legajo);
				}
			}
			else
			{
				printf("\nActivo");
				
			}
			bandera++;
		}
	}
	if(bandera==0)
	{
		mod=0;
	}
	else
	{
		mod=1;
	}
	fclose(pf);

	if(mod==0)
	{
	pf=fopen("empleados.bin","a+b");
	if(pf==NULL){
		
		exit -1;
	}
	
	fflush(stdin);
	printf("Ingrese el Apellido del Empleado: ");
	fflush(stdin);
	gets(emp.apellido);
	printf("Ingrese el Nombre del Empleado: ");
	fflush(stdin);
	gets(emp.nombre);
	printf("Ingrese la Edad del Empleado: ");
	fflush(stdin);
	scanf("%d",&emp.edad);
	printf("Ingrese el DNI del Empleado: ");
	fflush(stdin);
	scanf("%d",&emp.dni);
	printf("Ingrese los a%cos de antiguedad: ",164);
	fflush(stdin);
	scanf("%d",&emp.antiguedad);
	printf("\nIngrese el cargo a ocupar \n1-$20000\n2-$25000\n3-$30000\n4-$35000\n5-$40000\n");
	scanf("%d",&emp.cargo);
	fflush(stdin);
	emp.legajo=legajo;
	emp.borrado=0;
	fwrite(&emp,sizeof(Empleados),1,pf);
	printf("Alta Exitosa\n\n");
	fclose(pf);
	}
	system("pause");
}

void alta2(FILE* pf,long aux)
{
	system("cls");
	struct Empleados emp;
	int posicion;
	int salida;
	pf=fopen("empleados.bin","r+b");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1 && salida==0)
	{
		if(emp.legajo==aux)
		{
			emp.borrado=0;
			posicion=ftell(pf)-sizeof(Empleados);
			fseek(pf,posicion,0);
			fwrite(&emp,sizeof(Empleados),1,pf);
			posicion=ftell(pf)-sizeof(Empleados);
			fseek(pf,posicion,0);
			printf("Alta Exitosa\n");
			salida=1;
		}
	}
	system("pause");
	fclose(pf);
}

void bajaempleado(FILE* pf)
{
	system("cls");
	struct Empleados emp;
	int posicion;
	int bandera=0;
	int salida=0;
	long leg;
	printf("Ingrese el Numero de Legajo del Empleado a dar de Baja: ");
	scanf("%d",&leg);
	pf=fopen("empleados.bin","r+b");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1 && salida==0)
	{
		if(emp.legajo==leg)
		{
				
			if(emp.borrado==0)
			{
				emp.borrado=1;
				posicion=ftell(pf)-sizeof(Empleados);
				fseek(pf,posicion,0);
				fwrite(&emp,sizeof(Empleados),1,pf);
				posicion=ftell(pf)-sizeof(Empleados);
				fseek(pf,posicion,0);
				system("cls");
				printf("Baja Exitosa\n");
				salida=1;
			}
			else
			{
				system("cls");
				printf("\nEl Legajo Ingresado ya se encuentra dado de Baja.\n ");
				fclose(pf);
			}
			bandera++;
		}	
	}
	if(bandera==0)
	{
		system("cls");
		printf("No existe un Empleado con ese Numero de Legajo\n");
	}
	system("pause");
	fclose(pf);
}

void modificarempleado(FILE* pf)
{
	system("cls");
	struct Empleados emp;
	int posicion;
	int salida;
	int bandera=0;
	long leg;
	printf("Ingrese el numero de legajo del Empleado: ");
	scanf("%d",&leg);
	pf=fopen("empleados.bin","r+b");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1 && salida==0)
	{
		if(emp.legajo==leg)
		{
			system("cls");
			printf("\nEmpleado Encontrado Exitosamente \n");
			fflush(stdin);
			printf("\nLegajo: %d",emp.legajo);
			printf("\nApellido: %s ",emp.apellido);
			printf("\nNombre: %s ",emp.nombre);
			printf("\nEdad: %d a%cos ",emp.edad,164);
			printf("\nDNI: %d ",emp.dni);
			printf("\nAntiguedad: %d A%cos ",emp.antiguedad,164);
			if(emp.cargo==1)
			{
				printf("\nCargo 1");
			}
			else
			{
				if(emp.cargo==2)
				{
					printf("\nCargo 2");
				}
				else
				{
					if(emp.cargo==3)
					{
						printf("\nCargo 3");
					}
					else
					{
						if(emp.cargo==4)
						{
							printf("\nCargo 4 ");
						}
						else
						{
							if(emp.cargo==5)
							{
								printf("\nCargo 5");
							}
						}
					}
				}
			}
			
			
			fflush(stdin);
			printf("\nIngrese el Legajo del Empleado: ");
			fflush(stdin);
			scanf("%d",&emp.legajo);
			printf("Ingrese el Apellido del Empleado: ");
			fflush(stdin);
			gets(emp.apellido);
			printf("Ingrese el Nombre del Empleado: ");
			fflush(stdin);
			gets(emp.nombre);
			printf("Ingrese Edad del Empleado: ");
			fflush(stdin);
			scanf("%d",&emp.edad);
			printf("Ingrese el numero de DNI del Empleado: ");
			fflush(stdin);
			scanf("%d",&emp.dni);
			printf("Ingrese A%cos de Antiguedad: ",164);
			fflush(stdin);
			scanf("%d",&emp.antiguedad);
			printf("Ingrese el cargo a ocupar \n1-$20000\n2-$25000\n3-$30000\n4-$35000\n5-$40000\n");
			scanf("%d",&emp.cargo);
			fflush(stdin);
			
			posicion=ftell(pf)-sizeof(Empleados);
			fseek(pf,posicion,0);
			fwrite(&emp,sizeof(Empleados),1,pf);
			posicion=ftell(pf)-sizeof(Empleados);
			fseek(pf,posicion,0);
			printf("\nLos Datos se Modificaron\n");
			salida=1;
			bandera++;
		}
	}
	if(bandera==0)
	{
		printf("No Existe Empleado con ese Numero de Legajo\n");
	}
	system("pause");
	fclose(pf);
}

void listado(FILE* pf)
{
	system("cls");
	int bandera=0;
	struct Empleados emp;
	pf=fopen("empleados.bin","rb");
	if(pf==NULL)exit -1;
    printf("Legajo \t\t\t\t Apellido\t\t\t\t Nombre \t\t\t\tDNI\t\tEdad\t\tAntiguedad\t\tCargo");
	while (fread(&emp,sizeof(Empleados),1,pf)==1)
	{
		if(emp.borrado==0)
		{
			printf("\n%s\t\t\t\t %d\t\t\t\t %s\t\t\t\t %s\t\t %d\t\t %d\t\t %d\t\t\t\t",emp.legajo,emp.apellido,emp.nombre,emp.dni,emp.edad,emp.antiguedad);
			if(emp.cargo==1)
			{
				printf("1");
			}
			else
			{
				if(emp.cargo==2)
				{
					printf("2");
				}
				else
				{
					if(emp.cargo==3)
					{
						printf("3");
					}
					else
					{
						if(emp.cargo==4)
						{
							printf("4");
						}
						else
						{
							if(emp.cargo==5)
							{
								printf("5");
							}
						}
					}
				}
			}
			bandera++;
		}
	}
	if(bandera==0)
	{
		printf("NO HAY EMPLEADOS REGISTRADOS\n\n");
	}
	fclose(pf);
	system("pause");
}

void mostrarempleado(FILE* pf)
{
	system("cls");
	int i,tam=0,cantidademp=0;
	struct Empleados emp, vec[250];
	pf=fopen("empleados.bin","rb");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1 )
	{
		cantidademp++;                                                        
	}
	
	while (fread(&emp,sizeof(Empleados),1,pf)==1)
	{
		for(i=0;i<cantidademp-1;i++)
		{
			vec[tam]=emp;
			tam++;
		}
	}
	ordenarempleado(vec,tam);
	for(i=0;i<cantidademp-1;i++)
	{
		printf("%s \n",vec[i].apellido);
	}
	system("pause");
	fclose(pf);
}

void ordenarempleado(struct Empleados vec[],int tam)
{
	int i,j,a;
	struct Empleados menor;
	for(i=0;i<tam-1;i++)
	{
		menor=vec[i];
		a=i;
		for(j=i+1;j<tam;j++)
		{
			if(vec[j].apellido[0]==menor.apellido[0])
			{
				if(vec[j].apellido[1]<menor.apellido[1])
				{
					menor=vec[j];
					a=j;
				}
			}
			if(vec[j].apellido[0]<menor.apellido[0])
			{
				menor=vec[j];
				a=j;
			}
		}
		vec[a]=vec[i];
		vec[i]=menor;
	}
}  


int generarrecibo(FILE* pf,FILE* pf2)
{
	system("cls");
	struct Empleados emp;
	struct Recibos rec;
	int bandera=0, salida=0, mod=0;
	char nombreaux[30];
	char apellidoaux[30];
	int cargoaux;
	long legajoaux;
	int antiguedadaux;
	printf("Ingrese el Numero de Legajo del Empleado: ");
	scanf("%d",&legajoaux);
	pf=fopen("empleados.bin","rb");
	if(pf==NULL)exit -1;
	while (fread(&emp,sizeof(Empleados),1,pf)==1 && salida==0)
	{
		if(emp.legajo==legajoaux)
		{
			if(emp.borrado==0)
			{
				strcpy(nombreaux,emp.nombre);
				strcpy(apellidoaux,emp.apellido);
				cargoaux=emp.cargo;
				antiguedadaux=emp.antiguedad;
				system("cls");
				printf("\nEmpleado Encontrado \n");
				fflush(stdin);
				printf("\nLegajo: %d",emp.legajo);
				printf("\nApellido: %s ",emp.apellido);
				printf("\nNombre: %s ",emp.nombre);
				printf("\nDNI: %d \n",emp.dni);
				mod=1;
			}
			else
			{
				system("cls");
				printf("El empleado esta dado de Baja\n");
				system("pause");
				mod=0;
			}
			salida=1;
			bandera++;
		}
	}
	if(bandera==0)
	{
		system("cls");
		printf("No se encuentran Empleados Registrados con este Numero de Legajo\n");
	}
	fclose(pf);
	if(mod!=0)
	{
		pf2=fopen("recibos.bin","a+b");
		if(pf2==NULL)exit -1;
		printf("Ingrese el Numero de Recibo: ");
		fflush(stdin);
		scanf("%d",&rec.numrecibo);
		printf("\nFecha:\n");
		fflush(stdin);
		printf("\nMes: ");
		fflush(stdin);
		scanf("%d",&rec.mes);
		printf("\nIngrese a%co: ",164);
		fflush(stdin);
		scanf("%d",&rec.anio);
	
	
		strcpy(rec.nomb,nombreaux);
		strcpy(rec.ape,apellidoaux);
		rec.carg=cargoaux;
		rec.legaj=legajoaux;
		rec.antigued=antiguedadaux;
		if(rec.carg==1)
		{

			rec.sueldo=20000;
		}
		else
		{
			if(rec.carg==2)
			{
				
				rec.sueldo=25000;
			}
			else
			{
				if(rec.carg==3)
				{
					
					rec.sueldo=30000;
				}
				else
				{
					if(rec.carg==4)
					{
						
						rec.sueldo=35000;
					}
					else
					{
						if(rec.carg==5)
						{
							
							rec.sueldo=40000;
						}
					}
				}
			}
		}
		rec.jubilacion=0.20*rec.sueldo;
		rec.obrasocial=0.10*rec.sueldo;
		rec.sepelio=200;
		rec.accidentes=350;
		rec.descuentos=rec.obrasocial+rec.jubilacion+rec.sepelio+rec.accidentes;
		if(rec.antigued>=5 && rec.antigued<=9)
		{
		
			rec.antig=0.15*rec.sueldo;
			rec.porc=15;
		}
		else
		{
			if(rec.antigued>=10 && rec.antigued<=14)
			{
				
				rec.antig=0.35*rec.sueldo;
				rec.porc=35;
			}
			else
			{
				if(rec.antigued>=15 && rec.antigued<=19)
				{
					
					rec.antig=0.55*rec.sueldo;
					rec.porc=55;
				}
				else
				{
					if(rec.antigued>=20 && rec.antigued<=24)
					{
				
						rec.antig=0.75*rec.sueldo;
						rec.porc=75;
					}
					else
					{
						if(rec.antigued>=25)
						{
							rec.porc=0;
						}
					}
				}
			}
		}
		rec.haberes=rec.sueldo+rec.antig;
		rec.liquidacion=rec.haberes-rec.descuentos;
		
		fwrite(&rec,sizeof(Recibos),1,pf2);
		printf("\nRecibo Generado, Fecha :%d/%d\n\n",rec.mes,rec.anio);
		system("pause");
		fclose(pf2);
	}
}

void listarporfecha(FILE* pf2)
{
	system("cls");
	int bandera=0;
	int m,a;
	
	printf("Ingrese Mes: ");
	scanf("%d",&m);
	printf("\nIngrese a%co: ",164);
	scanf("%d",&a);
	system("cls");
	struct Recibos rec;
	pf2=fopen("recibos.bin","rb");
	if(pf2==NULL)exit -1;
	while (fread(&rec,sizeof(Recibos),1,pf2)==1)
	{
		if(rec.anio==a && rec.mes==m)
		{
			printf("\n\n-------------------------------------\n");
			printf("Numero de Recibo: %d",rec.numrecibo);
			printf("\nFecha: %d/%d",rec.mes,rec.anio);


			printf("\nApellido: %s",rec.ape);
			printf("\nNombre: %s",rec.nomb);
			if(rec.carg==1)
			{
				printf("\nCargo: 1");
			}
			else
			{
				if(rec.carg==2)
				{
					printf("\nCargo: 2");
				}
				else
				{
					if(rec.carg==3)
					{
						printf("\nCargo: 3");
					}
					else
					{
						if(rec.carg==4)
						{
							printf("\nCargo: 4");
						}
						else
						{
							if(rec.carg==5)
							{
								printf("\nCargo: 5");
							}
						}
					}
				}
			}
			printf("\nLegajo: %d",rec.legaj);
			printf("\nAntiguedad: %d A%cos",rec.antigued,164);
			fflush(stdin);
			
			printf("\nSueldo Basico: %f ",rec.sueldo);
			printf("\n%d porciento por a%cos de Antiguedad: %f",rec.porc,164,rec.antig);
			printf("\nHaberes Total: %f ",rec.haberes);

			printf("\nDescuentos: \n");
			fflush(stdin);
			printf("\n Obra Social: %f ",rec.obrasocial);
			printf("\n Jubilacion: %f ",rec.jubilacion);
			printf("\nSeguro de Sepelio: %d",rec.sepelio);
			printf("\nSeguro de Accidentes: %d",rec.accidentes);
			printf("\nDescuentos Total: %f ",rec.descuentos);
			fflush(stdin);
			printf("\n\nSueldo Total a Cobrar: ");
			printf("\nTotal: %f",rec.liquidacion);
			bandera++;
		}
	}
	if(bandera==0)
	{
		printf("No se Generaron Recibos en esa Fecha\n");
	}
	system("pause");
	fclose(pf2);
}

void listarporempleado(FILE* pf2)
{
	system("cls");
	struct Recibos rec;
	int bandera=0;
	long aux;
	
	int sepelio=200;
	int accidente=350;
	
	printf("Ingrese el Numero de Legajo del Empleado: ");
	scanf("%d",&aux);
	system("cls");
	pf2=fopen("recibos.bin","rb");
	if(pf2==NULL)exit -1;
	while (fread(&rec,sizeof(Recibos),1,pf2)==1)
	{
		if(rec.legaj==aux)
		{
			printf("\n\n-------------------------------------\n");
			printf("Numero de Recibo: %d",rec.numrecibo);
			printf("\nFecha: %d/%d \n",rec.mes,rec.anio);

			printf("\nApellido: %s",rec.ape);
			printf("\nNombre: %s",rec.nomb);
			if(rec.carg==1)
			{
				printf("\nCargo: 1");
			}
			else
			{
				if(rec.carg==2)
				{
					printf("\nCargo: 2");
				}
				else
				{
					if(rec.carg==3)
					{
						printf("\nCargo: 3");
					}
					else
					{
						if(rec.carg==4)
						{
							printf("\nCargo: 4");
						}
						else
						{
							if(rec.carg==5)
							{
								printf("\nCargo: 5");
							}
						}
					}
				}
			}
			printf("\nLegajo: %d",rec.legaj);
			printf("\nAntiguedad: %d a%cos",rec.antigued,164);
			fflush(stdin);
			printf("\nHaberes: \n");
			printf("\nSueldo Basico: %f ",rec.sueldo);
			printf("\n%d porciento por a%cos de Antiguedad: %f",rec.porc,164,rec.antig);
			printf("\nHaberes Total: %f ",rec.haberes);

			printf("\nDescuentos: \n");
			fflush(stdin);
			printf("\n Obra Social: %f ",rec.obrasocial);
			printf("\n Jubilacion: %f ",rec.jubilacion);
			printf("\n Seguro de Sepelio: %d",rec.sepelio);
			printf("\n Seguro de Accidentes: %d",rec.accidentes);
			printf("\n Descuentos Total: %f ",rec.descuentos);

			fflush(stdin);
			printf("\n\nLiquidacion a Cobrar");
			printf("\nTotal: %f",rec.liquidacion);
			bandera++;
		}
	}
	if(bandera==0)
	{
		printf("No hay Recibos de Sueldos\n");
	}
	system("pause");
	fclose(pf2);
}
