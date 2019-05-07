#ifndef _AVE_H
#define _AVE_H

#include "Animal.h"

using namespace std;

class Ave : public Animal{
protected:
	double m_tamanho_do_bico;
	double m_envergadura_das_asas;
public:
	Ave();
	Ave(int id, string classe, string nome_cientifico, char sexo,
			double tamanho, string dieta, Veterinario* veterinario,
			Tratador* tratador, string nome_batismo, double tamanho_do_bico,
			double envergadura_das_asas);
	~Ave();

	void set_tamanho_do_bico(double tamanho_do_bico);
	void set_envergadura_das_asas(double envergadura_das_asas);
	double get_tamanho_do_bico();
	double get_envergadura_das_asas();
	void write();
};

#endif