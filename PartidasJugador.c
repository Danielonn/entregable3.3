//Estructura para realizar consultas sobre las partidas que ha realizado un jugador.

#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *connexion;
	int err;
	// Estructura que sirve para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	int PartidasTotales;
	char JugadorConsultado [80];
	strcpy(JugadorConsultado, "Luis");
	
	//Creamos una conexion al servidor MySQL 
	connexion = mysql_init(NULL);
	if (connexion==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(connexion), mysql_error(connexion));
		exit (1);
	}
	
	//Inicializamos la conexión al servidor MySQL
	connexion = mysql_real_connect (connexion, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (connexion==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(connexion), mysql_error(connexion));
		exit (1);
	}
	
	//Creamos un string para poder hacer la consulta a MYSQL con una variable, que es el nombre del jugador buscado
	char ConsultaResultante [80];
	strcpy (ConsultaResultante,"SELECT Participacion.Partida FROM Participacion,Jugador WHERE Jugador.Nombre = '");
	strcat (ConsultaResultante, JugadorConsultado);
	strcat (ConsultaResultante,"' AND Jugador.Identificador = Participacion.Jugador");
	
	//Consulta SQL para obtener una tabla con los datos solicitados de la base de datos
	err=mysql_query (connexion, ConsultaResultante);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(connexion), mysql_error(connexion));
		exit (1);
	}
	
	//Recogemos el resultado de la consulta en una tabla virtual MySQL
	resultado = mysql_store_result (connexion);
	
	//Recogemos el resultado de la primera fila
	row = mysql_fetch_row (resultado);
	
	//Analizamos la primera fila para saber si hemos obtenido resultados con la consulta
	if (row == NULL)
		printf ("No se ha obtenido ningun dato en la consulta\n");
	
	//Si obtenemos resultados, se analiza cada fila hasta llegar a la primera fila con un valor nulo
	else
		while (row !=NULL) {
			
			//Convertimos a int la columna 0, que es la que contiene los puntos de la partida analizada
			PartidasTotales ++;
			
			//Obtenemos la siguiente fila para el siguiente loop
			row = mysql_fetch_row (resultado);
	}
		//Cerrar la conexion con el servidor MySQL 
		mysql_close (connexion);
		
		//Imprimimos en pantalla el resultado deseado, aunque esto se puede modificar para que solamente
		printf("%d\n",PartidasTotales);
		
		exit(0);
}
