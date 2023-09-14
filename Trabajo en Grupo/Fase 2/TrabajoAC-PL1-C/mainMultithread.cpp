/*
 * mainMultithread.cpp
 *	Version Multithread del trabajo de la asignatura: "Arquitectura de Computadores"
 *
 *  Created on: Noviembre 2021
 */

#include <stdio.h>
#include <math.h>
#include <pthread.h> // Paquete necesario para los hilos
#include <CImg.h>
#include <errno.h>
#include <fstream>


using namespace cimg_library;

const char* SOURCE_IMG      = "bailarina.bmp";
const char* SOURCE_IMG2     = "flores_3.bmp";
const char* DESTINATION_IMG = "bailarina2.bmp";
const int NREPEATS = 4; //Numero de repeticiones del algoritmo
const int NTHREADS = 8; //Numero de hilos que utilizamos


//Tipo de datos utilizado
typedef long data_t;

data_t *pRsrc, *pGsrc, *pBsrc; // Punteros para R G B de la foto
data_t *pRsrc2, *pGsrc2, *pBsrc2; // Punteros para R G B de la foto 2
data_t *pRdest, *pGdest, *pBdest; // Punteros para R G B de la foto destino
data_t *pDstImage; // Punteros para la nueva foto
uint width, height; // Ancho y alto de la foto
uint width2, height2; // Ancho y alto de la foto 2
uint nComp; // Numero de componentes de las fotos
int npix; // numero de pixeles de la foto


// funcion para comprobar si existen o no las imagenes
bool check_pictures(const char *namePicture){
	std::ifstream picture(namePicture);
	return picture.good();
}

//Creamos la estructura de los hilos
struct Hilos{
	int hStart;
	int hEnd;
};

//Metodo donde hace el algoritmo cada hilo
void *Task(void* arg){
	struct Hilos* hl = (struct Hilos*) arg;
	int start = hl->hStart;
	int end = hl->hEnd;
	for(int i = start; i<end ; i++){
		pRdest[i] = (sqrt((pRsrc[i] * pRsrc[i]) + (pRsrc2[i] * pRsrc2[i])))/sqrt(2);
		pGdest[i] = (sqrt((pGsrc[i] * pGsrc[i]) + (pGsrc2[i] * pGsrc2[i])))/sqrt(2);
		pBdest[i] = (sqrt((pBsrc[i] * pBsrc[i]) + (pBsrc2[i] * pBsrc2[i])))/sqrt(2);
	}
	return NULL;
}
int main() {

	//Comprobamos si existen las fotos
	if(check_pictures(SOURCE_IMG) == false){
		perror("La imagen fuente 1 no existe");
		exit(0);
	}
	if(check_pictures(SOURCE_IMG2) == false){
		perror("La imagen fuente 2 no existe");
		exit(0);
	}
	//Cargamos las imagentes
	CImg<data_t> srcImage(SOURCE_IMG);
	CImg<data_t> srcImage2(SOURCE_IMG2);
	//Obtenemos información de las fotos
	width  = srcImage.width(); 
	height = srcImage.height();
	nComp  = srcImage.spectrum();
	width2  = srcImage2.width(); 
	height2 = srcImage2.height();
	npix = height*width;
    pDstImage = (data_t *) malloc (width * height * nComp * sizeof(data_t));

	//Comprobamos que sea multiplo del numero de hilos
	if ( width * height % NTHREADS != 0){
		perror("El número de pixeles no es múltiplo de 8");
		exit(-2);
	}

	//Comprobamos que la destino imagen existe
	if (pDstImage == NULL) {
		perror("El destino de la imagen no existe");
		exit(-2);
	}
	//Comprobamos que las imagenes son iguales
	if((width * height) != (width2 * height2)){
		perror("El tamaño de las 2 imágenes fuente no coincide");
		exit(0);
	}	
	//Creamos la estructura para medir el tiempo
    struct timespec tStart, tEnd;
	double dElapsedTimeS;

	//Creamos los hilos
	pthread_t Threads[NTHREADS];
	int pixPerThread = npix / NTHREADS;
	struct Hilos hl[NTHREADS];

	//Medimos t inicial
	if(clock_gettime(CLOCK_REALTIME, &tStart)!=0)
	{
		printf("ERROR: clock_gettime: %d. \n", errno);
		exit(EXIT_FAILURE);
	}

	//Bucle para repetir varias veces
	for(int j=0; j<NREPEATS;j++){
		//Inicializamos las variables de las dos imagenes origen
		pRsrc = srcImage.data(); 
		pGsrc = pRsrc + height * width; 
		pBsrc = pGsrc + height * width; 
		pRsrc2 = srcImage2.data();		 
		pGsrc2 = pRsrc2 + height2 * width2; 
		pBsrc2 = pGsrc2 + height2 * width2;
		// Inicializamos las variablees de la imagen destino
		pRdest = pDstImage;
		pGdest = pRdest + height * width;
		pBdest = pGdest + height * width;

		//Asignamos pixeles a cada hilo	
		for(int i = 0; i< NTHREADS; i++){
			hl[i].hStart = i * pixPerThread; //Posi
			hl[i].hEnd = hl[i].hStart + pixPerThread;
			if(NTHREADS - 1 == i){
				hl[i].hEnd =npix;
			}
			//Creamos los hilos
			if(pthread_create(&Threads[i],NULL,Task,&hl[i]) != 0){
				perror("No se ha podido crear el hilo");
				exit(-2);
			}
		}

		//Lanzamiento de cada hilo
		for(int i = 0; i<NTHREADS; i++){
			pthread_join(Threads[i], NULL);
		}

	}

	//Calculamos el tiempo final
	if(clock_gettime(CLOCK_REALTIME, &tEnd) !=0)
	{
		printf("ERROR: clock_gettime: %d. \n", errno);
		exit(EXIT_FAILURE);
	}
	//Calculamos el tiempo que tardo
	dElapsedTimeS = (tEnd.tv_sec - tStart.tv_sec);
	dElapsedTimeS += (tEnd.tv_nsec - tStart.tv_nsec)/1e+9;
	printf("Elapsed time 	: %f s.\n", dElapsedTimeS);	
	//Creamos la nueva imagen
	CImg<data_t> dstImage(pDstImage, width, height, 1, nComp);

	// Guardamos la imagen
	dstImage.save(DESTINATION_IMG); 

	// Enseñamos la imagen nueva (Se ha comentado para no aumentar la duración del programa)
	//dstImage.display();
	
	// LIberamos memoria
	free(pDstImage);

	return 0;
}
