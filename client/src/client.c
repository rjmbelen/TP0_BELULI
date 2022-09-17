#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	/* ---------------- LOGGING ---------------- */

	t_log* logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Hola! Soy un log\n");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	t_config* config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	char* ip = config_get_string_value(config,"IP");
	char* puerto = config_get_string_value(config,"PUERTO");
	char* valor = config_get_string_value(config,"CLAVE");

	// Loggeamos el valor de config

	log_info(logger,valor);
	log_info(logger,puerto); //agrego esto
	log_info(logger,ip);  //agregue esto

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	int conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);
	if(nuevo_logger==NULL){
		printf("No se pudo crear el logger \n");
		exit(1);
	}
	else{
		return nuevo_logger;
	}
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	if(nuevo_config==NULL){
		printf("No se pudo encontrar la ubicacion/path del config\n");
		exit(1);
	}
	else{
		return nuevo_config;
	}
}

void leer_consola(t_log* logger)
{
	// La primera te la dejo de yapa
	char* leido = readline("> ");

	while(strcmp(leido,"")){ // mientras que sea 1 sigue corriendo
		bool variable = strcmp(leido,""); // te devuelve 0 cuando son = y termina el while
		printf("Mientras sea 1 sigo leyendo de consola: %d \n", variable);
		log_info(logger, leido);
		free(leido);
		leido  = readline("> ");
	}
	free(leido);
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido= readline("> ");
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	while(strcmp(leido,"")){
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		enviar_paquete(paquete, conexion);
		free(leido);
		leido  = readline("> ");
		}
		// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
		free(leido);
		eliminar_paquete(paquete);
}
	


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	if(logger!=NULL){
		log_destroy(logger);
	}
	if(config!=NULL){
		config_destroy(config);
	}

	if(conexion !=NULL){
		liberar_conexion(conexion);
	}

}
