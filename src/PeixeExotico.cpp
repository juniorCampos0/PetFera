#include "PeixeExotico.h"

PeixeExotico::PeixeExotico(){

}
PeixeExotico::PeixeExotico(int id, string nome_cientifico, char sexo, 
			double tamanho, string dieta, Veterinario* veterinario, 
			Tratador* tratador, string nome_batismo, string tipo_agua, 
			string autorizacao_ibama, string pais_origem, string cidade_origem):
	Peixe(id, "Gnathostomata", nome_cientifico, sexo, tamanho, dieta, veterinario,
		tratador, nome_batismo, tipo_agua), 
	AnimalExotico(autorizacao_ibama, pais_origem, cidade_origem){

}
PeixeExotico::~PeixeExotico(){

}

void PeixeExotico::set_autorizacao_ibama(string autorizacao_ibama){
	m_autorizacao_ibama = autorizacao_ibama;
};

void PeixeExotico::write(){
	cout<<"Campo;Tipo de Dados;Valores"<<endl;
	cout<<"Identificador Do animal;Inteiro;"<<m_id<<endl;
	cout<<"Classe do animal;Cadeia de caracteres;"<<m_classe<<endl;
	cout<<"Nome científico do animal;Cadeia de caracteres;"<<m_nome_cientifico<<endl;
	cout<<"Sexo do animal;Caractere;"<<m_sexo<<endl;
	cout<<"Tamanho média em métros;Decimal;"<<m_tamanho<<endl;
	cout<<"Dieta redominante;Cadeia de caracteres;"<<m_dieta<<endl;
	cout<<"Veterinário associado;Interio;"<<m_veterinario->get_id()<<endl;
	cout<<"Tratador responsável;Interio;"<<m_tratador->get_id()<<endl;
	cout<<"Nome de batismo;Cadeia de caracteres;"<<m_nome_batismo<<endl;
	cout<<"Tipo de agua;Cadeia de caracteres;"<<m_tipo_agua<<endl;
	cout<<"Autorização do Ibama;Cadeia de caracteres;"<<m_autorizacao_ibama<<endl;
	cout<<"País de origem;Cadeia de caracteres;"<<m_pais_origem<<endl;
	cout<<"Cidade de origem;Cadeia de caracteres;"<<m_cidade_origem<<endl;
};