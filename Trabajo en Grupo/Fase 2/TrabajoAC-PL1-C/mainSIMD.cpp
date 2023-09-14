/*
 * mainSIMD.cpp
 *	Version SIMD del trabajo de la asignatura: "Arquitectura de Computadores"
 *
 *  Created on: Noviembre 2021
 */

#include <stdio.h>
#include <immintrin.h> // Paquete requerido para SIMD
#include <CImg.h>
#include <errno.h>
#include <fstream>

using namespace cimg_library;

// Tipo de datos para las imagenes
typedef float data_t;

const char* SOURCE_IMG      = "bailarina.bmp";
const char* SOURCE_IMG2      = "flores_3.bmp";
const char* DESTINATION_IMG = "bailarina2.bmp";
const int NREPEATS = 4; // Numero de veces que se repite el algoritmo
const int NPIXSIZE = 8; // Tamaño de los paquetes simd

// funcion para comprobar si existen o no las imagenes
bool check_pictures(const char *namePicture){
	std::ifstream picture(namePicture);
	return picture.good();
}

int main() {
	// Comprobar si existen las imagenes
    if(check_pictures(SOURCE_IMG) == false){
		perror("La imagen fuente 1 no existe");
		exit(0);
	}
    if(check_pictures(SOURCE_IMG2) == false){
		perror("La imagen fuente 2 no existe");
		exit(0);
	}
	//Se cargan las fotos
    CImg<data_t> srcImage(SOURCE_IMG);
	CImg<data_t> srcImage2(SOURCE_IMG2);

    data_t *pRsrc, *pGsrc, *pBsrc; // Punteros para R G B de la foto
	data_t *pRsrc2, *pGsrc2, *pBsrc2; // Punteros para R G B de la foto 2
	data_t *pRdest, *pGdest, *pBdest; // Punteros para R G B de la foto destino
	data_t *pDstImage; // Punteros para la nueva foto
	uint width, height; // Ancho y alto de la foto
	uint width2, height2; // Ancho y alto de la foto 2
	uint nComp; // Numero de componentes de las fotos

   	width  = srcImage.width(); // Obtenemos la imformacion respecto a la imagen inicial
	height = srcImage.height();
	nComp  = srcImage.spectrum();
	width2  = srcImage2.width(); // Obtenemos la imformacion respecto a la imagen inicial 2
	height2 = srcImage2.height();

    pDstImage = (data_t *) malloc (width * height * nComp * sizeof(data_t));
	//Comprobamos que es multiplo del numero de pixeles con los que se va a trabajar
	if ( width * height % NPIXSIZE != 0){
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
    // Creamos la estructura para calcular el tiempo
    struct timespec tStart, tEnd;
	double dElapsedTimeS;
	// Tomamos el tiempo inicial
	if(clock_gettime(CLOCK_REALTIME, &tStart)!=0)
	{
		printf("ERROR: clock_gettime: %d. \n", errno);
		exit(EXIT_FAILURE);
	}
	// Se calcula el numero de pixeles de las imagenes
    int npix = height * width;


	//Bucle para el tiempo
	for(int j=0;j<NREPEATS;j++){

		//Inicializamos las variables 
        pRsrc = srcImage.data(); 
		pGsrc = pRsrc + height * width; 
		pBsrc = pGsrc + height * width; 
		pRsrc2 = srcImage2.data();		
		pGsrc2 = pRsrc2 + height2 * width2; 
		pBsrc2 = pGsrc2 + height2 * width2;
        pRdest = pDstImage;
		pGdest = pRdest + height * width;
		pBdest = pGdest + height * width;

		//Paquetes para R G B de cada imagen 
		__m256 rPacket, gPacket, bPacket;		
        __m256 rPacket2, gPacket2, bPacket2;
		//Paquete destino
		__m256 dRPack, dGPack, dBPack;
		//Paquetes para multiplicar
        __m256 prodRPack2, prodGPack2, prodBPack2;
		__m256 r2 = _mm256_set1_ps(2); //Se carga 2
        r2 = _mm256_sqrt_ps(r2); // Se hace la raiz cuadrada de 2
        //Inicio 
        for(int i = 0; i<npix; i+=8){
			//Cargar los datos desde memoria

			rPacket =_mm256_loadu_ps(pRsrc + i);
			gPacket =_mm256_loadu_ps(pGsrc + i);
			bPacket =_mm256_loadu_ps(pBsrc + i);
			rPacket2 =_mm256_loadu_ps(pRsrc2 + i);
			gPacket2 =_mm256_loadu_ps(pGsrc2 + i);
			bPacket2 =_mm256_loadu_ps(pBsrc2 + i);

            
            //Ejecutamos el algoritmo
            dRPack = _mm256_mul_ps(rPacket, rPacket);
            prodRPack2 = _mm256_mul_ps(rPacket2, rPacket2);
            dGPack = _mm256_mul_ps(gPacket, gPacket);
            prodGPack2 = _mm256_mul_ps(gPacket2, gPacket2);
            dBPack = _mm256_mul_ps(bPacket, bPacket);
            prodBPack2 = _mm256_mul_ps(bPacket2, bPacket2);
            dRPack = _mm256_add_ps(dRPack, prodRPack2);
            dGPack = _mm256_add_ps(dGPack, prodGPack2);
            dBPack = _mm256_add_ps(dBPack, prodBPack2);
            dRPack = _mm256_sqrt_ps(dRPack);
            dRPack = _mm256_div_ps(dRPack, r2);
            dGPack = _mm256_sqrt_ps(dGPack);
            dGPack = _mm256_div_ps(dGPack, r2);
            dBPack = _mm256_sqrt_ps(dBPack);
            dBPack = _mm256_div_ps(dBPack, r2);
			
            
            //Guardamos los resultados
            for (int k=0; k<NPIXSIZE; k++){
                pRdest[k] = dRPack[k];
				pGdest[k] =	dGPack[k];
				pBdest[k] = dBPack[k];
            }
		}
        		
	}
	//Medida de tiempo al iniciar
    if(clock_gettime(CLOCK_REALTIME, &tEnd) !=0)
	{
		printf("ERROR: clock_gettime: %d. \n", errno);
		exit(EXIT_FAILURE);
	}
	// Se calcula el tiempo tardado
	dElapsedTimeS = (tEnd.tv_sec - tStart.tv_sec);
	dElapsedTimeS += (tEnd.tv_nsec - tStart.tv_nsec)/1e+9;
	printf("Elapsed time 	: %f s.\n", dElapsedTimeS);	
	// Creamos la nueva imagen
	CImg<data_t> dstImage(pDstImage, width, height, 1, nComp);

	// Guardamos la imagen nueva
	dstImage.save(DESTINATION_IMG); 

	// Enseñamos la imagen nueva (Se ha comentado para no aumentar la duración del programa)
	//dstImage.display();
	
	// Liberamos la memoria
	free(pDstImage);

	return 0;
}
