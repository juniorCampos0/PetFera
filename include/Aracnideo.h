#ifndef _ARACNIDEO_H_
#define _ARACNIDEO_H_

#include "Animal.h"
#include "date.h"

using namespace std;

class Aracnideo : public Animal {
	protected:
		int m_total_de_mudas;
		string m_tipo_veneno; 
		date m_ultima_muda;
	public:
		Aracnideo();
		Aracnideo(int id, string classe, string nome_cientifico, char sexo, 
				double tamanho, string dieta, Veterinario* veterinario, 
				Tratador* tratador, string nome_batismo, int total_de_mudas, 
				string tipo_veneno, int day, int month, int year);
		~Aracnideo();

		void set_tipo_veneno(string tipo_veneno);
		void set_total_de_mudas(int total_de_mudas);
		void set_ultima_muda(date ultima_muda);
		string get_tipo_veneno();
		int get_total_de_mudas();
		date get_ultima_muda();
		string write();
		string Tipo();
};

#endif